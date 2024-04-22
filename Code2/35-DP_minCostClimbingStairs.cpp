#include "head.h"
/* 746. 使用最小花费爬楼梯
给你一个整数数组 cost ，其中 cost[i] 是从楼梯第 i
个台阶向上爬需要支付的费用。一旦你支付此费用，即可选择向上爬一个或者两个台阶。
你可以选择从下标为 0 或下标为 1 的台阶开始爬楼梯。
请你计算并返回达到楼梯顶部的最低花费。
示例 1：
输入：cost = [10,15,20]
输出：15
解释：你将从下标为 1 的台阶开始。
- 支付 15 ，向上爬两个台阶，到达楼梯顶部。
总花费为 15 。
示例 2：
输入：cost = [1,100,1,1,1,100,1,1,100,1]
输出：6
解释：你将从下标为 0 的台阶开始。
- 支付 1 ，向上爬两个台阶，到达下标为 2 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 4 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 6 的台阶。
- 支付 1 ，向上爬一个台阶，到达下标为 7 的台阶。
- 支付 1 ，向上爬两个台阶，到达下标为 9 的台阶。
- 支付 1 ，向上爬一个台阶，到达楼梯顶部。
总花费为 6 。
 */

// 若题意为，dp[i]代表从i起步，所需要的花费，则初始两步都要花费，最终应返回倒数第一、第二台阶的起步花费最小值
// 若题意为，dp[i]代表到达i所需花费，则初始两步无需花费。最终返回最后一个台阶的再后一步的到达花费
int minCostClimbingStairs(vector<int>& cost) {
  int dp[2] = {0};
  for (int i = 2; i <= cost.size(); i++) {
    int sum = min(dp[1] + cost[i - 1], dp[0] + cost[i - 2]);
    dp[0] = dp[1];
    dp[1] = sum;
  }
  return dp[1];
}

// 题意为，第一步是不花费代价的，最后一步登顶要花费。故dp[i]意为到达第i个台阶的花费。考虑到cost[i]为起步才花费的值
// 可以初始化为dp0和dp1均为0，递归公式为dp[i]=min(dp[i-1]+cost[i],dp[i-2]+cost[i-2])，最终要到达的是dp[cost.size]
int minCostClimbingStairs1(vector<int>& cost) {
  vector<int> dp(cost.size() + 1);
  dp[0] = 0;
  dp[1] = 0;
  for (int i = 2; i <= cost.size(); i++)
    dp[i] = min(cost[i - 1] + dp[i - 1], cost[i - 2] + dp[i - 2]);
  return dp[cost.size()];
}
// 省空间复杂度写法
int minCostClimbingStairs2(vector<int>& cost) {
  int dp0 = 0, dp1 = 0;
  for (int i = 2; i <= cost.size(); i++) {
    int dpi = min(dp0 + cost[i - 2], dp1 + cost[i - 1]);
    dp0 = dp1;
    dp1 = dpi;
  }
  return dp1;
}

// 若题意为，起步需要花费，最后一步到达不花费代价，则最后直接取倒数第一或倒数第二的值
int minCostClimbingStairs3(vector<int>& cost) {
  vector<int> dp(cost.size());
  dp[0] = cost[0];
  dp[1] = cost[1];
  for (int i = 2; i < cost.size(); i++)
    dp[i] = cost[i] + min(cost[i - 1], cost[i - 2]);
  return min(dp[cost.size() - 1], dp[cost.size() - 2]);
}

int main() {
  vector<int> cost1 = {10, 15, 20};
  vector<int> cost2 = {1, 100, 1, 1, 1, 100, 1, 1, 100, 1};
  cout << minCostClimbingStairs(cost1) << " " << minCostClimbingStairs(cost2)
       << " " << endl;
  cout << minCostClimbingStairs1(cost1) << " " << minCostClimbingStairs1(cost2)
       << " " << endl;
  return 0;
}