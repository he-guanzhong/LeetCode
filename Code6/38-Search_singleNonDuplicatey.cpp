#include "head.h"
/* 540. 有序数组中的单一元素
给你一个仅由整数组成的有序数组，其中每个元素都会出现两次，唯有一个数只会出现一次。
请你找出并返回只出现一次的那个数。
你设计的解决方案必须满足 O(log n) 时间复杂度和 O(1) 空间复杂度。
示例 1:
  输入: nums = [1,1,2,3,3,4,4,8,8]
  输出: 2
示例 2:
  输入: nums =  [3,3,7,7,10,11,11]
  输出: 10
提示:
  1 <= nums.length <= 105
  0 <= nums[i] <= 105 */

// 有序数组，并要求时间复杂度O(logN)，则不可以使用传统异或方法。
// 对于普通数组，记答案为分割点，其左侧nums[i]==nums[i+1]，i为偶数。或另一种表述nums[i]==nums[i-1]，i为奇数
// 显然，其右侧满足nums[i]==nums[i+1]，i为奇数。或另一种表述nums[i]==nums[i-1]，i为偶数
// 左侧全部满足要求，无论奇偶，注意异或特性：i为偶数时i+1=i^1，i为奇数时i-1=i^1。所以，只要满足nums[i]==nums[i^1]即向右查询
// 向右查询前提是i^1不能超过数组范围。注意退出条件，分割点必为偶数，且不满足条件nums[i]==nums[i+1]，故最后一步必然是将右指针移动
// 因此，最终答案是左指针指向的值（不是下标）
int singleNonDuplicate(vector<int>& nums) {
  int left = 0, right = nums.size() - 1;
  while (left <= right) {
    int mid = left + ((right - left) >> 1);
    if ((mid ^ 1) < nums.size() && nums[mid] == nums[mid ^ 1]) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return nums[left];
}

int main() {
  vector<int> arr1({1, 1, 2, 3, 3, 4, 4, 8, 8}), arr2({3, 3, 7, 7, 10, 11, 11}),
      arr3({1});
  cout << singleNonDuplicate(arr1) << " " << singleNonDuplicate(arr2) << " "
       << singleNonDuplicate(arr3) << endl;

  return 0;
}