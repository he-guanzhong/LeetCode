#include <iostream>
using namespace std;
// 静态成员，包括静态成员变量和静态成员函数
// 静态成员变量，所有对象共享一份数据，编译阶段分配内存，类内声明，类外初始化
// 静态成员函数，所有对象共享一个函数，只能访问静态成员变量
class Person {
 public:
  static int m_a;  // 类内声明，静态成员变量，不属于类的对象上
  int m_c;         // 非静态成员变量，属于类的对象上
  void func0() {  // 非静态成员函数，不属于类的对象上
    m_a = 100;
    cout << " func0() public  \n";
  }
  static void func1() {  // 静态成员函数，不属于类的对象上，
    m_a = 100;
    // m_c = 300;  // 非静态成员变量，不可被调用
    cout << "static func1() public  \n";
  }

 private:
  static int m_b;
  void func2() { cout << "static func2() private \n"; }
};
int Person::m_a = 100;  // 类外初始化

void static_member() {
  Person p1;
  cout << "p1 a: " << p1.m_a << endl;
  Person p2;
  p2.m_a = 200;
  cout << "p1 a: " << p1.m_a << endl;  // 两个对象共享一份数据

  Person p3;
  cout << "通过对象访问: " << p3.m_a << " 通过类名访问：" << Person::m_a
       << endl;
  // cout << "静态私有对象不能访问" << Person::m_b << endl;

  cout << "通过对象访问: ";
  p3.func1();
  cout << "通过类名访问：";
  Person::func1();
  // p3.func2(); private函数类外不能访问
}
class Test {};
void member_storage() {
  Test t;  // 空对象占用字节1，也有独一无二内存地址
  cout << "空对象的大小：" << sizeof(t) << endl;
  Person p;  // 只考虑非静态成员变量，一个Int 4字节
  cout << "对象的大小：" << sizeof(p) << endl;
}

// this 指针
class Person1 {
 public:
  Person1(int age) {
    this->age = age;
  }  // 有参构造，解决命名冲突,this指针为被调用成员函数所属对象
  void addPersonAge1(Person1& p) { this->age += p.age; }  // p2调用
  Person1& addPersonAge2(Person1& p) {  // 引用方式返回，this指向p3，解引用
    this->age += p.age;
    return *this;
  }
  Person1 addPersonAge3(Person1& p) {  // 值方式返回，返回的不是对象本身
    this->age += p.age;  // 之后调用拷贝构造函数，复制一个新对象，return之
    return *this;
  }

  int age;
};
void this_pointer() {
  Person1 p1(10);
  Person1 p2(20);
  Person1 p3(30);
  Person1 p4(40);
  p2.addPersonAge1(p1);
  cout << "p2 age: " << p2.age << endl;
  p3.addPersonAge2(p1).addPersonAge2(p1).addPersonAge2(p1);
  cout << "p3 age: " << p3.age << endl;  // 返回是p3本身，连续加连ing，链式编程
  p4.addPersonAge2(p1).addPersonAge2(p1).addPersonAge2(p1);
  cout << "p4 age: " << p4.age << endl;  // 返回的不是p4本身没而是拷贝的新对象
}

// 空指针可以访问成员函数，但如果用到this指针，需要加判断保证健壮性
class Person2 {
 public:
  void showClassName() { cout << "类名是" << endl; }
  void showClassAge() {
    if (this == NULL)  // 空指针return掉，避免报错，
      return;
    cout << "类年龄是" << m_age << endl;  // this->m_age 和m_age等效
  }
  int m_age;
};
void null_ptr_access() {
  Person2* p = NULL;
  p->showClassName();
  p->showClassAge();  // 空指针没有对象，访问属性会报错
}

// 常函数、常对象
class Person3 {
 public:
  Person3() {}
  // this 指针本质是指针常量，指向地址不可修改
  void func_const() const {  // 常函数，相当于const Person3 *const
                             // this，修饰this指向，使其内容也不可修改
    // m_a = 100;  // 等效于this->m_a = 100,不可修改
    m_b = 200;
    cout << "常函数调用" << endl;
  }
  void func_normal() { cout << "普通函数调用" << endl; }
  int m_a;
  mutable int m_b;  // mutable关键字，常对象也可更改
};
void const_func_object() {
  Person3 p1;
  p1.func_const();
  p1.func_normal();
  cout << "normal p1: m_b:" << p1.m_b << endl;

  // 常对象必须有构造函数，只能调用常函数，不能修改成员变量
  const Person3 p2;
  // p2.m_a = 300;      // 常对象不能修改普通成员变量
  p2.m_b = 400;
  cout << "const p2: m_b:" << p2.m_b << endl;
  p2.func_const();
  // p2.func_normal();  // 常对象不能调用普通函数
}
int main() {
  static_member();
  member_storage();
  this_pointer();
  null_ptr_access();
  const_func_object();
  return 0;
}
