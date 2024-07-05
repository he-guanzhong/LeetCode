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
  输出：23   */

int maxSubArray(vector<int>& nums) {
  int dp[2] = {0, 0};
  int ans = 0;
  for (int i = 0; i < nums.size(); i++) {
    dp[1] = max(nums[i], dp[0] + nums[i]);
    dp[0] = dp[1];
    ans = max(ans, dp[1]);
  }
  return ans;
}

// 动态规划。dp[i]代表以nums[i]为结尾的连续子数组最大和。则dp[0]=nums[0]。
// 递推公式，如果前面总和为负作用，则dp[i]=nums[i]，如果前面有正作用dp[i]=dp[i-1]+nums[i]
// 注意最终返回的最大值，不一定是dp[nums.size()-1]，因为只是以nums[i]为结尾的子数组最大和
int maxSubArray1(vector<int>& nums) {
  vector<int> dp(nums.size(), 0);
  int result = nums[0];
  dp[0] = nums[0];
  for (int i = 1; i < nums.size(); i++) {
    dp[i] = max(nums[i], nums[i] + dp[i - 1]);
    result = max(dp[i], result);
  }
  return result;
}

// 贪心，返回结果，一定初始化为首元素值，不能为0。保存到i前最大子数组pre，如果其为负即舍弃，为正即相加。返回值根据pre实时更新
// 动态规划。dp[i]表示以i结尾的连续子数组和最大值，不一定在最后一个元素。dp[i]基础为nums[i]，是否加dp[i-1]取决于其是否为正
int maxSubArray2(vector<int>& nums) {
  int result = nums[0];
  int pre = 0;
  for (int i = 0; i < nums.size(); i++) {
    pre = max(nums[i], nums[i] + pre);
    result = max(pre, result);
  }
  return result;
}

int main() {
  vector<int> nums1 = {-2, 1, -3, 4, -1, 2, 1, -5, 4}, nums2 = {1},
              nums3 = {5, 4, -1, 7, 8};
  cout << maxSubArray(nums1) << " " << maxSubArray(nums2) << " "
       << maxSubArray(nums3) << endl;
  cout << maxSubArray1(nums1) << " " << maxSubArray1(nums2) << " "
       << maxSubArray1(nums3) << endl;
  return 0;
}