#include <iostream>

using namespace std;
void array_name() {
  // 数组名就是首元素的位置，64位系统指针占用8字节，而int只4字节，故需要long
  // long类型转换
  int array[] = {11, 22, 33, 44, 55, 66};
  cout << sizeof(array) << " " << sizeof(array[0]) << endl;
  cout << (long long)array << " " << (long long)&array[0] << " "
       << (long long)&array[1] << endl;
  cout << array << " " << &array[0] << " " << &array[1] << endl;
}

void reverse_array() {
  // 逆转数组
  int array[] = {1, 2, 3, 4, 5};
  int start = 0;
  int end = sizeof(array) / sizeof(array[0]) - 1;
  while (start < end) {
    int temp = array[start];
    array[start] = array[end];
    array[end] = temp;
    start++;
    end--;
  }
  for (auto& i : array)
    cout << i << " ";
  cout << endl;
}

void bubble_sort() {
  int array[] = {4, 2, 8, 0, 5, 7, 1, 3, 9};
  cout << "before sort \t";
  for (const auto& i : array)
    cout << i << " ";
  cout << "\n";
  int len = sizeof(array) / sizeof(array[0]);
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (array[j] > array[j + 1])
        swap(array[j], array[j + 1]);
    }
  }
  cout << "after sort \t";
  for (const auto& i : array)
    cout << i << " ";
  cout << "\n";
}

void twoDimensional_array() {
  int array[][3] = {{100, 100, 100}, {90, 85, 95}, {80, 75, 85}};
  string name[] = {"张三", "李四", "王五"};
  int i = 0;
  for (const auto& person : array) {
    int sum = 0;
    for (auto& score : person)
      sum += score;
    cout << name[i++] << " 's score is " << sum << endl;
  }
}
int main() {
  array_name();
  reverse_array();
  bubble_sort();
  twoDimensional_array();
  return 0;
}