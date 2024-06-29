#include "head.h"
/* 爬楼梯（进阶版）
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬至多m (1 <= m < n)个台阶。你有多少种不同的方法可以爬到楼顶呢？
注意：给定 n 是一个正整数。
输入描述：输入共一行，包含两个正整数，分别表示n, m
输出描述：输出一个整数，表示爬到楼顶的方法数。
输入示例：3 2
输出示例：3
提示：
  当 m = 2，n = 3 时，n = 3 这表示一共有三个台阶，m = 2
  代表你每次可以爬一个台阶或者两个台阶。 此时你有三种方法可以爬到楼顶。 1 阶 + 1
  阶 + 1 阶段 1 阶 + 2 阶 2 阶 + 1 阶 */

int climbStairs(int n, int m) {
  vector<int> dp(n + 1, 0);
  dp[0] = 1;
  for (int j = 1; j <= n; ++j) {
    for (int i = 1; i <= m; i++) {
      if (j >= i)
        dp[j] += dp[j - i];
    }
  }
  return dp[n];
}

// 完全背包问题，求排列数
// 假定，现在每次可以走m个台阶，而非2台阶，那么问题转化为完全背包问题求排列，n为背包容量，m为物品
// 背包容量在外，物品在内，从前向后遍历。物品的重量就是自身大小
int climbStairs1(int n, int m) {
  vector<int> dp(n + 1, 0);
  dp[0] = 1;
  for (int j = 1; j <= n; j++)
    for (int i = 1; i <= m; i++) {
      if (j >= i)
        dp[j] += dp[j - i];
    }
  return dp[n];
}

int main() {
  for (int i = 1; i <= 5; i++)
    cout << climbStairs(i, 2) << " ";
  cout << endl;
  for (int i = 1; i <= 5; i++)
    cout << climbStairs1(i, 2) << " ";
  cout << endl;
  return 0;
}