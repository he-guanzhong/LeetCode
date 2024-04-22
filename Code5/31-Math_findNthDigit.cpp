#include "head.h"
/* 400. 第 N 位数字
给你一个整数 n ，请你在无限的整数序列 [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ...]
中找出并返回第 n 位上的数字。
示例 1：
输入：n = 3
输出：3
示例 2：
输入：n = 11
输出：0
解释：第 11 位数字在序列 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, ... 里是 0 ，它是 10
的一部分。
提示：
    1 <= n <= 231 - 1 */

int findNthDigit(int n) {
  int digit = 1, start = 1;
  long cnt = 9;
  while (n > cnt) {
    n -= cnt;
    digit++;
    start *= 10;
    cnt = digit * 9 * start;
  }
  int num = start + (n - 1) / digit;
  return to_string(num)[(n - 1) % digit] - '0';
}

// 分三步。一、确定n所在是几位数digit。对于数字n，定义三个特殊变量。数位digit，代表个十百千万等几位数，为int整型。
// 该数位下第一个起始数字start，如1、10、100等。该数位下数字的总位数cnt，如[10,99]总计90个数字，共180位，为避免越界使用long
// 初始化为个位，起始数字1，数位数量9个。while循环，不断迭代digit\cnt\start，直至剩余数量n小于等于该轮数位数量cnt
// 二、找到第n个数位所在数字num。由于该轮以start为基准，digit个单数组成数字，且n表示第n，故num=start+(n-1)/digit
// 三、找到第n个数位在数字num的第几位，读取其值。先将num转化位字符串，再读取其(n-1)%digit位，最后-‘0’转化为整型，得到最终结果
int findNthDigit1(int n) {
  int digit = 1;
  long cnt = 9, start = 1;
  while (n > cnt) {
    n -= cnt;
    start *= 10;
    digit++;
    cnt = start * digit * 9;
  }
  long num = start + (n - 1) / digit;
  return to_string(num)[(n - 1) % digit] - '0';
}

int main() {
  cout << findNthDigit(3) << " " << findNthDigit(11) << " "
       << findNthDigit(1000000000) << endl;
  cout << findNthDigit1(3) << " " << findNthDigit1(11) << " "
       << findNthDigit1(1000000000) << endl;
  return 0;
}