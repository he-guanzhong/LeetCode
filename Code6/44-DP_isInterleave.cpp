#include "head.h"

/* 97. 交错字符串
给定三个字符串 s1、s2、s3，请你帮忙验证 s3 是否是由 s1 和 s2 交错 组成的。
两个字符串 s 和 t 交错 的定义与过程如下，其中每个字符串都会被分割成若干 非空
子字符串：
s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1
交错 是 s1 + t1 + s2 + t2 + s3 + t3 + ... 或者 t1 + s1 + t2 + s2 + t3 + s3 + ...
注意：a + b 意味着字符串 a 和 b 连接。
示例 1：
  输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
  输出：true
示例 2：
  输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
  输出：false
示例 3：
  输入：s1 = "", s2 = "", s3 = ""
  输出：true
提示：
  0 <= s1.length, s2.length <= 100
  0 <= s3.length <= 200
  s1、s2、和 s3 都由小写英文字母组成
进阶：您能否仅使用 O(s2.length) 额外的内存空间来解决它? */

// 不能使用双指针，因为相同的字符可能来自s1或s2，，一旦错选，后续字符都匹配不上。例如在c和ca中挑出cac。
// 动态规划一维做法。由于动态数组开辟于s2，所以一定要保证其有值，所以务必通过交换的方式，使s2.size()>s1.size()
// dp[i+1][j+1]代表了下标[0,i]的s1和下标[0,j]的s2，是否能组成下标[0,i+j+1]的s3。具体取决于s3该位下标究竟与s1还是s2元素相等
// 初始化，dp[0][0]代表空集是否能组成空集，显然可以。dp[0][j+1]代表无s1时，仅凭s2，是否可以构成s3。显然要求s2和s3顺次字母相等
// 递推公式，s3[0,i+j+1]来自于s1[i]，则要求[0,i-1]范围的s1必须满足要求，即dp[i][j+1]为真。对s2同理
bool isInterleave(string s1, string s2, string s3) {
  int m = s1.size(), n = s2.size(), len = s3.size();
  if (m + n != len) return false;
  if (m > n) {
    return isInterleave(s2, s1, s3);
  }
  bool dp[n + 1] = {0};
  dp[0] = true;
  for (int j = 0; j < n && s2[j] == s3[j]; j++) {
    dp[j + 1] = true;
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      dp[j + 1] = (s1[i] == s3[i + j + 1] && dp[j + 1]) ||
                  (s2[j] == s3[i + j + 1] && dp[j]);
    }
  }
  return dp[n];
}

// 动态规划二维做法
bool isInterleave1(string s1, string s2, string s3) {
  if (s1.size() + s2.size() != s3.size()) return false;
  vector<vector<bool>> dp(s1.size() + 1, vector<bool>(s2.size() + 1, false));
  dp[0][0] = true;
  for (int j = 0; j < s2.size() && s2[j] == s3[j]; j++) dp[0][j + 1] = true;
  for (int i = 0; i < s1.size() && s1[i] == s3[i]; i++) dp[i + 1][0] = true;
  for (int i = 0; i < s1.size(); i++) {
    for (int j = 0; j < s2.size(); j++) {
      dp[i + 1][j + 1] = (s1[i] == s3[i + j + 1] && dp[i][j + 1]) ||
                         (s2[j] == s3[i + j + 1] && dp[i + 1][j]);
    }
  }
  return dp[s1.size()][s2.size()];
}

int main() {
  string s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac", s4 = "aadbbbaccc";

  cout << isInterleave(s1, s2, s3) << " " << isInterleave(s1, s2, s4) << " "
       << isInterleave("", "", "") << " " << isInterleave("a", "", "c") << endl;
  return 0;
}