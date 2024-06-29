#include "head.h"
/* 279. 完全平方数
给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。
完全平方数
是一个整数，其值等于另一个整数的平方；换句话说，其值等于一个整数自乘的积。例如，1、4、9
和 16 都是完全平方数，而 3 和 11 不是。
示例 1：
输入：n = 12
输出：3
解释：12 = 4 + 4 + 4
示例 2：
输入：n = 13
输出：2
解释：13 = 4 + 9 */

int numSquares(int n) {
  vector<int> dp(n + 1, INT_MAX);
  dp[0] = 0;
  for (int i = 1; i * i <= n; i++) {
    for (int j = i * i; j <= n; j++) {
      if (dp[j - i * i] != INT_MAX)
        dp[j] = min(dp[j], dp[j - i * i] + 1);
    }
  }
  return dp[n];
}

// 问题转化为，完全平方数的物品若干物品i*i，去填满总量为n的背包，求最小的物品数量。
// dp[j]表示大小为j的背包，里面最小的物品数量，递推公式为dp[j]=min(dp[j-i*i]+1,dp[j])
// 由于求的是最小数量，所有dp初始值必须要为最大INT_MAX，才不会被min函数覆盖。dp[0]=0因为填满0的背包不需要完全平方数
// 遍历顺序先遍历物品，再遍历背包。或二者相反均可以，因为本体求的是最小数量，非组合数和排列数。
// 特别注意，由于物品为1，4，9..故第一轮时，所有INT_MAX必被替换为1，2，3..，故递推公式前，不必加额外判断
int numSquares1(int n) {
  vector<int> dp(n + 1, INT_MAX);
  dp[0] = 0;
  for (int i = 1; i * i <= n; i++) {
    for (int j = i * i; j <= n; j++) {
      dp[j] = min(dp[j], dp[j - i * i] + 1);
    }
  }
  return dp[n];
}

// 无限取平方数，完全背包。容量为n，物品为i*i，先初始化为INT_MAX，由于平方数必从1开始，第一轮遍历即消除所有INT_MAX
// 后续递推公式，无需判断是否可能。dp[j]表示数j由完全平方数组成的最小数量，其值等于减去本轮i*i的数量加一。
// 也可以先遍历背包，再遍历物品
int numSquares2(int n) {
  vector<int> dp(n + 1, INT_MAX);
  dp[0] = 0;
  for (int j = 0; j <= n; j++) {
    for (int i = 1; i * i <= n; i++) {
      if (j >= i * i)
        dp[j] = min(dp[j], dp[j - i * i] + 1);
    }
  }
  return dp[n];
}

int main() {
  cout << numSquares(12) << " " << numSquares(13) << " " << numSquares(25)
       << endl;
  cout << numSquares1(12) << " " << numSquares1(13) << " " << numSquares1(25)
       << endl;
  return 0;
}