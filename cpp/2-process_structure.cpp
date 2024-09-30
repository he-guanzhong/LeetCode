#include <cmath>
#include <ctime>
#include <iostream>
using namespace std;
void if_statement() {
  // a, b, c三只小猪求最重
  int a = 2, b = 3, c = 4;
  if (a > b) {
    if (a > c)
      cout << "a is greatest " << a << endl;
    else
      cout << "c is greatest " << c << endl;
  } else {
    if (b > c)
      cout << "b is greatest " << b << endl;
    else
      cout << "c is greatest " << c << endl;
  }
  // 三目运算符
  int x = (a > b) ? ((a > c) ? a : c) : ((b > c) ? b : c);
  cout << "greatest is " << x << endl;
  // 三目运算符返回的是变量，可以继续赋值
  int x1 = 1, x2 = 2;
  (x1 < x2 ? x1 : x2) = 100;
  cout << "x1 = " << x1 << "  x2 = " << x2 << endl;
}

void switch_statement() {
  // 给游戏打分分级
  int score = 0;
  /*   cout << "please input your score: " << endl;
    cin >> score; */
  switch (score) {
    case 10:
    case 9:
      cout << "excellent \n";
      break;
    case 8:
    case 7:
      cout << "good \n";
      break;
    case 6:
      cout << "qualified \n";
      break;
    default:
      cout << "N\\A \n";
  }
}
void while_guessNumber() {
  srand((unsigned int)time(NULL));
  int num = rand() % 100 + 1;
  int cnt = 0;
  while (cnt < 10) {
    cout << "please input your guess\n";
    int guess = 0;
    cin >> guess;
    cnt++;
    if (guess > num)
      cout << "too big\n";
    else if (guess < num)
      cout << "too small\n";
    else {
      cout << "right! \n";
      break;
    }
  }
  cout << "result is " << num << endl;
}

void do_while_Narcissistic_number() {
  // 水仙花数，三位数，每位三次方相加，等于原数
  int n = 100;
  do {
    int a = n % 10;
    int b = n / 10 % 10;
    int c = n / 100;
    if (pow(a, 3) + pow(b, 3) + pow(c, 3) == n)
      cout << " narci = " << n << endl;
    n++;
  } while (n < 1000);
}

void for_knock_table() {
  // 敲桌子，个位、十位是7，数是7倍数。
  for (int i = 1; i < 100; i++) {
    if (i % 10 == 7 || i / 10 == 7 || i % 7 == 0)
      cout << " knock-" << i << " ";
  }
  cout << endl;
}

void nest_multiplicaton() {
  // 打印乘法表
  for (int i = 1; i < 10; i++) {
    for (int j = 1; j <= i; j++) {
      cout << j << "*" << i << "=" << j * i << " ";
    }
    cout << endl;
  }
}

void jump_statement() {
  // 打印可以100内可以被13整除的数
  for (int i = 1; i < 100; i++) {
    if (i % 13 != 0)
      continue;
    else
      cout << i << " ";
  }
  cout << endl;
  // goto 语句，尽量少用，flag非变量，引用位置时要加冒号
  cout << 1 << " ";
  goto FLAG;
  cout << 2 << " ";
  cout << 3 << " ";
FLAG:
  cout << 4 << endl;
}
int main() {
  if_statement();
  switch_statement();
  // while_guessNumber();
  do_while_Narcissistic_number();
  // for_knock_table();
  // nest_multiplicaton();
  jump_statement();
  return 0;
}