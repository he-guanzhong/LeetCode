#include "head.h"
/* 448. 找到所有数组中消失的数字
给你一个含 n 个整数的数组 nums ，其中 nums[i] 在区间 [1, n] 内。请你找出所有在
[1, n] 范围内但没有出现在 nums 中的数字，并以数组的形式返回结果。
示例 1：
输入：nums = [4,3,2,7,8,2,3,1]
输出：[5,6]
示例 2：
输入：nums = [1,1]
输出：[2]  */

vector<int> findDisappearedNumbers(vector<int>& nums) {
  int n = nums.size();
  for (int i = 0; i < n; i++) {
    nums[(nums[i] - 1) % n] += n;
  }
  vector<int> ans;
  for (int i = 0; i < n; i++) {
    if (nums[i] <= n)
      ans.push_back(i + 1);
  }
  return ans;
}

// 利用数组本身充当哈希表，节省空间复杂度O(1)。对每一个元素num，其理论应该在[1,n]之中。求出其在数组中的真实位置x,nums[x]+n处理。保证其一定大于n
// 二次遍历，以下标i遍历任何小于等于n的元素，说明数i+1没出现过。
vector<int> findDisappearedNumbers1(vector<int>& nums) {
  vector<int> ans;
  int n = nums.size();
  for (int& num : nums) {
    int x = (num - 1) % n;
    nums[x] += n;
  }
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] <= n)
      ans.push_back(i + 1);
  }
  return ans;
}

int main() {
  vector<int> nums1 = {4, 3, 2, 7, 8, 2, 3, 1}, nums2 = {1, 1};
  printVector(findDisappearedNumbers(nums1));
  printVector(findDisappearedNumbers(nums2));
  printVector(findDisappearedNumbers1(nums1));
  printVector(findDisappearedNumbers1(nums2));
  return 0;
}