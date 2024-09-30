#include <iostream>
using namespace std;

void pointer_concept() {
  int a = 3, b = 1000;
  int* p = &a;
  cout << "p = " << p << "  &a = " << &a << endl;
  cout << "*p = " << *p << endl;  // 解引用

  // 指针占用空间，64位系统8字节，32位系统4字节
  cout << "sizeof ptr int " << sizeof(int*) << "  sizeof ptr char "
       << sizeof(char*) << "  sizeof ptr float " << sizeof(float*)
       << "  sizeof ptr double " << sizeof(double*) << endl;

  // 空指针，必须大写，指向内存编号为0变量，用于初始化指针变量，但其指向内存不能访问，因为0-255见内存编号系统占用，不能更改
  int* p1 = NULL;
  p1 = &b;
  cout << "p1 = " << p1 << "  *p1 = " << *p1 << endl;

  // 野指针。指向非法内存空间
  int* p2 = (int*)0x110000;  // 不是自己申请的空间不要访问
  // cout << *p2 << endl;

  // const指针，看后面跟着什么
  // const修饰指针，为常量指针，指针指向的值不能改，指向位置可以改
  int a1 = 3, a2 = 5;
  const int* p3 = &a1;
  cout << "const int* p3 = " << p3 << "  *p3 = " << *p3;
  //*p3 = 4;   // 错误，修改了指向的值
  p3 = &a2;  // 正确，修改了指向地址
  cout << "  *p3 = " << *p3 << endl;
  // const修饰常量，指针常量，指针自身是一个常量，指向地址不能改，指向的值可以改
  int* const p4 = &a1;
  *p4 = 4;  // 正确，修改了指向的值
  // p4 = &a2;  // 错误，修改了指向的地址
  // const同时修饰指针和常量，位置和值均不能改
  const int* const p6 = &a1;

  // 指针与数组，指针访问数组中所有元素
  int array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  int* p7 = array;  // 数组名就是首地址
  for (int i = 0; i < sizeof(array) / sizeof(array[0]); i++) {
    cout << *p7 << " ";
    p7++;  // 指针后移一位，即向右偏移4个字节
  }
  cout << endl;
}

void swap(int* a, int* b) {
  // 函数的地址传递
  cout << "ori: a = " << *a << "  b = " << *b << endl;
  int temp = *a;
  *a = *b;
  *b = temp;
  cout << "new: a = " << *a << "  b = " << *b << endl;
}

void bubble_sort(int* array, int len) {  // 数组要传的是首地址
  cout << "before, ";
  for (int i = 0; i < len; i++)
    cout << array[i] << " ";
  cout << endl;

  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (array[j] > array[j + 1])
        swap(&array[j], &array[j + 1]);
    }
  }
  cout << "after, ";
  for (int i = 0; i < len; i++)
    cout << array[i] << " ";
  cout << endl;
}

int main() {
  pointer_concept();
  int a = 3, b = 5;
  swap(&a, &b);  // 变量地址传入函数，指针用来接收
  int array[] = {4, 2, 8, 6, 5, 7, 1, 3, 9};
  bubble_sort(array, 9);
  return 0;
}
