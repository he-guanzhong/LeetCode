#include "head.h"
/* 704. 二分查找
给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target
，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
示例 1:
  输入: nums = [-1,0,3,5,9,12], target = 9
  输出: 4
  解释: 9 出现在 nums 中并且下标为 4
示例 2:
  输入: nums = [-1,0,3,5,9,12], target = 2
  输出: -1
  解释: 2 不存在 nums 中因此返回 -1
  提示：
    你可以假设 nums 中的所有元素是不重复的。
    n 将在 [1, 10000]之间。
    nums 的每个元素都将在 [-9999, 9999]之间。 */

// 优选左闭有闭区间。允许左右边界相等，如果目标小于中间值，right=mid-1，目标大于中间值，更新左值+1。
// 注意一，mid计算防止越界。二、可以使用位操作>>1实现/2。
// 三、左闭右开区间，right=mid，不能减一，因为mid肯定不等，mid-1的区间是要搜索的
int search(vector<int>& nums, int target) {
  int l = 0, r = nums.size() - 1;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    if (nums[m] > target)
      r = m - 1;
    else if (nums[m] < target)
      l = m + 1;
    else
      return m;
  }
  return -1;
}

// 左闭右闭区间，left <= right组成了空间，right = middle -1
int search1(vector<int>& nums, int target) {
  int left = 0, right = nums.size() - 1;
  while (left <= right) {
    int middle = left + (right - left) / 2;  // 防止越界
    if (nums[middle] < target)
      left = middle + 1;
    else if (nums[middle] > target)
      right = middle - 1;
    else
      return middle;
  }
  return -1;
}
// 左闭右开区间，right = middle
int search2(vector<int>& nums, int target) {
  int left = 0, right = nums.size();
  while (left < right) {
    int middle = left + ((right - left) >> 1);  // 位操作代替/2
    if (nums[middle] < target)
      left = middle + 1;
    else if (nums[middle] > target)
      right = middle;
    else
      return middle;
  }
  return -1;
}

int main() {
  vector<int> nums1 = {-1, 0, 3, 5, 9, 12}, nums2 = {2, 5}, nums3 = {-1};
  int target1 = 9, target2 = 2;
  cout << search(nums1, target1) << " " << search(nums1, target2) << " "
       << search(nums2, 5) << " " << search(nums3, 2) << endl;
  cout << search1(nums1, target1) << " " << search2(nums1, target2) << " "
       << search1(nums2, 5) << " " << search1(nums3, 2) << endl;
  return 0;
}