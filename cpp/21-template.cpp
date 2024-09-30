#include "21-template.hpp"
#include <iostream>
using namespace std;

// 模板：提高代码利用性。分为函数模板和类模板
template <typename T>  // 声明模板，T为通用数据类型
// 类模板用class ,函数和类都可以用class
void mySwap(T& a, T& b) {
  T tmp = a;
  a = b;
  b = tmp;
}

void templateTest() {
  int a = 10, b = 20;
  mySwap(a, b);
  cout << "a = " << a << "  b = " << b << endl;
  string c = "abc";
  // mySwap(a, c);  // 自动类型推导，必须一致数据类型才能使用
  mySwap<int>(a, b);  // 显式指定类型，推荐使用
  cout << "a = " << a << "  b = " << b << endl;
}

template <class T>  // 之后必须紧跟
void mySort(T arr[], int len) {
  for (int i = 0; i < len; i++) {  // 选择排序
    int max = i;
    for (int j = i + 1; j < len; j++) {
      if (arr[i] < arr[j])
        max = j;
    }
    if (max != i)
      mySwap(arr[i], arr[max]);
  }
}
template <class T>
void printArr(T arr[], int len) {
  for (int i = 0; i < len; i++)
    cout << arr[i] << " ";
  cout << endl;
}

void templateSort() {
  char charArr[] = "badgcfe";
  int len1 = sizeof(charArr) / sizeof(char);
  mySort(charArr, len1);
  printArr(charArr, len1);
  int intArr[] = {2, 3, 6, 9, 20, 4, 37, 90, 11, 27};
  int len2 = sizeof(intArr) / sizeof(int);
  mySort(intArr, len2);
  printArr(intArr, len2);
}

// 普通函数和函数模板区别
// 普通函数可以隐式转换类型，函数模板若自动类型推导，不能隐式转换，若指定类型，可以隐式转换
int myAdd1(int a, int b) {
  return a + b;
}
template <class T>
T myAdd2(T a, T b) {
  return a + b;
}
void templateDifferent() {
  int a = 1, b = 2;
  char c = 'm';  // 普通函数和指定类型的函数模板，可以隐式转换
  cout << "Original: a + b = " << myAdd1(a, b)
       << ", (implicit) a + c = " << myAdd1(a, c) << endl;
  cout << "Template: a + b = " << myAdd2(a, b)
       << ", (implicit) a + c = " << myAdd2<int>(a, c) << endl;
  /*   cout << ", (implicit) a + c = " << myAdd2(a, c) << endl; */  // 不能调用，无法推导出一致类型
}

// 调用规则： 1. 优先调用普通函数。2. 空模板参数列表可以强制调用函数模板。
// 3.函数模板也可以重载。4。 如果函数模板有更好匹配，调用函数模板
void myPrint(int a, int b) {
  cout << "普通函数调用" << endl;
}
template <class T>
void myPrint(T a, T b) {
  cout << "函数模板调用" << endl;
}
template <class T>
void myPrint(T a, T b, T c) {
  cout << "函数模板调用 重载" << endl;
}
void functionCall() {
  int a = 1, b = 2, c = 3;
  char d = 'd', e = 'e';
  myPrint(a, b);     // 优先调用普通函数
  myPrint<>(a, b);   // 空参数强制调用函数模板
  myPrint(a, b, c);  // 函数模板也可以重载
  myPrint(d, e);     // 更适配情况，调用函数模板
}

// 模板局限性：特定情况下需要模板重载
template <class T>
bool myCompare(T a, T b) {
  return a == b;
}
class Person {
 public:
  Person(string name, int age) {
    m_name = name;
    m_age = age;
  }
  string m_name;
  int m_age;
};
template <>
bool myCompare(Person a, Person b) {
  return a.m_age == b.m_age && a.m_name == b.m_name;
}
void templateOverload() {
  int a = 2, b = 2;
  cout << "普通比较 " << myCompare(a, b) << endl;  // 比较时需要具体化Person
  Person p1("张三", 10);
  Person p2("李四", 12);
  cout << "类比较 " << myCompare(p1, p2) << endl;
}

// 类模板。与函数模板声明方式相同。但类模板不能自动推导类型
// 类模板允许有默认参数，函数模板不能
template <class NameType, class AgeType = int>
class Person1 {
 public:
  Person1(NameType name, AgeType age) {
    m_name = name;
    m_age = age;
  }
  void show() { cout << m_name << " " << m_age << endl; }
  NameType m_name;
  AgeType m_age;
};
void templateClass() {
  // Person1 p1("孙悟空", 99);  // 类模板不能自动推导
  Person1<string, int> p1("孙悟空", 99);
  Person1<string> p2("猪八戒", 88);
  p1.show();
  p2.show();
}

// 类模板在调用时才会创建
class Person2 {
 public:
  void showPerson2() { cout << "Person2 调用" << endl; }
};
class Person3 {
 public:
  void showPerson3() { cout << "Person3 调用" << endl; }
};
template <class T>
class myClass {
 public:
  T obj;
  void func2() { obj.showPerson2(); }  // 一开始不会创建，所以不报错
  void func3() { obj.showPerson3(); }
};
void templateClassCreate() {
  myClass<Person2> m;
  m.func2();
  // m.func3(); // 调用func2()已经确定了T为Person2,故此处报错
}

// 类模板可以作为函数参数。
// 1. 指定传入类型。2.参数模板化。3.整个类模板化
void printPerson1(Person1<string, int>& p) {  // 指定传入类型
  p.show();
}
template <class T1, class T2>
void printPerson2(Person1<T1, T2>& p) {  // 参数模板化
  p.show();
  cout << "T1的类型是：" << typeid(T1).name() << endl;
  cout << "T2的类型是：" << typeid(T2).name() << endl;
}
template <class T>
void printPerson3(T& p) {  // 整个类模板化
  p.show();
  cout << "T的类型是：" << typeid(T).name() << endl;
}
void templateAsParam() {
  Person1<string, int> p1("孙悟空", 99);
  printPerson1(p1);
  Person1<string> p2("猪八戒", 88);
  printPerson2(p2);
  Person1<string> p3("沙和尚", 77);
  printPerson3(p3);
}

// 模板与继承。父类为模板，子类继承必须指定类型
// 否则子类也应该写成模板
template <class T>
class Base {
 public:
  T m;
};
class Son1 : public Base<int> {};
template <class T1, class T2>
class Son2 : public Base<T1> {  // 子类也写为模板
 public:
  Son2() {
    cout << "T1类型：" << typeid(T1).name() << endl;
    cout << "T2类型：" << typeid(T2).name() << endl;
  }
  T2 n;
};
void templateInheritance() {
  Son2<int, char> son;
}

// 类模板成员类外实现
template <class T1, class T2>
class Person5 {
 public:
  Person5(T1 name, T2 age);  // 类内声明
  void show();               //
  T1 m_name;
  T2 m_age;
};
template <class T1, class T2>
Person5<T1, T2>::Person5(T1 name, T2 age) {  // 类外定义，必须要加作用域<T1, T2>
  m_name = name;
  m_age = age;
}
template <class T1, class T2>
void Person5<T1, T2>::show() {
  cout << "类模板类外定义 " << m_name << " " << m_age << endl;
}
void templateOutDefi() {
  Person5<string, int> p("Max", 24);
  p.show();
}

// 类模板和友元
template <class T1, class T2>
class Person6 {
  friend void printPerson6_in(Person6<string, int> p) {
    cout << "全局函数类内实现 " << p.m_name << " " << p.m_age << endl;
  }
  friend void printPerson6_out(Person6<string, int> p);

 public:
  Person6(T1 name, T2 age) {
    m_name = name;
    m_age = age;
  }

 private:
  T1 m_name;
  T2 m_age;
};
void printPerson6_out(Person6<string, int> p) {  // 全局函数类外实现
  cout << "全局函数类外实现 " << p.m_name << " " << p.m_age << endl;
}

void templateFriend() {
  Person6<string, int> p("Kimi", 40);
  printPerson6_in(p);
  printPerson6_out(p);
}

// 类模板份文件编写
// 此处不能包含.h头文件，类模板成员函数一开始不创建，使用时才创建，要包含cppc才可以
// 将h和cpp写到一起，为hpp即为类模板，非必须
void templateHpp() {
  Person7<string, int> p("Max", 24);
  p.show();
}

// 模板类案例 数组封装
void printIntArray(MyArray<int>& arr) {
  for (int i = 0; i < arr.getSize(); i++)
    cout << arr[i] << " ";
  cout << endl;
}
void templateArrayInt() {
  MyArray<int> arr1(5);
  cout << "数组一信息：" << endl;
  arr1.pop_back();  // 测试能否弹出
  printIntArray(arr1);
  for (int i = 0; i < arr1.getCapacity(); i++)
    arr1.push_back(i);
  printIntArray(arr1);
  cout << "容量和大小" << arr1.getCapacity() << " " << arr1.getSize() << endl;

  cout << "数组二信息：" << endl;
  MyArray<int> arr2(arr1);  // 测试拷贝函数
  arr2.push_back(7);        // 是否能继续
  arr2.pop_back();
  printIntArray(arr2);
  cout << "容量和大小" << arr2.getCapacity() << " " << arr2.getSize() << endl;

  cout << "数组三信息：" << endl;
  MyArray<int> arr3(10);
  arr3 = arr1;  // =重载
  printIntArray(arr3);
}
void printArrayClass(MyArray<Person7<string, int>>& arr) {
  for (int i = 0; i < arr.getSize(); i++)
    cout << arr[i].m_name << " " << arr[i].m_age << ", ";
  cout << endl;
}
void templateArrayClass() {
  MyArray<Person7<string, int>> arr(10);
  Person7<string, int> p1("孙悟空", 999);
  Person7<string, int> p2("张三", 20);
  Person7<string, int> p3("李四", 30);
  Person7<string, int> p4("星马豪", 10);
  Person7<string, int> p5("柯南", 17);
  arr.push_back(p1);
  arr.push_back(p2);
  arr.push_back(p3);
  arr.push_back(p4);
  arr.push_back(p5);
  printArrayClass(arr);
  cout << "容量和大小" << arr.getCapacity() << " " << arr.getSize() << endl;
}
int main() {
  templateTest();
  templateSort();
  templateDifferent();
  functionCall();
  templateOverload();

  cout << "类模板：" << endl;
  templateClass();
  templateClassCreate();
  templateAsParam();

  cout << "模板与继承：" << endl;
  templateInheritance();
  templateOutDefi();
  templateFriend();
  templateHpp();

  cout << "模板数组：" << endl;
  templateArrayInt();
  templateArrayClass();
  return 0;
}