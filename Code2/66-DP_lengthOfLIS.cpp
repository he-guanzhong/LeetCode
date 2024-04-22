#include "head.h"
/* 300. 最长递增子序列
给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
子序列
是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其余元素的顺序。例如，[3,6,2,7]
是数组 [0,3,1,6,2,2,7] 的子序列。
示例 1：
输入：nums = [10,9,2,5,3,7,101,18]
输出：4
解释：最长递增子序列是 [2,3,7,101]，因此长度为 4 。
示例 2：
输入：nums = [0,1,0,3,2,3]
输出：4
示例 3：
输入：nums = [7,7,7,7,7,7,7]
输出：1
 */

// dp[i]表示以i结尾的最长递增子序列长度，故最长递增子序列，不一定是dp[n-1]。需要中间值保存最大值
// 一个元素最长递增子序列长度也是1，故全部dp和res均初始化为1。
// 递推公式，使用j遍历[0,i-1]，一旦发现nums[i]>nums[j]，则dp[i]=max(dp[i],dp[j]+1)
int lengthOfLIS(vector<int>& nums) {
  vector<int> dp(nums.size(), 1);
  int result = 1;
  for (int i = 1; i < nums.size(); i++) {
    for (int j = 0; j < i; j++) {
      if (nums[j] < nums[i])
        dp[i] = max(dp[i], dp[j] + 1);
    }
    result = max(result, dp[i]);
  }
  return result;
}

// dp[i]表示以字母nums[i]为结尾的最长递增子序列数。故最大子序列数不一定是最后dp[last-1]。
// 首先排除只有1个元素影响。只要里面存在元素，最长递增子序列数至少为1，故所有都位置都初始化为1
// 递推公式，dp[i]元素为，从0~i-1中挑出的j元素，只要其结尾nums[j]<nums[i]即可构成子序列，子序列数+1，则dp[i]=max(dp[i],dp[j]+1)
// 从前向后遍历过程中，随时记录最大的dp[i]，作为结果，时间复杂度O(n)=n^2，空间复杂度O(n)=n
int lengthOfLIS1(vector<int>& nums) {
  if (nums.size() == 1)
    return 1;
  vector<int> dp(nums.size(), 1);
  int result = 0;
  for (int i = 1; i < nums.size(); i++) {
    for (int j = 0; j < i; j++) {
      if (nums[j] < nums[i])
        dp[i] = max(dp[i], dp[j] + 1);
    }
    result = max(result, dp[i]);
  }
  return result;
}
int main() {
  vector<int> nums1 = {10, 9, 2, 5, 3, 7, 101, 18}, nums2 = {0, 1, 0, 3, 2, 3},
              nums3 = {7, 7, 7, 7, 7, 7, 7};
  cout << lengthOfLIS(nums1) << " " << lengthOfLIS(nums2) << " "
       << lengthOfLIS(nums3) << endl;
  cout << lengthOfLIS1(nums1) << " " << lengthOfLIS1(nums2) << " "
       << lengthOfLIS1(nums3) << endl;
  return 0;
}