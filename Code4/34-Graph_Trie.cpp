#include "head.h"
/* 208. 实现 Trie (前缀树)
Trie（发音类似 "try"）或者说 前缀树
是一种树形数据结构，用于高效地存储和检索字符串数据集中的键。这一数据结构有相当多的应用情景，例如自动补完和拼写检查。
请你实现 Trie 类：
    Trie() 初始化前缀树对象。
    void insert(String word) 向前缀树中插入字符串 word 。
    boolean search(String word) 如果字符串 word 在前缀树中，返回
true（即，在检索之前已经插入）；否则，返回 false 。 boolean startsWith(String
prefix) 如果之前已经插入的字符串 word 的前缀之一为 prefix ，返回 true
；否则，返回 false 。
示例：
  输入
    ["Trie", "insert", "search", "search", "startsWith", "insert", "search"]
    [[], ["apple"], ["apple"], ["app"], ["app"], ["app"], ["app"]]
  输出
    [null, null, true, false, true, null, true]
  解释
    Trie trie = new Trie();
    trie.insert("apple");
    trie.search("apple");   // 返回 True
    trie.search("app");     // 返回 False
    trie.startsWith("app"); // 返回 True
    trie.insert("app");
    trie.search("app");     // 返回 True */

class Trie {
 public:
  Trie() {
    isEnd = false;
    next.resize(26);
  }

  void insert(string word) {
    Trie* p = this;
    for (const char& i : word) {
      int ch = i - 'a';
      if (p->next[ch] == nullptr) {
        p->next[ch] = new Trie();
      }
      p = p->next[ch];
    }
    p->isEnd = true;
  }

  bool search(string word) {
    Trie* p = find(word);
    return p && p->isEnd;
  }

  bool startsWith(string prefix) { return find(prefix); }

 private:
  bool isEnd;
  vector<Trie*> next;
  Trie* find(string prefix) {
    Trie* p = this;
    for (const char& c : prefix) {
      int ch = c - 'a';
      if (p->next[ch] == nullptr)
        return nullptr;
      p = p->next[ch];
    }
    return p;
  }
};

// 两个特征，vector存储26个孩子指针，isEnd存储是否为最后一个字符。insert函数将node初始化为当前层。
// 对每word每个字符，如果没孩子，就创造孩子。然后移动到孩子的位置上，如此node停于最后孩子，isEnd置真。
// 单独设置返回Trie*的search函数，node处于树上，对每一个word字符，找不到立刻返回空。找到了就移动置孩子位的节点Trie*，最终返回孩子位节点Trie*。
class Trie1 {
 public:
  Trie1() {
    children.resize(26);
    isEnd = false;
  }

  void insert(string word) {
    Trie1* node = this;
    for (char ch : word) {
      ch -= 'a';
      if (node->children[ch] == nullptr)
        node->children[ch] = new Trie1();
      node = node->children[ch];
    }
    node->isEnd = true;
  }

  bool search(string word) {
    Trie1* node = searchPrefix(word);
    return node && node->isEnd;
  }

  bool startsWith(string prefix) { return this->searchPrefix(prefix); }

 private:
  vector<Trie1*> children;
  bool isEnd;

  Trie1* searchPrefix(string prefix) {
    Trie1* node = this;
    for (char ch : prefix) {
      ch -= 'a';
      if (node->children[ch] == nullptr)
        return nullptr;
      node = node->children[ch];
    }
    return node;
  }
};

int main() {
  Trie trie;
  trie.insert("apple");
  cout << trie.search("apple") << " ";    // 返回 True
  cout << trie.search("app") << " ";      // 返回 False
  cout << trie.startsWith("app") << " ";  // 返回 True
  trie.insert("app");
  cout << trie.search("app") << endl;  // 返回 True */
  Trie1 trie1;
  trie1.insert("apple");
  cout << trie1.search("apple") << " ";    // 返回 True
  cout << trie1.search("app") << " ";      // 返回 False
  cout << trie1.startsWith("app") << " ";  // 返回 True
  trie1.insert("app");
  cout << trie1.search("app") << endl;  // 返回 True */
  return 0;
}