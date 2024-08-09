#include "head.h"
/* 673. 最长递增子序列的个数
给定一个未排序的整数数组 nums ， 返回最长递增子序列的个数 。
注意 这个数列必须是 严格 递增的。
示例 1:
  输入: [1,3,5,4,7]
  输出: 2
  解释: 有两个最长递增子序列，分别是 [1, 3, 4, 7] 和[1, 3, 5, 7]。
示例 2:
  输入: [2,2,2,2,2]
  输出: 5
  解释: 最长递增子序列的长度是1，并且存在5个子序列的长度为1，因此输出5。 */

// dp[i]表示到i位置最长递增子序列长度,cnt[i]表示以i为结尾最长递增子序列个数。显然，考虑全等数列，初始化长度、个数初始化均为1
// 使用j切割[0,i]区间，如果nums[i]>nums[j]时，递增长度加一，dp[i]=dp[j]+1。同时由于子序列保持递增，故数量不变cnt[i]=cnt[j]
// 若发现j切割出两个相同长度子序列dp[i]==dp[j]+1，说明递增子序列的数量要增加了，其为cnt[i]+=cnt[j]
// 考虑[3,4,5,5,1,2]数组，后两个数字由于小于前两位，递增子序列长度依然为[1,2]，数量依然为[1,1]。最长子序列不一定包含最后一位数字。
// 因此要额外记录最长子序列长度maxlen，其初始值是1，而非0。二次遍历dp[i]，找到以i结尾的各个递增序列点，统计其数量cnt[i]之和
int findNumberOfLIS(vector<int>& nums) {
  vector<int> dp(nums.size(), 1);
  vector<int> cnt(nums.size(), 1);
  int maxLen = 1;
  for (int i = 1; i < nums.size(); i++) {
    for (int j = 0; j < i; j++) {
      if (nums[i] > nums[j]) {
        if (dp[i] < dp[j] + 1) {  // 最长子序列长度延申
          dp[i] = dp[j] + 1;
          cnt[i] = cnt[j];
        } else if (dp[i] == dp[j] + 1) {
          cnt[i] += cnt[j];
        }
        maxLen = max(maxLen, dp[i]);  // 每次切割都统计最大长度
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (dp[i] == maxLen)
      ans += cnt[i];
  }
  return ans;
}

int main() {
  vector<int> nums1 = {1, 3, 5, 4, 7}, nums2 = {2, 2, 2, 2, 2},
              nums3 = {1, 2, 4, 3, 5, 4, 7, 2};
  cout << findNumberOfLIS(nums1) << " " << findNumberOfLIS(nums2) << " "
       << findNumberOfLIS(nums3) << endl;
  return 0;
}