#include <cstring>
#include "head.h"
/* 1002. 查找共用字符
给你一个字符串数组 words ，请你找出所有在 words 的每个字符串中都出现的共用字符（
包括重复字符），并以数组形式返回。你可以按 任意顺序 返回答案。
示例 1：
  输入：words = ["bella","label","roller"]
  输出：["e","l","l"]
示例 2：
  输入：words = ["cool","lock","cook"]
  输出：["c","o"]
提示：
    1 <= words.length <= 100
    1 <= words[i].length <= 100
    words[i] 由小写英文字母组成 */

vector<string> commonChars(vector<string>& words) {
  int n = words.size();
  vector<vector<int>> dp(n, vector<int>(26, 0));
  for (int i = 0; i < words.size(); i++) {
    for (int j = 0; j < words[i].size(); j++)
      dp[i][words[i][j] - 'a']++;
  }
  vector<string> ans;
  for (int j = 0; j < 26; j++) {
    int maxVal = INT_MAX;
    for (int i = 0; i < n; i++) {
      maxVal = min(maxVal, dp[i][j]);
    }
    if (maxVal != INT_MAX)
      for (int k = 0; k < maxVal; k++) {
        char t = 'a' + j;
        ans.push_back(string(1, t));
      }
  }
  return ans;
}

// 本质上是一个二维哈希表，记录每一个单词中，每一个字符的出现次数。最终对每个字符出现的次数取小
// 初始化两行哈希表。第一个单词的基准哈希表hash。然后对第2个及以后单词，维护滚动哈希表，不断更新基准哈希表
// char转换string的四种方法：1.构造函数string(1,c)或string(c)，1代表后续字符串中要转换的数量
// 2.相加一个空string，隐式转换string+=""+c。3.不得使用to_string(char)，因为其限定了只能是数值类型int/float
// 使用对象stringstream ss，ss<<c; string= ss.str()
vector<string> commonChars1(vector<string>& words) {
  int hash[26] = {0};
  int curHash[26] = {0};
  for (int j = 0; j < words[0].size(); j++)
    hash[words[0][j] - 'a']++;
  for (int i = 1; i < words.size(); i++) {
    memset(curHash, 0, sizeof(curHash));
    for (int j = 0; j < words[i].size(); j++) {
      curHash[words[i][j] - 'a']++;
    }
    for (int k = 0; k < 26; k++) {
      hash[k] = min(hash[k], curHash[k]);
    }
  }
  vector<string> ans;
  for (int i = 0; i < 26; i++) {
    while (hash[i]) {
      string tmp(1, i + 'a');
      ans.push_back(tmp);
      hash[i]--;
    }
  }
  return ans;
}

int main() {
  vector<string> word1 = {"bella", "label", "roller"};
  vector<string> word2 = {"cool", "lock", "cook"};
  printVector(commonChars(word1));
  printVector(commonChars(word2));
  printVector(commonChars1(word1));
  printVector(commonChars1(word2));
  return 0;
}