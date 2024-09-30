#include <iostream>
using namespace std;
// 面向对象的编程
// 内存管理分为，代码区，全局/静态存储区、堆区、栈区
// 代码区：运行前就存在，保存CPU执行机器指令，只读性、共享的
// 全局区：运行前就存在，保存全局变量、静态变量、常量，程序结束时自动释放
// 堆区：  程序员主动申请、释放。
// 栈区：  编译器自动申请、释放。存放函数参数值、局部变量

int b = 20;        // 全局变量
const int d = 40;  // 全局常量
int* func0() {
  int* p = new int(10);  // 数据开辟到堆区, malloc()
  return p;  // 指针为局部变量，在栈区，保存的数据在堆区
}
void heap_test1() {
  int* p = func0();
  cout << *p << endl;
  delete p;  // delete释放堆区数据，free()
}
void heap_test2() {
  int* arr = new int[10];  // 堆区创建数组
  for (int i = 0; i < 10; i++) {
    arr[i] = i + 10;
    cout << arr[i] << " ";
  }
  cout << endl;
  delete[] arr;  // 释放数组要[]
}

// 引用。给变量起别名，必须初始化，初始化后不能更改，让形参修饰实参，简化指针。
// 引用本质是C++内部实现的指针常量
void swap1(int a, int b) {  // 值传递，实参改变
  swap(a, b);
}
void swap2(int* a, int* b) {  // 地址传递，实参改变
  swap(*a, *b);
}
void swap3(int& a, int& b) {  // 引用传递，实参改变
  swap(a, b);
}
/* int& return1() {  // 不能返回局部变量的引用
  int a = 10;
  return a;
} */
int& return2() {  // 可以返回静态变量的引用
  static int a = 10;
  return a;
}
void showValue(const int& val) {  // const修饰常量引用，不能修改实参
  cout << "show value " << val << endl;
  // val = 10;
}

// 函数默认参数
// 如果某位置有默认值，那之后都要有默认值，声明和实现只有一个能有默认参数
void func1(int a, int b = 20, int c = 30) {
  cout << "默认参数：" << a + b + c << endl;
}
void func2(int a, int) {
  cout << "占位参数：" << a << endl;
}
void func3(int a, int = 20) {
  cout << "占位默认参数：" << a << endl;
}

// 函数重载：1.同一作用域。2.函数名相同。3.参数类型、数量、顺序不同
void func() {
  cout << "func " << endl;
}
void func(int a) {
  cout << "func(int a)" << endl;
}
void func(double a) {
  cout << "func(double a)" << endl;
}
void func(int a, double b) {
  cout << "func(int a, double b)" << endl;
}
void func(double a, int b) {
  cout << "func(double a, int b)" << endl;
}
/* int func(double a, int b) {  // 返回值不同不能作为重载条件
  cout << "func(double a, int b)" << endl;
  return 0;
} */
void function(int& a) {
  cout << "func(int& a)" << endl;
}
void function(const int& a) {  // 加const可以重载
  cout << "func(const int& a)" << endl;
}
void function1(int a) {  // 加默认参数可以重载，尽量避免
  cout << "func(int a)" << endl;
}
void function1(int a, int b = 10) {  // 加默认参数可以重载，尽量避免
  cout << "func(int a, int b = 10)" << endl;
}

int main() {
  // 内存分区模型
  int a = 10;  // 局部变量
  cout << "局部变量 " << &a << " 全局变量 " << &b << endl;
  const int c = 10;  // 局部常量
  cout << "局部常量 " << &c << " 全局常量 " << &d << endl;
  static int e = 50;  // 静态变量
  cout << "静态变量 " << &e << " 常量 " << &"50" << endl;
  int* q = func0();
  cout << *q << " " << *q << endl;
  delete q;
  heap_test1();
  heap_test2();

  // 引用
  int x = 10;
  int& y = x;  // 自动转化为指针常量 int* const y =
               // &x，指向不能更改，所以引用不能更改
  cout << "x = " << x << "  y = " << y << endl;
  y = 20;  // 自动转化为 *y = 20, 解引用
  cout << "x = " << x << "  y = " << y << endl;
  int m = 4, n = 6;
  swap1(m, n);
  cout << "值传递  m = " << m << "  n = " << n << endl;
  swap2(&m, &n);
  cout << "地址传递 m = " << m << "  n = " << n << endl;
  swap3(m, n);
  cout << "引用传递 m = " << m << "  n = " << n << endl;
  /*   int& ref1 = return1();
    cout << ref1 << endl; */
  int& ref2 = return2();  // 函数返回值为引用
  cout << ref2 << endl;
  return2() = 1000;  // 函数返回值为引用，函数调用可以作为左值
  cout << ref2 << endl;
  int z = 30;  // 常量引用，修饰形参，防止误操作
  int& ref3 = z;
  // int& ref4 = 30; 引用必须引用合法内存空间，不能引用常量区
  const int& ref4 =
      30;  // const之后，编译器处理为 int temp = 30; int& ref4 = temp
  showValue(z);

  // 函数默认参数
  func1(10);
  func2(10, 20);
  func3(10);

  // 函数的重载
  func();
  func(1);
  func(3.14);
  func(1, 3.14);
  func(3.14, 1);
  int val = 10;
  function(val);  // 变量，不加const
  function(10);   // 常量，加const，func(int a) == func(const int& a)
  // function1(10);  // 不能只调一个参数，尽量避免
  function1(10, 20);

  return 0;
}