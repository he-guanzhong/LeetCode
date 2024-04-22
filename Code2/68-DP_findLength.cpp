#include "head.h"
/* 718. 最长重复子数组
给两个整数数组 nums1 和 nums2 ，返回 两个数组中 公共的
、长度最长的子数组的长度。
示例 1： 输入：nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7] 输出：3
解释：长度最长的公共子数组是 [3,2,1] 。
示例 2： 输入：nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0] 输出：5 */

// dp[i][j]为，以第i、j个元素（下标i-1，j-1）为结尾的子数组，最长重复子数组长度。相应地，子数组末尾元素是nums1[i-1]和num2[j-1]
// 初始化注意，dp[i][j]不能表示i、j下标为结尾的子数组，因为递推公式dp[i][j]=dp[i-1][j-1]+1，第一个元素不好考虑。
// 一维数组注意两点。一、由于dp[i][j]由左上角数值得来，故dp[j]内部要从右往左遍历。二、dp转移至下一层时，末尾元素不等时要置0
int findLength(vector<int>& nums1, vector<int>& nums2) {
  int result = 0;
  vector<int> dp(nums2.size() + 1, 0);
  for (int i = 1; i <= nums1.size(); i++) {
    for (int j = nums2.size(); j > 0; j--) {
      if (nums1[i - 1] == nums2[j - 1])
        dp[j] = dp[j - 1] + 1;
      else
        dp[j] = 0;
      result = max(result, dp[j]);
    }
  }
  return result;
}

// dp[i][j]含义是第i、j个元素（即i-1,j-1位置）上的元素为结尾时，最长重复子数组长度
// 初始化，i、j从1开始遍历，初始值全部设置为0。
// 递推公式，当两个子数组，末尾元素相等时nums1[i-1]==nums2[j-1]，则该处长度+1。dp[i][j]=dp[i-1][j-1]+1
int findLength1(vector<int>& nums1, vector<int>& nums2) {
  vector<vector<int>> dp(nums1.size() + 1, vector<int>(nums2.size() + 1, 0));
  int result = 0;
  for (int i = 1; i <= nums1.size(); i++) {
    for (int j = 1; j <= nums2.size(); j++) {
      if (nums1[i - 1] == nums2[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      result = max(result, dp[i][j]);
    }
  }
  return result;
}

// 一维数组。节省空间复杂度。但是内层遍历必须从右向左遍历，另外对于该层，两个子数组尾元素不等时，dp[j]置0，否则会遗传上一轮i的值
int findLength2(vector<int>& nums1, vector<int>& nums2) {
  vector<int> dp(nums2.size() + 1, 0);
  int result = 0;
  for (int i = 1; i <= nums1.size(); i++) {
    for (int j = nums2.size(); j > 0; j--) {
      if (nums1[i - 1] == nums2[j - 1])
        dp[j] = dp[j - 1] + 1;
      else
        dp[j] = 0;  // 额外置0
      result = max(result, dp[j]);
    }
  }
  return result;
}

// 假定dp[i][j]表示以nums1[i]和nums2[j]结尾的最长子数组长度。
// 由于递推公式是从第二行第二列开始，故第一行第一列必须首先特殊处理初始化。
// 如果存在第一行、或第一列的元素等于内部元素，则result一定要将其考虑在内，故遍历时必须从0开始，而不是从1开始
int findLength3(vector<int>& nums1, vector<int>& nums2) {
  vector<vector<int>> dp(nums1.size(), vector<int>(nums2.size(), 0));
  int result = 0;
  for (int i = 0; i < nums1.size(); i++) {
    if (nums1[i] == nums2[0])
      dp[i][0] = 1;
  }
  for (int j = 0; j < nums2.size(); j++) {
    if (nums1[0] == nums2[j])
      dp[0][j] = 1;
  }
  for (int i = 0; i < nums1.size(); i++) {
    for (int j = 0; j < nums2.size(); j++) {
      if (nums1[i] == nums2[j] && i > 0 && j > 0)
        dp[i][j] = dp[i - 1][j - 1] + 1;
      result = max(result, dp[i][j]);
    }
  }
  return result;
}
int main() {
  vector<int> nums1 = {1, 2, 3, 2, 1}, nums2 = {3, 2, 1, 4, 7},
              nums3 = {0, 0, 0, 0, 0}, nums4 = {0, 0, 0, 0, 0},
              nums5 = {1, 2, 3, 2, 8}, nums6 = {5, 6, 1, 4, 7};

  cout << findLength(nums1, nums2) << " " << findLength(nums3, nums4) << " "
       << findLength(nums5, nums6) << endl;
  cout << findLength1(nums1, nums2) << " " << findLength1(nums3, nums4) << " "
       << findLength1(nums5, nums6) << endl;
  return 0;
}