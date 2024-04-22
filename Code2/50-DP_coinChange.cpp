#include "head.h"
#include <string.h>
/* 322. 零钱兑换
给你一个整数数组 coins ，表示不同面额的硬币；以及一个整数 amount ，表示总金额。
计算并返回可以凑成总金额所需的 最少的硬币个数
。如果没有任何一种硬币组合能组成总金额，返回 -1 。
你可以认为每种硬币的数量是无限的。
示例 1：
输入：coins = [1, 2, 5], amount = 11
输出：3
解释：11 = 5 + 5 + 1
示例 2：
输入：coins = [2], amount = 3
输出：-1
示例 3：
输入：coins = [1], amount = 0
输出：0 */

// 可以无限取，完全背包，求最少硬币个数。dp[j]表示装满容量j背包最少硬币数，全部初始化为INT_MAX，为假值。dp[0]=0，因为装满容量为0背包无需硬币
// 递推公式，为dp[j]为不装coins[i]数量加一。注意，前提是不装coins[i]的数量为真值，若其本身不可行，则不递推。最终检查dp[amount]是否为真值
int coinChange(vector<int> &coins, int amount) {
  int dp[amount + 1];
  for (int i = 0; i <= amount; i++)
    dp[i] = INT_MAX;
  dp[0] = 0;
  for (int i = 0; i < coins.size(); i++) {
    for (int j = coins[i]; j <= amount; j++) {
      if (dp[j - coins[i]] != INT_MAX)
        dp[j] = fmin(dp[j], dp[j - coins[i]] + 1);
    }
  }
  return dp[amount] == INT_MAX ? -1 : dp[amount];
}

// 硬币可以无限取，典型完全背包问题。dp[i]表示背包容量i时最小硬币个数。第j容量的硬币个数，等于第j-coins[i]硬币个数加一
// 递推公式dp[j]=min(dp[j],dp[j-size[i]]+1)，遍历物品和背包内外层均可。
// 初始哈由于求的时最小硬币个数，所以所有值初始化为INT_MAX。容量为0的背包硬币个数也必为0，故dp[0]=0
// 由于默认硬币个数均初始化为INT_MAX，故递推公式进入条件是，dp[j-size[i]]必须是一个真值，而不是默认值。
// 同理，返回条件，如果发现最终dp[amount]还是默认值，则返回-1
int coinChange1(vector<int> &coins, int amount) {
  vector<int> dp(amount + 1, INT_MAX);
  dp[0] = 0;
  for (int i = 0; i < coins.size(); i++) {
    for (int j = coins[i]; j <= amount; j++) {
      if (dp[j - coins[i]] != INT_MAX)
        dp[j] = min(dp[j], dp[j - coins[i]] + 1);
    }
  }
  if (dp[amount] == INT_MAX)
    return -1;
  return dp[amount];
}

// 也可以先遍历背包，再遍历物品
int coinChange2(vector<int> &coins, int amount) {
  vector<int> dp(amount + 1, INT_MAX);
  dp[0] = 0;
  for (int j = 0; j <= amount; j++) {
    for (int i = 0; i < coins.size(); i++) {
      if (j >= coins[i] && dp[j - coins[i]] != INT_MAX)
        dp[j] = min(dp[j], dp[j - coins[i]] + 1);
    }
  }
  if (dp[amount] == INT_MAX)
    return -1;
  return dp[amount];
}

int main() {
  vector<int> coins1 = {1, 2, 5}, coins2 = {2}, coins3 = {1};
  int amount1 = 11, amount2 = 3, amount3 = 0;
  cout << coinChange(coins1, amount1) << " " << coinChange(coins2, amount2)
       << " " << coinChange(coins3, amount3) << endl;
  cout << coinChange1(coins1, amount1) << " " << coinChange1(coins2, amount2)
       << " " << coinChange1(coins3, amount3) << endl;
  return 0;
}