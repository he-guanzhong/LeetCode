#include "head.h"
/* 941. 有效的山脉数组
给定一个整数数组 arr，如果它是有效的山脉数组就返回 true，否则返回 false。
让我们回顾一下，如果 arr 满足下述条件，那么它是一个山脉数组：
    arr.length >= 3
    在 0 < i < arr.length - 1 条件下，存在 i 使得：
        arr[0] < arr[1] < ... arr[i-1] < arr[i]
        arr[i] > arr[i+1] > ... > arr[arr.length - 1]
示例 1：
  输入：arr = [2,1]
  输出：false
示例 2：
  输入：arr = [3,5,5]
  输出：false
示例 3：
  输入：arr = [0,3,2,1]
  输出：true */

bool validMountainArray(vector<int>& arr) {
  int n = arr.size();
  if (n < 3)
    return false;
  int i = 0, j = arr.size() - 1;
  while (i < n - 2 && arr[i + 1] > arr[i]) {
    i++;
  }
  while (j > 1 && arr[j - 1] > arr[j]) {
    j--;
  }
  return i == j;
}

// 双指针法，山峰定义是，从左到右递增，从右到左递减，双指针汇聚于一峰，且不存在单调递增或单调递减的情况
// 相邻元素两两对比，双指针向中央收束。若相遇，且相遇点不是左、右边界（即其中一方指针从未移动过），则返回真
bool validMountainArray1(vector<int>& arr) {
  if (arr.size() < 3)
    return false;
  int left = 0, right = arr.size() - 1;
  while (left < arr.size() - 1 && arr[left] < arr[left + 1])
    left++;
  while (right > 0 && arr[right - 1] > arr[right])
    right--;
  return (left == right && left != 0 && right != arr.size() - 1);
}

int main() {
  vector<int> nums1 = {2, 1}, nums2 = {3, 5, 5}, nums3 = {0, 3, 2, 1},
              nums4 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  cout << validMountainArray(nums1) << " " << validMountainArray(nums2) << " "
       << validMountainArray(nums3) << " " << validMountainArray(nums4) << endl;
  cout << validMountainArray1(nums1) << " " << validMountainArray1(nums2) << " "
       << validMountainArray1(nums3) << " " << validMountainArray1(nums4)
       << endl;

  return 0;
}