#include "head.h"
/* 1，继承构造
2，委托构造
3，继承控制：final和override
4，类默认函数的控制：=default和=delete函数 */

// 继承构造
// C++11中允许继承父类的构造函数，但默认构造、拷贝构造、移动构造除外
// 继承构造只能初始化父类参数，子类独有参数不能初始化
// 父类构造函数不能私有，继承不能虚继承。
// 继承构造后，子类不能提供默认构造
class Father {
 public:
  Father(int a, int b) : a_(a), b_(b) {}

 protected:
  int a_;
  int b_;
};
class Son : public Father {
 public:
  using Father::Father;  // 继承构造
  Son(int a, int b) : Father(a, b) {}  // 参数列表给子类传参，C++11默认如此操作
  void show() { cout << "a = " << a_ << ", b = " << b_ << endl; }
  // int c_; // 子类独有参数不能继承初始化
};

void inheritConstruct() {
  Son son(1, 2);
  son.show();
}

// 委托构造。允许多个构造函数，一个构造函数调用另一个构造函数，但必须通过初始化列表
class Delegate {
 public:
  // 被调用函数如果private也可以成功
  Delegate(int x, char y) : a_(x), b_(y) {}
  Delegate() : Delegate(1, 'b') {}
  Delegate(int num) : Delegate(num, 'c') {}
  Delegate(char str) : Delegate(10, str) {}

 public:
  int a_;
  char b_;
};

void delegateConstruct() {
  Delegate dele1;
  cout << "Default: " << dele1.a_ << " " << dele1.b_ << endl;
  Delegate dele2(9);
  cout << "num input: " << dele2.a_ << " " << dele2.b_ << endl;
  Delegate dele3('z');
  cout << "char input: " << dele3.a_ << " " << dele3.b_ << endl;
}

// 继承控制
// final: 阻止进一步子类派生，和虚函数重写
// override: 确保子类虚函数声明和父类相同
class A1 final {
 public:
  int a;
};
// 加了final 的类不能被继承
// class A2 : public A1 {};

// 纯虚函数，加了final不能被重写
class A3 {
 public:
  virtual void func() final = 0;
};
class A4 : public A3 {
 public:
  // void func() {} // 不能重写
};

// 子类override标记的虚函数重写，必须和父类一致，不得遗漏形参，否则会变成重载，编译时报错
class OverrideFather {
 public:
  virtual void func(int a) = 0;
};
class OverrideSon : public OverrideFather {
 public:
  virtual void func(int a) override { cout << "override\n"; }
};

void inheritanceControl() {
  OverrideSon a5;
}

// =default可以让编译器自动生成默认构造函数，比自行手写效率高
// default只能修饰默认构造，拷贝构造，析构，赋值运算符重载（=）这四类函数，不得修饰有参构造和普通函数
// 可以类内声明，类外实现
class DefaultClass {
 public:
  // DefaultClass() {} // 不必手写
  DefaultClass() = default;
  DefaultClass(int a) : m_a(a) {}
  // DefaultClass(int a) = default; 不能修饰带参构造
  // void func() = default; 不能修饰普通函数
  ~DefaultClass() = default;
  int m_a;
};
class A7 {
 public:
  A7();
};
A7::A7() = default;  // default支持类内声明类外实现

// =delete应用于函数声明，可禁用该函数，类似将函数放入private
// 除了以上四类，还可用于带参构造函数，和普通函数
class DeleteClass {
 public:
  DeleteClass() { cout << "DeleteClass construction" << endl; }
  ~DeleteClass() = default;
  DeleteClass(int a) = delete;                   // 禁用带参构造
  DeleteClass(const DeleteClass& obj) = delete;  // 禁用拷贝构造
  DeleteClass& operator=(const DeleteClass& obj) =
      delete;           // 禁用赋值运算符重载
  int func() = delete;  // 禁用普通函数
  // 只在栈区创建对象，禁止堆区创建，禁用new和delete操作
  // 注意new有size_t类型的入参，delete接收无类型指针入参
  void* operator new(size_t t) = delete;
  void* operator new[](size_t t) = delete;
  void operator delete(void* ptr) = delete;
  int m_a;
};

void DefaultDeleteConstruct() {
  DefaultClass a6;
  A7 a7;
  DeleteClass a81;
  // a81.func(); // 禁止调用普通函数
  // DeleteClass a82(a81); // 禁止拷贝构造
  return;
}

int main() {
  inheritConstruct();
  delegateConstruct();
  inheritanceControl();
  DefaultDeleteConstruct();
  return 0;
}