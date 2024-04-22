#include "head.h"
/* LCR 134. Pow(x, n)
实现 pow(x, n) ，即计算 x 的 n 次幂函数（即，xn）。
示例 1：
输入：x = 2.00000, n = 10
输出：1024.00000
示例 2：
输入：x = 2.10000, n = 3
输出：9.26100
示例 3：
输入：x = 2.00000, n = -2
输出：0.25000
解释：2-2 = 1/22 = 1/4 = 0.25 */

double quick(double x, long n) {
  if (n == 0)
    return 1;
  double tmp1 = quick(x, n / 2);
  double tmp2 = tmp1 * tmp1;
  return (n % 2 == 1) ? tmp2 * x : tmp2;
}
double myPow(double x, int n) {
  return n >= 0 ? quick(x, n) : 1.0 / quick(x, -n);
}

// 一定要使用long临时保存n，否则INT_MIN下限。
double myPow1(double x, int n) {
  if (x == 0.0)
    return x;
  long b = n;
  if (n < 0) {
    x = 1.0 / x;
    b *= -1;
  }
  double ans = 1.0;
  while (b > 0) {
    if (b % 2 == 1)
      ans *= x;
    x *= x;
    b >>= 1;
  }
  return ans;
}

int main() {
  cout << myPow(2.0, 10) << " " << myPow(2.1, 3) << " " << myPow(2.0, -2) << " "
       << myPow(1.0, -2147483648) << endl;
  cout << myPow1(2.0, 10) << " " << myPow1(2.1, 3) << " " << myPow1(2.0, -2)
       << " " << myPow1(1.0, -2147483648) << endl;
  return 0;
}