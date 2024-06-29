#include "head.h"
/* 139. 单词拆分
给你一个字符串 s 和一个字符串列表 wordDict
作为字典。请你判断是否可以利用字典中出现的单词拼接出 s 。
注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
示例 1：
  输入: s = "leetcode", wordDict = ["leet", "code"]
  输出: true
  解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。
示例 2：
  输入: s = "applepenapple", wordDict = ["apple", "pen"]
  输出: true
  解释: 返回 true 因为 "applepenapple" 可以由 "apple" "pen" "apple" 拼接成。
     注意，你可以重复使用字典中的单词。
示例 3：
  输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
  输出: false */

bool wordBreak(string s, vector<string>& wordDict) {
  unordered_set<string> uset(wordDict.begin(), wordDict.end());
  vector<int> dp(s.size() + 1, 0);
  dp[0] = 1;
  for (int i = 0; i < s.size(); i++) {
    for (int j = 0; j <= i; j++) {
      string tmp = s.substr(j, i - j + 1);
      if (uset.find(tmp) != uset.end() && dp[j] == 1) {
        dp[i + 1] = dp[j];
      }
    }
  }
  return dp[s.size()] == 1;
}

// dp[i]表示到第i个字母（其下标为i-1）为止的字符串能否被组成。固定i，在[0,i]内使用j分割为两部分。j范围为[0,i)，因为起始允许空分割，终止下标为i-1
// s子数组长度为i-1-j+1=i-j。注意，dp[0]=true空集必可以组成，dp[i]是否为真，取决于dp[j]是否为真，和单词[j,i]是否能找到
// 注意，考虑案例aaaa,aaa例子，第四个字母dp[j]一旦为真，不允许再覆盖为假，故不能只判断count>0后，让dp[i]=dp[j]

// dp[i]表示长度为i的字符串，是否可以被拼出。初始化时全部设置为false，但是dp[0]表示长度为0字符串必可以拼出，置为true
// 递推公式为，如果j<i,dp[j]为真，且i-j这部分字符串也可以再字典中找到，就dp[i]为真。
// 遍历顺序。求本体字符有先后顺序，属于求排列，必须先遍历背包，再遍历物品。物品是否是否存在可以使用unordered_set.find来判断
// 时间复杂度n^3，空间复杂度n
bool wordBreak3(string s, vector<string>& wordDict) {
  vector<bool> dp(s.size() + 1, false);
  dp[0] = true;
  unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
  for (int i = 1; i <= s.size(); i++) {
    for (int j = 0; j < i; j++) {
      string word = s.substr(j, i - j);
      if (wordSet.find(word) != wordSet.end() && dp[j] == true)
        dp[i] = true;
    }
  }
  return dp[s.size()];
}

// 也可以使用回溯算法，暴力搜索。返回值是是否搜到了类似信息。时间复杂度2^n，空间复杂度n
bool backtracking1(const string s,
                   const unordered_set<string>& wordSet,
                   int startIndex) {
  if (startIndex >= s.size())
    return true;
  for (int i = startIndex; i < s.size(); i++) {
    string word = s.substr(startIndex, i - startIndex + 1);
    if (wordSet.find(word) != wordSet.end() && backtracking1(s, wordSet, i + 1))
      return true;
  }
  return false;
}
bool wordBreak1(string s, vector<string>& wordDict) {
  unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
  return backtracking1(s, wordSet, 0);
}

// 可以使用记忆化递归，节省资源。使用一个memory数组，记录startIndex之后的必不可以拆分
bool backtracking2(const string& s,
                   const unordered_set<string>& wordSet,
                   int startIndex,
                   vector<bool>& memory) {
  if (startIndex >= s.size())
    return true;
  if (!memory[startIndex])  // 如果发现此位后不能分割，则直接返回
    return memory[startIndex];
  for (int i = startIndex; i < s.size(); i++) {
    string word = s.substr(startIndex, i - startIndex + 1);
    if (wordSet.find(word) != wordSet.end() &&
        backtracking2(s, wordSet, i + 1, memory))
      return true;
  }
  memory[startIndex] = false;
  return false;
}
bool wordBreak2(string s, vector<string>& wordDict) {
  unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
  vector<bool> memory(s.size(), true);
  return backtracking2(s, wordSet, 0, memory);
}

int main() {
  string s1 = "leetcode", s2 = "applepenapple", s3 = "catsandog",
         s4 = "aaaaaaa";
  vector<string> wordDict1 = {"leet", "code"}, wordDict2 = {"apple", "pen"},
                 wordDict3 = {"cats", "dog", "sand", "and", "cat"},
                 wordDict4 = {"aaaa", "aaa"};
  cout << wordBreak(s1, wordDict1) << " " << wordBreak(s2, wordDict2) << " "
       << wordBreak(s3, wordDict3) << " " << wordBreak(s4, wordDict4) << " "
       << endl;
  cout << wordBreak3(s1, wordDict1) << " " << wordBreak3(s2, wordDict2) << " "
       << wordBreak3(s3, wordDict3) << " " << wordBreak3(s4, wordDict4) << " "
       << endl;
  return 0;
}