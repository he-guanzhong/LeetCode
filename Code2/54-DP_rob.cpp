#include "head.h"
/* 198. 打家劫舍
你是一个专业的小偷，计划偷窃沿街的房屋。每间房内都藏有一定的现金
影响你偷窃的唯一制约因素就是相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯入，系统会自动报警。
给定一个代表每个房屋存放金额的非负整数数组，计算你 不触动警报装置的情况下
，一夜之内能够偷窃到的最高金额。
示例 1：
  输入：[1,2,3,1]
  输出：4
  解释：偷窃 1 号房屋 (金额 = 1) ，然后偷窃 3 号房屋 (金额 = 3)。
     偷窃到的最高金额 = 1 + 3 = 4 。
示例 2：
  输入：[2,7,9,3,1]
  输出：12
  解释：偷窃 1 号房屋 (金额 = 2), 偷窃 3 号房屋 (金额 = 9)，接着偷窃 5 号房屋
    (金额 = 1)。 偷窃到的最高金额 = 2 + 9 + 1 = 12 。 */

int rob(vector<int>& nums) {
  if (nums.size() == 1)
    return nums[0];
  else if (nums.size() == 2)
    return max(nums[0], nums[1]);
  vector<int> dp(nums.size(), 0);
  dp[0] = nums[0], dp[1] = max(nums[0], nums[1]);
  for (int i = 2; i < nums.size(); i++) {
    dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
  }
  return dp[nums.size() - 1];
}

// 当i天最大收益dp[i]，取决于今天不偷（前一天最大收益）和今天偷（前两天的收益）两种情况。先排除数组大小为0和1的特殊情况。
// 注意第二天收益初始化dp[1]为前两天的最大值
// dp[i]代表房屋i能偷到的最大钱数。递归公式取决于偷本间和上上一间，或者本间不偷，偷上一间。dp[i]=max(dp[i-1],dp[i-2]+nums[i])
// 初始化，必须先排除只有一个元素的情况。然后第二个元素起，可偷数为前两个元素之和。从第三个元素开始遍历
int rob1(vector<int>& nums) {
  if (nums.size() == 1)
    return nums[0];
  vector<int> dp(nums.size(), 0);
  dp[0] = nums[0];
  dp[1] = max(nums[0], nums[1]);
  for (int i = 2; i < nums.size(); i++) {
    dp[i] = max(dp[i - 1], dp[i - 2] + nums[i]);
  }
  return dp[nums.size() - 1];
}

int main() {
  vector<int> nums1 = {1, 2, 3, 1}, nums2 = {2, 7, 9, 3, 1},
              nums3 = {2, 1, 1, 2};
  cout << rob(nums1) << " " << rob(nums2) << " " << rob(nums3) << endl;
  cout << rob1(nums1) << " " << rob1(nums2) << " " << rob1(nums3) << endl;
  return 0;
}