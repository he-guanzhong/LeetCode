#include "head.h"
/* 35. 搜索插入位置
给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
请必须使用时间复杂度为 O(log n) 的算法。
示例 1:
输入: nums = [1,3,5,6], target = 5
输出: 2
示例 2:
输入: nums = [1,3,5,6], target = 2
输出: 1
示例 3:
输入: nums = [1,3,5,6], target = 7
输出: 4 */

int searchInsert(vector<int>& nums, int target) {
  int left = 0, right = nums.size() - 1;
  while (left <= right) {
    int mid = left + ((right - left) >> 1);
    if (target <= nums[mid])
      right = mid - 1;
    else
      left = mid + 1;
  }
  return left;
}

// 二分法。注意位运算替代/2操作，其优先级小于+-*/。另外，左闭右闭区间，target<=中值，右边界左移，保证target一定大于right。
// 否则左边界右移，保证target一定小于等于left。left即为大于等于target的第一个数值
int searchInsert1(vector<int>& nums, int target) {
  int left = 0, right = nums.size() - 1;
  while (left <= right) {
    int mid = left + ((right - left) >> 1);
    if (target <= nums[mid])
      right = mid - 1;
    else
      left = mid + 1;
  }
  return left;
}

int searchInsert2(vector<int>& nums, int target) {
  return lower_bound(nums.begin(), nums.end(), target) - nums.begin();
}
int main() {
  vector<int> nums{1, 3, 5, 6};
  cout << searchInsert(nums, 5) << " " << searchInsert(nums, 2) << " "
       << searchInsert(nums, 7) << endl;
  cout << searchInsert1(nums, 5) << " " << searchInsert1(nums, 2) << " "
       << searchInsert1(nums, 7) << endl;
  return 0;
}