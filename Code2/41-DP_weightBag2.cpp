#include "head.h"
/* 0-1背包问题
一维滚动数组。必须背包从右向左遍历，因为要利用原始的左上角信息 */

int weightBag(vector<int>& weight, vector<int>& value, int bagweight) {
  vector<int> dp(bagweight + 1, 0);
  for (int i = 0; i < weight.size(); i++) {
    for (int j = bagweight; j >= weight[i]; j--)
      dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
  }
  return dp[bagweight];
}

// 一维滚动数组记录背包重量j内元素的最大值。必须先遍历物品，再遍历重量，不能颠倒。
// 背包一定要从后向前遍历，否则dp[j]记录的是i更新后的数据，而不是i-1的数据。造成元素重复叠加
int weightBag1(vector<int>& weight, vector<int>& value, int bagweight) {
  vector<int> dp(bagweight + 1, 0);
  for (int i = 0; i < weight.size(); i++) {
    for (int j = bagweight; j >= weight[i]; j--) {
      dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
    }
  }
  return dp[bagweight];
}

int main() {
  vector<int> weight = {1, 3, 4};
  vector<int> value = {15, 20, 30};
  int bagweight = 4;
  cout << weightBag(weight, value, bagweight) << endl;
  cout << weightBag1(weight, value, bagweight) << endl;
  return 0;
}
