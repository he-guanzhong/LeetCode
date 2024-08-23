#include "head.h"
/* 153. 寻找旋转排序数组中的最小值
已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转
后，得到输入数组。例如，原数组 nums = [0,1,2,4,5,6,7] 在变化后可能得到：
    若旋转 4 次，则可以得到 [4,5,6,7,0,1,2]
    若旋转 7 次，则可以得到 [0,1,2,4,5,6,7]
注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0],
a[1], a[2], ..., a[n-2]] 。
给你一个元素值 互不相同 的数组 nums
，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的
最小元素 。
你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
示例 1：
  输入：nums = [3,4,5,1,2]
  输出：1
  解释：原数组为 [1,2,3,4,5] ，旋转 3 次得到输入数组。
示例 2：
  输入：nums = [4,5,6,7,0,1,2]
  输出：0
  解释：原数组为 [0,1,2,4,5,6,7] ，旋转 3 次得到输入数组。
示例 3：
  输入：nums = [11,13,15,17]
  输出：11
  解释：原数组为 [11,13,15,17] ，旋转 4 次得到输入数组。*/

int findMin(vector<int>& nums) {
  int l = 0, r = nums.size() - 1;
  while (l < r) {
    int m = l + ((r - l) >> 1);
    if (nums[m] > nums[r])
      l = m + 1;
    else
      r = m;
  }
  return nums[l];
}

// 性质，以最右元素为标杆、最小元素为分割点。最小元素向右元素均小于末尾元素，最小元素之左均大于末尾元素。
// while循环条件，left不必等于right，相等即退出。中点mid元素小于最右元素,说明最小元素在mid之左，right=mid，而不是right-1，考虑[4,1,2]例子
// 中点mid大于最右元素，说明最小元素在mid之右，left=mid+1，考虑[2,3,1]情况，left多进一步，left和right相遇退出，返回值即为left
int findMin1(vector<int>& nums) {
  int left = 0, right = nums.size() - 1;
  while (left < right) {
    int mid = left + ((right - left) >> 1);
    if (nums[mid] > nums[right])
      left = mid + 1;
    else
      right = mid;
  }
  return nums[left];
}

int main() {
  vector<int> nums1 = {3, 4, 5, 1, 2}, nums2 = {4, 5, 6, 7, 0, 1, 2},
              nums3 = {11, 13, 15, 17};
  cout << findMin(nums1) << " " << findMin(nums2) << " " << findMin(nums3)
       << endl;
  cout << findMin1(nums1) << " " << findMin1(nums2) << " " << findMin1(nums3)
       << endl;
  return 0;
}