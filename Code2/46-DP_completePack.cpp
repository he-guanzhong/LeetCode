#include "head.h"
/* 完全背包问题
背包重量bagweight，有i件物品，其重量weight[i]，价值是value[i]，所有物品可以重复取，问最多能有多少价值
*/

int completePack(vector<int>& weight, vector<int>& value, int bagweight) {
  vector<int> dp(bagweight + 1, 0);
  for (int i = 0; i < weight.size(); i++) {
    for (int j = weight[i]; j <= bagweight; j++)
      dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
  }
  return dp[bagweight];
}

// 与01背包不同，dp[j]表示j容量内的最大价值。遍历背包重量顺序是从前至后，且先遍历物品还是容量均可，但一定是从背包容量大于该物品开始递推
// 先遍历物品，再遍历重量
int completePack1(vector<int>& weight, vector<int>& value, int bagweight) {
  vector<int> dp(bagweight + 1, 0);
  for (int i = 0; i < weight.size(); i++) {
    for (int j = weight[i]; j <= bagweight; j++)
      dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
  }
  return dp[bagweight];
}

// 同样，也可以先遍历重量，再遍历物品
int completePack2(vector<int>& weight, vector<int>& value, int bagweight) {
  vector<int> dp(bagweight + 1, 0);
  for (int j = 0; j <= bagweight; j++) {
    for (int i = 0; i < weight.size(); i++)
      if (j >= weight[i])
        dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
  }
  return dp[bagweight];
}

int main() {
  vector<int> weight = {1, 3, 4};
  vector<int> value = {15, 20, 30};
  int bagweight = 4;
  cout << completePack(weight, value, bagweight) << endl;
  cout << completePack1(weight, value, bagweight) << endl;
  return 0;
}