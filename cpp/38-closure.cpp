#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

using namespace std;
// 闭包
// 1.仿函数。2.bind。3.Lambda
// 具有自身变量，也是一个类，必须与状态捆绑

// 1. 仿函数（并非C++11）特性
class MyFunctor {
 public:
  MyFunctor(int a) : ref(a) {}

  // 重载括号，以替代加号
  int operator()(int a) { return ref + a; }
  // 重载括号，以返回比较结果
  bool operator()(int a, int b) { return a > b && b > ref; }

 private:
  int ref;  // class自有变量，即其状态
};

void FunctorTest() {
  MyFunctor func(5);
  cout << "Overload single arg: " << func(10) << endl;
  cout << "Overload double args: " << func(10, 20) << endl;
  cout << "Overload double args: " << func(20, 10) << endl;
}

// 2. function 与 bind应用
// C++中可以调用实体包括：普通函数，函数指针，函数引用，可隐式转换为函数的对象，重载了operator()的对象
// C++11中新增了std::function类模板，是对C++可调用实体的一种类型案例打包，需要加载头文件functional
// 通过制定模板参数，可以统一处理函数、函数对象、函数指针，并允许保存了延迟执行
// function最大作用是实现函数回调，但两个function不可比较相等，但是可以与nullptr和NULL比较
void NormalFunc() {
  // 使用 __func__ 来打印函数名字
  cout << __func__ << endl;
}
class classStaticFunc {
 public:
  static int StaticFunc(int a) {
    cout << __func__ << ", a = " << a << endl;
    return a * 2;
  }
};
class OperatorFunc {
 public:
  double operator()(double a) {
    cout << __func__ << ", a = " << a << endl;
    return a * 3;
  }
};

void FunctionTest() {
  // 创建function对象，与普通函数绑定
  function<void() /*入参没有参数就不写，或void*/> f1 = NormalFunc;
  f1();  // 等价于直接调用NormalFunc();

  // 绑定静态类内函数
  function<int(int)> f2 =
      classStaticFunc::StaticFunc;  // 只有静态函数才能如此调用
  cout << f2(2) << endl;            // 等价于 classStaticFunc::StaticFunc(2)

  // 绑定仿函数，即绑定对象。仿函数本身调用方法是obj()，故对象名相当于函数名
  OperatorFunc obj;
  function<double(double)> f3 = obj;
  cout << f3(2.5) << endl;
}

// bind将可调用实体某些参数绑定到已有变量，产生一个新的可调用实体，回调函数中常用
// C++11中bind参数个数不首先，具体绑定那些参数也不受限，用户指定，非常灵活
void NormFunc(int x, int y) { cout << "x = " << x << ", y = " << y << endl; }

void BindTest() {
  // 将括号后半参数，与函数绑定，相当于NormFunc(1,2)
  bind(NormFunc, 1, 2);  // 1, 2
  // 使用占位符placeholders::_1，将后方括号排序某位的参数绑定
  bind(NormFunc, placeholders::_1, placeholders::_2)(3, 4);  // 3,4
  // 占位符前缀复杂，可以使用命名空间
  using namespace placeholders;
  bind(NormFunc, _1, _2)(5, 6);  // 5,6
  // 灵活使用占位符，不一定从左至右
  bind(NormFunc, 10, _3)(1, 2, 3, 4);  // 10,3
  bind(NormFunc, _2, _1)(1, 2);
}
// function与bind联合使用
class ClassFunc {
 public:
  // 成员函数，非静态
  void func(int x, int y) { cout << x << " " << y << endl; }

  int a;  // 成员变量
};

void FunctionBindTest() {
  // 绑定非静态成员函数，要先创建对象。静态成员函数才不需要创建
  ClassFunc obj;
  // bind 先绑定成员函数，再传给function绑定
  function<void(int, int)> f1 =
      bind(&ClassFunc::func, &obj, placeholders::_1, placeholders::_2);
  f1(1, 2);  // 等价于obj.func(1, 2);

  // 绑定成员变量，其没有入参
  function<int &()> f2 = bind(&ClassFunc::a, &obj);
  f2() = 3;
  cout << "obj.a = " << obj.a << endl;  // 等价于obj.a = 3
}

// 3. lamda函数，用于创建匿名函数，来源于数学中λ演算
// 形式是[]()mutable exeption -> int {}
// []中为捕获列表，标志lambda函数开始，捕获外面参数类型，可以有
/* []空
   没有任何对象，[=]值捕获所有，[&]引用捕获所有，[a]值捕获变量a，[&a]引用捕获变量a
    [this]可以捕获类内和全局变量
    [=, &a, b] a引用传递，b值传递，=其余值传递，注意=一定放在最前面
*/
int globalVar = 1;  // 全局变量
class LambdaObj {
 public:
  void func() {
    // this 指针可以捕获类内变量，和全局变量
    auto f1 = [this]() { cout << globalVar << " " << memberVar << endl; };
    f1();  // f1是函数名，调用时要加括号
    auto f2 = [=]() { cout << globalVar << " " << memberVar << endl; };
    f2();
    auto f3 = [&]() { cout << globalVar << " " << memberVar << endl; };
    f3();
  }
  int memberVar = 2;  // 成员变量
};

void LambdaTest() {
  LambdaObj obj;
  obj.func();

  vector<int> vec{1, 2, 3};
  int &a = vec[0];
  int &b = vec[1];
  int &c = vec[2];
  // a, b以值捕获
  auto f4 = [a, b]() { cout << "heap, a: " << &a << ", b: " << &b << endl; };
  f4();
  // 其余以引用传递，b以值传递，注意&必须在前
  auto f5 = [&, b]() { cout << "a: " << &a << ", &b: " << &b << endl; };
  f5();
  // 其余以值传递，b以引用传递，注意&必须在前
  auto f6 = [=, &b]() { cout << "a: " << &a << ", &b: " << &b << endl; };
  f6();
  // 值传递默认const，需要修改要加 mutable
  auto f7 = [=]() mutable {
    a += 10;
    cout << "a = " << a << endl;
  };
  f7();

  int d = 10, e = 20;
  // 值传递，即使通过mutable修改内部变量，但实质是传入的d新建了一个变量并修改值，不更改真实d值
  auto f8 = [=]() mutable {
    d++;
    cout << "Val pass, Inner d = " << d << ", addr: " << &d << endl;
  };
  f8();
  cout << "Val pass, Outer d = " << d << ", addr: " << &d << endl;
  // 引用传递，不用mutable可直接修改传入的操作地址
  auto f9 = [&]() {
    d++;
    cout << "Ref pass, Inner d = " << d << ", addr: " << &d << endl;
  };
  f9();
  cout << "Ref pass, Outer d = " << d << ", addr: " << &d << endl;
}

// Lambda函数比仿函数实现更简洁。lambda无需定义class和重载operator()
// 事实上仿函数是编译器实现lambda函数的一种方式
void LambdaAndFunctor() {
  // 仿函数
  MyFunctor obj(5);
  cout << "Functor: " << obj(10) << ",\t" << obj(20, 10) << endl;
  cout << "Lambda: ";
  int a = 5;
  auto f1 = [a](int x) { return a + x; };
  auto f2 = [a](int x, int y) { return x > y && y > a; };
  cout << f1(10) << ",\t" << f2(20, 10) << endl;
  return;
}

// lambda函数类型，是闭包对象，而非一个函数指针。
// 允许在不捕获的前提下，将lambda转化为函数指针

void LambdaType() {
  function<void(int)> f1 = [](int a) { cout << "normal a " << a << endl; };
  function<int(int)> f2 = [](int a) {
    cout << "return int, a ";
    return a;
  };
  // bind先绑定lambda表达式，再给f5入参
  function<int(int, int)> f5 = bind([](int a, int b) { return a + b; },
                                    placeholders::_1, placeholders::_2);
  f1(1);
  f2(1);
  cout << f5(1, 2) << endl;

  // 使用auto关键字，要指定返回值类型
  auto f3 = [](int a, int b) -> int { return a - b; };
  // 推断f3的类型，并生成对象f4，将f3赋值给他
  decltype(f3) f4 = f3;
  // 声明一个函数指针，并将lambda转化为函数指针
  int (*ptr)(int, int);
  ptr = f3;
  // 但函数指针不能转化为lambda表达式
  // decltype(f3) f6 = ptr;
  cout << "auto lambda " << f3(5, 3) << endl;
  cout << "decltype " << f4(5, 3) << endl;
  cout << "func ptr " << ptr(5, 3) << endl;
}

// lambda与for_each()配合，不再需要回调函数
vector<int> largeNums;
void PushLargeNums(int &x) {
  if (x > 5) largeNums.push_back(x);
}
void PrintNums(int &x) { cout << x << " "; }
void LambdaForEach() {
  // 传统做法
  vector<int> nums(9);
  for (int i = 0; i < nums.size(); i++) nums[i] = i + 1;
  for_each(nums.begin(), nums.end(), PushLargeNums);
  for_each(largeNums.begin(), largeNums.end(), PrintNums);
  cout << endl;
  // lambda函数做法
  largeNums.clear();
  for_each(nums.begin(), nums.end(), [&](int &x) {
    if (x > 5) largeNums.push_back(x);
  });
  for_each(largeNums.begin(), largeNums.end(),
           [](int &x) { cout << x << " "; });
  cout << endl;
}

// C++11中Lambda形式参数必须有具体类型，但C++14引入泛型Lambda允许使用auto声明型参
auto lambda1 = [](auto x, auto y) { return x + y; };
// 泛型lambda要遵守模板参数推导规则
struct UnnamedLambda {
  template <class T, class U>
  auto operator()(T x, U y) {
    return x + y
  }
};

auto lambda2 = UnnamedLambda{};
// lambda捕获参数使用赋值表达式
auto lambda3 = [value = 1]() { return value; };
// lambda表达式参数可以使用auto
auto lambda4 = [](auto x) { return x; };

int main() {
  FunctorTest();
  FunctionTest();
  BindTest();
  FunctionBindTest();
  LambdaTest();
  LambdaAndFunctor();
  LambdaType();
  LambdaForEach();
  return 0;
}