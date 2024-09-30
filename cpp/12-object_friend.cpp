#include <iostream>
using namespace std;
// 友元函数，让一个函数或类访问 另一个类中的私有成员
// 友元声明一定要在 友元本身之后，否则报错
// 函数一定要写在类外，否则报错。
class Building;  // goodguy 引用了 building，故提前声明
class GoodGuy {  // 创建友好类，其内函数只写声明，类外写成员函数定义
 public:
  GoodGuy();
  void visit();
  void sleep();

  Building* home;
};
class Building {
 public:
  friend void goodGuy(
      Building& home);  // 全局友元函数，此处需要声明，即可访问私有成员
  // friend class GoodGuy;          // 类做友元
  friend void GoodGuy::sleep();  // 成员函数做友元
  string m_sittingroom;
  Building();

 private:
  string m_bedroom;
};
Building::Building() {  // 类外实现构造函数
  m_bedroom = "卧室";
  m_sittingroom = "客厅";
}

// 1. 全局函数做友元
void goodGuy(Building& home) {
  cout << "全局友元访问 " << home.m_sittingroom << endl;
  cout << "全局友元访问 " << home.m_bedroom << endl;
}
void global_func_friend() {
  Building home;
  goodGuy(home);
}

// 2. 类做友元
GoodGuy::GoodGuy() {
  home = new Building;  // 堆区创建一个building对象
}
void GoodGuy::visit() {
  cout << "类友元，成员" << home->m_sittingroom << endl;
  // cout << "类友元，成员" << home->m_bedroom << endl;  // 类友元才可实现
}
// 3. 成员函数做友元
void GoodGuy::sleep() {
  cout << "成员函数友元" << home->m_bedroom << endl;  // 成员友元和类友元均可
}

void member_func_friend() {
  GoodGuy g;
  g.visit();
  g.sleep();
}

int main() {
  global_func_friend();
  member_func_friend();
  return 0;
}