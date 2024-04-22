#include "head.h"
/* 72. 编辑距离
给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数。
你可以对一个单词进行如下三种操作：
插入一个字符
删除一个字符
替换一个字符
示例 1：
输入：word1 = "horse", word2 = "ros"
输出：3
解释：
horse -> rorse (将 'h' 替换为 'r')
rorse -> rose (删除 'r')
rose -> ros (删除 'e')
示例 2：
输入：word1 = "intention", word2 = "execution"
输出：5
解释：
intention -> inention (删除 't')
inention -> enention (将 'i' 替换为 'e')
enention -> exention (将 'n' 替换为 'x')
exention -> exection (将 'n' 替换为 'c')
exection -> execution (插入 'u') */

// dp[i][j]表示以s[i-1]和t[j-1]结尾字符串，相转化的最小操作次数。
// 初始化dp[i][0]=i，因为从s删到空，需要次数为i，dp[0][j]=j,因为从空增添到t，需要次数为j。
// 末尾元素相等，不增次数。末尾元素不相等，要看删除s，删除t（新增s），替换s，三种情况最小值，再多加一步。最终返回矩阵右下角
int minDistance(string word1, string word2) {
  vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
  for (int i = 0; i <= word1.size(); i++)
    dp[i][0] = i;
  for (int j = 0; j <= word2.size(); j++)
    dp[0][j] = j;
  for (int i = 1; i <= word1.size(); i++) {
    for (int j = 1; j <= word2.size(); j++) {
      if (word1[i - 1] == word2[j - 1])
        dp[i][j] = dp[i - 1][j - 1];
      else
        dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
    }
  }
  return dp[word1.size()][word2.size()];
}

// dp[i][j]表示以word1[i-1]和word2[j-1]为结尾的两子串，最小剪辑距离。故dp[i][0]表示i长度子串要缩减为空，所需操作为i,dp[i][0]=i。同理dp[0][j]=j
// 递推公式，如果两子串末尾相等，则无需剪辑dp[i][j]=dp[i-1][j-1]。如两子串末尾不相等，则word1必剪辑次数+1，可能为删除dp[i-1][j]，可能为新增dp[i][j-1]，可能为替换dp[i-1][j-1]
// 注意，word2元素的删除，即可认为是word1元素的新增。dp[i][j]=min(dp[i-1][j-1],dp[i][j-1],dp[i-1][j])+1
// dp[word1.size()][word2.size()]即为两个字符串，相互变换，所求的最小剪辑距离
// C++11中，min函数中加{}，初始化列表，可以比较多个元素大小，但要求其中元素类型必须一致，不得uint,int,float
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
        dp[i][j] = min({dp[i - 1][j - 1], dp[i][j - 1], dp[i - 1][j]}) + 1;
    }
  }
  return dp[word1.size()][word2.size()];
}

int main() {
  string s1 = "horse", t1 = "ros";
  string s2 = "intention", t2 = "execution";
  cout << minDistance(s1, t1) << " " << minDistance(s2, t2) << endl;
  cout << minDistance1(s1, t1) << " " << minDistance1(s2, t2) << endl;

  return 0;
}