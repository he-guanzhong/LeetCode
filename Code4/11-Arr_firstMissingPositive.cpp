#include "head.h"
/* 41. 缺失的第一个正数
给你一个未排序的整数数组 nums ，请你找出其中没有出现的最小的正整数。
请你实现时间复杂度为 O(n) 并且只使用常数级别额外空间的解决方案。
示例 1：
输入：nums = [1,2,0]
输出：3
示例 2：
输入：nums = [3,4,-1,1]
输出：2
示例 3：
输入：nums = [7,8,9,11,12]
输出：1 */

int firstMissingPositive(vector<int>& nums) {
  int sum = 0;
  int n = nums.size();
  for (int& num : nums) {
    if (num <= 0) {
      num = n + 1;
    }
  }
  for (int i = 0; i < nums.size(); i++) {
    int num = abs(nums[i]);
    if (num <= n)
      nums[num - 1] = -abs(nums[num - 1]);
  }
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] > 0)
      return i + 1;
  }
  return n + 1;
}

// 方法一，数组自身哈希表。利用原数组下标i，负号标记数字i+1的有无。一个数组，两套信息。三次遍历，第一步，负数和0，全部标记为N+1。
// 第二步，下标索引后绝对值在[1,n]间的数字num，强制标记下标num-1数字为负，原来为负，仍旧为负。第三步，遍历首次遇到正值时，返回i+1，否则返回n+1
int firstMissingPositive1(vector<int>& nums) {
  int n = nums.size();
  for (int i = 0; i < n; i++) {
    if (nums[i] <= 0)
      nums[i] = n + 1;
  }
  for (int i = 0; i < n; i++) {
    // num记录了索引值的新下标，可能已被改为负，故必先abs
    int num = abs(nums[i]);
    if (num <= n)
      nums[num - 1] = -abs(nums[num - 1]);
  }
  for (int i = 0; i < n; i++) {
    if (nums[i] > 0)
      return i + 1;
  }
  return n + 1;
}

// 推荐方法二，置换。将nums[i]元素换至nums[nums[i]-1]位置。退出条件为二者不相等，或新下标nums[i]-1位置不合法。
// 最终遍历，nums[i]不是i+1，即返回
int firstMissingPositive2(vector<int>& nums) {
  int n = nums.size();
  for (int i = 0; i < n; i++) {
    while (nums[i] > 0 && nums[i] <= n && nums[i] != nums[nums[i] - 1])
      swap(nums[i], nums[nums[i] - 1]);
  }
  for (int i = 0; i < n; i++) {
    if (nums[i] != i + 1)
      return i + 1;
  }
  return n + 1;
}

int main() {
  vector<int> nums1{1, 2, 0}, nums2{3, 4, -1, 1}, nums3{7, 8, 9, 11, 12},
      nums4{1}, nums5{1, 1};
  cout << firstMissingPositive(nums1) << " " << firstMissingPositive(nums2)
       << " " << firstMissingPositive(nums3) << " "
       << firstMissingPositive(nums4) << " " << firstMissingPositive(nums5)
       << endl;
  nums1 = {1, 2, 0}, nums2 = {3, 4, -1, 1}, nums3 = {7, 8, 9, 11, 12},
  nums4 = {1}, nums5 = {1, 1};
  cout << firstMissingPositive1(nums1) << " " << firstMissingPositive1(nums2)
       << " " << firstMissingPositive1(nums3) << " "
       << firstMissingPositive1(nums4) << " " << firstMissingPositive1(nums5)
       << endl;
  return 0;
}