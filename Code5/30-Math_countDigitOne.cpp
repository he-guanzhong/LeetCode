#include "head.h"
/* 233. 数字 1 的个数
给定一个整数 n，计算所有小于等于 n 的非负整数中数字 1 出现的个数。
示例 1：
  输入：n = 13
  输出：6
示例 2：
  输入：n = 0
  输出：0
提示：
    0 <= n <= 10^9 */

int countDigitOne(int n) {
  int ans = 0;
  long digit = 1;
  int cur = n % 10, high = n / 10, low = 0;
  while (cur || high) {
    if (cur == 0) {
      ans += high * digit;
    } else if (cur == 1) {
      ans += high * digit + low + 1;
    } else {
      ans += (high + 1) * digit;
    }
    low += cur * digit;
    digit *= 10;
    cur = high % 10;
    high /= 10;
  }
  return ans;
}

// 1的个数，要看1处于哪个位置，设当前位置为digit，其上数字为cur，其左的多位数字high，其右多位数字low。初始化为个位digit=1,low=0
// 注意digit要使用long，32位系统和int一样为4字节，但64位系统为8字节。其范围是21亿，即2*10^9，但是题目中说
// 当digit==10，cur==0，考虑2304的案例，范围[000,229]，总计230个即为high*digit
// 当cur==1，考虑2314案例，范围[000,234]，总计235个，即high*digit+low+1。当cur>=2，考虑2324案例，范围[000,239]，总计240个，即(high+1)*digit。
// 按照low,cur,high,digit的顺序依次更新。直至high==0&&cur==0，说明已经越过最高一位，循环停止。故循环条件为high和cur任意一个不为0
int countDigitOne1(int n) {
  int high = n / 10, cur = n % 10, low = 0, ans = 0;
  long digit = 1;
  while (high != 0 || cur != 0) {
    if (cur == 0)
      ans += high * digit;
    else if (cur == 1)
      ans += high * digit + low + 1;
    else
      ans += (high + 1) * digit;
    low += cur * digit;
    cur = high % 10;
    high /= 10;
    digit *= 10;
  }
  return ans;
}

int main() {
  cout << countDigitOne(13) << " " << countDigitOne(0) << endl;
  cout << countDigitOne1(13) << " " << countDigitOne1(0) << endl;

  return 0;
}