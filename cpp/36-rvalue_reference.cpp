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
    cout << "析构函数" << endl;
    if (str) {
      delete[] str;
      str = nullptr;
      cout << "析构调用delete" << endl;
    }
  }

 private:
  int len = 0;
  char* str = nullptr;
};

// 返回普通函数对象，右值
MyString func() {
  MyString obj("abcd");
  cout << "orignal obj addr:\t" << &obj << endl;
  return obj;  // 返回的是临时对象的地址，不是obj
}
void normalObj() {
  MyString s = func();
  cout << "returned obj addr:\t" << &s << endl;
}
int main() {
  lValueReference();
  rValueReference();
  valueOverload();
  normalObj();
  return 0;
}