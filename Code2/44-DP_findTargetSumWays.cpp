#include "head.h"
/* 494. 目标和
给你一个非负整数数组 nums 和一个整数 target 。
向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：
    例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-'
，然后串联起来得到表达式 "+2-1" 。
返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。
示例 1：
  输入：nums = [1,1,1,1,1], target = 3
  输出：5
  解释：一共有 5 种方法让最终目标和为 3 。
  -1 + 1 + 1 + 1 + 1 = 3
  +1 - 1 + 1 + 1 + 1 = 3
  +1 + 1 - 1 + 1 + 1 = 3
  +1 + 1 + 1 - 1 + 1 = 3
  +1 + 1 + 1 + 1 - 1 = 3
示例 2：
  输入：nums = [1], target = 1
  输出：1  */

int findTargetSumWays(vector<int>& nums, int target) {
  int sum = accumulate(nums.begin(), nums.end(), 0);
  if (abs(target) > sum || (target + sum) % 2 == 1)
    return 0;
  int n = (sum + target) / 2;
  vector<int> dp(n + 1, 0);
  dp[0] = 1;
  for (int i = 0; i < nums.size(); i++) {
    for (int j = n; j >= nums[i]; j--) {
      dp[j] += dp[j - nums[i]];
    }
  }
  return dp[n];
}

// 回溯算法，改为已知负数一堆的总和为(sum-target)/2组合问题。注意排除两种意外情况，一是全为负也不行，即abs(target)>sum，二是sum-target为奇数.
// 01背包，分正负两堆,已知和差。问题转化为已知正数堆和为背包总重，求填满背包种类数。dp[j]为重j背包填满的方法数。dp[j]+=dp[j-nums[i]]
// 关键在于将所有元素总和分成left和right两堆，之和sum已知，两堆之差target已知。则left=(sum+target)/2，其必不可能为小数
// 问题转化为在一系列元素中，已知某部分总和，求组合问题，可以使用回溯
vector<vector<int>> result1;
vector<int> path1;
void backtracking1(vector<int>& nums, int target, int sum, int startIndex) {
  if (sum == target)
    result1.push_back(path1);
  for (int i = startIndex; i < nums.size() && sum + nums[i] <= target; i++) {
    sum += nums[i];
    path1.push_back(nums[i]);
    backtracking1(nums, target, sum, i + 1);
    sum -= nums[i];
    path1.pop_back();
  }
}

int findTargetSumWays1(vector<int>& nums, int target) {
  int sum = accumulate(nums.begin(), nums.end(), 0);
  if (target > sum)  // 差比总和还大，不可能
    return 0;
  if ((sum + target) % 2 == 1)  // left部分是小数，不可能
    return 0;
  int bagSize = (sum + target) / 2;
  result1.clear();
  path1.clear();
  sort(nums.begin(), nums.end());
  backtracking1(nums, bagSize, 0, 0);
  return result1.size();
}

// 先排除两种必不可能分的情况。即左右两堆差值大于总和和左堆数量不是整数。
// 左堆的数量即背包容量。dp[j]表示填满j大小的包，总共几种方法。显然填满dp[0]只有一种办法。初始化dp[0]=1
// 已经有nums[i]这个元素选定后，还剩余空间被填满方法是dp[j-nums[i]]种。递推公式dp[j]+=dp[j-nums[i]]
// 遍历顺序，nums[i]放在外循环，包的容量放在内循环，且必需倒序
int findTargetSumWays2(vector<int>& nums, int target) {
  int sum = accumulate(nums.begin(), nums.end(), 0);
  if (abs(target) > sum)  // 最大差值比总和还大，不可能
    return 0;
  if ((sum - target) % 2 == 1)
    return 0;
  int bagSize = (sum - target) / 2;
  vector<int> dp(bagSize + 1, 0);
  dp[0] = 1;  // 初始化一定是设为1
  for (int i = 0; i < nums.size(); i++) {
    for (int j = bagSize; j >= nums[i]; j--)
      dp[j] += dp[j - nums[i]];
  }
  return dp[bagSize];
}

int main() {
  vector<int> nums1 = {1, 1, 1, 1, 1};
  vector<int> nums2 = {1};
  int target1 = 3, target2 = 1;
  cout << findTargetSumWays(nums1, target1) << " "
       << findTargetSumWays(nums2, target2) << endl;
  cout << findTargetSumWays2(nums1, target1) << " "
       << findTargetSumWays2(nums2, target2) << endl;
  return 0;
}