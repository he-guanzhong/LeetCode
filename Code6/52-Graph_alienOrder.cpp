#include "head.h"

/* LCR 114. 火星词典
现有一种使用英语字母的外星文语言，这门语言的字母顺序与英语顺序不同。
给定一个字符串列表 words ，作为这门语言的词典，words 中的字符串已经
按这门新语言的字母顺序进行了排序 。
请你根据该词典还原出此语言中已知的字母顺序，并 按字母递增顺序
排列。若不存在合法字母顺序，返回 "" 。若存在多种可能的合法字母顺序，返回其中
任意一种 顺序即可。
字符串 s 字典顺序小于 字符串 t 有两种情况：
在第一个不同字母处，如果 s 中的字母在这门外星语言的字母顺序中位于 t
中字母之前，那么 s 的字典顺序小于 t 。 如果前面 min(s.length, t.length)
字母都相同，那么 s.length < t.length 时，s 的字典顺序也小于 t 。
示例 1：
  输入：words = ["wrt","wrf","er","ett","rftt"]
  输出："wertf"
示例 2：
  输入：words = ["z","x"]
  输出："zx"
示例 3：
  输入：words = ["z","x","z"]
  输出：""
  解释：不存在合法字母顺序，因此返回 ""。
提示：
  1 <= words.length <= 100
  1 <= words[i].length <= 100
  words[i] 仅由小写英文字母组成 */

string alienOrder(vector<string>& words) {
  unordered_map<char, int> inDeg;
  unordered_map<char, unordered_set<char>> umap;
  for (const auto& word : words) {
    for (int i = 0; i < word.size(); i++) {
      umap[word[i]] = {};
      inDeg[word[i]] = 0;
    }
  }
  for (int i = 0; i < words.size() - 1; i++) {
    string pre = words[i], cur = words[i + 1];
    int len = min(pre.size(), cur.size());
    bool equal = true;
    for (int j = 0; j < len; j++) {
      char ch1 = pre[j], ch2 = cur[j];
      if (ch1 == ch2)
        continue;
      equal = false;
      if (umap[ch1].count(ch2) == 0) {
        umap[ch1].insert(ch2);
        inDeg[ch2]++;
      }
      break;
    }
    if (equal && pre.size() > cur.size())
      return "";
  }
  queue<char> que;
  for (const auto& itr : inDeg) {
    if (itr.second == 0)
      que.push(itr.first);
  }
  string ans;
  while (!que.empty()) {
    char c = que.front();
    que.pop();
    ans.push_back(c);
    unordered_set<char> tmp = umap[c];
    for (const auto& i : tmp) {
      if (--inDeg[i] == 0)
        que.push(i);
    }
  }
  return ans.size() == inDeg.size() ? ans : "";
}

string alienOrder1(vector<string>& words) {
  // 根据字符串建图，统计所有出现过的字符，初始化graph和inDeg
  unordered_map<char, unordered_set<char>> graph;
  unordered_map<char, int> inDeg;
  for (const string& word : words) {
    for (const char& c : word) {
      if (!graph.count(c))
        graph[c] = {};
      if (!inDeg.count(c))
        inDeg[c] = 0;
    }
  }
  // 对所有两个相邻的string，依次比较字符建图。统计所有结点的入度信息。
  for (int i = 1; i < words.size(); i++) {
    string before = words[i - 1], current = words[i];
    int len = min(before.size(), current.size());
    int j = 0;
    for (; j < len; j++) {
      char ch1 = before[j], ch2 = current[j];
      if (ch1 != ch2) {
        if (!graph[ch1].count(ch2)) {
          graph[ch1].insert(ch2);
          inDeg[ch2]++;
        }
        break;
      }
    }
    // 特殊情况，abc和ab，原本就不符合规则
    if (j == len && before.size() > current.size())
      return "";
  }
  // 拓扑排序。统计入度为0的结点，其必为结果字符串起始点。不断删除结点已更新入度
  string ans;
  queue<char> que;
  for (const auto i : inDeg) {
    if (i.second == 0)
      que.push(i.first);
  }
  while (!que.empty()) {
    char c = que.front();
    que.pop();
    ans.push_back(c);
    // 如果有a->b且b->a的情况。某节点c->a，删除c时，a必不可能入队，如此最终结果的长度即不是所有字符长
    for (const auto& u : graph[c]) {
      if (--inDeg[u] == 0)
        que.push(u);
    }
  }
  return ans.size() == inDeg.size() ? ans : "";
}

int main() {
  vector<string> words1 = {"wrt", "wrf", "er", "ett", "rftt"},
                 words2 = {"z", "x"}, words3 = {"z", "x", "z"},
                 words4 = {"abc", "ab"}, words5 = {"ac", "ab", "zc", "zb"};
  cout << alienOrder(words1) << " " << alienOrder(words2) << " "
       << alienOrder(words3) << " " << alienOrder(words4) << " "
       << alienOrder(words5) << endl;
  cout << alienOrder1(words1) << " " << alienOrder1(words2) << " "
       << alienOrder1(words3) << " " << alienOrder1(words4) << " "
       << alienOrder1(words5) << endl;
  return 0;
}