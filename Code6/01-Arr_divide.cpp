#include "head.h"
/* 29. 两数相除
给你两个整数，被除数 dividend 和除数 divisor。将两数相除，要求 不使用
乘法、除法和取余运算。
整数除法应该向零截断，也就是截去（truncate）其小数部分。例如，8.345 将被截断为 8
，-2.7335 将被截断至 -2 。返回被除数 dividend 除以除数 divisor 得到的 商 。
注意：假设我们的环境只能存储 32 位 有符号整数，其数值范围是 [−231,  231 − 1]
。本题中，如果商 严格大于 231 − 1 ，则返回 231 − 1 ；如果商 严格小于 -231
，则返回 -231 。
示例 1:
  输入: dividend = 10, divisor = 3
  输出: 3
  解释: 10/3 = 3.33333.. ，向零截断后得到 3 。
示例 2:
  输入: dividend = 7, divisor = -3
  输出: -2
  解释: 7/-3 = -2.33333.. ，向零截断后得到 -2 。
提示：
  -2^31 <= dividend, divisor <= 2^31 - 1
  divisor != 0 */

// 只能存储有符号32位整型int，因此INT_MIN如果再乘以-1，则会越界INT_MAX。必须首先特殊处理
// 负数范围大于正数，故将所有元素均转换为负数，对除数、被除数符号反转记录，由于记录cnt也是负数，故默认反转，反转要返回的答案要有负号
// 自制除法函数，原理是利用减法模拟除法，不得使用div()名，会和系统冲突。只要被除数绝对值大于除数，就要不停减下去，一层循环
// 每层循环内，除数记为tmp，二轮循环，不断翻倍膨胀，临时计数cnt也翻倍，直至tmp2倍值大于被除数，且其2倍值仍在INT_MIN范围内。
// 临时计数cnt累加至答案，被除数减去本轮消弭除数翻倍值。最终返回的计数是一个负值，即默认取反后的结果
int myDiv(int dividend, int divisor) {
  int ans = 0;
  while (dividend <= divisor) {
    int cnt = -1;
    int tmp = divisor;
    while (tmp >= INT_MIN - tmp && dividend <= tmp + tmp) {
      tmp += tmp;
      cnt += cnt;
    }
    ans += cnt;
    dividend -= tmp;
  }
  return ans;
}

int divide(int dividend, int divisor) {
  if (dividend == INT_MIN && divisor == -1)
    return INT_MAX;
  bool sign_switch = true;
  if (dividend > 0) {
    sign_switch = !sign_switch;
    dividend = -dividend;
  }
  if (divisor > 0) {
    sign_switch = !sign_switch;
    divisor = -divisor;
  }
  int ans = myDiv(dividend, divisor);
  return sign_switch ? -ans : ans;
}

int main() {
  cout << divide(10, 3) << " " << divide(7, -3) << " " << divide(INT_MIN, -1)
       << " " << divide(INT_MIN, 1) << endl;
  return 0;
}