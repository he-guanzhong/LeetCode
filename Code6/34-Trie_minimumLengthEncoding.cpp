#include "head.h"

/* 820. 单词的压缩编码
单词数组 words 的 有效编码 由任意助记字符串 s 和下标数组 indices 组成，且满足：
words.length == indices.length
助记字符串 s 以 '#' 字符结尾
对于每个下标 indices[i] ，s 的一个从 indices[i] 开始、到下一个 '#'
字符结束（但不包括 '#'）的 子字符串 恰好与 words[i] 相等 给你一个单词数组 words
，返回成功对 words 进行编码的最小助记字符串 s 的长度 。
示例 1：
  输入：words = ["time", "me", "bell"]
  输出：10
  解释：一组有效编码为 s = "time#bell#" 和 indices = [0, 2, 5] 。
    words[0] = "time" ，s 开始于 indices[0] = 0 到下一个 '#'
    结束的子字符串，如加粗部分所示 "time#bell#" words[1] = "me" ，s 开始于
    indices[1] = 2 到下一个 '#' 结束的子字符串，如加粗部分所示 "time#bell#"
words[2] = "bell" ，s 开始于 indices[2] = 5 到下一个 '#'
结束的子字符串，如加粗部分所示 "time#bell#" 示例 2： 输入：words = ["t"] 输出：2
  解释：一组有效编码为 s = "t#" 和 indices = [0] 。
提示：
  1 <= words.length <= 2000
  1 <= words[i].length <= 7
  words[i] 仅由小写字母组成 */

struct Trie {
  vector<Trie*> children;
  int branch;
  Trie() {
    children.resize(26, 0);
    branch = 0;
  }
};
int minimumLengthEncoding(vector<string>& words) {
  Trie* root = new Trie();
  int ans = 0;
  unordered_map<Trie*, int> umap;
  for (const auto& word : words) {
    Trie* node = root;
    for (int i = word.size() - 1; i >= 0; i--) {
      int index = word[i] - 'a';
      if (node->children[index] == nullptr) {
        node->children[index] = new Trie();
        node->branch++;
      }
      node = node->children[index];
    }
    umap[node] = word.size();
  }
  for (auto& node : umap) {
    if (node.first->branch == 0)
      ans += node.second + 1;
  }
  return ans;
}

struct Trie1 {
  vector<Trie1*> children;
  int cnt;
  Trie1() {
    cnt = 0;  // 节点分支数
    children.resize(26, nullptr);
  }
};
// 所有单词倒序插入前缀树，即可找到共同后缀。前缀树无需存储是否为最后isEnd标志位，但要存储该结点有几个子分支branch
// 哈希表存储最后一个节点（即字符串首字母）指针，及其对应单词长度。因此，前缀树深度信息不重要，字符串长度已知，并由哈希表记录
// 如此可以通过指针指向节点是否末尾（无其余分支，cnt==0），判断是否要将此单词长度加入
int minimumLengthEncoding1(vector<string>& words) {
  Trie1* root = new Trie1();
  unordered_map<Trie1*, int> umap;
  for (const string& word : words) {
    Trie1* cur = root;
    for (int i = word.size() - 1; i >= 0; i--) {
      if (!cur->children[word[i] - 'a']) {
        cur->children[word[i] - 'a'] = new Trie1();
        cur->cnt++;  // 该层节点有新分支
      }
      cur = cur->children[word[i] - 'a'];
    }
    umap[cur] = word.size();
  }
  int ans = 0;
  for (const auto& it : umap) {
    if (it.first->cnt == 0)
      ans += it.second + 1;
  }
  return ans;
}

// 利用uset去除单词重，对每一个word，分别在uset中删除其所有可能的后缀元素，剩下uset中的即为不重复单词
// 时间复杂度O(w^2)，
int minimumLengthEncoding2(vector<string>& words) {
  unordered_set<string> uset(words.begin(), words.end());
  for (const string& word : words) {
    for (int i = 1; i < word.size(); i++)
      uset.erase(word.substr(i));
  }
  int ans = 0;
  for (const string& word : uset)
    ans += word.size() + 1;
  return ans;
}

int main() {
  vector<string> s1 = {"time", "me", "bell"}, s2 = {"t"};
  cout << minimumLengthEncoding(s1) << " " << minimumLengthEncoding(s2) << endl;
  cout << minimumLengthEncoding1(s1) << " " << minimumLengthEncoding1(s2)
       << endl;

  return 0;
}