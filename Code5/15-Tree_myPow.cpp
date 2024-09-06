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
  解释：2-2 = 1/22 = 1/4 = 0.25
示例 4：
  输入：x = 1.0, n = -2147483648
示例 5：
  输入：x = 0.00001, n = 2147483647 */

double myPow(double x, int n) {
  if (n == 0)
    return 1.0;
  long m = n;
  if (m < 0) {
    m *= -1;
    x = 1 / x;
  }
  double ans = 1;
  while (m) {
    if (m % 2 == 1)
      ans *= x;
    x *= x;
    m /= 2;
  }
  return ans;
}

// 一定要使用long临时保存n，否则INT_MIN下限取反，正好会超过INT_MAX，例如-128取反，会超过127的上限。
// 除以2操作可以使用右移>>代替，判定奇偶取余%2可以使用按位与&1代替
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
    if (b & 1)
      ans *= x;
    x *= x;
    b >>= 1;
  }
  return ans;
}

// 递归法。注意使用longl
// long保存n。退出条件是，任何数x的0次幂等于1。此方法时间和空间复杂度均为logN
double quick2(double x, long long n) {
  if (n == 0)
    return 1.0;
  double y = quick2(x, n / 2);
  return n % 2 == 1 ? y * y * x : y * y;
}
double myPow2(double x, int n) {
  long long m = n;
  return n > 0 ? quick2(x, m) : 1.0 / quick2(x, -m);
}

int main() {
  cout << myPow(2.0, 10) << " " << myPow(2.1, 3) << " " << myPow(2.0, -2) << " "
       << myPow(1.0, -2147483648) << " " << myPow(0.00001, 2147483647) << endl;
  cout << myPow1(2.0, 10) << " " << myPow1(2.1, 3) << " " << myPow1(2.0, -2)
       << " " << myPow1(1.0, -2147483648) << " " << myPow1(0.00001, 2147483647)
       << endl;
  return 0;
}