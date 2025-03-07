#include "head.h"

/* 713. 乘积小于 K 的子数组
给你一个整数数组 nums 和一个整数 k ，请你返回子数组内所有元素的乘积严格小于 k
的连续子数组的数目。
示例 1：
  输入：nums = [10,5,2,6], k = 100
  输出：8
  解释：8 个乘积小于 100
    的子数组分别为：[10]、[5]、[2]、[6]、[10,5]、[5,2]、[2,6]、[5,2,6]。
    需要注意的是 [10,5,2] 并不是乘积小于 100 的子数组。
示例 2：
  输入：nums = [1,2,3], k = 0
  输出：0
提示:
  1 <= nums.length <= 3 * 104
  1 <= nums[i] <= 1000
  0 <= k <= 106 */

// 滑动窗口左右边界[j,i]，窗口内积要时刻保持小于k，此时以i为结尾的连续数组，均满足条件。数量为i-j+1个
// 乘积prod最大可能是k*max{nums[i]}，即1e9，不超过INT_MAX，所以不会产生越界问题
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
  int prod = 1;
  int ans = 0;
  int j = 0;
  for (int i = 0; i < nums.size(); i++) {
    prod *= nums[i];
    while (j <= i && prod >= k) {
      prod /= nums[j++];
    }
    ans += i - j + 1;
  }
  return ans;
}

int main() {
  vector<int> nums1({10, 5, 2, 6}), nums2({1, 2, 3});
  cout << numSubarrayProductLessThanK(nums1, 100) << " "
       << numSubarrayProductLessThanK(nums2, 0) << endl;
  return 0;
}
