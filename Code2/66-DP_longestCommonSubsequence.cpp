#include "head.h"
/* 1143. 最长公共子序列
给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列
的长度。如果不存在 公共子序列 ，返回 0 。
一个字符串的 子序列
是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
    例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。
示例 1：
  输入：text1 = "abcde", text2 = "ace"
  输出：3
  解释：最长公共子序列是 "ace" ，它的长度为 3 。
示例 2：
  输入：text1 = "abc", text2 = "abc"
  输出：3
  解释：最长公共子序列是 "abc" ，它的长度为 3 。
示例 3：
  输入：text1 = "abc", text2 = "def"
  输出：0
  解释：两个字符串没有公共子序列，返回 0 。 */

int longestCommonSubsequence(string text1, string text2) {
  int m = text1.size(), n = text2.size();
  vector<int> dp(n + 1, 0);
  for (int i = 1; i <= m; i++) {
    int pre = dp[0];
    for (int j = 1; j <= n; j++) {
      int cur = dp[j];
      if (text1[i - 1] == text2[j - 1])
        dp[j] = pre + 1;
      else
        dp[j] = max(dp[j - 1], dp[j]);
      pre = cur;
    }
  }
  return dp[n];
}

// dp[i][j]表示以text1[i-1]和text2[j-1]结尾的子序列，公共最长值。末尾元素相等dp[i][j]=dp[i-1][j-1]+1
// 末尾元素不等，则延续dp[i][j-1]和dp[i-1][j]二者的最大值。最终返回为矩阵右下角的值

// 最长公共子序列，要求可以不连续，故dp[i][j]表示以nums[i-1]和nums[j-1]为结尾的子序列，最长公共值
// 递推公式，如果两个最后一位相等，则dp[i][j]=dp[i-1][j-1]+1。如果不相等，则延续最大值dp[i][j]=max(dp[i-1][j],dp[i][j-1])
// 最终返回值为，矩阵右下角最后一个dp的值
int longestCommonSubsequence1(string text1, string text2) {
  vector<vector<int>> dp(text1.size() + 1, vector<int>(text2.size() + 1, 0));
  for (int i = 1; i <= text1.size(); i++) {
    for (int j = 1; j <= text2.size(); j++) {
      if (text1[i - 1] == text2[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  return dp[text1.size()][text2.size()];
}

// 一维数组写法。由于dp[i][j]需要依赖上、左、上左三个方向的值，故遍历方向只能从左至右。
// 使用pre保存左上值。
int longestCommonSubsequence2(string text1, string text2) {
  vector<int> dp(text2.size() + 1, 0);
  for (int i = 1; i <= text1.size(); i++) {
    int pre = dp[0];
    for (int j = 1; j <= text2.size(); j++) {
      int cur = dp[j];
      if (text1[i - 1] == text2[j - 1])
        dp[j] = pre + 1;
      else
        dp[j] = max(dp[j], dp[j - 1]);
      pre = cur;
    }
  }
  return dp[text2.size()];
}

int main() {
  string text1 = "abcde", text2 = "ace";
  string text3 = "abc", text4 = "abc";
  string text5 = "abc", text6 = "def";
  string text7 = "ezupkr", text8 = "ubmrapg";
  string text9 = "abcba", text0 = "abcbcba";
  cout << longestCommonSubsequence(text1, text2) << " "
       << longestCommonSubsequence(text3, text4) << " "
       << longestCommonSubsequence(text5, text6) << " "
       << longestCommonSubsequence(text7, text8) << " "
       << longestCommonSubsequence(text9, text0) << endl;
  cout << longestCommonSubsequence1(text1, text2) << " "
       << longestCommonSubsequence1(text3, text4) << " "
       << longestCommonSubsequence1(text5, text6) << " "
       << longestCommonSubsequence1(text7, text8) << " "
       << longestCommonSubsequence1(text9, text0) << endl;
  return 0;
}