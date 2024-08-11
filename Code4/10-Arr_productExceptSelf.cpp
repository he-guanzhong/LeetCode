#include "head.h"
/* 238. 除自身以外数组的乘积
给你一个整数数组 nums，返回 数组 answer ，其中 answer[i] 等于 nums 中除 nums[i]
之外其余各元素的乘积 。
题目数据 保证 数组 nums之中任意元素的全部前缀元素和后缀的乘积都在  32 位
整数范围内。
请 不要使用除法，且在 O(n) 时间复杂度内完成此题。
示例 1:
  输入: nums = [1,2,3,4]
  输出: [24,12,8,6]
示例 2:
  输入: nums = [-1,1,0,-3,3]
  输出: [0,0,9,0,0]*/

vector<int> productExceptSelf(vector<int>& nums) {
  vector<int> ans(nums.size(), 1);
  for (int i = 1; i < nums.size(); i++) {
    ans[i] = ans[i - 1] * nums[i - 1];
  }
  int right = 1;
  for (int i = nums.size() - 1; i >= 0; i--) {
    ans[i] *= right;
    right *= nums[i];
  }
  return ans;
}

// 类似双指针接雨水，两个数组两次遍历，分别保存i处，左侧所有元素乘积，和右侧所有元素乘积。再次遍历，求每个位置左右积之积
vector<int> productExceptSelf1(vector<int>& nums) {
  int n = nums.size();
  vector<int> L(n, 0), R(n, 0);
  vector<int> ans(n, 0);
  L[0] = 1, R[n - 1] = 1;  // 首元素左、末元素右无积，初始化为1
  for (int i = 1; i < n; i++)
    L[i] = L[i - 1] * nums[i - 1];
  for (int i = n - 2; i >= 0; i--)
    R[i] = R[i + 1] * nums[i + 1];
  for (int i = 0; i < n; i++)
    ans[i] = L[i] * R[i];
  return ans;
}

// 空间复杂度O(1)优化，因为输出数组不计入空间复杂度。将返回ans和左侧乘积L功能合并，右侧乘积R计算和第三次遍历求结果合并。
// 右测乘积使用单个int，从末元素向左遍历，先利用原L数值更新结果ans，在更新右侧乘积值R
vector<int> productExceptSelf2(vector<int>& nums) {
  int n = nums.size();
  vector<int> ans(n, 0);
  ans[0] = 1;
  for (int i = 1; i < n; i++)
    ans[i] = ans[i - 1] * nums[i - 1];
  int R = 1;
  for (int i = n - 1; i >= 0; i--) {
    ans[i] = ans[i] * R;  // 更新结果为左侧、右侧乘积之积
    R *= nums[i];         // 更新右侧乘积
  }
  return ans;
}

int main() {
  vector<int> nums1{1, 2, 3, 4}, nums2{-1, 1, 0, -3, 3}, nums3{1, -1, 0};
  printVector(productExceptSelf(nums1));
  printVector(productExceptSelf(nums2));
  printVector(productExceptSelf(nums3));
  printVector(productExceptSelf1(nums1));
  printVector(productExceptSelf1(nums2));
  printVector(productExceptSelf1(nums3));
  return 0;
}