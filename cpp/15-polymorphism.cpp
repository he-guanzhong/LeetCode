#include <iostream>
using namespace std;
// 多态是面向对象的三大特性。要求：1.有继承关系；2.子类重写父类虚函数; 3.父类指针或引用指向子类对象
// 静态多态：编译时确定函数地址，函数重载，运算符重载
// 动态多态：运行时才确定函数地址。派生类和虚函数实现多态

class Animal {
 public:
  virtual void speak() {
    cout << "动物说话" << endl;
  }  // 虚函数，函数地址碗绑定
};
class Cat : public Animal {
 public:
  void speak() { cout << "猫说话" << endl; }  // 函数重写，子类virtual可加可不加
};
class Dog : public Animal {
 public:
  void speak() { cout << "狗说话" << endl; }
};
void doSpeak(Animal& animal) {  // 父类的引用可以直接指向子类对象
  animal.speak();  // 之前地址早绑定，编辑阶段确定。virtual后运行阶段才绑定
}
void polymorphism() {
  Cat cat;
  Dog dog;
  doSpeak(cat);
  doSpeak(dog);
}

// 纯虚函数和抽象类
// 父类虚函数无实际作用的，可以写为纯虚函数：virtual 返回值 函数名（参数列表）=0
// 含有纯虚函数的为抽象类，不可实例化对象，且子类必须重写抽象类中纯虚函数，否则子类也为抽象类
class Base {
 public:
  virtual void func() = 0;  // 纯虚函数，无{}
};
class Son : public Base {
 public:
  virtual void func() { cout << "func()调用" << endl; }
};

void pureVirtualFunc() {
  // Base s; // 抽象类不能实例化对象
  //  Base* p = new Base; // 堆区也不能实例化抽象类对象
  Son s;
  Base* p = new Son;  // 父类指针指向子类对象，就可以多态了
  p->func();
  delete p;  // 必须手动释放
}

// 虚析构和纯虚析构
// 子类若有属性开辟到堆区，父类指针无法调用子类析构函数，需将父类析构函数写为虚函数
// 虚析构和纯虚析构共性：1.都可以释放子类堆区空间；2.都需要具体函数实现
// 虚析构和纯虚析构区别：纯虚析构适用于抽象类，无法实例化对象
// 子类中没有堆区数据，可以不写虚析构
class Mammal {
 public:
  Mammal() { cout << "Mammal 构造" << endl; }
  // virtual ~Mammal() { cout << "Mammal 虚析构" << endl; }
  // virtual void speak() {}
  virtual ~Mammal() = 0;     // 纯虚析构函数
  virtual void speak() = 0;  // 纯虚函数
};
Mammal::~Mammal() {  // 纯虚析构一定要有具体的实现函数
  cout << "Mammal 纯虚析构" << endl;
}
class Lion : public Mammal {
 public:
  Lion(string s) {
    cout << "lion 构造" << endl;
    m_Name = new string(s);  // 开辟到堆区
  }
  ~Lion() {  // 父类必须虚析构，子类虚构才能调用
    cout << "lion 析构" << endl;
    delete m_Name;
    m_Name = nullptr;
  }
  void speak() { cout << *m_Name << "在叫" << endl; }
  string* m_Name;
};

void pureDestruction() {
  Mammal* p = new Lion("Simba");
  p->speak();
  delete p;
  p = nullptr;
}

int main() {
  polymorphism();
  pureVirtualFunc();
  pureDestruction();
  return 0;
}