#include "head.h"
/* 1035. 不相交的线
在两条独立的水平线上按给定的顺序写下 nums1 和 nums2 中的整数。
现在，可以绘制一些连接两个数字 nums1[i] 和 nums2[j]
的直线，这些直线需要同时满足满足：
     nums1[i] == nums2[j]
    且绘制的直线不与任何其他连线（非水平线）相交。
请注意，连线即使在端点也不能相交：每个数字只能属于一条连线。
以这种方法绘制线条，并返回可以绘制的最大连线数。
示例 1：
输入：nums1 = [1,4,2], nums2 = [1,2,4]
输出：2
解释：可以画出两条不交叉的线，如上图所示。
但无法画出第三条不相交的直线，因为从 nums1[1]=4 到 nums2[2]=4 的直线将与从
nums1[2]=2 到 nums2[1]=2 的直线相交。
示例 2：
输入：nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
输出：3
示例 3：
输入：nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
输出：2 */

// 问题转化为，两个数组公共最长子序列问题
int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
  vector<vector<int>> dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
  for (int i = 1; i <= nums1.size(); i++) {
    for (int j = 1; j <= nums2.size(); j++) {
      if (nums1[i - 1] == nums2[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  return dp[nums1.size()][nums2.size()];
}

// 转化问题为，求两个数组公共子序列的最大长度。dp[i][j]表示以nums[i-1]和nums[j-1]为结尾的最长子序列数
// 末尾元素相等，则取dp[i-1][j-1]+1，若末尾元素不等，则延续上一元素最大值
int maxUncrossedLines1(vector<int>& nums1, vector<int>& nums2) {
  vector<vector<int>> dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
  for (int i = 1; i <= nums1.size(); i++) {
    for (int j = 1; j <= nums2.size(); j++) {
      if (nums1[i - 1] == nums2[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
    }
  }
  return dp[nums1.size()][nums2.size()];
}

// 一维版本
int maxUncrossedLines2(vector<int>& nums1, vector<int>& nums2) {
  vector<int> dp(nums2.size() + 1, 0);
  for (int i = 1; i <= nums1.size(); i++) {
    int pre = dp[0];
    for (int j = 1; j <= nums2.size(); j++) {
      int cur = dp[j];  // 保存上一周期值
      if (nums1[i - 1] == nums2[j - 1])
        dp[j] = pre + 1;
      else
        dp[j] = max(dp[j], dp[j - 1]);
      pre = cur;  // 更新左上值
    }
  }
  return dp[nums2.size()];
}
int main() {
  vector<int> nums1 = {1, 4, 2}, nums2 = {1, 2, 4};
  vector<int> nums3 = {2, 5, 1, 2, 5}, nums4 = {10, 5, 2, 1, 5, 2};
  vector<int> nums5 = {1, 3, 7, 1, 7, 5}, nums6 = {1, 9, 2, 5, 1};

  cout << maxUncrossedLines(nums1, nums2) << " "
       << maxUncrossedLines(nums3, nums4) << " "
       << maxUncrossedLines(nums5, nums6) << endl;
  cout << maxUncrossedLines1(nums1, nums2) << " "
       << maxUncrossedLines1(nums3, nums4) << " "
       << maxUncrossedLines1(nums5, nums6) << endl;
  return 0;
}