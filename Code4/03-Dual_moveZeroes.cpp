#include "head.h"
/* 283. 移动零
给定一个数组 nums，编写一个函数将所有 0
移动到数组的末尾，同时保持非零元素的相对顺序。 请注意
，必须在不复制数组的情况下原地对数组进行操作。
示例 1:
  输入: nums = [0,1,0,3,12]
  输出: [1,3,12,0,0]
示例 2:
  输入: nums = [0]
  输出: [0] */

void moveZeroes(vector<int>& nums) {
  int slow = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i])
      nums[slow++] = nums[i];
  }
  for (int i = slow; i < nums.size(); i++)
    nums[i] = 0;
}

// 方法一，快慢指针两次遍历。第一次，快指针如果指向不是0，就慢指针赋值并挪动。如此慢指针停到所有非0值的下一位，二次遍历，对之后的所有数赋0
void moveZeroes1(vector<int>& nums) {
  int j = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] != 0)
      nums[j++] = nums[i];
  }
  for (int i = j; i < nums.size(); i++)
    nums[i] = 0;
  return;
}

// 方法二，参考快排，一次遍历,对只要非0元素，就交换位置
void moveZeroes2(vector<int>& nums) {
  int j = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] != 0)
      swap(nums[j++], nums[i]);
  }
  return;
}

int main() {
  vector<int> nums1 = {0, 1, 0, 3, 12}, nums2 = {0}, nums3 = {};
  moveZeroes(nums1);
  moveZeroes(nums2);
  moveZeroes(nums3);
  printVector(nums1);
  printVector(nums2);
  printVector(nums3);
  nums1 = {0, 1, 0, 3, 12}, nums2 = {0}, nums3 = {};
  moveZeroes1(nums1);
  moveZeroes1(nums2);
  moveZeroes1(nums3);
  printVector(nums1);
  printVector(nums2);
  printVector(nums3);
  return 0;
}