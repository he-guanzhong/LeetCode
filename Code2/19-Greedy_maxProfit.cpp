#include "head.h"
/* 122. 买卖股票的最佳时机 II
给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多
只能持有一股股票。你也可以先购买，然后在 同一天 出售。返回你能获得的 最大 利润。
示例 1：
  输入：prices = [7,1,5,3,6,4]
  输出：7
  解释：在第 2 天（股票价格 = 1）的时候买入，在第 3 天（股票价格 =5）的时候卖出,
    这笔交易所能获得利润 = 5 - 1 = 4 。 随后，在第 4 天（股票价格 =
    3）的时候买入，在第 5 天（股票价格 = 6）的时候卖出, 这笔交易所能获得利润 =
    6- 3 = 3 。 总利润为 4 + 3 = 7 。 示例 2： 输入：prices = [1,2,3,4,5]
输出：4 解释：在第 1 天（股票价格 = 1）的时候买入，在第 5 天 （股票价格 =
    5）的时候卖出, 这笔交易所能获得利润 = 5 - 1 = 4 。 总利润为 4 。 示例 3：
  输入：prices = [7,6,4,3,1]
  输出：0
  解释：在这种情况下,
    交易无法获得正利润，所以不参与交易可以获得最大利润，最大利润为 0 。*/

int maxProfit(vector<int>& prices) {
  vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
  dp[0][0] = -prices[0];
  for (int i = 1; i < prices.size(); i++) {
    dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
    dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
  }
  return dp[prices.size() - 1][1];
}

// 贪心，初始化为0，相邻两日只要是正利润就收集。也可动态规划，看前一天是否持股，计算今日是否持股获利
// 贪心，把连续几天的利润拆分为多个相邻两天的利润，得到每天的利润数组，只收集正利润，最后即为最大利润
int maxProfit1(vector<int>& prices) {
  int result = 0;
  for (int i = 1; i < prices.size(); i++) {
    result += max(prices[i] - prices[i - 1], 0);
  }
  return result;
}

// 动态规划，分别记第i天持有股票最大现金，无股票最大现金。全部初始化为0，第一天有股票特殊处理
// 自第二天起，有股票现金=前一天有股票+前一天无股票今天买股。无股票现金=前一天无股票+前一天有股票今天卖了
// 最终输出，是否持有股票的最大值
int maxProfit2(vector<int>& prices) {
  vector<vector<int>> dp(prices.size(), vector<int>(2, 0));
  dp[0][0] = -prices[0];  // 第一天持股现金
  int n = prices.size();
  for (int i = 1; i < n; i++) {
    dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
    dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i]);
  }
  return max(dp[n - 1][0], dp[n - 1][1]);
}

int main() {
  vector<int> nums1 = {7, 1, 5, 3, 6, 4};
  vector<int> nums2 = {1, 2, 3, 4, 5};
  vector<int> nums3 = {7, 6, 4, 3, 1};
  cout << maxProfit(nums1) << " " << maxProfit(nums2) << " " << maxProfit(nums3)
       << " " << endl;
  cout << maxProfit1(nums1) << " " << maxProfit1(nums2) << " "
       << maxProfit1(nums3) << " " << endl;
  return 0;
}
