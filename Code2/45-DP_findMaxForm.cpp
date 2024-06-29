#include "head.h"
/* 474. 一和零
给你一个二进制字符串数组 strs 和两个整数 m 和 n 。
请你找出并返回 strs 的最大子集的长度，该子集中 最多 有 m 个 0 和 n 个 1 。
如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集 。
示例 1：
  输入：strs = ["10", "0001", "111001", "1", "0"], m = 5, n = 3
  输出：4
  解释：最多有 5 个 0 和 3 个 1 的最大子集是 {"10","0001","1","0"} ，因此答案是
4 。 其他满足题意但较小的子集包括 {"0001","1"} 和 {"10","1","0"} 。{"111001"}
    不满足题意，因为它含 4 个 1 ，大于 n 的值 3 。
示例 2：
  输入：strs = ["10", "0", "1"], m = 1, n = 1
  输出：2
  解释：最大的子集是 {"0", "1"} ，所以答案是 2 。*/

int findMaxForm(vector<string>& strs, int m, int n) {
  vector<vector<int>> dp(m + 1, vector<int>(n + 1));
  dp[0][0] = 0;
  vector<int> zero(strs.size()), one(strs.size());
  for (int i = 0; i < strs.size(); i++) {
    for (char c : strs[i]) {
      if (c == '0')
        zero[i]++;
      else if (c == '1')
        one[i]++;
    }
  }
  for (int i = 0; i < strs.size(); i++) {
    for (int j = m; j >= zero[i]; j--) {
      for (int k = n; k >= one[i]; k--) {
        dp[j][k] = max(dp[j][k], dp[j - zero[i]][k - one[i]] + 1);
      }
    }
  }
  return dp[m][n];
}

// 二维的0-1背包，背包容量m、n，字符串为物品两个属性重量，求最多物品数。dp[i][j]表示i个0和j个1之内，最长子串长度。全部初始化为0
// 统计每个字符串01数量，从后向前遍历，dp[i][j]分放和不放该串两种情况，即没有该串0和1数量容量的dp，再加一，取其和原值最大值

// 最大子集，是指里面所有元素的0和1统计数量，要小于等于m和n，故例子二的{"10","0","1"}子集是自身不满足要求
// 0-1背包的二维形式，m和n为背包容量，dp[i][j]代表i和j容量之内，可行的字符串个数。
// 对每个字符串，统计其0和1的数量，从mn后向前遍历因为容量大于01数量的包，必能容纳01这个字符串。
// 递推公式是dp[i][j]=max()，因为不同字符串要取最大值。当前dp[i][j]要看当前字符串，没有zeroNum个0和oneNum个1时的数量，再加一
// 时间复杂度O(mnk)，其中k为字符串容器的size
int findMaxForm1(vector<string>& strs, int m, int n) {
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
  for (string str : strs) {
    int zeroNum = 0, oneNum = 0;
    for (char c : str) {
      if (c == '0')
        zeroNum++;
      else
        oneNum++;
    }
    for (int i = m; i >= zeroNum; i--) {
      for (int j = n; j >= oneNum; j--) {
        dp[i][j] = max(dp[i][j], dp[i - zeroNum][j - oneNum] + 1);
      }
    }
  }
  return dp[m][n];
}

int main() {
  vector<string> strs1 = {"10", "0001", "111001", "1", "0"};
  vector<string> strs2 = {"10", "0", "1"};
  cout << findMaxForm(strs1, 5, 3) << " " << findMaxForm(strs2, 1, 1) << endl;
  cout << findMaxForm1(strs1, 5, 3) << " " << findMaxForm1(strs2, 1, 1) << endl;
  return 0;
}