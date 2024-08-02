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
  int l = 0, r = nums.size() - 1;
  while (l <= r) {
    int mid = l + ((r - l) >> 1);
    if (nums[mid] >= target)
      r = mid - 1;
    else
      l = mid + 1;
  }
  return l;
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

// 传统左闭右闭写法。元素分四种情况讨论，1.比最小的元素还小，2.等于数组中某元素，3.处于数组某区间，4.比最大的元素还大
int searchInsert3(vector<int>& nums, int target) {
  int left = 0, right = nums.size() - 1;
  while (left <= right) {  // 左右边界相等时仅有一个元素，有意义
    int mid = left + ((right - left) >> 1);
    if (nums[mid] > target)
      right = mid - 1;
    else if (nums[mid] < target)
      left = mid + 1;
    else
      return mid;  // 情况三
  }
  // 情况一，左边界0从未移动，最终状态为[0,-1]。情况二，状态为[right,target,left]。
  // 情况四，右边界n-1从始至终未移动，状态为[n,n-1]。综上返回left或right+1均可
  return right + 1;
}

// 左闭右开写法。
int searchInsert4(vector<int>& nums, int target) {
  int left = 0, right = nums.size();
  while (left < right) {  // [left,right)，不相等才有意义
    int mid = left + ((right - left) >> 1);
    if (nums[mid] > target)
      right = mid;  // mid元素已被区间右开排除
    else if (nums[mid] < target)
      left = mid + 1;
    else
      return mid;  // 情况三
  }
  // 情况一，左边界0从未移动，最终状态为[0,0)。情况二，状态为[target,right==left)。
  // 情况四，右边界n从始至终未移动，状态为[n,n)。综上返回left或right均可
  return right;
}

int main() {
  vector<int> nums{1, 3, 5, 6};
  cout << searchInsert(nums, 5) << " " << searchInsert(nums, 2) << " "
       << searchInsert(nums, 7) << endl;
  cout << searchInsert1(nums, 5) << " " << searchInsert1(nums, 2) << " "
       << searchInsert1(nums, 7) << endl;
  return 0;
}