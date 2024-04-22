#include "head.h"
/* 309. 买卖股票的最佳时机含冷冻期
给定一个整数数组prices，其中第  prices[i] 表示第 i 天的股票价格
。​
设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:
    卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
示例 1:
输入: prices = [1,2,3,0,2]
输出: 3
解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]
示例 2:
输入: prices = [1]
输出: 0
 */

// dp[j]表示，1为持有，2为卖出，3为卖出冷冻，4为不持有不冷冻。注意持有，分三种情况，昨天就持有，昨天不冷冻今天买入，昨天冷冻今天买入。
int maxProfit(vector<int>& prices) {
  vector<vector<int>> dp(prices.size(), vector<int>(5, 0));
  dp[0][1] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    dp[i][1] =
        max({dp[i - 1][1], dp[i - 1][4] - prices[i], dp[i - 1][3] - prices[i]});
    dp[i][2] = dp[i - 1][1] + prices[i];
    dp[i][3] = dp[i - 1][2];
    dp[i][4] = max(dp[i - 1][4], dp[i - 1][3]);
  }
  return max({dp[prices.size() - 1][2], dp[prices.size() - 1][3],
              dp[prices.size() - 1][4]});
}

// 标准解法，dp[i][j]表示第i天第j状态的最大利润。dp[i][0]为持股，dp[i][1]为不持股不冷冻，dp[i][2]为当天卖出，dp[i][3]为冷冻期
// 初始化，dp[0][0]当天持股，利润为-prices[0]。其余三种情况都不持股，均为0
// 递推公式。持股，dp[i][0]为昨天就持股，或昨天不持股不冷冻+今日股价的成本，或者冷冻+今日股价的成本。三者最大值
// 不持股且不冷冻，dp[i][1]为昨天就如此，或昨天冷冻了
// 当天卖出，dp[i][2]为昨天持股加当日股价利润。今天冷冻期，dp[i][3]为昨日刚卖过股票
// 最终输出最大利润为，不是持股的三种情况，最大值
int maxProfit1(vector<int>& prices) {
  if (prices.size() == 0)
    return 0;
  vector<vector<int>> dp(prices.size(), vector<int>(4, 0));
  dp[0][0] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][1], dp[i - 1][3]) - prices[i]);
    dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
    dp[i][2] = dp[i - 1][0] + prices[i];
    dp[i][3] = dp[i - 1][2];
  }
  return max(dp[prices.size() - 1][1],
             max(dp[prices.size() - 1][2], dp[prices.size() - 1][3]));
}
// 自己解法，将前两天的情况独立出来。从第三天开始计算，第i天持股值dp[i][1]一定是上一天也持股dp[i-1][1]和前天不持股，今天买入的最大值
int maxProfit2(vector<int>& prices) {
  if (prices.size() < 2)
    return 0;
  vector<vector<int>> dp(prices.size(), vector<int>(3, 0));
  dp[0][1] = -prices[0];
  dp[1][1] = max(dp[0][1], -prices[1]);
  dp[1][2] = max(dp[0][2], dp[0][1] + prices[1]);
  for (int i = 2; i < prices.size(); i++) {
    dp[i][1] = max(dp[i - 1][1], dp[i - 2][2] - prices[i]);
    dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
  }
  return dp[prices.size() - 1][2];
}

int main() {
  vector<int> nums1 = {1, 2, 3, 0, 2}, nums2 = {1}, nums3 = {7, 6, 4, 3, 1},
              nums4 = {1};
  cout << maxProfit(nums1) << " " << maxProfit(nums2) << " " << maxProfit(nums3)
       << " " << maxProfit(nums4) << endl;
  cout << maxProfit1(nums1) << " " << maxProfit1(nums2) << " "
       << maxProfit1(nums3) << " " << maxProfit1(nums4) << endl;
  return 0;
}