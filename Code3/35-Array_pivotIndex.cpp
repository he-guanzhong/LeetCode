#include "head.h"
/* 724. 寻找数组的中心下标
给你一个整数数组 nums ，请计算数组的 中心下标 。
数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。
如果中心下标位于数组最左端，那么左侧数之和视为 0
，因为在下标的左侧不存在元素。这一点对于中心下标位于数组最右端同样适用。
如果数组有多个中心下标，应该返回 最靠近左边
的那一个。如果数组不存在中心下标，返回 -1 。
示例 1：
  输 入：nums = [1, 7, 3, 6, 5, 6]
  输出：3
  解释：
    中心下标是 3 。
    左侧数之和 sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11 ，
    右侧数之和 sum = nums[4] + nums[5] = 5 + 6 = 11 ，二者相等。
示例 2：
  输入：nums = [1, 2, 3]
  输出：-1
  解释：
    数组中不存在满足此条件的中心下标。
示例 3：
  输入：nums = [2, 1, -1]
  输出：0
  解释：
    中心下标是 0 。
    左侧数之和 sum = 0 ，（下标 0 左侧不存在元素），
    右侧数之和 sum = nums[1] + nums[2] = 1 + -1 = 0 。 */

int pivotIndex(vector<int>& nums) {
  int sum = accumulate(nums.begin(), nums.end(), 0);
  int left = 0, right = sum;
  for (int i = 0; i < nums.size(); i++) {
    if (left == right - nums[i])
      return i;
    left += nums[i];
    right -= nums[i];
  }
  return -1;
}

// 前缀和。先求所有总和，然后从左向右对每一位i遍历，累加求包含i的左总和，于总和相减得到包含i的右总和，两和相等即为最左侧的数组中心下标
int pivotIndex1(vector<int>& nums) {
  int sum = 0;
  for (int i = 0; i < nums.size(); i++)
    sum += nums[i];
  int left = 0, right = 0;
  for (int i = 0; i < nums.size(); i++) {
    left += nums[i];
    right = sum - left + nums[i];
    if (left == right)
      return i;
  }
  return -1;
}

// left和right也可以存不包含nums[i]的总和，此时right要初始化为所有总和
int pivotIndex2(vector<int>& nums) {
  int left = 0, right = accumulate(nums.begin(), nums.end(), 0);
  for (int i = 0; i < nums.size(); i++) {
    right -= nums[i];
    if (left == right)
      return i;
    left += nums[i];
  }
  return -1;
}

int main() {
  vector<int> nums1 = {1, 7, 3, 6, 5, 6}, nums2 = {1, 2, 3}, nums3 = {2, 1, -1},
              nums4 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  cout << pivotIndex(nums1) << " " << pivotIndex(nums2) << " "
       << pivotIndex(nums3) << " " << pivotIndex(nums4) << endl;
  cout << pivotIndex1(nums1) << " " << pivotIndex1(nums2) << " "
       << pivotIndex1(nums3) << " " << pivotIndex1(nums4) << endl;
  return 0;
}