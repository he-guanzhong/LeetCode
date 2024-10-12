#include <iostream>
using namespace std;

// 1.右尖括号>改进。
// C++11标准要求下，编译器可以自动识别>>为右移符号，还是模板嵌套模板，模板参数表结束的标记。无需人工中间空一格>>
template <int i>
class T1 {};

template <class T>
class T2 {};

void RightAngleBracket() {
  T2<T1<8>> t1;  // 无需T2<T2<8> >
}

// 2.模板的别名，不同于传统typedef，C++11可以使用using ..=..为模板创建别名
typedef int trad_int32;
using alias_int32 = int;

void TemplateAlias() {
  // is_same<>模板位于<type_traits>中，类型不同is_same<T,U>继承于false_type。
  // 类型相同is_same<T,T>继承与true_type，取其value值，相同即返回1
  cout << is_same<trad_int32, alias_int32>::value << endl;
  // typeid()是操作符，不是函数。操作对象可以是类型或者变量，使用.name()输出其名称
  cout << typeid(trad_int32).name() << endl;
  cout << typeid(alias_int32).name() << endl;
}

// 3.函数模板的默认模板参数
// 普通函数带默认参数取值
void NormalFunc(int a = 3) {
  cout << a << endl;
}
// 类模板的默认模板参数
template <class T = int>
class DefaultClass1 {
  T a;
};
// 函数模板的默认模板参数
template <class T = int>
void DefaultFunc(T a) {
  cout << a << endl;
}
// 类模板默认模板参数默认从右向左定义。可以两侧都定义，或都不定义
template <class T1 = int, class T2 = double>
class DefaultClass2 {
  T1 a;
  T2 b;
};
// 左边第一个定义类型，而右边不定义模板参数。不支持。
// 报错 no default argument for T2。即对T2没有默认的实参
/* template <class T1 = int, class T2>
class DefaultClass3 {
  T1 a;
  T2 b;
}; */
// 右侧第一个参数定义默认模板参数，左边不定义。支持
template <class T1, class T2 = double>
class DefaultClass4 {
  T1 a;
  T2 b;
};
// 函数模板的默认模板参数，可以两个都带或都不带
// 左右是否明确给出默认模板参数，均支持
template <class T1 = int, class T2>
void DefaultFunc2(T1 a, T2 b) {
  cout << a << b << endl;
}
template <class T1, class T2 = double>
void DefaultFunc3(T1 a, T2 b) {
  cout << a << b << endl;
}

void DefaultTemplateParam() {
  NormalFunc();
  DefaultFunc(2);
  // DefaultClass3<int, float> defClass3;
  DefaultClass4<int> defClass4;
  DefaultFunc2(1, "a");
  DefaultFunc3("cd", 2.5);
}

// 4.可变参数模板，C++11新特性，对模板高度泛化
// 函数模板可变参数 在class和T中加 ... 表示未知个数，T为模板参数包，可传多个参数
template <class... T>
void VariableFunc(T... a) {
  // a为函数参数包，可以接收多个参数
  // sizeof打印传入参数的个数
  cout << "arg num =  " << sizeof...(a) << endl;
}

void VariableParamTemplate() {
  VariableFunc(1);
  VariableFunc<int, double, char>(2, 3.0, 'a');  // 同时传多个类型参数
  VariableFunc(4, 5.0, 'b', "de");               // 隐式类型推导
}

// 递归展开模板参数包
// 递归终止函数，当参数包内无数据时终止
void Debug() {
  cout << "empty" << endl;
}
// 可选地，递归在仅剩一个参数时终止
/* template <class T>
void Debug(T t) {
  cout << "last = " << t << " ";
} */
template <class T1, class... T2>
void Debug(T1 t1, T2... t2) {
  cout << t1 << " ";
  Debug(t2...);  // t2...每调用一次减少一个数据，直至为空，调用终止函数
}

void TraversalTerminateTemplate() {
  cout << "Traversal Terminate Template:" << endl;
  Debug(1, 2, 3, 4);          // 递归进入
  Debug(1, 'a', 3.0, "Tom");  // 可以使用不同类型
}

// 非递归展开模板参数包
template <class T>
void print(T t) {
  cout << t << " ";
}
template <class... T>
void expand(T... t) {
  int a[] = {(print(t), 0)...};
  cout << endl;
}
void NonTraversalExpandTemplate() {
  cout << "NonTraversal Terminate Template:" << endl;
  expand(1, 2, 3, 4);
  expand(1, 'a', 3.0, "Tom");
}

// 继承方式展开模板参数包
// 必须提前声明
template <class... T>
class Car {};
// 递归终止函数
template <>
class Car<> {
 public:
  Car() { cout << "end" << endl; }
};
template <class head, class... tail>
class Car<head, tail...> : public Car<tail...> {
 public:
  Car() { cout << typeid(head).name() << " "; }
};

void InheritExpandTemplate() {
  cout << "Inherit Expand Template:" << endl;
  Car<int, float, double, char> cars;
  cout << endl;
}

// 模板类递归与特化方式展开参数包
// 1. 模板类提前声明
template <int... i>
class Test {};
// 2. 终止递归函数
template <>
class Test<> {
 public:
  static const int val = 1;
  static const int sum = 0;
};
// 3. 边长模板类定义
template <int first, int... nums>
class Test<first, nums...> {
 public:
  static const int val = first * Test<nums...>::val;
  static const int sum = first + Test<nums...>::sum;
};
void SpecialExpandTemplate() {
  cout << "val: " << Test<1, 2, 3, 4>::val << endl;
  cout << "sum: " << Test<1, 2, 3, 4>::sum << endl;
}

// 变参模板的应用
// 1.打印。递归终止函数
void printX() {
  cout << endl;
}
template <class T, class... Types>
void printX(const T& arg, const Types&... args) {
  cout << arg << " ";
  printX(args...);
}

// 2. max函数。
int maxinum(int n) {
  return n;
}
template <class... T>
int maxinum(int n, T... args) {
  return max(n, maxinum(args...));
}

// 3. sum函数
template <class T>
int summary(T n) {
  return n;
}
template <class T1, class... T2>
int summary(T1 n, T2... args) {
  return n + summary(args...);
}
void ApplicationTemplate() {
  printX(1, 'c', 3.1, "Jerry");
  cout << "MaxVal: " << maxinum(1, 2, 3.1, 4) << endl;
  cout << "Summary: " << summary(1, 2, 3.1, 4) << endl;
}

// C++14支持别名模板
template <class U, class T>
struct OriginalTemplate {
  U u;
  T t;
};
template <class T>
using Alias = OriginalTemplate<int, T>;

int main() {
  RightAngleBracket();
  TemplateAlias();
  DefaultTemplateParam();
  VariableParamTemplate();
  TraversalTerminateTemplate();
  NonTraversalExpandTemplate();
  InheritExpandTemplate();
  SpecialExpandTemplate();
  ApplicationTemplate();
  return 0;
}