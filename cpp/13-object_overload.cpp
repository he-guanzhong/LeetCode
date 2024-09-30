#include <iostream>
using namespace std;

// 运算符重载
// 成员函数重载+
class Person1 {
 public:
  Person1() {}
  Person1(int a, int b) : m_a(a), m_b(b) {}
  ~Person1() {}
  /*   Person1 operator+(Person1& p) {
      Person1 temp;
      temp.m_a = this->m_a + p.m_a;
      temp.m_b = this->m_b + p.m_b;
      return temp;
    } */
  // void operator<<(cout) {} //
  // 一般不用成员函数重载cout，因为cout不能出现等号左边 P1<<cout

 public:  // 此处不能private
  int m_a;
  int m_b;
};

// 全局函数重载+，运算符重载也可以
Person1 operator+(Person1& p1, Person1& p2) {
  Person1 temp;
  temp.m_a = p1.m_a + p2.m_a;
  temp.m_b = p1.m_b + p2.m_b;
  return temp;
}
Person1 operator+(Person1& p1, int num) {
  Person1 temp;
  temp.m_a = p1.m_a + num;
  temp.m_b = p1.m_b + num;
  return temp;
}

// 左移运算符全局重载<<
ostream& operator<<(ostream& out, Person1& p) {
  out << "p.m_a = " << p.m_a << ","
      << "  p.m_b = " << p.m_b << endl;
  return out;
}
void test_basic() {
  Person1 p1(10, 15);
  cout << " << overload test:" << p1 << endl;
  Person1 p2 = Person1(20, 30);
  // 全局函数重载本质 p3 = operator+(p1, p2)
  // 局部函数重载本质 p3 = p1.operator+(p2)
  Person1 p3 = p1 + p2;  // 全局函数重载
  cout << "global+ test:" << p3 << endl;
  Person1 p4 = p1 + 100;  // 函数重载
  cout << "global+ test:" << p4 << endl;
}

// 递增运算符重载
class myInt {
 public:
  friend ostream& operator<<(ostream& out, myInt i);  // 友元函数访问私有值
  myInt() { m_num = 0; }  // 构造函数初始化值
  myInt& operator++() {  // 重载前置++，要返回引用，否则会返回拷贝的新对象
    m_num++;
    return *this;  // 非静态成员函数，返回对象本身
  }
  myInt operator++(int) {  // 重载后置++，(int)占位参数代表后置，不能返回引用
    myInt temp = *this;
    m_num++;
    return temp;
  }

 private:
  int m_num = 0;
};
ostream& operator<<(ostream& out, myInt i) {
  out << i.m_num;
  return out;
}
void test_increment() {
  myInt new_int;
  cout << "origin: " << new_int << ", ";
  cout << "++i: " << ++new_int << ", ";
  cout << "++++i: " << ++(++new_int) << ", ";
  cout << "i++ before: " << new_int++ << ", ";
  cout << "i++ after: " << new_int << endl;
}

// 赋值运算符重载
// C++编译器默认四个函数，构造函数、析构函数、拷贝构造函数（浅）、赋值运算符
// 若类中有属性指向堆区，则易出现深浅拷贝问题
class Person2 {
 public:
  Person2(int age) { m_age = new int(age); }
  ~Person2() {
    if (m_age != NULL)
      delete m_age;
    m_age = NULL;
  }
  Person2& operator=(Person2& p) {  // 返回自身，可链式编程
    // 编译器默认 m_age = p.m_age 浅拷贝
    // 必须先判断是否有属性在堆区，如有，应释放干净再浅拷贝
    if (this->m_age != NULL)
      delete m_age;
    m_age = NULL;
    this->m_age = new int(*p.m_age);
    return *this;
  }
  int* m_age;
};

void test_assignment() {
  Person2 p1(10);
  Person2 p2(20);
  Person2 p3(30);
  p2 = p1;
  p3 = p2 = p1;
  cout << "Age p1: " << *(p1.m_age) << "  p2: " << *(p2.m_age)
       << "  p3: " << *(p3.m_age) << endl;
  cout << "Addr p1: " << (p1.m_age) << "  p2: " << (p2.m_age)
       << "  p3: " << (p3.m_age) << endl;
}

// 关系运算符重载 == != > <
class Person3 {
 public:
  Person3(string name, int age) {
    m_name = name;
    m_age = age;
  }
  bool operator==(Person3& p) {
    return (this->m_age == p.m_age && this->m_name == p.m_name) ? true : false;
  }
  bool operator!=(Person3& p) {
    return (this->m_age == p.m_age && this->m_name == p.m_name) ? false : true;
  }
  bool operator<(Person3& p) { return (this->m_age < p.m_age) ? true : false; }
  bool operator>(Person3& p) { return (this->m_age > p.m_age) ? true : false; }

  string m_name;
  int m_age;
};

void test_relation() {
  Person3 p1("张三", 13);
  Person3 p2("李四", 15);
  Person3 p3("张三", 13);
  cout << "p1 == p2 ? " << (p1 == p2) << "  p1 == p3 ?" << (p1 == p3) << endl;
  cout << "p1 > p2 ? " << (p1 > p2) << "  p1 < p2 ?" << (p1 < p2) << endl;
}

// 函数调用运算符重载()，也叫仿函数
class MyPrint {
 public:  // class默认访问权限是private
  void operator()(string str) { cout << str << endl; }
};
class MyAdd {
 public:
  int operator()(int num1, int num2) { return num1 + num2; }
};

void test_functor() {
  MyPrint myprint;
  myprint("overload print functor");
  MyAdd myadd;
  cout << "myadd res: " << myadd(3, 5) << endl;
}
int main() {
  test_basic();
  test_increment();
  test_assignment();
  test_relation();
  test_functor();
  return 0;
}