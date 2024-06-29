#include "head.h"
/* 392. 判断子序列
给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。
（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。
进阶：
如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >=
10亿，你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？
示例 1：
输入：s = "abc", t = "ahbgdc"
输出：true
示例 2：
输入：s = "axc", t = "ahbgdc"
输出：false */

// 问题转化为求两个字符串公共子序列长度，若其等于s.size即为真。区别在于，本题s必短于t，末尾元素不等时删除t[j-1]元素即可，不必删除s[i-1]
bool isSubsequence(string s, string t) {
  vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
  for (int i = 1; i <= s.size(); i++) {
    for (int j = 1; j <= t.size(); j++) {
      if (s[i - 1] == t[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  return s.size() == dp[s.size()][t.size()];
}

// s为t的子序列，s必比t短。可以求s与t的公共最长子序列。dp[i][j]代表以s[i-1]结尾的s和以t[j-1]结尾的t，最长子序列
// 显然，初始化dp[i][j]=0，因为公共序列一开始不存在。
// 递推公式。如果s[i-1]==t[j-1]，则dp[i][j]=dp[i-1][j-1]+1。如果二者不相等，则dp[i][j]=dp[i][j-1]，因为要跳过t[j-2]的位置
// 返回值是，末端dp[s.size][t.size]==s.size，即公共子串长度就是s长度
bool isSubsequence1(string s, string t) {
  vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
  for (int i = 1; i <= s.size(); i++) {
    for (int j = 1; j <= t.size(); j++) {
      if (s[i - 1] == t[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = dp[i][j - 1];
    }
  }
  return dp[s.size()][t.size()] == s.size();
}

// 双指针法。i、j指向字符串s/t初始位置，元素相等i\j都右移，不等则只有j右移。最后查看i是否移至s的末尾
bool isSubsequence2(string s, string t) {
  int i = 0, j = 0;
  while (i < s.size() && j < t.size()) {
    if (s[i] == t[j])
      i++;
    j++;
  }
  return i == s.size();
}
int main() {
  string s1 = "abc", t1 = "ahbgdc";
  string s2 = "axc", t2 = "ahbgdc";
  cout << isSubsequence(s1, t1) << " " << isSubsequence(s2, t2) << endl;
  cout << isSubsequence2(s1, t1) << " " << isSubsequence2(s2, t2) << endl;
  return 0;
}