#include "head.h"
/* 33. 搜索旋转排序数组
整数数组 nums 按升序排列，数组中的值 互不相同 。
在传递给函数之前，nums 在预先未知的某个下标 k（0 <= k < nums.length）上进行了
旋转，使数组变为 [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ...,
nums[k-1]]（下标 从 0 开始 计数）。例如， [0,1,2,4,5,6,7] 在下标 3
处经旋转后可能变为 [4,5,6,7,0,1,2] 。
给你 旋转后 的数组 nums 和一个整数 target ，如果 nums 中存在这个目标值 target
，则返回它的下标，否则返回 -1 。
你必须设计一个时间复杂度为 O(log n) 的算法解决此问题。
示例 1：
  输入：nums = [4,5,6,7,0,1,2], target = 0
  输出：4
示例 2：
  输入：nums = [4,5,6,7,0,1,2], target = 3
  输出：-1
示例 3：
  输入：nums = [1], target = 0
  输出：-1 */

int search(vector<int>& nums, int target) {
  int l = 0, r = nums.size() - 1;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    if (target == nums[m]) {
      return m;
    } else if (nums[m] > nums[r]) {
      if (target >= nums[l] && target < nums[m])
        r = m - 1;
      else
        l = m + 1;
    } else {
      if (target <= nums[r] && target > nums[m])
        l = m + 1;
      else
        r = m - 1;
    }
  }
  return -1;
}

// mid截断左右两区间，其中之一必为有序。如果左有序闭区间[left,mid]，要确保target在左有序区间内，右边界左移，否则在右无序区间中继续找。
// 如果右有序(mid,right]，则确保元素在右区间内，左边界右移。否则在左无序区间继续寻找。
int search1(vector<int>& nums, int target) {
  int l = 0, r = nums.size() - 1;
  while (l <= r) {
    int mid = l + ((r - l) >> 1);
    if (target == nums[mid])
      return mid;
    else if (nums[l] <= nums[mid]) {  // 左区间[left,mid]有序
      target >= nums[l] && target < nums[mid] ? r = mid - 1 : l = mid + 1;
    } else {  // 右区间(mid,right]有序
      target <= nums[r] && target > nums[mid] ? l = mid + 1 : r = mid - 1;
    }
  }
  return -1;
}

int main() {
  vector<int> nums1 = {4, 5, 6, 7, 0, 1, 2}, nums2 = nums1, nums3 = {1},
              nums4 = {1, 3}, nums5 = {3, 1};
  cout << search(nums1, 0) << " " << search(nums2, 3) << " " << search(nums3, 0)
       << " " << search(nums4, 3) << " " << search(nums5, 1) << endl;
  cout << search1(nums1, 0) << " " << search1(nums2, 3) << " "
       << search1(nums3, 0) << " " << search1(nums4, 3) << " "
       << search1(nums5, 1) << endl;
  return 0;
}