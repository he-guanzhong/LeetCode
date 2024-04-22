#include "head.h"
/* 312. 戳气球
有 n 个气球，编号为0 到 n - 1，每个气球上都标有一个数字，这些数字存在数组 nums
中。
现在要求你戳破所有的气球。戳破第 i 个气球，你可以获得 nums[i - 1] * nums[i] *
nums[i + 1] 枚硬币。 这里的 i - 1 和 i + 1 代表和 i 相邻的两个气球的序号。如果 i
- 1或 i + 1 超出了数组的边界，那么就当它是一个数字为 1 的气球。
求所能获得硬币的最大数量
示例 1：
输入：nums = [3,1,5,8]
输出：167
解释：
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
示例 2：
输入：nums = [1,5]
输出：10 */

int maxCoins(vector<int>& nums) {}

// 动态规划，先增广nums左右边界1的新容器val，避免越界。动态规划矩阵dp[i][j]表示开区间(i,j)内戳气球最大值，其大小为n+2，且默认值为0
// 三层遍历，从val[0,n+1]右侧开始遍历左边界i，允许范围[1,n-1]。终点为右边界，允许范围[i+2,n+1]。
// 对[i+1,j-1]范围内k，每次取值。计算其乘积总和,并叠加以k划分(i,k)的结果，保存最大值，作为最终的dp[i][j]
// 最终dp[0][n+1]即(0,n+1)范围内乘积最大值。时间复杂度O(n)=n^3，空间复杂度O(n)=n^2
int maxCoins1(vector<int>& nums) {
  int n = nums.size();
  vector<int> val(n + 2, 1);
  for (int i = 0; i < n; i++)
    val[i + 1] = nums[i];
  vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
  for (int i = n - 1; i >= 0; i--) {
    for (int j = i + 2; j <= n + 1; j++) {
      for (int k = i + 1; k <= j - 1; k++) {
        int sum = val[i] * val[j] * val[k] + dp[i][k] + dp[k][j];
        dp[i][j] = max(dp[i][j], sum);
      }
    }
  }
  return dp[0][n + 1];
}

int main() {
  vector<int> nums1 = {3, 1, 5, 8}, nums2 = {1, 5};
  cout << maxCoins(nums1) << " " << maxCoins(nums2) << endl;
  cout << maxCoins1(nums1) << " " << maxCoins1(nums2) << endl;
  return 0;
}