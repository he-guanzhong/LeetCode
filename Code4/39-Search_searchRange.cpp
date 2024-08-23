#include "head.h"
/* 34. 在排序数组中查找元素的第一个和最后一个位置
给你一个按照非递减顺序排列的整数数组 nums，和一个目标值
target。请你找出给定目标值在数组中的开始位置和结束位置。
如果数组中不存在目标值 target，返回 [-1, -1]。
你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。
示例 1：
  输入：nums = [5,7,7,8,8,10], target = 8
  输出：[3,4]
示例 2：
  输入：nums = [5,7,7,8,8,10], target = 6
  输出：[-1,-1]
示例 3：
  输入：nums = [], target = 0
  输出：[-1,-1] */

int helper(vector<int>& nums, int target, bool first) {
  int left = 0, right = nums.size() - 1;
  while (left <= right) {
    int mid = left + ((right - left) >> 1);
    if (nums[mid] > target || nums[mid] == target && first)
      right = mid - 1;
    else
      left = mid + 1;
  }
  return first ? left : right;
}
vector<int> searchRange(vector<int>& nums, int target) {
  int l = helper(nums, target, 1);
  int r = helper(nums, target, 0);
  l = l >= 0 && l < nums.size() && nums[l] == target ? l : -1;
  r = r >= 0 && r < nums.size() && nums[r] == target ? r : -1;
  return {l, r};
}

// 单独设立二分法函数，同时寻找第一个大于等于target的位置，为left（target<=nums[mid]，即使相等也右指针左移）。
// 第一个大于target的位置为right（target<nums[mid]，相等时左指针右移）,最后检查[left,right-1]区间合理性
int binarySearch1(vector<int>& nums, int target, bool lower) {
  int l = 0, r = nums.size() - 1;
  while (l <= r) {
    int mid = l + ((r - l) >> 1);
    if (target < nums[mid] || (lower && target <= nums[mid]))
      r = mid - 1;
    else
      l = mid + 1;
  }
  return l;
}
vector<int> searchRange1(vector<int>& nums, int target) {
  int left = binarySearch1(nums, target, true);
  int right = binarySearch1(nums, target, false) - 1;
  if (right < nums.size() && left <= right && nums[left] == target &&
      nums[right] == target)
    return {left, right};
  return {-1, -1};
}

int main() {
  vector<int> nums1 = {5, 7, 7, 8, 8, 10}, nums2 = nums1, nums3 = {};
  printVector(searchRange(nums1, 8));
  printVector(searchRange(nums2, 6));
  printVector(searchRange(nums3, 0));
  printVector(searchRange1(nums1, 8));
  printVector(searchRange1(nums2, 6));
  printVector(searchRange1(nums3, 0));
  return 0;
}