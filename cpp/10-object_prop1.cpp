#include <iostream>
using namespace std;

// 构造、析构和拷贝函数
// 构造函数：创建对象时为成员属性赋值。分无参、有参，普通、拷贝
// 析构函数：销毁对象时编译器自动调用
// 用户定义有参构造，C++不提供默认构造，但提供拷贝构造
// 用户定义拷贝构造，C++不提供默认和有参构造
class Person {
 public:
  // 构造函数与类名相同，无返回值但不写void，可以重载，但创建对象时只调用一次
  Person() { printf("无参函数调用\n"); }  // 无参即默认构造
  Person(int age) {                       // 有参
    m_age = age;
    printf("有参函数调用\n");
  };
  Person(const Person& p) {  // 拷贝构造必加const，因不改变原对象属性
    m_age = p.m_age;
    printf("拷贝函数调用\n");
  }
  // 析构函数类名相同前加~，无返回值不写void，可以重载，不能有参，对象销毁前只调用一次
  ~Person() { printf("析构函数调用\n"); }
  int getAge() { return m_age; }

 private:
  int m_age;
};
void inputClass(Person p) {}
void inputTest() {
  Person p;
  inputClass(p);
  cout << "值传递给函数参数传值\n";
}
Person outputClass() {
  Person p;
  return p;
}
void outputTest() {
  Person p = outputClass();
  cout << "值方式返回局部对象\n";
}

void createObject() {
  // 括号法
  Person p0;  // 默认构造函数，不能带括号，否则被认为是函数声明
  Person p1(20);  // 有参构造函数
  Person p2(p2);  // 拷贝构造函数
  cout << "p1 age: " << p1.getAge() << "  p2 age:" << p1.getAge() << endl;

  // 显示法
  Person p3 = Person(30);  // 有参构造，匿名对象
  Person(40);
  cout << "匿名对象。" << endl;
  Person p4 = Person(p3);  // 拷贝构造，匿名对象
  cout << "p3 age: " << p3.getAge() << "  p4 age:" << p4.getAge() << endl;
  // Person(p3); // 不能用拷贝构造初始化匿名对象

  // 隐式转换法
  Person p5 = 50;  // 相当于 Person p5 = Person(50) 有参构造
  Person p6 = p5;  // 拷贝构造
  cout << "p5 age: " << p5.getAge() << "  p6 age:" << p6.getAge() << endl;

  cout << endl;
  inputTest();
  cout << endl;
  outputTest();
}

// 深拷贝和浅拷贝
class Person1 {
 public:
  Person1() { cout << "默认无参构造\n"; }
  Person1(int a, int h) {
    m_age = a;
    m_height = new int(h);  // 创建堆区，返回指针
  }
  Person1(const Person1& p) {  // 创建拷贝构造函数，实现深拷贝
    m_age = p.m_age;
    // m_height = p.m_height;  // 编译器默认提供，堆区重复释放
    m_height = new int(*p.m_height);
    // 深拷贝，重新开辟一块内存，m_height指向新内存，避免二次释放
  }
  ~Person1() {
    if (m_height != NULL) {
      delete m_height;  // 手动开辟内存，需要手动释放
      m_height = NULL;  // 防止野指针，滞空
    }
  }
  int getAge() { return m_age; }
  int* getHeight() { return m_height; }

 private:
  int m_age;
  int* m_height;
};

void deep_shallow_copy() {
  // 深拷贝、浅拷贝
  // 编译器自己提供拷贝构造函数是浅拷贝。易造成堆区内存重复释放，二次释放是非法操作
  // 深拷贝，堆区开辟的属性，一定要自己定义拷贝构造函数，防止浅拷贝问题
  Person1 p10(30, 180);
  cout << "p10 info: " << p10.getAge() << " " << p10.getHeight() << endl;
  Person1 p11(p10);
  cout << "p11 info: " << p11.getAge() << " " << p11.getHeight() << endl;
}

// 初始化列表，
class Person2 {
 public:
  Person2(int a, int b, int c) : m_a(a), m_b(b), m_c(c) {}
  int m_a, m_b, m_c;
};
void initializeList() {
  Person2 p20(100, 200, 300);
  cout << p20.m_a << " " << p20.m_b << " " << p20.m_c << endl;
}

// 类对象作为成员
class Phone {
 public:
  Phone(string name, long long number) : m_name(name), m_number(number) {
    cout << " phone 构造 " << endl;
  }
  ~Phone() { cout << " phone 析构 " << endl; }
  string m_name;
  long long m_number;
};
class Person3 {
 public:
  Person3(string name, Phone phone) : m_name(name), m_phone(phone) {
    cout << " person 构造 " << endl;
  }
  ~Person3() { cout << " person 析构 " << endl; }
  string m_name;
  Phone m_phone;
};
void classAsMember() {
  Phone phone("华为", 13065489795);
  Person3 person("张三", phone);
  cout << person.m_name << " " << person.m_phone.m_name << " "
       << person.m_phone.m_number << endl;
}

int main() {
  createObject();
  deep_shallow_copy();
  initializeList();
  classAsMember();
  return 0;
}
