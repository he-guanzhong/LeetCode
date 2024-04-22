#include "head.h"
/* 121. 买卖股票的最佳时机
给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子
卖出该股票。设计一个算法来计算你所能获取的最大利润。
返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
示例 1：
输入：[7,1,5,3,6,4]
输出：5
解释：在第 2 天（股票价格 = 1）的时候买入，在第 5 天（股票价格 =
6）的时候卖出，最大利润 = 6-1 = 5 。 注意利润不能是 7-1 = 6,
因为卖出价格需要大于买入价格；同时，你不能在买入前卖出股票。
示例 2：
输入：prices = [7,6,4,3,1]
输出：0
解释：在这种情况下, 没有交易完成, 所以最大利润为 0。
 */

// 贪心，只能买卖一次。实时记录最小值出现位置，实时计算当前价格与最小值的差，输入最大值。
// 动态规划，当天持有，等于前一天就持有，或者今天第一次直接买入，二者最大值。当天不持有，等于前一天就不持有，或者今天卖出，二者最大值。
int maxProfit(vector<int>& prices) {
  vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
  dp[0][0] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    dp[i][0] = max(dp[i - 1][0], -prices[i]);
    dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
  }
  return dp[prices.size() - 1][1];
}

// 动态规划，dp[i][0]表示第i天持有股票钱数，dp[i][1]表示第i天不持有股票钱。初始化dp[0][0]为首天价格负数。dp[0][1]为0。
// 递推公式。第i天持有股票，分i-1天就不持有，或i天买入两种情况。第i天不持股，分i-1天就不持股，或i天卖出（第i-1天持有+i天股票价值）两种情况。分别取其最大值
// 最终输入，比是最后一天不持股的情况，因为股票价格为正，卖出必挣钱。
// 时间复杂度n，空间复杂度n。
int maxProfit1(vector<int>& prices) {
  vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
  dp[0][0] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    dp[i][0] = max(dp[i - 1][0], -prices[i]);
    dp[i][1] = max(dp[i - 1][1], prices[i] + dp[i - 1][0]);
  }
  return dp[prices.size() - 1][1];
}

// 滚动数组可以节省空间。时间复杂度n，空间复杂度1
int maxProfit2(vector<int>& prices) {
  vector<int> dp(2, 0);
  dp[0] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    int tmp = dp[0];
    dp[0] = max(dp[0], -prices[i]);
    dp[1] = max(dp[1], prices[i] + tmp);
  }
  return dp[1];
}

// 贪心。最大收益就是从左往右遍历，找到当前最小值。同时计算该起点继续遍历找到的，最大值差值。时间复杂度n，空间复杂度1
int maxProfit3(vector<int>& prices) {
  int result = 0;
  int low = INT_MAX;
  for (int i = 0; i < prices.size(); i++) {
    low = min(prices[i], low);
    result = max(result, prices[i] - low);
  }
  return result;
}

// 只能买卖一次，故暴力搜索法。时间复杂度n^2，空间复杂度1
int maxProfit4(vector<int>& prices) {
  int result = 0;
  for (int i = 0; i < prices.size(); i++) {
    for (int j = i + 1; j < prices.size(); j++) {
      result = max(result, prices[j] - prices[i]);
    }
  }
  return result;
}

int main() {
  vector<int> nums1 = {7, 1, 5, 3, 6, 4}, nums2 = {7, 6, 4, 3, 1},
              nums3 = {1, 2, 3}, nums4 = {0, 0};
  cout << maxProfit(nums1) << " " << maxProfit(nums2) << " " << maxProfit(nums3)
       << " " << maxProfit(nums4) << endl;
  cout << maxProfit1(nums1) << " " << maxProfit1(nums2) << " "
       << maxProfit1(nums3) << " " << maxProfit1(nums4) << endl;
  return 0;
}