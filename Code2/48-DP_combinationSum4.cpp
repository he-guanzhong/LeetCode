#include "head.h"
/*  377. 组合总和 Ⅳ
给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。请你从 nums
中找出并返回总和为 target 的元素组合的个数。
题目数据保证答案符合 32 位整数范围。
示例 1：
输入：nums = [1,2,3], target = 4
输出：7
解释：
所有可能的组合为：
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)
请注意，顺序不同的序列被视作不同的组合。
示例 2：
输入：nums = [9], target = 3
输出：0*/

// 完全背包，从前向后遍历。求排列数，先遍历容量，再遍历物品。
// 注意，此题在某dp[j]值会大于INT_MAX，故额外条件限制，只计算dp[j]小于INT_MAX的结果
int combinationSum4(vector<int>& nums, int target) {
  vector<int> dp(target + 1, 0);
  dp[0] = 1;
  for (int j = 0; j <= target; j++) {
    for (int i = 0; i < nums.size(); i++) {
      if (j >= nums[i] && dp[j] + dp[j - nums[i]] < INT_MAX)
        dp[j] += dp[j - nums[i]];
    }
  }
  return dp[target];
}

// 完全背包问题，如果求具体排列，必须回溯。但是求数量，可以完全背包，注意外层遍历背包，内层遍历物品
// 由于力扣内部存在两个数相加超过INT_MAX的数据，所以if判断条件要额外加INT_MAX判断
int combinationSum41(vector<int>& nums, int target) {
  vector<int> dp(target + 1, 0);
  dp[0] = 1;
  for (int j = 0; j <= target; j++) {
    for (int i = 0; i < nums.size(); i++) {
      if (j >= nums[i] && dp[j] < INT_MAX - dp[j - nums[i]])
        dp[j] += dp[j - nums[i]];
    }
  }
  return dp[target];
}
int main() {
  int target1 = 4, target2 = 3, target3 = 999;
  vector<int> nums1 = {1, 2, 3};
  vector<int> nums2 = {9};
  vector<int> nums3 = {
      10,  20,  30,  40,  50,  60,  70,  80,  90,  100, 110, 120, 130, 140, 150,
      160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300,
      310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440, 450,
      460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600,
      610, 620, 630, 640, 650, 660, 670, 680, 690, 700, 710, 720, 730, 740, 750,
      760, 770, 780, 790, 800, 810, 820, 830, 840, 850, 860, 870, 880, 890, 900,
      910, 920, 930, 940, 950, 960, 970, 980, 990, 111};
  cout << combinationSum4(nums1, target1) << " "
       << combinationSum4(nums2, target2) << " "
       << combinationSum4(nums3, target3) << endl;
  cout << combinationSum41(nums1, target1) << " "
       << combinationSum41(nums2, target2) << " "
       << combinationSum41(nums3, target3) << endl;
}