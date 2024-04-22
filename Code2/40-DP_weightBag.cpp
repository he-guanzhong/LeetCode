#include "head.h"
// 0-1背包问题，总重bagweight的背包，可以内装物品质量weight，价值value的若干物品，每样物品只能取一次。问如何装价值最大

int weightBag(vector<int> &weight, vector<int> &value, int bagweight) {
  vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));
  for (int i = weight[0]; i <= bagweight; i++)
    dp[0][i] = value[0];
  for (int i = 1; i < weight.size(); i++) {
    for (int j = 0; j <= bagweight; j++) {
      if (j < weight[i])
        dp[i][j] = dp[i - 1][j];
      else
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
    }
  }
  return dp[weight.size() - 1][bagweight];
}

// dp[i][j]代表，从0-i个物品中任选，在j重量背包下能取得的最大价值。
// 递推公式为dp[i][j]=max(dp[i-1][j],dp[i-1][j-weight[i]]+value[i])。
// 即i新价值为，不放物品i即i质量过大，dp[i-1][j]的值。和放物品i，刨去weight[i]的总价值加i的价值value[i]。取二者的最大值
// 初始化时，首行即物品0放与不放的价值。背包j<weight[0]时放不进去，价值必为0。否则可以放进去，等于价值value[0]
// 遍历方向为先遍历物品，再遍历背包大小。注意如果背包质量j小于物品i质量，必放不进去，则直接等于不放i的值dp[i-1][j]
int weightBag1(vector<int> &weight, vector<int> &value, int bagweight) {
  vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));
  for (int j = weight[0]; j <= bagweight; j++)
    dp[0][j] = value[0];
  for (int i = 1; i < weight.size(); i++) {
    for (int j = 0; j <= bagweight; j++) {
      if (j < weight[i])
        dp[i][j] = dp[i - 1][j];
      else
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
    }
  }
  return dp[weight.size() - 1][bagweight];
}
int main() {
  vector<int> weight = {1, 3, 4};
  vector<int> value = {15, 20, 30};
  int bagweight = 4;
  cout << weightBag(weight, value, bagweight) << endl;
  cout << weightBag1(weight, value, bagweight) << endl;
}