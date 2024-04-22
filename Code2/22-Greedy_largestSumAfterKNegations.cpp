#include <numeric>  // accumulate函数需要
#include "head.h"
/* 1005. K 次取反后最大化的数组和
给你一个整数数组 nums 和一个整数 k ，按以下方法修改该数组：
    选择某个下标 i 并将 nums[i] 替换为 -nums[i] 。
重复这个过程恰好 k 次。可以多次选择同一个下标 i 。
以这种方式修改数组后，返回数组 可能的最大和 。
示例 1：
输入：nums = [4,2,3], k = 1
输出：5
解释：选择下标 1 ，nums 变为 [4,-2,3] 。
示例 2：
输入：nums = [3,-1,0,2], k = 3
输出：6
解释：选择下标 (1, 2, 2) ，nums 变为 [3,1,0,2] 。
示例 3：
输入：nums = [2,-3,-1,5,-4], k = 2
输出：13
解释：选择下标 (1, 4) ，nums 变为 [2,3,-1,5,4] 。
*/

// 方法一：先排序，对小于0的负数取反，同时k--，情况一：如果k==0则直接返回结果。情况二：遍历后k仍不为0，再次排序，按照k为奇偶数，对首元素取反
// 方法二：直接按照绝对值，从大到小排序，从前至后k次取反
int largestSumAfterKNegations(vector<int>& nums, int k) {
  sort(nums.begin(), nums.end(),
       [](const int& a, const int& b) { return abs(a) > abs(b); });
  for (int& num : nums) {
    if (num < 0 && k > 0) {
      num *= -1;
      k--;
    }
  }
  if (k % 2 == 1)
    nums[nums.size() - 1] *= -1;
  return accumulate(nums.begin(), nums.end(), 0);
}

// 先用绝对值从大到小排序，如此即可不用两次排序，然后从前到后如遇到负数则求反。
// 如之后还k>0，则置多一次，反转最小的那个数。偶数次是不用一次一次处理的
int largestSumAfterKNegations1(vector<int>& nums, int k) {
  sort(nums.begin(), nums.end(), [](int a, int b) { return abs(a) > abs(b); });
  for (int i = 0; i < nums.size(); i++) {
    if (k > 0 && nums[i] < 0) {
      nums[i] *= -1;
      k--;
    }
  }
  if (k % 2 == 1)
    nums[nums.size() - 1] *= -1;
  int res = accumulate(nums.begin(), nums.end(), 0);
  return res;
}

int main() {
  vector<int> nums1 = {4, 2, 3};
  vector<int> nums2 = {3, -1, 0, 2};
  vector<int> nums3 = {2, -3, -1, 5, -4};
  int k1 = 1, k2 = 3, k3 = 2;
  cout << largestSumAfterKNegations(nums1, k1) << " "
       << largestSumAfterKNegations(nums2, k2) << " "
       << largestSumAfterKNegations(nums3, k3) << " " << endl;
  nums1 = {4, 2, 3};
  nums2 = {3, -1, 0, 2};
  nums3 = {2, -3, -1, 5, -4};
  cout << largestSumAfterKNegations1(nums1, k1) << " "
       << largestSumAfterKNegations1(nums2, k2) << " "
       << largestSumAfterKNegations1(nums3, k3) << " " << endl;
  return 0;
}