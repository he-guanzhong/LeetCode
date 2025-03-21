#include "head.h"

/* 953. 验证外星语词典
某种外星语也使用英文小写字母，但可能顺序 order
不同。字母表的顺序（order）是一些小写字母的排列。
给定一组用外星语书写的单词 words，以及其字母表的顺序
order，只有当给定的单词在这种外星语中按字典序排列时，返回 true；否则，返回
false。
示例 1：
  输入：words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
  输出：true
  解释：在该语言的字母表中，'h' 位于 'l' 之前，所以单词序列是按字典序排列的。
示例 2：
  输入：words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
  输出：false
  解释：在该语言的字母表中，'d' 位于 'l' 之后，那么 words[0] >
    words[1]，因此单词序列不是按字典序排列的。
示例 3：
  输入：words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
  输出：false
  解释：当前三个字符 "app" 匹配时，第二个字符串相对短一些，然后根据词典编纂规则
    "apple" > "app"，因为 'l' > '∅'，其中 '∅'
    是空白字符，定义为比任何其他字符都小（更多信息）。*/

// 使用数组替代哈希表，记录order每个字符出现的优先级顺序，
bool isAlienSorted(vector<string>& words, string order) {
  int alpha[26] = {0};
  for (int i = 0; i < order.size(); i++)
    alpha[order[i] - 'a'] = i;
  for (int i = 1; i < words.size(); i++) {
    int m = words[i - 1].size(), n = words[i].size();
    bool valid = false;
    for (int j = 0; j < m && j < n; j++) {
      int index1 = words[i - 1][j] - 'a';
      int index2 = words[i][j] - 'a';
      if (alpha[index1] < alpha[index2]) {
        valid = true;
        break;
      } else if (alpha[index1] > alpha[index2]) {
        return false;
      }
    }
    if (!valid && m > n)
      return false;
  }
  return true;
}

int main() {
  vector<string> words1 = {"hello", "leetcode"},
                 words2 = {"word", "world", "row"}, words3 = {"apple", "app"},
                 words4 = {"apap", "app"};
  string order1 = "hlabcdefgijkmnopqrstuvwxyz",
         order2 = "worldabcefghijkmnpqstuvxyz",
         order3 = "abcdefghijklmnopqrstuvwxyz",
         order4 = "abcdefghijklmnopqrstuvwxyz";
  cout << isAlienSorted(words1, order1) << " " << isAlienSorted(words2, order2)
       << " " << isAlienSorted(words3, order3) << " "
       << isAlienSorted(words4, order4) << endl;
  return 0;
}