#include <cmath>
#include <iostream>
#define day 7  // 宏常量，前文替换后文
using namespace std;

int main() {
  cout << "only one main program should exist." << endl;

  // 变量与常量
  int val = 10;
  const int month = 12;  // const常量
  cout << "val = " << val << "  day = " << day << "  month = " << month << endl;

  // 标识符
  int number1 = 3, number2 = 5;
  int sum = number1 + number2;
  cout << number1 << " + " << number2 << " = " << sum << endl;

  // 数据类型，char = bool = 1, short = 2, int = long = float = 4,
  // double = long long  = 8
  int num1 = 99;
  short num2 = 999;
  long num3 = 99999;
  long long num4 = 9999999;
  cout << "size: int " << sizeof(num1) << "  short " << sizeof(num2)
       << "  long " << sizeof(num3) << "  long long " << sizeof(num4) << endl;

  float num5 = 3.14f;
  double num6 = 2.71;
  cout << "size: float " << sizeof(float) << "  double " << sizeof(double)
       << endl;
  float num7 = 3e4f;
  float num8 = 3e-4f;
  cout << "num7 = " << num7 << "  num8 = " << num8 << endl;

  char ch = 'a';
  cout << "size: char " << sizeof(ch) << "  ascii: " << (int)ch << endl;
  // 水平制表符，对齐字节，未满8个字符，就补齐至8个
  cout << "hello world \n";
  cout << "\\ \n";
  cout << "1234567\t8" << endl;
  cout << "12345678\t9" << endl;
  cout << "123456789\t10" << endl;

  // 字符串
  char str1[] = "thr1 based on C. ";
  string str2 = "str2 based on C++. ";
  cout << str1 << str2 << endl;

  // 布尔类型
  bool flag = true;
  cout << flag << " ";
  flag = false;
  cout << flag << endl;

  // 输入数据
  int input1 = 0;
  cout << "please input int ";
  cin >> input1;
  cout << "int is " << input1 << endl;
  float input2 = 0.0f;
  cout << "please input float ";
  cin >> input2;
  cout << "float is " << input2 << endl;
  char input3 = 'a';
  cout << "please input char ";
  cin >> input3;
  cout << "char is " << input3 << endl;
  string input4 = "sd";
  cout << "please input string ";
  cin >> input4;
  cout << "string is " << input4 << endl;
  bool input5 = false;
  cout << "please input bool ";
  cin >> input5;
  cout << "bool is " << input5 << endl;

  // 运算符 + - * / %
  int a = 3, b = 5;
  cout << a + b << " " << a - b << " " << a * b << " " << a / b << " " << a % b
       << endl;  // 整数不能直接相除
  // 前置递增 ++ ，后置递增
  int x1 = 6;
  int x2 = x1++ * 5;
  x1--;
  int x3 = ++x1 * 5;
  cout << "x1 = " << x1 << "  x2 = " << x2 << "  x3 = " << x3 << endl;
  double x4 = 9;
  double x5 = x4-- / 4;
  x4++;
  double x6 = --x4 / 4;
  cout << "x4 = " << x4 << "  x5 = " << x5 << "  x6 = " << x6 << endl;
  // 幂运算，需要 math.h 或 cmath
  cout << pow(2, 3) << " " << pow(2, -3) << endl;
  // 赋值运算 += -= /= *= %=
  a += 2;
  b -= 2;
  // 比较运算 == != <= >= < >
  cout << "a = " << a << "  b = " << b << "  a > b ? " << (a == b) << endl;
  // system("pause");  // 按任意键退出

  return 0;
}