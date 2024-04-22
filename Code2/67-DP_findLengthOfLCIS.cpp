#include "head.h"
/* 674. 最长连续递增序列
给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。
连续递增的子序列 可以由两个下标 l 和 r（l < r）确定，如果对于每个 l <= i <
r，都有 nums[i] < nums[i + 1] ，那么子序列 [nums[l], nums[l + 1], ..., nums[r -
1], nums[r]] 就是连续递增子序列。
示例 1：
输入：nums = [1,3,5,4,7]
输出：3
解释：最长连续递增序列是 [1,3,5], 长度为3。
尽管 [1,3,5,7] 也是升序的子序列, 但它不是连续的，因为 5 和 7 在原数组里被 4
隔开。
示例 2：
输入：nums = [2,2,2,2,2]
输出：1
解释：最长连续递增序列是 [2], 长度为1。 */

// 连续递增子序列，只和前一个元素有关。最长递增子序列，和前面所有元素都有关。dp[i]表示以i结尾递增子序列长度，故需额外int保存最大值
// 贪心算法。使用一个count计数连续递增的次数，否则置1，节省了空间复杂度
int findLengthOfLCIS(vector<int>& nums) {
  int cnt = 1;
  int result = 1;
  for (int i = 1; i < nums.size(); i++) {
    if (nums[i] > nums[i - 1])
      cnt++;
    else
      cnt = 1;
    result = max(result, cnt);
  }
  return result;
}

// dp[i]表示以nums[i]结尾的连续递增子序列长度。默认初始长度均初始化为1
// 递推公式，比较相邻元素，nums[i]>nums[i-1]则dp[i]=dp[i-1]+1。因为其只和前一个元素有关，而不连续子序列，和前面所有元素都有关
// 时间复杂度O(n)=n,空间复杂度O(n)=n
int findLengthOfLCIS1(vector<int>& nums) {
  if (nums.size() == 0)
    return 0;
  vector<int> dp(nums.size(), 1);
  int result = 1;  // 注意，此处连续递增子序列，最短也是1
  for (int i = 1; i < nums.size(); i++) {
    if (nums[i] > nums[i - 1])
      dp[i] = max(dp[i], dp[i - 1] + 1);
    result = max(result, dp[i]);
  }
  return result;
}

// 贪心。对比相邻元素，如果nums[i]>nums[i-1]则count++，否则就返回count=1。记录最大值
int findLengthOfLCIS2(vector<int>& nums) {
  int count = 1, result = 1;
  for (int i = 1; i < nums.size(); i++) {
    if (nums[i] > nums[i - 1])
      count++;
    else
      count = 1;
    result = max(count, result);
  }
  return result;
}
int main() {
  vector<int> nums1 = {1, 3, 5, 4, 7}, nums2 = {2, 2, 2, 2, 2},
              nums3 = {10, 9, 2, 5, 3, 7, 101, 18};
  cout << findLengthOfLCIS(nums1) << " " << findLengthOfLCIS(nums2) << " "
       << findLengthOfLCIS(nums3) << endl;
  cout << findLengthOfLCIS1(nums1) << " " << findLengthOfLCIS1(nums2) << " "
       << findLengthOfLCIS1(nums3) << endl;
  return 0;
}