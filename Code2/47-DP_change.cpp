#include "head.h"
/* 518. 零钱兑换 II
给你一个整数数组 coins 表示不同面额的硬币，另给一个整数 amount 表示总金额。
请你计算并返回可以凑成总金额的硬币组合数。如果任何硬币组合都无法凑出总金额，返回0
。 假设每一种面额的硬币有无限个。 题目数据保证结果符合 32 位带符号整数。
示例 1：
输入：amount = 5, coins = [1, 2, 5]
输出：4
解释：有四种方式可以凑成总金额：
    5=5
    5=2+2+1
    5=2+1+1+1
    5=1+1+1+1+1
示例 2：
  输入：amount = 3, coins = [2]
  输出：0
  解释：只用面额 2 的硬币不能凑成总金额 3 。
示例 3：
  输入：amount = 10, coins = [10]
  输出：1*/

int change(int amount, vector<int>& coins) {
  vector<int> dp(amount + 1, 0);
  dp[0] = 1;
  for (int i = 0; i < coins.size(); i++) {
    for (int j = coins[i]; j <= amount; j++) {
      dp[j] += dp[j - coins[i]];
    }
  }
  return dp[amount];
}

// 完全背包。dp[j]代表容量j之内组合数。初始化dp[0]=1表示单取coins[i]算一种方法。
// 递推公式，dp[j]组合数为上一轮金额j组合数，和本轮减去coins[i]组合数之和。组合数遍历顺序必须先物品再背包，否则为排列数。

// 硬币可以无限取，完全背包问题。但是本题求的是数量，而非最大价值。故dp[j]表示背包容量，即总金额为j时的可能组合数量
// 递推公式dp[j]+=dp[j-coins[i]]，即金额为j的组合数量，等于上一轮金额j的组合数量，加本轮刨去硬币coins[i]的数量
// 初始化注意，dp[0]=1，因为金额总和为0只有一种方法。容量1的背包放价值1的硬币，只有一种可能。但是其余起始金额j总和均初始化为0。
// 遍历顺序，一定要先遍历硬币，再遍历容量。才是组合数。否则颠倒过来是排列数
int change1(int amount, vector<int>& coins) {
  vector<int> dp(amount + 1, 0);
  dp[0] = 1;
  for (int i = 0; i < coins.size(); i++) {
    for (int j = coins[i]; j <= amount; j++) {
      dp[j] += dp[j - coins[i]];
    }
  }
  return dp[amount];
}

int main() {
  int amount1 = 5, amount2 = 3, amount3 = 10;
  vector<int> coin1 = {1, 2, 5};
  vector<int> coin2 = {2};
  vector<int> coin3 = {10};
  cout << change(amount1, coin1) << " " << change(amount2, coin2) << " "
       << change(amount3, coin3) << endl;
  cout << change1(amount1, coin1) << " " << change1(amount2, coin2) << " "
       << change1(amount3, coin3) << endl;
  return 0;
}