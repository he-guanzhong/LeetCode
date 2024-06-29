#include "head.h"

/* 多重背包。有N种物品和一个容量为V的背包。第i种物品最多有Mi件可用，每件耗费的空间是Ci，价值是Wi。
求解将哪些物品装入背包可使这些物品的耗费的空间，总和不超过背包容量，且价值总和最大。
每个物品是有限的，可以转化为01背包问题 */
int multiPack(vector<int>& weight,
              vector<int>& value,
              vector<int>& nums,
              int bagWeight) {
  vector<int> dp(bagWeight + 1, 0);
  for (int i = 0; i < weight.size(); i++) {
    for (int k = 0; k < nums[i]; k++) {
      for (int j = bagWeight; j >= weight[i]; j--) {
        dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
      }
    }
  }
  return dp[bagWeight];
}

// 多重背包，已经每个物品的存在个数，价值、重量，求整体总重bagWeight的背包，最大能乘早的价值是多少
// 讲物品存在的个数展开，转化为01背包问题求解。先遍历物品，再从后向前遍历背包
// 时间复杂度，m*n*k。
int multiPack1(vector<int>& weight,
               vector<int>& value,
               vector<int>& nums,
               int bagWeight) {
  for (int i = 0; i < nums.size(); i++) {
    while (nums[i] > 1) {  // 此处必须先保留到1
      weight.push_back(weight[i]);
      value.push_back(value[i]);
      nums[i]--;
    }
  }
  vector<int> dp(bagWeight + 1, 0);
  for (int i = 0; i < weight.size(); i++) {
    for (int j = bagWeight; j >= weight[i]; j--)
      dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
  }
  return dp[bagWeight];
}

// 解法超时，原因是vector动态扩容。可以直接在遍历中展开k项
int multiPack2(vector<int>& weight,
               vector<int>& value,
               vector<int>& nums,
               int bagWeight) {
  vector<int> dp(bagWeight + 1, 0);
  for (int i = 0; i < weight.size(); i++) {
    for (int j = bagWeight; j >= weight[i]; j--) {
      for (int k = 1; k <= nums[i] && j - weight[i] * k >= 0; k++) {
        dp[j] = max(dp[j], dp[j - weight[i] * k] + value[i] * k);
      }
    }
  }
  return dp[bagWeight];
}

int main() {
  vector<int> weight = {1, 3, 4};
  vector<int> value = {15, 20, 30};
  vector<int> nums = {2, 3, 2};
  int bagWeight = 10;
  cout << multiPack(weight, value, nums, bagWeight) << endl;
  cout << multiPack2(weight, value, nums, bagWeight) << endl;
  return 0;
}