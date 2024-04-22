#include "head.h"
/* 122. 买卖股票的最佳时机 II
给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股
股票。你也可以先购买，然后在 同一天 出售。 返回 你能获得的 最大 利润 。
示例 1：
输入：prices = [7,1,5,3,6,4]
输出：7
解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 = 5）的时候卖出,
这笔交易所能获得利润 = 5 - 1 = 4 。 随后，在第 4 天（股票价格 =
3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 = 6 - 3
= 3 。 总利润为 4 + 3 = 7 。
示例 2： 输入：prices = [1,2,3,4,5] 输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出,
这笔交易所能获得利润 = 5 - 1 = 4 。 总利润为 4 。
示例 3： 输入：prices =
[7,6,4,3,1] 输出：0 解释：在这种情况下,
交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0 。 */

// 优选贪心，相邻两天相减，收集所有正利润。
// 动态规划。该天持有股票最大利润dp[0]等于前一天即持有，或前一天不持有当天买入的最大值。dp[1]亦然。
// 滚动数组，无需临时保存dp[0]，因为允许当天买卖，对结果无影响。
int maxProfit(vector<int>& prices) {
  vector<int> dp(2, 0);
  dp[0] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    dp[0] = max(dp[0], dp[1] - prices[i]);
    dp[1] = max(dp[1], dp[0] + prices[i]);
  }
  return dp[1];
}

// 动态规划。dp[0][0]代表第0天持有股票，则初始化为负数。dp[0][1]代表第0天不持股。空间复杂度O(n)，空间复杂度O(n)
// 注意此题与前提区别，股票可以买卖多次，故第i天持股，dp[i][0]考虑当天买入股票-prices[i]时，前一天不持股dp[i-1][1]可能有利润
// 而前一题由于只能买卖一次，故之前不可能有不持股的利润，所以此处公式不同。
int maxProfit1(vector<int>& prices) {
  vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
  dp[0][0] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
    dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
  }
  return dp[prices.size() - 1][1];
}

// 滚动数组节省资源。空间复杂度O(n)，空间复杂度O(1)
int maxProfit2(vector<int>& prices) {
  vector<int> dp(2, 0);
  dp[0] = -prices[0];
  for (int i = 0; i < prices.size(); i++) {
    int hold = dp[0];
    int unhold = dp[1];
    dp[0] = max(dp[0], unhold - prices[i]);
    dp[1] = max(dp[1], hold + prices[i]);
  }
  return dp[1];
}

// 贪心。第三天利润等于第一天和第二天利润和。故只要是每隔一天是正利润，就计入结果。时间复杂度O(n)
int maxProfit3(vector<int>& prices) {
  int result = 0;
  for (int i = 1; i < prices.size(); i++) {
    if (prices[i] > prices[i - 1])
      result += prices[i] - prices[i - 1];
  }
  return result;
}

int main() {
  vector<int> nums1 = {7, 1, 5, 3, 6, 4}, nums2 = {1, 2, 3, 4, 5},
              nums3 = {7, 6, 4, 3, 1}, nums4 = {0, 0};
  cout << maxProfit(nums1) << " " << maxProfit(nums2) << " " << maxProfit(nums3)
       << " " << maxProfit(nums4) << endl;
  cout << maxProfit1(nums1) << " " << maxProfit1(nums2) << " "
       << maxProfit1(nums3) << " " << maxProfit1(nums4) << endl;
  return 0;
}