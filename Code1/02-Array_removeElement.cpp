#include "head.h"
/* 27. 移除元素
给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val
的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并原地修改输入数组。
元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

示例 1: 给定 nums = [3,2,2,3], val = 3, 函数应该返回新的长度 2, 并且 nums
中的前两个元素均为 2。 你不需要考虑数组中超出新长度后面的元素。
示例 2: 给定 nums = [0,1,2,2,3,0,4,2], val = 2, 函数应该返回新的长度 5, 并且
nums 中的前五个元素为 0, 1, 3, 0, 4。
你不需要考虑数组中超出新长度后面的元素。 */

// 优选快慢指针法，快指针定义在循环内。慢指针代表了要更改的下一位置，和新数组长度
int removeElement(vector<int>& nums, int val) {
  int j = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] != val)
      nums[j++] = nums[i];
  }
  return j;
}

// 暴力解法，发现相同，就从此往后向前移动一位，同时下标和总长度减一
int removeElement1(vector<int>& nums, int val) {
  int size = nums.size();
  for (int i = 0; i < size; i++) {
    if (nums[i] == val) {
      for (int j = i + 1; j < size; j++) {
        nums[j - 1] = nums[j];
      }
      i--;
      size--;
    }
  }
  return size;
}
// 快慢指针法
int removeElement2(vector<int>& nums, int val) {
  int slow = 0;
  for (int fast = 0; fast < nums.size(); fast++) {
    if (nums[fast] != val) {
      nums[slow++] = nums[fast];  // 赋值同时移动至下一位置
    }
  }
  return slow;
}

int main() {
  vector<int> nums1 = {3, 2, 2, 3};
  vector<int> nums2 = {0, 1, 2, 2, 3, 0, 4, 2};
  int val1 = 3, val2 = 2;
  cout << removeElement(nums1, val1) << " " << removeElement(nums2, val2)
       << endl;
  nums1 = {3, 2, 2, 3};
  nums2 = {0, 1, 2, 2, 3, 0, 4, 2};
  cout << removeElement2(nums1, val1) << " " << removeElement2(nums2, val2)
       << endl;
  return 0;
}