#include "head.h"
/* 416. 分割等和子集
给你一个 只包含正整数 的 非空 数组 nums
。请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
示例 1：
  输入：nums = [1,5,11,5]
  输出：true
  解释：数组可以分割成 [1, 5, 5] 和 [11] 。
示例 2：
  输入：nums = [1,2,3,5]
  输出：false
  解释：数组不能分割成两个元素和相等的子集。
  提示：
    1 <= nums.length <= 200
    1 <= nums[i] <= 100 */

bool canPartition(vector<int>& nums) {
  int sum = accumulate(nums.begin(), nums.end(), 0);
  if (sum % 2 == 1)
    return false;
  int n = sum / 2;
  vector<int> dp(n + 1, 0);
  for (int i = 0; i < nums.size(); i++) {
    for (int j = n; j >= nums[i]; j--) {
      dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
    }
  }
  return dp[n] == n;
}

// 01背包问题，包容量为数组总和的一半。排除其为奇数的情况。dp[j]表示容量为j的包，可容纳物品最大重量或最大价值（均为nums[i]）
// 如果dp[target]==target，包容量被完全装满，意为物品nums[i]可以凑整为数组的一半，返回真。

// 可否分割主要看总和sum的一半target是否为偶数。如果是则背包总量为target。重量和价格均为数字值
// 鉴于数字数量和大小有限，故dp[j]表示最大数量20000的一半10001即可。
// dp[j]代表j重量之内能能容纳的最大价值，即target数量下的最大价值，如果dp[target]=target说明可以等分
bool canPartition1(vector<int>& nums) {
  int sum = accumulate(nums.begin(), nums.end(), 0);
  if (sum % 2 == 1)
    return false;
  int target = sum / 2;
  vector<int> dp(10001, 0);
  for (int i = 0; i < nums.size(); i++) {
    for (int j = target; j >= nums[i]; j--) {
      dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]);
    }
  }
  if (dp[target] == target)
    return true;
  return false;
}

int main() {
  vector<int> nums1 = {1, 5, 11, 5};
  vector<int> nums2 = {1, 2, 3, 5};
  cout << canPartition(nums1) << " " << canPartition(nums2) << endl;
  cout << canPartition1(nums1) << " " << canPartition1(nums2) << endl;
  return 0;
}