#include "head.h"
/* 34. 在排序数组中查找元素的第一个和最后一个位置
给你一个按照非递减顺序排列的整数数组 nums，和一个目标值
target。请你找出给定目标值在数组中的开始位置和结束位置。 如果数组中不存在目标值
target，返回 [-1, -1]。 你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。
示例 1：
输入：nums = [5,7,7,8,8,10], target = 8
输出：[3,4]
示例 2：
输入：nums = [5,7,7,8,8,10], target = 6
输出：[-1,-1]
示例 3：
输入：nums = [], target = 0
输出：[-1,-1] */

// 两个二分查找，nums[m]>=target右边界仍然左移，l保存的是第一个大于等于target元素。
// nums[m]<=target，左边界仍然右移，r保存最后一个小于等于target元素
vector<int> searchRange(vector<int>& nums, int target) {
  vector<int> ans = {-1, -1};
  int l = 0, r = nums.size() - 1;
  int leftBorder = -2;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    if (nums[m] < target)
      l = m + 1;
    else {
      r = m - 1;
      leftBorder = r;
    }
  }
  int rightBorder = -2;
  l = 0, r = nums.size() - 1;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    if (nums[m] <= target) {
      l = m + 1;
      rightBorder = l;
    } else
      r = m - 1;
  }
  if (leftBorder == -2 || rightBorder == -2)  // 比最大的还大，或比最小的还小
    return ans;
  else if (rightBorder - leftBorder > 1)
    return {leftBorder + 1, rightBorder - 1};
  return ans;
}

int main() {
  vector<int> nums1 = {5, 7, 7, 8, 8, 10}, nums2 = {}, nums3 = {1};
  printVector(searchRange(nums1, 8));
  printVector(searchRange(nums1, 6));
  printVector(searchRange(nums2, 0));
  printVector(searchRange(nums3, 0));

  return 0;
}