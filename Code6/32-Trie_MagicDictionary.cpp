#include "head.h"

/* 676. 实现一个魔法字典
设计一个使用单词列表进行初始化的数据结构，单词列表中的单词 互不相同 。
如果给出一个单词，请判定能否只将这个单词中一个字母换成另一个字母，使得所形成的新单词存在于你构建的字典中。
实现 MagicDictionary 类：
MagicDictionary() 初始化对象
void buildDict(String[] dictionary) 使用字符串数组 dictionary
设定该数据结构，dictionary 中的字符串互不相同 bool search(String searchWord)
给定一个字符串 searchWord ，判定能否只将字符串中 一个
字母换成另一个字母，使得所形成的新字符串能够与字典中的任一字符串匹配。如果可以，返回
true ；否则，返回 false 。
示例：
  输入
    ["MagicDictionary", "buildDict", "search", "search", "search", "search"]
    [[], [["hello", "leetcode"]], ["hello"], ["hhllo"], ["hell"], ["leetcoded"]]
  输出
    [null, null, false, true, false, false]
  解释
    MagicDictionary magicDictionary = new MagicDictionary();
    magicDictionary->buildDict(["hello", "leetcode"]);
    magicDictionary->search("hello"); // 返回 False
    magicDictionary->search("hhllo"); // 将第二个 'h' 替换为 'e' 可以匹配
"hello" ，所以返回 True magicDictionary->search("hell"); // 返回 False
    magicDictionary->search("leetcoded"); // 返回 False
提示：
  1 <= dictionary.length <= 100
  1 <= dictionary[i].length <= 100
  dictionary[i] 仅由小写英文字母组成
  dictionary 中的所有字符串 互不相同
  1 <= searchWord.length <= 100
  searchWord 仅由小写英文字母组成
  buildDict 仅在 search 之前调用一次
  最多调用 100 次 search */

// 暴力搜索。存储下字典，搜索字典中与searchWord等长的单词。依次序比较其每个字符是否相等。一旦不相等次数大于1，说明肯定不行，直接退出该单词比较
// 只有遍历完毕该单词，不等字符数等于1时，才返回真
class MagicDictionary1 {
 public:
  MagicDictionary1() {}

  void buildDict(vector<string> dictionary) { words = dictionary; }

  bool search(string searchWord) {
    for (const string& word : words) {
      if (word.size() != searchWord.size())
        continue;
      int diff = 0;
      for (int i = 0; i < word.size(); i++) {
        diff += (word[i] != searchWord[i]);
        if (diff > 1)
          break;
      }
      if (diff == 1)
        return true;
    }
    return false;
  }
  vector<string> words;
};

// 字典树优化版本
struct Trie {
  vector<Trie*> children;
  bool isFinished;
  Trie() {
    children.resize(26, nullptr);
    isFinished = false;
  }
};
class MagicDictionary {
 public:
  MagicDictionary() { this->root = new Trie(); }

  void buildDict(vector<string> dictionary) {
    Trie* cur = this->root;
    for (const string& word : dictionary) {
      cur = root;
      for (const char& c : word) {
        if (!cur->children[c - 'a'])
          cur->children[c - 'a'] = new Trie();
        cur = cur->children[c - 'a'];
      }
      cur->isFinished = true;
    }
  }

  bool search(string searchWord) {
    bool isMod = false;
    return dfs(root, searchWord, 0, isMod);
  }

  // 终止条件，到达最后一个字符，且修改过，且前缀树到达底层
  bool dfs(Trie* cur, const string& searchWord, int pos, bool isMod) {
    if (pos == searchWord.size())
      return cur->isFinished && isMod;
    int index = searchWord[pos] - 'a';
    if (cur->children[index] &&
        dfs(cur->children[index], searchWord, pos + 1, isMod)) {
      return true;
    }
    if (!isMod) {
      for (int i = 0; i < 26; i++) {
        if (i != index && cur->children[i] &&
            dfs(cur->children[i], searchWord, pos + 1, true)) {
          return true;
        }
      }
    }
    return false;
  }

 private:
  Trie* root;
};

int main() {
  MagicDictionary* magicDictionary = new MagicDictionary();
  magicDictionary->buildDict({"hello", "leetcode"});
  cout << magicDictionary->search("hello") << " "
       << magicDictionary->search("hhllo") << " "
       << magicDictionary->search("hell") << " "
       << magicDictionary->search("leetcoded") << endl;
  return 0;
}