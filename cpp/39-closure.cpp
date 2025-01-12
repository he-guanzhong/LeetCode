#include <functional>
#include <iostream>

using namespace std;
// 闭包
// 1.仿函数。2.bind。3.Lamda
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
void NormFunc(int x, int y) {
  cout << "x = " << x << ", y = " << y << endl;
}

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
  function<int&()> f2 = bind(&ClassFunc::a, &obj);
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

  int memberVar = 2;
};

void LamdaTest() {
  LambdaObj obj;
  obj.func();
}

int main() {
  FunctorTest();
  FunctionTest();
  BindTest();
  FunctionBindTest();
  return 0;
}