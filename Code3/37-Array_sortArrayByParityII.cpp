#include "head.h"
/* 922. 按奇偶排序数组 II
给定一个非负整数数组 nums，  nums 中一半整数是 奇数 ，一半整数是 偶数 。
对数组进行排序，以便当 nums[i] 为奇数时，i 也是 奇数 ；当 nums[i] 为偶数时， i
也是 偶数 。
你可以返回 任何满足上述条件的数组作为答案 。
示例 1：
  输入：nums = [4,2,5,7]
  输出：[4,5,2,7]
  解释：[4,7,2,5]，[2,5,4,7]，[2,7,4,5] 也会被接受。
示例 2：
  输入：nums = [2,3]
  输出：[2,3] */

vector<int> sortArrayByParityII(vector<int>& nums) {
  int oddIndex = 1;
  for (int i = 0; i < nums.size(); i += 2) {
    if (nums[i] % 2 == 1) {
      while (nums[oddIndex] % 2 == 0)
        oddIndex += 2;
      if (oddIndex < nums.size())
        swap(nums[i], nums[oddIndex]);
    }
  }
  return nums;
}

// 节省空间做法，双指针分别指向奇数位odd和偶数位even。偶数指针遍历，遇到奇数，则找到奇数位存偶数的地方，二者交换
// 时间复杂度O(n)，因为奇数位和偶数位都只操作了一次
vector<int> sortArrayByParityII1(vector<int>& nums) {
  int oddIndex = 1;
  for (int i = 0; i < nums.size(); i += 2) {
    if (nums[i] % 2 == 1) {            // 偶数位看到了奇数
      while (nums[oddIndex] % 2 == 1)  // 奇数位找到了偶数
        oddIndex += 2;
      swap(nums[i], nums[oddIndex]);
    }
  }
  return nums;
}

// 传统做法，利用额外空间。初始化奇数位为1，偶数位为0。遍历nums[i]，遇到奇偶数就分别对奇偶数所指位置赋值
vector<int> sortArrayByParityII2(vector<int>& nums) {
  vector<int> ans(nums.size(), 0);
  int oddIndex = 1, evenIndex = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] % 2 == 1) {
      ans[oddIndex] = nums[i];
      oddIndex += 2;
    } else {
      ans[evenIndex] = nums[i];
      evenIndex += 2;
    }
  }
  return ans;
}

int main() {
  vector<int> nums1 = {4, 2, 5, 7}, nums2 = {2, 3}, nums3 = {1, 2};
  printVector(sortArrayByParityII(nums1));
  printVector(sortArrayByParityII(nums2));
  printVector(sortArrayByParityII(nums3));
  nums1 = {4, 2, 5, 7}, nums2 = {2, 3}, nums3 = {1, 2};
  printVector(sortArrayByParityII1(nums1));
  printVector(sortArrayByParityII1(nums2));
  printVector(sortArrayByParityII1(nums3));
  return 0;
}