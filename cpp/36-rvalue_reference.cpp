#include <cstring>
#include <iostream>
using namespace std;

// 1. 右值引用
// 2. 移动语义
// 3. move函数与完美转发

// 1. 右值引用
// 一般地， 等号=左边的为左值locator value, 右边的为右值read value
// C++中，左值为有名字的，可取地址定位的，非临时的变量。反之即为右值
// 右值一般有：常量（1），表达式（a+b），函数的非引用返回值（func()）
// 左值、右值引用都必须立刻初始化，左值是有名字变量的别名，右值是匿名变量的别名
int& returnLValue() {  // 返回一个左值引用
  static int a = 5;
  return a;  // 静态变量不会释放
}
void lValueReference() {
  int a = 1;
  // int& b;  // 引用必须立刻初始化
  int& b = a;  // 初始化

  // int& c = a + 1;    // (a+1)是右值，不可引用
  // int& d = 1;        // 常量是右值，不可引用
  const int& e = 1;  // const修饰左值，常引用左值

  int& f = returnLValue();        // 均为左值引用
  const int& g = returnLValue();  // const int& 为万能引用

  const int h = 10;
  const int& l = h;  // 左值引用
}

int returnRValue() {  // 返回右值
  return 5;
}
void rValueReference() {
  int&& a = 1;  // 右值引用，常量。
  int&& b = returnRValue();

  int&& c = 1 + 2;  // 右值引用表达式。
  // int&& c = a;  // 右值引用不可引用左值
}
void printValue(int& a) {
  cout << "lvalue ref " << a << endl;
}
void printValue(int&& a) {
  cout << "rvalue ref " << a << endl;
}
void valueOverload() {
  int a = 4;
  printValue(a);
  printValue(5);
}

// 2. 返回值优化技术与移动语义
// 右值引用用于实现移动语义，可以将资源（堆、系统资源）从一个对象转移到另一对象中。
// 避免临时对象无意义地创建、析构、拷贝、赋值。移动语义与拷贝语义相对，可以提高程序运行效率。
// 临时对象的资源可以转移到另一对象中
// 移动语义定义：
// 原C++已有拷贝构造和赋值操作符重载，移动语义需新增转移构造函数，和转移赋值操作符
// 对于右值的拷贝和赋值，会调用转移构造函数，和转移赋值操作符
// 普通函数也可以使用右值引用实现移动语义。及时没有系统优化选项，移动语义依然可以减少临时对象的创建、析构
// 移动构造和移动赋值注意：
// 1. 参数均为&&右值，且不带const，因为要修改原对象。
// 2. 参数不能为常量
// 3. 资源转移后，原参数链接和标记必须修改。例如指针要置空，避免浅拷贝产生的问题

class MyString {
 public:
  // 默认有参构造
  MyString(const char* s = "abc") {
    len = strlen(s);
    str = new char[len + 1];
    // strcpy(char* dst, const char* src) 无法保证缓冲区尺寸，不够安全
    // strcpy_s(char* dst, size_t nums, const char* src)
    strcpy_s(str, len + 1, s);
    cout << "有参构造 " << str << endl;
  }

  // 拷贝构造
  MyString(const MyString& s) {
    len = s.len;
    str = new char[len + 1];  // 堆区申请空间，深拷贝。防止重复释放
    strcpy_s(str, len + 1, s.str);
    cout << "拷贝构造 " << str << endl;
  }

  // 移动构造，参数是不带const右值引用，即可不调用拷贝构造，减少临时变量操作
  MyString(MyString&& s) {
    len = s.len;
    str = s.str;  // 浅拷贝，拷贝地址
    s.len = 0;
    s.str = nullptr;  // 原指针置空，防止二次释放同一堆区
    cout << "移动构造 " << str << endl;
  }

  // 运算符=重载
  MyString& operator=(const MyString& s) {
    if (&s == this)
      return *this;
    // 先释放原有内存
    len = 0;
    delete[] str;
    // 重新申请内存
    len = s.len;
    str = new char[len + 1];
    strcpy_s(str, len + 1, s.str);
    cout << "运算符重载 " << str << endl;
    return *this;
  }
  // 移动赋值
  MyString& operator=(MyString&& s) {
    if (&s == this)
      return *this;
    // 先释放原有内存
    len = 0;
    delete[] str;
    // 无需重新申请内存
    len = s.len;
    str = s.str;
    s.len = 0;
    s.str = nullptr;  // 注意原指针置空，避免浅拷贝
    cout << "移动赋值函数 " << str << endl;
    return *this;
  }

  ~MyString() {
    len = 0;
    cout << "析构函数";
    if (str) {
      delete[] str;
      str = nullptr;
      cout << "调用 delete";
    }
    cout << endl;
  }

 private:
  int len = 0;
  char* str = nullptr;
};

// 返回普通函数对象，右值
MyString func(const char* s) {
  MyString obj(s);
  // 打印指针类型时，推荐强制转为无类型指针，避免类似char*
  // s将字符串本身打印出来的问题
  cout << "orignal obj addr:\t" << (void*)&obj << endl;
  return obj;  // 返回的是临时对象的地址，不是obj
}
void normalObj() {
  // 此处系统默认做一次优化，把临时对象直接给了s，故地址相等
  // 如果没优化，再调用一遍构造、析构函数
  MyString s = func("normal obj");
  cout << "normal return obj addr:\t" << (void*)&s << endl;
}
void rValueConstructObj() {
  MyString&& s = func("construct obj");  // 右值引用，调用移动构造函数
  cout << "rvalue construct obj addr:\t" << (void*)&s << endl;
}
void rValueAssignObj() {
  MyString s("origin");    // 实例化对象
  s = func("assign obj");  // 调用赋值运算符重载
  cout << "rvalue assign obj addr:\t" << &s << endl;
}

int main() {
  lValueReference();
  rValueReference();
  valueOverload();
  normalObj();
  rValueConstructObj();
  rValueAssignObj();
  return 0;
}