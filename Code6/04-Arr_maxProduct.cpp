#include "head.h"
/* 318. 最大单词长度乘积
给你一个字符串数组 words ，找出并返回 length(words[i]) * length(words[j])
的最大值，并且这两个单词不含有公共字母。如果不存在这样的两个单词，返回 0 。
示例 1：
  输入：words = ["abcw","baz","foo","bar","xtfn","abcdef"]
  输出：16
  解释：这两个单词为 "abcw", "xtfn"。
示例 2：
  输入：words = ["a","ab","abc","d","cd","bcd","abcd"]
  输出：4
  解释：这两个单词为 "ab", "cd"。
示例 3：
  输入：words = ["a","aa","aaa","aaaa"]
  输出：0
  解释：不存在这样的两个单词。
提示：
    2 <= words.length <= 1000
    1 <= words[i].length <= 1000
    words[i] 仅包含小写字母  */

int maxProduct(vector<string>& words) {
  vector<int> dp(words.size(), 0);
  for (int i = 0; i < words.size(); i++) {
    for (int j = 0; j < words[i].size(); j++) {
      dp[i] |= 1 << (words[i][j] - 'a');
    }
  }
  int ans = 0;
  for (int i = 0; i < dp.size(); i++) {
    for (int j = i + 1; j < dp.size(); j++) {
      if ((dp[i] & dp[j]) == 0) {
        int tmp = words[i].size() * words[j].size();
        ans = max(ans, tmp);
      }
    }
  }
  return ans;
}

// 32位整型数字可表征26个字母是否出现过。每一个word中各字符出现情况，记录于num。
// 单词两两比较，按位与&结果==0，表示二者没有共同字符。默认时间复杂度O(n^2)。
// 考虑a,aa,aaa这类同一种字符组成的，只需记录其最大长度即可。因此，使用哈希表记录每型的最大长度。
// 遍历哈希表，即可获得最大长度
// 注意：1.size()函数返回的是无符号整型，不能直接和int相比。2.按位与&优先级低于比较符号==
int maxProduct1(vector<string>& words) {
  vector<int> nums(words.size(), 0);
  unordered_map<int, int> umap;
  for (int i = 0; i < words.size(); i++) {
    for (const char& c : words[i]) {
      nums[i] |= 1 << (c - 'a');
    }
    if (umap.count(nums[i]))
      umap[nums[i]] = max(umap[nums[i]], (int)words[i].size());
    else
      umap[nums[i]] = words[i].size();
  }
  int ans = 0;
  for (const auto& i : umap) {
    for (const auto& j : umap) {
      if ((i.first & j.first) == 0)
        ans = max(ans, int(i.second * j.second));
    }
  }
  return ans;
}

int main() {
  vector<string> words1 = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
  vector<string> words2 = {"a", "ab", "abc", "d", "cd", "bcd", "abcd"};
  vector<string> words3 = {"a", "aa", "aaa", "aaaa"};

  cout << maxProduct(words1) << " " << maxProduct(words2) << " "
       << maxProduct(words3) << endl;
  cout << maxProduct1(words1) << " " << maxProduct1(words2) << " "
       << maxProduct1(words3) << endl;
  return 0;
}
