#include <cmath>
#include <iostream>
using namespace std;
// 使用多态技术，设计制作饮品的抽象类，设计制作咖啡和茶叶的子类；
// 制作饮品流程：煮水，冲泡，倒入杯中，加入辅料；

class BasicDrinking {
 public:
  virtual void Boil() = 0;
  virtual void Brew() = 0;
  virtual void Pour() = 0;
  virtual void PutinSth() = 0;
  virtual void Stir() = 0;
  void makeDrink() {
    Boil();
    Brew();
    Pour();
    PutinSth();
    Stir();
  }
};
class Coffee : public BasicDrinking {
 public:
  void Boil() { cout << "煮咖啡水 "; }
  void Brew() { cout << "冲咖啡 "; }
  void Pour() { cout << "倒咖啡 "; }
  void PutinSth() { cout << "加糖 "; }
  void Stir() { cout << "搅拌咖啡" << endl; }
};
class Tee : public BasicDrinking {
 public:
  void Boil() { cout << "煮茶水 "; }
  void Brew() { cout << "冲茶 "; }
  void Pour() { cout << "倒茶 "; }
  void PutinSth() { cout << "加柠檬 "; }
  void Stir() { cout << "搅拌茶" << endl; }
};
class Midic : public BasicDrinking {
 public:
  void Boil() { cout << "煮药水 "; }
  void Brew() { cout << "冲药 "; }
  void Pour() { cout << "倒药 "; }
  void PutinSth() { cout << " "; }
  void Stir() { cout << "搅拌药" << endl; }
};

void doDrinking(BasicDrinking* p) {  // BasicDrinking* p = new Coffee
  p->makeDrink();
  delete p;  // 释放堆区数据
}

int main() {
  doDrinking(new Coffee);
  doDrinking(new Tee);
  doDrinking(new Midic);
}