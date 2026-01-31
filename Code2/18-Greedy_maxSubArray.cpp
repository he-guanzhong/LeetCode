#include "head.h"
/* 53. 最大子数组和
给你一个整数数组 nums
，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
子数组 是数组中的一个连续部分。
示例 1：
  输入：nums = [-2,1,-3,4,-1,2,1,-5,4]
  输出：6
  解释：连续子数组 [4,-1,2,1] 的和最大，为 6 。
示例 2：
  输入：nums = [1]
  输出：1
示例 3：
  输入：nums = [5,4,-1,7,8]
  输出：23 */

int maxSubArray(vector<int>& nums) {
  int ans = nums[0];
  vector<int> dp(nums.size(), nums[0]);
  for (int i = 1; i < nums.size(); i++) {
    dp[i] = max(nums[i], nums[i] + dp[i - 1]);
    ans = max(dp[i], ans);
  }
  return ans;
}

// 先判空，pre记录此下标时，最长连续子数组和，如果此前pre有正增益，则pre+i，如果此前pre为负增益，则舍弃pre取i
// 额外的result记录整个数组的最长连续子数组和，初始化不能为0，而为首元素，或者INT_MIN
// 传统方法，动态规划。pre记录此前是否为负，产生负面影响。并时刻记录最大值
int maxSubArray1(vector<int>& nums) {
  int maxValue = nums[0];
  int pre = 0;
  for (int i = 0; i < nums.size(); i++) {
    pre = max(nums[i], pre + nums[i]);
    maxValue = max(maxValue, pre);
  }
  return maxValue;
}

// 动态规划。dp记录包括i的此前最大子序列和
int maxSubArray3(vector<int>& nums) {
  vector<int> dp(nums.size(), 0);
  dp[0] = nums[0];
  int result = dp[0];
  for (int i = 1; i < nums.size(); i++) {
    dp[i] = max(dp[i - 1] + nums[i], nums[i]);
    result = max(result, dp[i]);
  }
  return result;
}

// 局部最优为连续和为正，count累计和，取最大值计入result
// 一旦发现count为负则立刻置零，因为会对后续产生负面影响。
int maxSubArray2(vector<int>& nums) {
  int result = INT_MIN;
  int count = 0;
  for (int i = 0; i < nums.size(); i++) {
    count += nums[i];
    result = max(count, result);
    count = max(count, 0);
  }
  return result;
}

int main() {
  vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
  vector<int> nums2 = {1};
  vector<int> nums3 = {5, 4, -1, 7, 8};
  vector<int> nums4 = {-1};
  cout << maxSubArray(nums1) << " " << maxSubArray(nums2) << " "
       << maxSubArray(nums3) << " " << maxSubArray(nums4) << endl;
  cout << maxSubArray1(nums1) << " " << maxSubArray1(nums2) << " "
       << maxSubArray1(nums3) << " " << maxSubArray1(nums4) << endl;
  return 0;
}