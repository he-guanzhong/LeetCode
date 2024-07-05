#include "head.h"
/* 516. 最长回文子序列
给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。
子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。
示例 1：
  输入：s = "bbbab"
  输出：4
  解释：一个可能的最长回文子序列为 "bbbb" 。
示例 2：
  输入：s = "cbbd"
  输出：2
  解释：一个可能的最长回文子序列为 "bb" 。 */

int longestPalindromeSubseq(string s) {
  int n = s.size();
  vector<vector<int>> dp(n, vector<int>(n, 0));
  for (int i = n - 1; i >= 0; i--) {
    for (int j = i; j < n; j++) {
      if (s[i] == s[j])
        dp[i][j] = j - i < 3 ? j - i + 1 : dp[i + 1][j - 1] + 2;
      else
        dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
    }
  }
  return dp[0][n - 1];
}

// dp[i][j]表示[i,j]子序列最长回文长度，注意不是连续子串长度。故二维矩阵先初始化左上-右下斜线为1，求长度问题，一定要单独初始化
// 遍历方向为朝右上，首尾元素相等，dp[i][j]为掐头去尾长度+2。若j从i+1开始遍历，则已考虑了连续两个元素相等的情况，故不必对子序列长度为1、2特殊处理
// 首尾元素不等，继承分别不考虑首、尾两种情况的最大值。最终返回的是右上角值，[0,size-1]范围内最长子序列长度。

// 本题求最长子序列（不连续），故非子串（连续）。故dp[i][j]不能代表是否回文，而代表以i开始j结束，最长回文子序列的长度
// 初始化时，单个字母子序列长度必为1，故dp[i][i]=1
// 递推公式，当子序列首尾元素相等时，则子序列长度+2，dp[i][j]=dp[i+1][j-1]+2。子序列首尾元素不相等，则要看不取首、尾的最长子序列长度dp[i+1][j]或dp[i][j-1]
// 遍历顺序，一定是从左下到右上。注意由于已经初始化，则j要从i+1开始算。最终返回值是以0为首，s.size()-1为尾的全部长度dp[0][s.size()-1]
int longestPalindromeSubseq1(string s) {
  vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
  for (int i = 0; i < s.size(); i++)
    dp[i][i] = 1;
  for (int i = s.size() - 1; i >= 0; i--) {
    for (int j = i + 1; j < s.size(); j++) {
      if (s[i] == s[j])
        dp[i][j] = dp[i + 1][j - 1] + 2;
      else
        dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
    }
  }
  return dp[0][s.size() - 1];
}

int main() {
  string s1 = "bbbab", s2 = "cbbd";
  string s3 = "intention", s4 = "execution";
  cout << longestPalindromeSubseq(s1) << " " << longestPalindromeSubseq(s2)
       << " " << longestPalindromeSubseq(s3) << " "
       << longestPalindromeSubseq(s4) << endl;
  cout << longestPalindromeSubseq1(s1) << " " << longestPalindromeSubseq1(s2)
       << " " << longestPalindromeSubseq1(s3) << " "
       << longestPalindromeSubseq1(s4) << endl;
  return 0;
}