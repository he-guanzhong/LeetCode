#include "head.h"
/* 343. 整数拆分
给定一个正整数 n ，将其拆分为 k 个 正整数 的和（ k >= 2
），并使这些整数的乘积最大化。
返回 你可以获得的最大乘积 。
示例 1:
  输入: n = 2
  输出: 1
  解释: 2 = 1 + 1, 1 × 1 = 1。
示例 2:
  输入: n = 10
  输出: 36
  解释: 10 = 3 + 3 + 4, 3 × 3 × 4 = 36。 */

int integerBreak(int n) {
  vector<int> dp(n + 1, 0);
  dp[2] = 1;
  for (int i = 3; i <= n; i++) {
    for (int j = 1; j <= i / 2; j++)
      dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
  }
  return dp[n];
}

// 贪心算法。小于4，等于4特殊处理。不断减3，结果乘3，直至n<=4的特殊情况，乘以末尾
// 动态规划。dp[i]表示拆分i的最大乘积。j为拆分点至j<=i/2，分为i-j可拆、可不拆，原dp[i]三种情况最大值

// 动态规划。dp[i]表示数字i拆分下的最大乘积。初始化dp[2]=1因为dp[0]和dp[1]无意义。
// 递推公式dp[i]=max(dp[i],max(j*(i-j),j*dp[i-j]))。因为以j分i，可拆2份，也可拆更多。
// 时间复杂度n^2，空间复杂度n
int integerBreak1(int n) {
  vector<int> dp(n + 1);
  dp[2] = 1;
  for (int i = 3; i <= n; i++) {
    for (int j = 1; j <= i / 2; j++) {  // 从1开始，拆到一半即可
      dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
    }
  }
  return dp[n];
}

// 贪心算法。时间复杂度O(n)，空间复杂度O(1)
int integerBreak2(int n) {
  if (n < 4)
    return n - 1;
  else if (n == 4)
    return n;
  int result = 1;
  while (n > 4) {
    n -= 3;
    result *= 3;
  }
  return result * n;
}

int main() {
  cout << integerBreak(2) << " " << integerBreak(5) << " " << integerBreak(10)
       << endl;
  cout << integerBreak1(2) << " " << integerBreak1(5) << " "
       << integerBreak1(10) << endl;
  return 0;
}