#pragma once
#include <iostream>
using namespace std;
template <class T1, class T2>
class Person7 {
 public:
  Person7() {}  // 注意，下文中生成arr时必须有默认构造，空实现
  Person7(T1 name, T2 age);  // 类内声明
  void show();

  T1 m_name;
  T2 m_age;
};

template <class T1, class T2>
Person7<T1, T2>::Person7(T1 name, T2 age) {  // 构造函数类外实现，要加<T1, T2>
  m_name = name;
  m_age = age;
}
template <class T1, class T2>
void Person7<T1, T2>::show() {
  std::cout << "类模板分文件编写 " << m_name << " " << m_age << std::endl;
}

template <class T>
class MyArray {
 public:
  MyArray(int capacity) {
    cout << "有参构造函数" << endl;
    m_capacity = capacity;
    pAddress = new T[m_capacity];  // 数组开辟到堆区
    m_size = 0;
  }
  MyArray(const MyArray& arr) {  // 拷贝构造函数，深拷贝
    cout << "拷贝构造函数" << endl;
    m_capacity = arr.m_capacity;
    m_size = arr.m_size;
    // pAddress = arr.pAddress // 浅拷贝，会导致两次释放
    pAddress = new T[m_capacity];
    for (int i = 0; i < m_size; i++)
      this->pAddress[i] = arr.pAddress[i];
  }
  MyArray& operator=(const MyArray& arr) {  // 重载=号，防止浅拷贝
    cout << "operator=防止浅拷贝" << endl;
    if (pAddress != nullptr) {  // 原来堆区是否有数据，直接释放
      delete[] pAddress;
      pAddress = nullptr;
      m_capacity = 0;
      m_size = 0;
    }
    m_capacity = arr.m_capacity;
    m_size = arr.m_size;
    pAddress = new T[m_capacity];
    for (int i = 0; i < m_size; i++)
      pAddress[i] = arr.pAddress[i];
    return *this;  // 重载符号时，要返回引用值
  }
  void push_back(const T& val) {  // 压入值推荐为引用
    if (m_size == m_capacity) {
      cout << "容器已满，不能压入" << endl;
      return;
    }
    pAddress[m_size++] = val;
  }
  void pop_back() {
    if (m_size == 0) {
      cout << "容器已空，不能弹出" << endl;
      return;
    }
    m_size--;
  }
  T& operator[](int index) {
    return pAddress[index];
  }  // 重载[]才能通过下标访问，函数调用如果想作为等号左边，要引用
  int getCapacity() { return m_capacity; }
  int getSize() { return m_size; }
  ~MyArray() {
    cout << "析构函数" << endl;
    if (pAddress != nullptr)
      delete[] pAddress;
    pAddress = nullptr;
  }

 private:
  int m_capacity;  // 容量
  int m_size;      /// 大小
  T* pAddress;     // 指针指向堆区开辟真实数组
};