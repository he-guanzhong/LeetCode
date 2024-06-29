#include "head.h"
/* 188. 买卖股票的最佳时机 IV
给你一个整数数组 prices 和一个整数 k ，其中 prices[i] 是某支给定的股票在第 i
天的价格。设计一个算法来计算你所能获取的最大利润。你最多可以完成 k
笔交易。也就是说，你最多可以买 k 次，卖 k 次。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
示例 1：
  输入：k = 2, prices = [2,4,1]
  输出：2
  解释：在第 1 天 (股票价格 = 2) 的时候买入，在第 2 天 (股票价格 = 4)
    的时候卖出，这笔交易所能获得利润 = 4-2 = 2 。
示例 2：
  输入：k = 2, prices = [3,2,6,5,0,3]
  输出：7
  解释：在第 2 天 (股票价格 = 2) 的时候买入，在第 3 天 (股票价格 = 6)
    的时候卖出, 这笔交易所能获得利润 = 6-2 = 4 。 随后，在第 5 天 (股票价格 = 0)
    的时候买入，在第 6 天(股票价格 = 3)的时候卖出,这笔交易所能获得利润=3-0=3。*/

int maxProfit(int k, vector<int>& prices) {
  vector<int> dp(2 * k + 1, INT_MIN);
  dp[0] = 0;
  for (int i = 0; i < prices.size(); i++) {
    for (int j = 1; j <= 2 * k; j += 2) {
      dp[j] = max(dp[j], dp[j - 1] - prices[i]);
      dp[j + 1] = max(dp[j + 1], dp[j] + prices[i]);
    }
  }
  return dp[2 * k];
}

// dp[i][2*j-1]表示第i天，第j次持有股票，所得到的利润。dp[i][2*j]表示第i天，第j次不持股票，得到利润，dp总和为2k+1
// 初始化时，所有奇数j次表示买入了股票，均为-prices[0]，所有偶数位次j表示不持股票，均为0
// 时间复杂度O(n*k)，空间复杂度O(n*k)
int maxProfit1(int k, vector<int>& prices) {
  if (prices.size() == 0)
    return 0;
  vector<vector<int>> dp(prices.size(), vector<int>(2 * k + 1, 0));
  for (int j = 1; j < 2 * k; j += 2)  // 本处2k或2k+1均可
    dp[0][j] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    for (int j = 1; j < 2 * k + 1; j += 2) {
      dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] - prices[i]);
      dp[i][j + 1] = max(dp[i - 1][j + 1], dp[i - 1][j] + prices[i]);
    }
  }
  return dp[prices.size() - 1][2 * k];
}

// 代码统一性，dp[i]表示持有与否的的最大金额。[1,2k]代表第k次持有、不持有的最大金额，不要使用dp[0]。对所有持有的dp[i]均初始化为-prices[0]
// 从第二件物品i=1开始，利用dp[j]对k次持有、不持有情况遍历，每次+=2。最终返回第k次不持有的最大金额。
// 滚动数组节省空间。j不表示第j次买入卖出操作，只表示基本的数值
int maxProfit2(int k, vector<int>& prices) {
  vector<int> dp(k * 2 + 1, 0);
  for (int i = 1; i < 2 * k; i += 2)  // 本处2k或2k+1均可
    dp[i] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    for (int j = 1; j < 2 * k + 1; j += 2) {
      dp[j] = max(dp[j], dp[j - 1] - prices[i]);
      dp[j + 1] = max(dp[j + 1], dp[j] + prices[i]);
    }
  }
  return dp[2 * k];
}

int main() {
  int k1 = 2, k2 = 2, k3 = 2, k4 = 2;
  vector<int> nums1 = {2, 4, 1}, nums2 = {3, 2, 6, 5, 0, 3},
              nums3 = {7, 6, 4, 3, 1}, nums4 = {1};
  cout << maxProfit(k1, nums1) << " " << maxProfit(k2, nums2) << " "
       << maxProfit(k3, nums3) << " " << maxProfit(k4, nums4) << endl;
  cout << maxProfit1(k1, nums1) << " " << maxProfit1(k2, nums2) << " "
       << maxProfit1(k3, nums3) << " " << maxProfit1(k4, nums4) << endl;
  return 0;
}