#include "head.h"
/* 714. 买卖股票的最佳时机含手续费
给定一个整数数组 prices，其中 prices[i]表示第 i 天的股票价格 ；整数 fee
代表了交易股票的手续费用。
你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。
返回获得利润的最大值。
注意：这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。
示例 1：
输入：prices = [1, 3, 2, 8, 4, 9], fee = 2
输出：8
解释：能够达到的最大利润:
在此处买入 prices[0] = 1
在此处卖出 prices[3] = 8
在此处买入 prices[4] = 4
在此处卖出 prices[5] = 9
总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8
示例 2：
输入：prices = [1,3,7,5,10,3], fee = 3
输出：6
*/

// 动态规划。出时加收手续费。返回时要返回持有与否二者最大值，因为卖出股票可能负收益。
// 贪心算法。
int maxProfit(vector<int>& prices, int fee) {
  vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
  dp[0][0] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
    dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
  }
  return dp[prices.size() - 1][1];
}

// dp[i][0]表示第i天持股现有现金，dp[i][1]表示第i天不持股现有现金。初始化dp[0][0]一开始持股，必为-prices[0]
// 递推公式，相比传统买卖股票，假定卖出股票时要计算手续费，则不持股dp[i][1]=max(dp[i-1][1],dp[i-1][0]+prices[i]-fee)
// 最终的返回值，是持股和不持股最大值，因为有可能持股才是最大值，卖股票有负收益
int maxProfit1(vector<int>& prices, int fee) {
  if (prices.size() == 0)
    return 0;
  vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
  dp[0][0] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
    dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
  }
  return max(dp[prices.size() - 1][1], dp[prices.size() - 1][0]);
}

// 贪心算法。情况一，持有价格在某区间内不动，因为此时卖了就亏。情况二，价格比最低价低，此时买入。情况三、价格更高，收利润
// 收利润时，注意同步更新最低价格，其不是当前股票价格，而是做出-fee的补偿。因为以后在卖的时候，就不用付费了
int maxProfit2(vector<int>& prices, int fee) {
  int result = 0;
  int minPrice = prices[0];
  for (int i = 1; i < prices.size(); i++) {
    if (prices[i] >= minPrice && prices[i] <= minPrice + fee)
      continue;
    else if (prices[i] < minPrice)
      minPrice = prices[i];
    else {
      result += max(prices[i] - minPrice - fee, 0);
      minPrice = prices[i] - fee;
    }
  }
  return result;
}
int main() {
  vector<int> nums1 = {1, 3, 2, 8, 4, 9}, nums2 = {1, 3, 7, 5, 10, 3},
              nums3 = {4, 5, 5, 2, 4, 3, 5, 5, 2, 3}, nums4 = {1};
  int fee1 = 2, fee2 = 3, fee3 = 3, fee4 = 0;
  cout << maxProfit(nums1, fee1) << " " << maxProfit(nums2, fee2) << " "
       << maxProfit(nums3, fee3) << " " << maxProfit(nums4, fee4) << endl;
  cout << maxProfit1(nums1, fee1) << " " << maxProfit1(nums2, fee2) << " "
       << maxProfit1(nums3, fee3) << " " << maxProfit1(nums4, fee4) << endl;
  return 0;
}