#include "head.h"
/* 152. 乘积最大子数组
给你一个整数数组 nums
，请你找出数组中乘积最大的非空连续子数组（该子数组中至少包含一个数字），并返回该子数组所对应的乘积。
测试用例的答案是一个 32-位 整数。
子数组 是数组的连续子序列。
示例 1:
  输入: nums = [2,3,-2,4]
  输出: 6
  解释: 子数组 [2,3] 有最大乘积 6。
示例 2:
  输入: nums = [-2,0,-1]
  输出: 0
  解释: 结果不能为 2, 因为 [-2,-1] 不是子数组。
提示:
    1 <= nums.length <= 2 * 104
    -10 <= nums[i] <= 10
    nums 的任何前缀或后缀的乘积都 保证 是一个 32-位 整数 */

int maxProduct(vector<int>& nums) {
  vector<int> maxVal(nums.size(), 0);
  vector<int> minVal(nums.size(), 0);
  int ans = nums[0];
  maxVal[0] = max(nums[0], 0), minVal[0] = min(nums[0], 0);
  for (int i = 1; i < nums.size(); i++) {
    maxVal[i] =
        max({nums[i], maxVal[i - 1] * nums[i], minVal[i - 1] * nums[i]});
    minVal[i] =
        min({nums[i], maxVal[i - 1] * nums[i], minVal[i - 1] * nums[i]});
    ans = max(ans, maxVal[i]);
  }
  return ans;
}

// 当前位乘积，取决于三种情况，不考虑前一位（前位是0则不能乘），前一位乘积是否为最大的正数，前一位是否为最小的负数。
// dp[i][0]表示到i位置最大正乘积，dp[i][1]表示到i位置最小负乘积。dp[0]全部初始化为nums[0]，利用额外int整型，记录遍历过程中出现的最大正乘积
int maxProduct1(vector<int>& nums) {
  vector<vector<int>> dp(nums.size(), vector<int>(2));
  int ans = nums[0];
  dp[0][0] = dp[0][1] = nums[0];
  for (int i = 1; i < nums.size(); i++) {
    dp[i][0] = max({nums[i], nums[i] * dp[i - 1][0], nums[i] * dp[i - 1][1]});
    dp[i][1] = min({nums[i], nums[i] * dp[i - 1][0], nums[i] * dp[i - 1][1]});
    ans = max(dp[i][0], ans);
  }
  return ans;
}

// 由于i状态之和i-1有关，故节省空间复杂度
int maxProduct2(vector<int>& nums) {
  int ans = nums[0], maxF = nums[0], minF = nums[0];
  for (int i = 1; i < nums.size(); i++) {
    maxF = max({nums[i], nums[i] * maxF, nums[i] * minF});
    minF = min({nums[i], nums[i] * maxF, nums[i] * minF});
    ans = max(maxF, ans);
  }
  return ans;
}

int main() {
  vector<int> nums1 = {2, 3, -2, 4}, nums2 = {-2, 0, -1}, nums3 = {-2, 3, -4},
              nums4 = {0, 2}, nums5 = {2, -1, 1, 1};
  cout << maxProduct(nums1) << " " << maxProduct(nums2) << " "
       << maxProduct(nums3) << " " << maxProduct(nums4) << " "
       << maxProduct(nums5) << endl;
  cout << maxProduct2(nums1) << " " << maxProduct2(nums2) << " "
       << maxProduct2(nums3) << " " << maxProduct2(nums4) << " "
       << maxProduct2(nums5) << endl;
  return 0;
}