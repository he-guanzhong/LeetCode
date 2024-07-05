#include "head.h"
/* 583. 两个字符串的删除操作
给定两个单词 word1 和 word2 ，返回使得 word1 和  word2 相同所需的最小步数。
每步 可以删除任意一个字符串中的一个字符。
示例 1：
  输入: word1 = "sea", word2 = "eat"
  输出: 2
  解释: 第一步将 "sea" 变为 "ea" ，第二步将 "eat "变为 "ea"
示例  2:
  输入：word1 = "leetcode", word2 = "etco"
  输出：4 */

int minDistance(string word1, string word2) {
  int m = word1.size(), n = word2.size();
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (word1[i - 1] == word2[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  return m + n - 2 * dp[m][n];
}

// 首选，将问题转换为，求公共字符串长度。两字符串总长度减其二倍，即为删除操作数
// 次选，动态规划dp[i][j]表示以s[i-1]和t[j-1]末尾的元素，要想等需删除次数。初始化dp[i][0]=dp[0][j]=i，即删到空需将所有字母均删除
// 末尾元素相等，无需删除dp[i][j]=dp[i-1][j-1]。末尾元素不等，取删除s末尾和t末尾的最小值，不必考虑左上角，因为已经考虑过了

// dp[i][j]表示以word1[i-1]和word2[j-1]为结尾的字符串，若想相等，最少删除字符数。
// 初始化dp[i][0]表示，i长度的word1，想删除到空，须删除的字符数，故dp[i][0]=i，同理dp[0][j]=j
// 递推公式，如果两子串末字母相等，则不必增加删除字符数，dp[i][j]=dp[i-1][j-1]。若末字母不等，则必须在二子串之中删除一个字符,取最小。dp[i][j]=min(dp[i-1][j]+1,dp[i][j-1]+1)
// 最终返回值即为矩阵右下角，两个字符串总长下的dp[word1.size()][word2.size()]
int minDistance1(string word1, string word2) {
  vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
  for (int i = 1; i <= word1.size(); i++)
    dp[i][0] = i;
  for (int j = 1; j <= word2.size(); j++)
    dp[0][j] = j;
  for (int i = 1; i <= word1.size(); i++) {
    for (int j = 1; j <= word2.size(); j++) {
      if (word1[i - 1] == word2[j - 1])
        dp[i][j] = dp[i - 1][j - 1];
      else
        dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
    }
  }
  return dp[word1.size()][word2.size()];
}

// 求公共子序列的长度，dp[i][j]表示以字母word1[i-1]和word2[j-1]为结尾的两个字符串最大子串长度
// 返回值为word1长度-公共子串长度，和word2长度-公共子串长度，二者之和
int minDistance2(string word1, string word2) {
  vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
  for (int i = 1; i <= word1.size(); i++) {
    for (int j = 1; j <= word2.size(); j++) {
      if (word1[i - 1] == word2[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + 1;
      else
        dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
    }
  }
  return word1.size() + word2.size() - 2 * dp[word1.size()][word2.size()];
}

int main() {
  string s1 = "sea", t1 = "eat";
  string s2 = "leetcode", t2 = "etco";
  string s3 = "a", t3 = "b";
  cout << minDistance(s1, t1) << " " << minDistance(s2, t2) << " "
       << minDistance(s3, t3) << endl;
  cout << minDistance1(s1, t1) << " " << minDistance1(s2, t2) << " "
       << minDistance1(s3, t3) << endl;
  return 0;
}