#include "head.h"
/* 69. x 的平方根
给你一个非负整数 x ，计算并返回 x 的 算术平方根 。
由于返回类型是整数，结果只保留 整数部分 ，小数部分将被 舍去 。
注意：不允许使用任何内置指数函数和算符，例如 pow(x, 0.5) 或者 x ** 0.5 。
示例 1：
  输入：x = 4
  输出：2
示例 2：
  输入：x = 8
  输出：2
  解释：8 的算术平方根是 2.82842..., 由于返回类型是整数，小数部分将被舍去。
提示：
  0 <= x <= 231 - 1 */

int mySqrt(int x) {
  int left = 0, right = x / 2;
  while (left <= right) {
    long long mid = left + ((right - left) >> 1);
    if (mid * mid > x) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return right;
}

// 二分法，注意一些核心细节。考虑到x最小值是0，一般左边界下界left取0。事实上考虑x为0或1的情况，也可以取1
// x最大值为INT_MAX，故有边界right上界一定是x，不得自作聪明取x/2。因为当x==1是right==0，直接跳过了答案所在范围
// 鉴于mid可能为INT_MAX/2，其平方超过了INT_MAX，故要使用long long做临时存储
// 答案要求平方根舍去小数部分，因此求的是第一个小于等于真实平方根的整数，也即第一个“不”大于真实平方根的整数
// 二分法使用upper_bound逻辑，计算值小于等于target时，向右移动left，保证其为第一个大于真实平方根的整数，此时right即为答案。
// 不得使用lower_bound逻辑，此时left为第一个大于等于真实平方根的整数，当等于时left是答案，大于时right才是答案，不唯一
int mySqrt2(int x) {
  int left = 0, right = x;
  while (left <= right) {
    long long mid = left + ((right - left) >> 1);
    if (mid * mid > x) {
      right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  return right;
}

// 正统方法，牛顿法Newton-Raphson。实质是求y=x*x-C这个方程在y=0时的正整数解。
// 设定x0为初始值，x1为本轮更新值。计算公式为，x1 = x0 - y / y'
// 展开式 x1 = x0 - (x0 * x0 - C) / (2 * x0)
// while循环退出条件是x1和x0足够接近，注意不得使用numeric_limits<double>::epsilon()，因为求解精度不足，会无限时间
// 一般地，1e-6的精度足够。特殊地，为保证进入循环前x0和x1不等。每轮x0赋值一定是在计算x1之前。
// 因此，虽然x1是更新值，但初始化一定要等于x，因为其实质上是x0的初始值。x0可以初始化不等于x的任意数，一般取0，如此节省判断x==0时特殊处理逻辑
int mySqrt1(int x) {
  double x0 = 0;
  double x1 = x;
  while (fabs(x0 - x1) > 1e-6) {
    x0 = x1;
    x1 = x0 - (x0 * x0 - x) / 2.0 / x0;
  }
  return (int)x0;
}

int main() {
  cout << mySqrt(4) << " " << mySqrt(8) << " " << mySqrt(0) << " " << mySqrt(1)
       << " " << mySqrt(2147395599) << " " << mySqrt(2147483647) << endl;
  cout << mySqrt1(4) << " " << mySqrt1(8) << " " << mySqrt1(0) << " "
       << mySqrt1(1) << " " << mySqrt1(2147395599) << " " << mySqrt1(2147483647)
       << endl;
  return 0;
}