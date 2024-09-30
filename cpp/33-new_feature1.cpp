#include "head.h"
/* 1，auto的使用
2，decltype的使用
3，追踪函数的返回类型
4，初始化列表和成员
5，基于范围的for循环
6，静态断言
7，noexcept修饰符
8，nullptr的使用
9，强类型枚举
10，常量表达式
11，原生字符串 */

// 1.
// auto关键字。C语言中修饰局部变量、自动变量，在栈区，由程序自动维护。inta等价于auto
// int a; C++11中，auto可以根据用户初始化内容，自动推导类型
double auto_func() {
  return 1.1;
}
struct auto_struct {
  int m_a;
  string m_b;
};
void auto_test_C11() {
  auto b = 1;            // 自动推断为int
  auto c = auto_func();  // 自动推断为double
  auto_struct strct;
  auto d = strct;  // 自动推断为struct
  vector<int> v = {1, 2, 3, 4, 5};
  for (vector<int>::iterator it = v.begin(); it != v.end(); it++) {  // 传统写法
  }
  for (auto it = v.begin(); it != v.end(); it++) {  // 自动推断迭代器
  }
}
// C++14中，auto可以作为函数返回类型的推导
auto auto_test_C14(int i) {
  // 函数实现中含有多个return语句，这些表达式必须可以推断为相同的类型

  // 返回初始化列表，推导也失败。auto不能处理列表
  // return {1, 2, 3};

  // 虚函数，也不能返回值类型推导
  /*   virtual auto func() {
      return 1;
    } */
  // 返回类型推导可以用于递归，但必须至少一个返回语句做向导
  if (i == 1)
    return i;
  else
    return auto_test_C14(i - 1) + 1;
}

void auto_test() {
  // auto使用注意事项：
  /*    1. 定义变量必须初始化
    auto a;  // 没有初始化，无法推到a类型
    a = 10; */

  // 2. VS编译器不支持auto作为形参
  // void func(auto a) {}

  // 3. auto不能作为结构体或类的成员变量
  /*   class A {
     public:
      auto a;       // 成员变量不能为auto
      auto b = 10;  // 初始化也不行
    }; */

  // 4. 不能定义一个auto类型的数组
  // auto arr[] = {1, 2, 3};

  // 5. 模板实例化类型不能是auto
  /*   vector<auto> b;
    vector<auto> c = {1};  */ // 即使初始化了也不行
}

// 2. decltype使用
// decltype类似auto反函数，auto声明一个变量，decltype从一个变量或表达式中得到类型
enum { OK, ERROR } flag;  // 匿名枚举变量
void decltype_test() {
  auto a = 1;
  decltype(a) b;  // 获取a变量类型为int，用这个变量定义b
  cout << typeid(b).name() << endl;       // b变量的类型名字，int
  cout << typeid(b).hash_code() << endl;  // b变量hashcode

  float c = 1.1f;
  double d = 2.2;
  decltype(c + d) e;
  cout << typeid(e).name() << endl;  // e类型是double

  vector<int> tmp = {1, 2, 3};
  decltype(tmp.begin()) it;  // 推断类型是iterator，定义给it
  for (it = tmp.begin(); it != tmp.end(); it++) {
  }
  for (auto it = tmp.begin(); it != tmp.end(); it++) {  // 二者等价
  }

  decltype(flag) flag2;  // decltype获取类型，再定义其余变量
  cout << typeid(flag2).name() << endl;
  cout << typeid(flag2).hash_code() << endl;
}

// 3.追踪函数的返回类型
int trailling_return1(int a, int b) {  // 传统写法
  return a + b;
}
auto trailling_return2(int a, double b) -> int {
  return a + b;
}
auto trailling_return3(int a, double b) -> decltype(a + b) {
  return a + b;
}
// 配合模板使用。T1和T2类型位置，为泛型，所以需要decltype指定类型，auto接收
template <class T1, class T2>
auto multiply(const T1& a, const T2& b) -> decltype(a * b) {
  return a * b;
}
void trailling_test() {
  auto c = trailling_return2(1, 1.2);
  auto d = trailling_return3(1, 1.2);
  cout << "c = " << c << " typeid = " << typeid(c).name() << endl;
  cout << "d = " << d << " typeid = " << typeid(d).name() << endl;
  auto e = multiply(1, 1.2);
  cout << "e = " << e << " typeid = " << typeid(e).name() << endl;
}

// 4. 初始化列表和成员
class A {
 public:
  int m_a;
  int m_b;
  A(int i) {  // 传统构造函数
    m_a = i;
    m_b = 0;
  }
  A() : m_a(1), m_b(2) {}  // 初始化列表，有参构造直接赋值
  A(int i, int j) : m_a(i), m_b(j) {}  // 初始化列表，等价于有参构造
};
class B {
 public:
  int m_a{1};   // 直接赋值初始化，不依赖构造函数
  int m_b = 2;  // 直接赋值初始化
  string m_c{"Tom"};
  A tmp{10, 20};  // 实例化对象时赋值初始化，需要存在有参构造或初始化列表
};

// 列表初始化
struct ListInit {
  int m_a;
  int m_b;
  string m_c;
};
void init_member() {
  B obj;
  cout << obj.m_a << " " << obj.m_b << " " << obj.m_c << " " << obj.tmp.m_a
       << " " << obj.tmp.m_b << endl;

  int a1 = 10;                   // 传统初始化
  int a2 = {100};                // 列表初始化
  int a3{100};                   // 列表初始化
  int arr1[] = {1, 2, 3};        // 传统写法
  int arr2[]{1, 2, 3};           // 列表初始化
  vector<int> arr3{1, 2, 3};     // 列表初始化
  ListInit t = {1, 2, "Jerry"};  // 使用{}方式为列表初始化

  // 列表初始化防止类型收窄
  // 数据类型变化或数据精度丢失的隐式类型转换。列表初始化可防止
  const int a = 1024;
  /*    char b = a;  // 可编译，但是数据会丢失
     cout << b << endl;  // C++无法打印，需要C语言
    printf("%d\n", b);  // 输出0，数据丢失
     char c = {a};  // 列表初始化不会收窄，直接报类型转换错误 */
}

// 5. 基于范围的for循环
template <typename T>
void printArray(T& a) {
  for (auto i : a)
    cout << i << " ";
  cout << endl;
}
void range_variable() {
  int arr[]{1, 2, 3, 4, 5};  // 列表初始化
  int len = sizeof(arr) / sizeof(arr[0]);
  for (int i = 0; i < len; i++) {  // 传统写法
    int temp = arr[i];
    temp *= 2;
  }
  for (auto i : arr)  // 等价于上述写法
    i *= 2;
  printArray(arr);  // 只改变了形参

  for (int i = 0; i < len; i++) {  // 传统写法
    int& temp = arr[i];
    temp *= 2;
  }
  for (auto& i : arr)  // 引用，可以修改实参
    i *= 2;
  printArray(arr);  // 只改变了形参
}

// 6. 静态断言
#include <cassert>  //静态断言头文件
void assert_test() {
  // 断言是C++提供的一种调试工具，宏，运行时对断言检查。如果内在条件为真，则执行后序语句，否则调用abort()报错
  bool flag = true;
  assert(flag);  // 断言，为真时执行后序语句
  cout << "C++ assert activated " << endl;
  // C++11提供静态断言，在编译过程中就及时报错，故条件中只能为常量
  static_assert(sizeof(void*) == 8, "64位系统");  // 指针占8位，64位系统
  // static_assert(sizeof(void*) == 4, "32位系统");
  cout << "C++11 assert activated" << endl;
}

// 7. noexcept修饰符
// C++11使用noexcept提到throw()，修饰不可抛出异常
void throw1() {
  throw 1;
}
void throw2() throw() {  // 不可抛出异常，C++已不用
  throw 2;
}
void throw3() noexcept {  // 不可抛出任何异常
  throw 3;
}
void noexcept_test() {
  throw1();
  throw2();
  throw3();
}

// 8. nullptr空指针
// 为了解决之前空指针NULL和0的二义性。C++11引入了nullptr作为单纯的空指针
void null_print(int a) {
  cout << __LINE__ << endl;  // 打印行数
}
void null_print(int* a) {
  cout << __LINE__ << endl;
}
void nullptr_test() {
  int* p1 = NULL;
  int* p2 = 0;
  int* p3 = nullptr;
  // null_print(NULL); // 还是调用值传递的函数
  null_print(0);  // 调用值传递的函数，C++11版本无歧义。以前版本有歧义
  null_print(nullptr);  // 调用指针传递的函数
  null_print(p1);
  null_print(p2);
  null_print(p3);
  // int a = NULL; // C++11已经不能把NULL作为0的值，赋值给int
  //  int b = nullptr;
  if (p1 == p3)
    cout << "NULL equals to nullptr" << endl;
}

// 9. 强类型枚举
// 传统枚举，即使枚举名不同，但如果变量相同，也判定为重定义报错
// enum Status1 { OK, ERROR };
// enum Status2 { OK, ERROR };
// 强类型枚举，enum之后加class
// 或者struct，可规避此问题，同时还可以指定变量类型，初始化赋值
enum class Status3 : char { OK = 3, ERROR = 4 };
enum struct Status4 : long long { OK = 100, ERROR = 101 };
enum struct Status5 { OK, ERROR };

void strong_enum() {
  // Status1 status1 = Status1::ERROR;
  // Status2 status2 = Status2::ERROR;
  Status3 status3 = Status3::ERROR;
  Status4 status4 = Status4::ERROR;
  Status5 status5 = Status5::ERROR;

  printf("%d %d %d\n", status3, status4, status5);  // 不能用cout打印
  cout << "3 size: " << sizeof(status3) << "\t4 size: " << sizeof(status4)
       << "\t5 size: " << sizeof(status5) << endl;
}

// 10. 常量表达式
// 一些运算在编译时就运行过，如此在程序运行时就不用反复运行，提高效率
int getNum1() {
  return 3;
}
const int getNum2() {
  return 3;
}
constexpr int getNum3() {
  return 3;
}
enum class NumsOut {
  // num1 = getNum1(), 枚举成员初始化，必须是整型常量
  // num1 = getNum2(), 即使const修饰，也不行
  num1 = getNum3(),  // 常量表达式，在编译阶段执行，运行时就不执行了
  num2
};
void constexpr_test() {
  const int tmp1 = getNum3();      // 常量
  constexpr int tmp2 = getNum3();  // 常量
  enum class NumsIn {
    // num1 = getNum1(), 函数中的枚举，也必须为常量
    num1 = tmp1,
    num2 = tmp2  // 赋值的tmp必须是constexpr或者const修饰的常量
  };

  printf("%d %d\n", NumsOut::num2, NumsIn::num2);
}
/* constexpr函数限制
1.函数只能一个return语句，但C++14大幅放松
2.函数必须有返回值，不能为void
3.使用前必须已有定义
4.return表达式中，不能使用非常量表达式、全局变量，必须是一个常量表达式，或者常量
 */
constexpr int func1() {
  static_assert(1, "fail");  // 允许使用静态断言，typedef, using
  constexpr int a = 1;
  return a;  // 新编译器可以
}
int a_global = 2;  // 全局变量
constexpr int func2() {
  // return a_global;  // 新编译器可以
  return 2;
}
constexpr int func3() {
  // return getNum1();  // 不行，因为getNum1运行时才调用
  return getNum3();  // 可以，因为也是编译时调用的
}
void constexpr_test2() {
  int m_a = func1();
  int m_b = func2();
  int m_c = func3();
  cout << m_a << " " << m_b << " " << m_c << endl;
}
// 类函数成员是常量表达式
class Date {
 public:
  // constexpr修饰构造函数，构造函数体内必须为空，但是可以通过初始化列表的方式初始化
  constexpr Date(int y, int m, int d) : year(y), month(m), day(d) {}
  /*   constexpr Date(int y, int m, int d) {
      year = y;
      month = m;
      day = d;
    } */
  // constexpr int getYear() 会报错
  // 对外接口，加上expr会提示不兼容，需要使用常函数
  int getYear() const { return year; }
  int getMonth() const { return month; }
  int getDay() const { return day; }

 private:
  int year;
  int month;
  int day;
};

// C++14支持变量模板
template <class T>
constexpr T pi = T(3.1415926535L);
void constexpr_test3() {
  // 必须使用常量或者常量表达式给构造函数传参
  constexpr Date date(2023, 11, 2);
  cout << date.getYear() << " " << date.getMonth() << " " << date.getDay()
       << endl;
  cout << pi<int> << " " << pi<double> << endl;
}

// 11. 原生字符串。
//  原生字符串使用户所见即所得，保留用户格式输出，格式R"()"
void raw_string() {
  cout << R"(raw string\n)" << endl;
  cout << R"(raw \t
              string \0)"
       << endl;
}
int main() {
  decltype_test();
  trailling_test();
  init_member();
  range_variable();
  assert_test();
  // noexcept_test();
  nullptr_test();
  strong_enum();
  constexpr_test();
  constexpr_test2();
  constexpr_test3();
  raw_string();
  return 0;
}
