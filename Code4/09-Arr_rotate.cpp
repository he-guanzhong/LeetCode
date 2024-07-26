#include "head.h"
/* 189. 轮转数组
给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
示例 1:
  输入: nums = [1,2,3,4,5,6,7], k = 3
  输出: [5,6,7,1,2,3,4]
  解释:
    向右轮转 1 步: [7,1,2,3,4,5,6]
    向右轮转 2 步: [6,7,1,2,3,4,5]
    向右轮转 3 步: [5,6,7,1,2,3,4]
示例 2:
  输入：nums = [-1,-100,3,99], k = 2
  输出：[3,99,-1,-100]
  解释:
    向右轮转 1 步: [99,-1,-100,3]
    向右轮转 2 步: [3,99,-1,-100] */

void rotate(vector<int>& nums, int k) {
  k %= nums.size();
  reverse(nums.begin(), nums.end() - k);
  reverse(nums.end() - k, nums.end());
  reverse(nums.begin(), nums.end());
}

// 方法一，使用额外数组，原数组i向右移动k步，故在新数组的位置为(i+k)%n。使用assign函数将其赋值到原数组上。空间复杂度O(n)
void rotate1(vector<int>& nums, int k) {
  int n = nums.size();
  vector<int> newArr(n, 0);
  for (int i = 0; i < n; i++)
    newArr[(i + k) % n] = nums[i];
  nums.assign(newArr.begin(), newArr.end());
}

// 方法二，推荐三次反转数组。核心在于将后k%n个元素放置于队首。故先全部反转，在分别反转[0,k%n-1]和[k&n,n-1]两个区间。时间复杂度2n，因为每个元素仅反转两次，空间复杂度1
void rotate2(vector<int>& nums, int k) {
  k %= nums.size();
  reverse(nums.begin(), nums.end());
  reverse(nums.begin(), nums.begin() + k);
  reverse(nums.begin() + k, nums.end());
}

int main() {
  vector<int> nums1{1, 2, 3, 4, 5, 6, 7}, nums2{-1, -100, 3, 99},
      nums3{1, -1, 0}, nums4{-1};
  int k1 = 3, k2 = 2, k3 = 0, k4 = 2;
  rotate(nums1, k1);
  rotate(nums2, k2);
  rotate(nums3, k3);
  rotate(nums4, k4);
  printVector(nums1);
  printVector(nums2);
  printVector(nums3);
  printVector(nums4);
  nums1 = {1, 2, 3, 4, 5, 6, 7}, nums2 = {-1, -100, 3, 99}, nums3 = {1, -1, 0},
  nums4 = {-1};
  rotate2(nums1, k1);
  rotate2(nums2, k2);
  rotate2(nums3, k3);
  rotate2(nums4, k4);
  printVector(nums1);
  printVector(nums2);
  printVector(nums3);
  printVector(nums4);
  return 0;
}