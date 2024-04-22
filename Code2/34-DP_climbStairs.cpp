#include "head.h"
/* 70. 爬楼梯
假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
示例 1：
输入：n = 2
输出：2
解释：有两种方法可以爬到楼顶。
1. 1 阶 + 1 阶
2. 2 阶
示例 2：
输入：n = 3
输出：3
解释：有三种方法可以爬到楼顶。
1. 1 阶 + 1 阶 + 1 阶
2. 1 阶 + 2 阶
3. 2 阶 + 1 阶
 */

// 动态规划，dp[i]代表i级台阶有多少种方法。
int climbStairs(int n) {
  if (n < 3)
    return n;
  int dp[n + 1] = {0};
  dp[1] = 1;
  dp[2] = 2;
  for (int i = 3; i <= n; i++) {
    dp[i] = dp[i - 1] + dp[i - 2];
  }
  return dp[n];
}

// 动态规划。1.dp[i]代表i个台阶多少中方法。2.递推公式为斐波那契亚数列。3.初始化dp[1]=1,dp[2]=2,dp[0]无意义。
// 4.遍历方向从前向后。5.具体实例
int climbStairs1(int n) {
  if (n < 3)
    return n;
  int dp
      [3];  // 此处起始最好不要dp[2]，因为和定义不符。如为省空间，可以两个整形变量
  dp[1] = 1;
  dp[2] = 2;
  for (int i = 3; i <= n; i++) {
    int sum = dp[1] + dp[2];
    dp[1] = dp[2];
    dp[2] = sum;
  }
  return dp[2];
}

// 动态规划，时间复杂度n，空间复杂度n
int climbStairs2(int n) {
  if (n < 3)
    return n;
  int dp[n + 1];
  dp[1] = 1;
  dp[2] = 2;
  for (int i = 3; i <= n; i++)
    dp[i] = dp[i - 1] + dp[i - 2];
  return dp[n];
}

// 递归，时间复杂度2^n，空间复杂度n
int climbStairs3(int n) {
  if (n < 3)
    return n;
  return climbStairs3(n - 1) + climbStairs3(n - 2);
}

int main() {
  for (int i = 0; i <= 10; i++)
    cout << climbStairs(i) << " ";
  cout << endl;
  for (int i = 0; i <= 10; i++)
    cout << climbStairs1(i) << " ";
  cout << endl;
  return 0;
}