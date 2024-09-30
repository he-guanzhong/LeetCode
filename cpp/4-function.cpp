#include "4-function.h"  // .h文件已经声明，故不用重复编写
using namespace std;

int add(int num1, int num2) {
  return num1 + num2;
}

void swap(int num1, int num2) {  // 形参不改变实际值
  int temp = num1;
  num1 = num2;
  num2 = temp;
  // void 类型的 return 可以省略
}

int max(int num1, int num2) {
  return num1 > num2 ? num1 : num2;
}

int main() {
  int a = 3, b = 5;
  cout << "a + b = " << add(a, b) << endl;
  swap(a, b);
  cout << "a = " << a << ", b = " << b << endl;
  cout << "max of (a, b) is " << max(a, b) << endl;
}
