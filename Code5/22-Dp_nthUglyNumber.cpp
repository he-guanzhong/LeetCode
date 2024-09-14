#include "head.h"
/* LCR 168. 丑数
给你一个整数 n ，请你找出并返回第 n 个 丑数 。
说明：丑数是只包含质因数 2、3 和/或 5 的正整数；1 是丑数。
示例 1：
  输入: n = 10
  输出: 12
  解释: 1, 2, 3, 4, 5, 6, 8, 9, 10, 12 是前 10 个丑数。
提示：
    1 <= n <= 1690 */

int nthUglyNumber(int n) {
  int a = 0, b = 0, c = 0;
  vector<int> dp(n, 1);
  for (int i = 1; i < n; i++) {
    dp[i] = min({dp[a] * 2, dp[b] * 3, dp[c] * 5});
    if (dp[i] % 2 == 0)
      a++;
    if (dp[i] % 3 == 0)
      b++;
    if (dp[i] % 5 == 0)
      c++;
  }
  return dp[n - 1];
}

// 丑数必定由若干个2、3、5作为质因数，相乘构成。故假定由分别由a个2，b个3，c个5，全部初始化为0。dp[i-1]代表第i个丑数
// 第一个丑数为1，故初始化dp[0]=1。从第二个丑数开始，第一个丑数dp[a],dp[b],dp[c]三个丑数，分别多乘一个2、3、5，去最小值，为dp[i]
// 当dp[i]为第a个丑数已经通过*2得到了新丑数，那么下一个需要*2的应该时第(a+1)个丑数。
int nthUglyNumber1(int n) {
  int a = 0, b = 0, c = 0;
  vector<int> dp(n);
  dp[0] = 1;
  for (int i = 1; i < n; i++) {
    int n2 = dp[a] * 2, n3 = dp[b] * 3, n5 = dp[c] * 5;
    dp[i] = min({n2, n3, n5});
    if (dp[i] == n2)
      a++;
    if (dp[i] == n3)
      b++;
    if (dp[i] == n5)
      c++;
  }
  return dp[n - 1];
}

int main() {
  cout << nthUglyNumber(10) << " " << nthUglyNumber(1) << " " << endl;
  cout << nthUglyNumber1(10) << " " << nthUglyNumber1(1) << " " << endl;

  return 0;
}