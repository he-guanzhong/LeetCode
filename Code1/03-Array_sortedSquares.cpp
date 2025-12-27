#include "head.h"
/* 977. 有序数组的平方
给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方
组成的新数组，要求也按 非递减顺序 排序。
示例 1：
  输入：nums = [-4,-1,0,3,10]
  输出：[0,1,9,16,100]
  解释：平方后，数组变为
    [16,1,0,9,100]，排序后，数组变为 [0,1,9,16,100]
示例 2：
  输入：nums = [-7,-3,2,3,11]
  输出：[4,9,9,49,121]
请你设计时间复杂度为 O(n) 的算法解决本问题 */

vector<int> sortedSquares(vector<int>& nums) {
  vector<int> ans(nums.size(), 0);
  int k = ans.size() - 1;
  for (int i = 0, j = nums.size() - 1; i <= j;) {
    if (abs(nums[i]) >= abs(nums[j])) {
      ans[k--] = nums[i] * nums[i];
      i++;
    } else {
      ans[k--] = nums[j] * nums[j];
      j--;
    }
  }
  return ans;
}

// 双指针法，O(n) = n
vector<int> sortedSquares2(vector<int>& nums) {
  int k = nums.size() - 1;
  vector<int> result(nums.size(), 0);
  for (int i = 0, j = nums.size() - 1;
       i <= j;) {  // 注意此处i <= j 因为要处理两个元素
    if (nums[i] * nums[i] < nums[j] * nums[j]) {
      result[k--] = nums[j] * nums[j];
      j--;
    } else {
      result[k--] = nums[i] * nums[i];
      i++;
    }
  }
  return result;
}

// 暴力解法，O(n) = n + nlogn
vector<int> sortedSquares1(vector<int>& nums) {
  for (int i = 0; i < nums.size(); i++) {
    nums[i] *= nums[i];  // 注意平方写法
  }
  sort(nums.begin(), nums.end());
  return nums;
}

int main() {
  vector<int> nums1 = {-4, -1, 0, 3, 10};
  vector<int> nums2 = {-7, -3, 2, 3, 11};
  printVector(sortedSquares(nums1));
  printVector(sortedSquares(nums2));
  nums1 = {-4, -1, 0, 3, 10};
  nums2 = {-7, -3, 2, 3, 11};
  printVector(sortedSquares2(nums1));
  printVector(sortedSquares2(nums2));
  return 0;
}