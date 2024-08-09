#include "head.h"
/* 367. 有效的完全平方数
给你一个正整数 num 。如果 num 是一个完全平方数，则返回 true ，否则返回 false 。
完全平方数
是一个可以写成某个整数的平方的整数。换句话说，它可以写成某个整数和自身的乘积。
不能使用任何内置的库函数，如  sqrt 。
示例 1：
  输入：num = 16
  输出：true
  解释：返回 true ，因为 4 * 4 = 16 且 4 是一个整数。
示例 2：
  输入：num = 14
  输出：false
  解释：返回 false ，因为 3.742 * 3.742 = 14 但 3.742 不是一个整数。
提示!!：
    1 <= num <= 2^31 - 1 */

bool isPerfectSquare(int num) {
  double x_n0 = 0, x_n1 = num / 2.0;
  double eps = 1e-3f;
  while (abs(x_n0 - x_n1) > eps) {
    x_n0 = x_n1;
    x_n1 = x_n0 - (x_n0 * x_n0 - num) / 2.0 / x_n0;
  }
  return (x_n1 - (int)x_n1) < 1e-6;
}

// 二分查找。注意涉及中间值m*m，可能会超限，要使用long类型保存数据。时间复杂度O(logN)
bool isPerfectSquare1(int num) {
  int l = 0, r = num;
  while (l <= r) {
    long m = l + ((r - l) >> 1);
    if (m * m > num)
      r = m - 1;
    else if (m * m < num)
      l = m + 1;
    else
      return true;
  }
  return false;
}

// 数学方法，(n+1)^2-n^2=2n+1，故完全平方数，可以由1+3+5+7...组成。时间复杂度O(sqrt(n))，其高于二分法
bool isPerfectSquare2(int num) {
  int i = 1;
  while (num > 0) {
    num -= i;
    i += 2;
  }
  return num == 0;
}

// 牛顿迭代法Newton_Raphson_method。x^2-n=0方程求导，构造斜线(y-y0)=2x0(x-x0)。y=2x*x0-x0^2-n。解得x=1/2*(x0+n/x0)
// 时间复杂度O(logN)，但是底数为4，比二分法更优
// 易错点：1.使用double而非float。2.判断误差标准一般位1e-6，可使用numeric_limits模板类定义的最小精度epsilon()。
// 3.收敛后，要先取整int，再乘方与原数比较，不是两个float相乘的结果再取整int
bool isPerfectSquare3(int num) {
  double x0 = 0;
  double x1 = num;
  numeric_limits<double>::epsilon();
  while (fabs(x1 - x0) > 1e-6) {
    x0 = x1;
    x1 = x0 / 2.0 + num / 2.0 / x0;
  }
  int x = x1;
  return x * x == num;
}

int main() {
  cout << isPerfectSquare(16) << " " << isPerfectSquare(14) << " "
       << isPerfectSquare(2000105819) << " " << isPerfectSquare(100000001)
       << endl;
  cout << isPerfectSquare3(16) << " " << isPerfectSquare3(14) << " "
       << isPerfectSquare3(2000105819) << " " << isPerfectSquare3(100000001)
       << endl;
  return 0;
}