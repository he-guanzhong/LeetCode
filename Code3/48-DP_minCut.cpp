#include "head.h"
/* 132. 分割回文串 II
给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文串。
返回符合要求的 最少分割次数 。
示例 1：
  输入：s = "aab"
  输出：1
  解释：只需一次分割就可将 s 分割成 ["aa","b"] 这样两个回文子串。
示例 2：
  输入：s = "a"
  输出：0
示例 3：
  输入：s = "ab"
  输出：1 */

int minCut(string s) {
  int n = s.size();
  vector<vector<bool>> isPalin(n, vector<bool>(n, false));
  for (int i = n - 1; i >= 0; i--) {
    for (int j = i; j < n; j++) {
      if (s[i] == s[j])
        isPalin[i][j] = j - i < 3 ? true : isPalin[i + 1][j - 1];
    }
  }
  vector<int> dp(n, 0);
  for (int i = 0; i < n; i++)
    dp[i] = i;
  for (int i = 0; i < n; i++) {
    if (isPalin[0][i]) {
      dp[i] = 0;
      continue;
    }
    for (int j = 0; j < i; j++) {
      if (isPalin[j + 1][i])
        dp[i] = min(dp[i], dp[j] + 1);
    }
  }
  return dp[n - 1];
}

// 先求所有子串是否回文矩阵。[0,i]内最少分割的回文次数，取决于[0,j]内最小次数，和[j+1,i]是不是回文串，如果是，则切割一次dp[j]+1
// 初始化dp[i]=i，因为最差的情况就是每个字符一切割。i从小到大顺序遍历，注意如果[0,i]直接回文，dp[i]=0
int minCut1(string s) {
  vector<vector<bool>> isPalindrome(s.size(), vector<bool>(s.size(), 0));
  for (int i = s.size() - 1; i >= 0; i--) {
    for (int j = i; j < s.size(); j++) {
      if (s[i] == s[j] && (j - i < 3 || isPalindrome[i + 1][j - 1]))
        isPalindrome[i][j] = true;
    }
  }
  vector<int> dp(s.size(), 0);
  for (int i = 0; i < s.size(); i++)
    dp[i] = i;
  for (int i = 1; i < s.size(); i++) {
    if (isPalindrome[0][i]) {
      dp[i] = 0;
      continue;
    }
    for (int j = 0; j < i; j++) {
      if (isPalindrome[j + 1][i])
        dp[i] = min(dp[i], dp[j] + 1);
    }
  }
  return dp[s.size() - 1];
}

int main() {
  string s1 = "aab", s2 = "a", s3 = "ab";
  cout << minCut(s1) << " " << minCut(s2) << " " << minCut(s3) << endl;
  cout << minCut1(s1) << " " << minCut1(s2) << " " << minCut1(s3) << endl;
  return 0;
}