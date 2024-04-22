#include "head.h"
/* 5. 最长回文子串
给你一个字符串 s，找到 s 中最长的回文子串。
如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。
示例 1：
输入：s = "babad"
输出："bab"
解释："aba" 同样是符合题意的答案。
示例 2：
输入：s = "cbbd"
输出："bb" */

string longestPalindrome(string s) {
  int left = 0, len = 0;
  vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
  for (int i = s.size() - 1; i >= 0; i--) {
    for (int j = i; j < s.size(); j++) {
      if (s[i] == s[j])
        dp[i][j] = (j - i < 3) ? true : dp[i + 1][j - 1];
      if (dp[i][j] && j - i + 1 > len) {
        left = i;
        len = j - i + 1;
      }
    }
  }
  return s.substr(left, len);
}

// dp[i][j]表示下标区间[i.j]的字符串是否为回文。额外记录最终应该返回的，起始点left和长度len，从左下至右上遍历。
// 一次判断，子串首尾是否相等，如相等，分两种情况讨论：长度小于等于3，直接为真，长度大于3，要看[i+1,j+1]的值
// 二次判断，dp[i][j]是否为真，为真则看该子串长度是否大于原值，如更长，则记录新子串起始点和长度。最终返回目标子串。注意，一二次遍历不能混同处理
string longestPalindrome1(string s) {
  vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
  int left = 0, len = 0;
  for (int i = s.size() - 1; i >= 0; i--) {
    for (int j = i; j < s.size(); j++) {
      if (s[i] == s[j]) {
        dp[i][j] = (j - i < 3) ? true : dp[i + 1][j - 1];
        if (dp[i][j] && j - i + 1 > len) {
          len = j - i + 1;
          left = i;
        }
      }
    }
  }
  return s.substr(left, len);
}

int main() {
  string s1 = "babad", s2 = "cbbd", s3 = "aacabdkacaa";
  cout << longestPalindrome(s1) << " " << longestPalindrome(s2) << " "
       << longestPalindrome(s3) << endl;
  cout << longestPalindrome1(s1) << " " << longestPalindrome1(s2) << " "
       << longestPalindrome1(s3) << endl;
  return 0;
}