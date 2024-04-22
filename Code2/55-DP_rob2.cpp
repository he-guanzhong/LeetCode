#include "head.h"
/* 213. 打家劫舍 II
你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。这个地方所有的房屋都
围成一圈，这意味着第一个房屋和最后一个房屋是紧挨着的。同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警
。给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下
，今晚能够偷窃到的最高金额。
示例 1：
输入：nums = [2,3,2]
输出：3
解释：你不能先偷窃 1 号房屋（金额 = 2），然后偷窃 3 号房屋（金额 = 2）,
因为他们是相邻的。
示例 2：
输入：nums = [1,2,3,1]
输出：4
解释：你可以先偷窃 1 号房屋（金额 = 1），然后偷窃 3 号房屋（金额 = 3）。
     偷窃到的最高金额 = 1 + 3 = 4 。
示例 3：
输入：nums = [1,2,3]
输出：3
 */

// 拆分为，不考虑首元素，和不考虑尾元素，二者情况的最大值。传参可以使用起始下标，先排除0和1特殊情况影响，使用左闭右开，或左开右闭均可
int test(vector<int>& nums) {
  if (nums.size() == 0)
    return 0;
  if (nums.size() == 1)
    return nums[0];
  vector<int> dp(nums.size(), 0);
  dp[0] = nums[0];
  dp[1] = max(nums[0], nums[1]);
  for (int i = 2; i < nums.size(); i++)
    dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
  return dp[nums.size() - 1];
}
int rob(vector<int>& nums) {
  if (nums.size() <= 2)
    return test(nums);
  vector<int> nums1 = vector<int>(nums.begin(), nums.end() - 1);
  vector<int> nums2 = vector<int>(nums.begin() + 1, nums.end());
  return max(test(nums1), test(nums2));
}

// 成环打家劫舍，拆分成不考虑首元素的普通情况，和不考虑末元素的普通情况。取二者的最大值即可
// 注意，普通打家劫舍函数，必须保证里面至少有两个元素。故一个元素的情况要额外排除。
int robRange(const vector<int>& nums, int start, int end) {
  if (start == end)
    return nums[start];
  vector<int> dp(nums.size(), 0);
  dp[start] = nums[start];
  dp[start + 1] = max(nums[start], nums[start + 1]);
  for (int i = start + 2; i <= end; i++) {
    dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
  }
  return dp[end];
}
int rob1(vector<int>& nums) {
  if (nums.size() == 0)
    return 0;
  if (nums.size() == 1)
    return nums[0];
  int result1 = robRange(nums, 0, nums.size() - 2);
  int result2 = robRange(nums, 1, nums.size() - 1);
  return max(result1, result2);
}
int main() {
  vector<int> nums1 = {2, 3, 2}, nums2 = {1, 2, 3, 1}, nums3 = {1, 2, 3},
              nums4 = {0, 0};
  cout << rob(nums1) << " " << rob(nums2) << " " << rob(nums3) << " "
       << rob(nums4) << endl;
  cout << rob1(nums1) << " " << rob1(nums2) << " " << rob1(nums3) << " "
       << rob1(nums4) << endl;
  return 0;
}