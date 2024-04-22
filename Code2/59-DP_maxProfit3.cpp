#include "head.h"
/* 123. 买卖股票的最佳时机 III
给定一个数组，它的第 i 个元素是一支给定的股票在第 i 天的价格。
设计一个算法来计算你所能获取的最大利润。你最多可以完成 两笔 交易。
注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
示例 1:
输入：prices = [3,3,5,0,0,3,1,4]
输出：6
解释：在第 4 天（股票价格 = 0）的时候买入，在第 6 天（股票价格 =
3）的时候卖出，这笔交易所能获得利润 = 3-0 = 3 。 随后，在第 7 天（股票价格 =
1）的时候买入，在第 8 天 （股票价格 = 4）的时候卖出，这笔交易所能获得利润 = 4-1
= 3 。
示例 2：
输入：prices = [1,2,3,4,5]
输出：4
解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 = 5）的时候卖出,
这笔交易所能获得利润 = 5-1 = 4 。 注意你不能在第 1 天和第 2
天接连购买股票，之后再将它们卖出。
     因为这样属于同时参与了多笔交易，你必须在再次购买前出售掉之前的股票。
示例 3：
输入：prices = [7,6,4,3,1]
输出：0
解释：在这个情况下, 没有交易完成, 所以最大利润为 0。
示例 4：
输入：prices = [1]
输出：0
 */

// 0/1/2/3分别对应第一次持有，不持有，持有，不持有状态。注意允许当天买卖，故只要持有，均初始化为-prices[0]。
// 同理，由于当天允许买卖，故dp[1]第一次不持有，不必上一周期考虑dp[0]，本周期dp[0]也可，因为当天卖买结果为0，无影响
// 最终返回必为第二次不持有dp[3]，因为已经包含了第一次不持有的结果。
int maxProfit(vector<int>& prices) {
  vector<int> dp(4, 0);
  dp[0] = dp[2] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    dp[0] = max(dp[0], -prices[i]);
    dp[1] = max(dp[1], dp[0] + prices[i]);
    dp[2] = max(dp[2], dp[1] - prices[i]);
    dp[3] = max(dp[3], dp[2] + prices[i]);
  }
  return max(dp[1], dp[3]);
}

// dp[i][0~5]记录第i天，第一次买入1，第一次卖出2，第二次买入3，第二次卖出4，四种状态的最大利润额。初始化时，第一次买入和第二次买入，均为-prices[0]
// 递推公式，第一次持有，注意值肯定是-prices[i]。
// 第三次持有为本来就持有，或第一次卖出减去当前股票价格的最大值dp[i][3]=max(dp[i-1][3],dp[i-1][2]-prices[i])
// 第二次卖出，等于本来就不持有，或之前第二次持有，加上本次股票价格dp[i][4]=max(dp[i-1][4],dp[i-1][3]+prices[i])
// 最终返回值，必为第二次不持有值，因为即使第一次不持有最大，也可以当前再次买卖，完成第二次卖出
// 时间复杂度O(n)，空间复杂度O(n*5)
int maxProfit1(vector<int>& prices) {
  vector<vector<int>> dp(prices.size(), vector<int>(5, 0));
  dp[0][1] = -prices[0];
  dp[0][3] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    dp[i][1] = max(dp[i - 1][1], -prices[i]);
    dp[i][2] = max(dp[i - 1][2], dp[i - 1][1] + prices[i]);
    dp[i][3] = max(dp[i - 1][3], dp[i - 1][2] - prices[i]);
    dp[i][4] = max(dp[i - 1][4], dp[i - 1][3] + prices[i]);
  }
  return dp[prices.size() - 1][4];
}

// 节省空间复杂度，O(1)。第i天不持股票dp[2]为i-1天不持股票，或i-1天持股，i天卖出。
int maxProfit2(vector<int>& prices) {
  vector<int> dp(5, 0);
  dp[1] = dp[3] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    dp[1] = max(dp[1], -prices[i]);
    dp[2] = max(dp[2], dp[1] + prices[i]);
    dp[3] = max(dp[3], dp[2] - prices[i]);
    dp[4] = max(dp[4], dp[3] + prices[i]);
  }
  return dp[4];
}
int main() {
  vector<int> nums1 = {3, 3, 5, 0, 0, 3, 1, 4}, nums2 = {1, 2, 3, 4, 5},
              nums3 = {7, 6, 4, 3, 1}, nums4 = {1};
  cout << maxProfit(nums1) << " " << maxProfit(nums2) << " " << maxProfit(nums3)
       << " " << maxProfit(nums4) << endl;
  cout << maxProfit1(nums1) << " " << maxProfit1(nums2) << " "
       << maxProfit1(nums3) << " " << maxProfit1(nums4) << endl;
  return 0;
}