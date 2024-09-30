#include <iostream>
using namespace std;

// 继承。面向对象的三大特性。
// 子类（派生类），父类（基类）
// 继承方式：公共、保护、私有

// 普通方法实现网页
class Java {
 public:
  void header() { cout << " head " << endl; }
  void footer() { cout << " footer" << endl; }
  void left() { cout << " left" << endl; }
  void content() { cout << " java content ... " << endl; }
};
class Python {
 public:
  void header() { cout << " head " << endl; }
  void footer() { cout << " footer" << endl; }
  void left() { cout << " left" << endl; }
  void content() { cout << " python content ... " << endl; }
};
class Cpp {
 public:
  void header() { cout << " head " << endl; }
  void footer() { cout << " footer" << endl; }
  void left() { cout << " left" << endl; }
  void content() { cout << " cpp content ... " << endl; }
};
void createPageNormal() {
  Java java;
  java.header();
  java.content();
  Python python;
  python.header();
  python.content();
  Cpp cpp;
  cpp.header();
  cpp.content();
}

// 用继承来实现网页
class BasePage {  // 公共页面
 public:
  void header() { cout << " head public" << endl; }
  void footer() { cout << " footer public" << endl; }
  void left() { cout << " left public" << endl; }
};
class JavaPage : public BasePage {
 public:
  void content() { cout << " java content ... " << endl; }
};
class PythonPage : public BasePage {
 public:
  void content() { cout << " python content ... " << endl; }
};
class CppPage : public BasePage {
 public:
  void content() { cout << " cpp content ... " << endl; }
};
void createPageInheritance() {
  JavaPage java;
  java.header();
  java.content();
  PythonPage python;
  python.header();
  python.content();
  CppPage cpp;
  cpp.header();
  cpp.content();
}

// 继承中的对象模型
class Base {
 public:
  int m_a;

 protected:
  int m_b;

 private:
  int m_c;
};
class SonPub : public Base {
 public:  // 公共继承，继承原有公共、保护、私有属性。
  void func() {
    m_a = 10;
    m_b = 20;
    // m_c = 30;  // 父类私有成员继承了，但被编译器隐藏，不可访问
  }
  int m_dPub;
};
class SonPro : protected Base {
 public:  // 保护继承，原公共成员变为保护，保护和私有属性不变
  void func() {
    m_a = 10;  // 公共->保护成员
    m_b = 20;
    // m_c = 30; // 父类私有成员不可访问
  }
  int n_dPro;
};
class SonPri : private Base {
 public:  // 私有继承，原公共、保护成员变为私有
  void func() {
    m_a = 10;  // 公共->私有
    m_b = 20;  // 保护->私有
    // m_c = 30; // 父类私有成员不可访问
  }
  int m_dPri;
};
void inheritanceMothod() {
  SonPub s1;
  SonPro s2;
  SonPri s3;
  s1.m_a = 100;
  // s1.m_b = 200;  // 保护对象类外不可访问
  // s2.m_a = 100;  // 保护对象类外不可访问
  // s3.m_a = 100;  // 私有对象类外不可访问
  cout << "Son Public size  \t" << sizeof(s1) << endl;
  cout << "Son Protected size\t" << sizeof(s2) << endl;
  cout << "Son Private size\t" << sizeof(s3)
       << endl;  // 16，因为所有成员都被继承了，只是不可访问
}

class Father {
 public:
  Father() {
    cout << "父类构造" << endl;
    m_a = 10;
  }
  ~Father() { cout << "父类析构" << endl; }
  void func() { cout << "父类 func " << endl; }
  void static staticFunc() { cout << "父类 static func " << endl; }

  int m_a;
  static int
      m_b;  // 静态成员变量，编译分配内存，所有对象共享一份数据，类外初始化
};
int Father::m_b = 20;  // 类外初始化
class Son1 : public Father {
 public:
  Son1() {
    cout << "子类构造" << endl;
    m_a = 100;
  }
  ~Son1() { cout << "子类析构" << endl; }
  void func() { cout << "子类 func " << endl; }
  void static staticFunc() { cout << "子类 static func " << endl; }
  int m_a;
  static int m_b;
};
int Son1::m_b = 200;

// C++允许多个继承，但是带来同名成员变量和函数的问题
class Father1 {
 public:
  Father1() { m_a = 10; }
  int m_a;
};
class Father2 {
 public:
  Father2() { m_a = 20, m_b = 30; }
  int m_a, m_b;
};
class Son2 : public Father1, public Father2 {  // 多继承，中间逗号隔开
 public:
  Son2() { m_c = 50; }
  int m_c;
};

void inheritanceMemberProcess() {
  // 构造顺序上，父类构造-子类构造-子类析构-父类析构
  Son1 son;
  // 同名成员变量访问
  cout << "子类的 m_a = " << son.m_a << endl;  // 子类直接访问子类成员
  cout << "父类的 m_a = " << son.Father::m_a
       << endl;  // 子类后加父类作用域访问父类成员

  // 同名函数访问
  son.func();
  son.Father::func();  // 子类后加父类作用域，调用同名函数

  // 同名静态成员变量访问
  cout << "对象访问子类的 m_b = " << son.m_b << endl;  // 子类直接访问子类成员
  cout << "对象访问父类的 m_b = " << son.Father::m_b
       << endl;  // 子类后加父类作用域访问父类成员
  cout << "类名访问子类的 m_b = " << Son1::m_b << endl;  // 类名访问，而非作用域
  cout << "类名访问父类的 m_b = " << Son1::Father::m_b
       << endl;  // Son1是类名，Father是作用域
  son.staticFunc();
  son.Father::staticFunc();
  Son1::staticFunc();
  Son1::Father::staticFunc();

  // C++多个继承
  Son2 son2;
  // cout << "多继承下 m_a = " << son2.m_a << endl; // 同名成员变量，必须定义域
  cout << "多继承Father1 m_a = " << son2.Father1::m_a << endl;
  cout << "多继承Father2 m_a = " << son2.Father2::m_a << endl;
}

// 菱形继承（钻石继承）父类两个子类，一个子类同时继承两个子类
class Animal {
 public:
  int m_age;
};
class Sheep : virtual public Animal {};  // 虚继承
class Camel : virtual public Animal {};
class Alpaca : public Sheep, public Camel {};

void diamondInheritance() {
  Alpaca al;
  al.Sheep::m_age = 3;  // 父类同名成员，作用域区分
  al.Camel::m_age = 5;  // 菱形继承资源浪费，且需要虚继承，虚继承后只有一份数据
  cout << "Sheep age = " << al.Sheep::m_age << endl;
  cout << "Camel age = " << al.Camel::m_age << endl;
  cout << "Alpaca age = " << al.m_age
       << endl;  // 虚继承不明确。若无virtual则此处报错
}
int main() {
  createPageNormal();
  createPageInheritance();
  inheritanceMothod();
  inheritanceMemberProcess();
  diamondInheritance();
  return 0;
}