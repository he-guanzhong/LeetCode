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

class MagicDictionary {
 public:
  struct Trie {
    vector<Trie*> children;
    bool isEnd;
    Trie() {
      children.resize(26, nullptr);
      isEnd = false;
    }
  };

  MagicDictionary() { root_ = new Trie(); }

  void buildDict(vector<string> dictionary) {
    for (const auto& dic : dictionary) {
      Trie* node = root_;
      for (const char& c : dic) {
        int index = c - 'a';
        if (node->children[index] == nullptr)
          node->children[index] = new Trie();
        node = node->children[index];
      }
      node->isEnd = true;
    }
  }

  bool dfs(Trie* node, string& searchWord, int i, bool used) {
    if (i == searchWord.size()) {
      return node->isEnd && used;
    }
    int index = searchWord[i] - 'a';
    if (node->children[index] &&
        dfs(node->children[index], searchWord, i + 1, used)) {
      return true;
    }
    if (!used) {
      for (int j = 0; j < 26; j++) {
        if (node->children[j] && j != index &&
            dfs(node->children[j], searchWord, i + 1, true))
          return true;
      }
    }
    return false;
  }
  bool search(string searchWord) { return dfs(root_, searchWord, 0, false); }
  Trie* root_;
};

// 字典树优化版本。构造记录最后一个结点isEnd标志位。鉴于有一次修改字母的机会。而不知道改成何种字母才能成功，所以必通过递归回溯
// DFS辅助函数入参应当包括：目标字符串word，当前深度pos，结点node，是否已经用过修改机会标志位used（由上至下单向，故传值即可，不必传引用）
// 搜索到一条路径就成功，故递归dfs放在if条件中。node结点永远必pos要提前一位，故终止条件是深度到字符串末尾之后。此时isEnd和used均为真才满足条件
// 辅助函数首先要处理node->children存在，可以向下拓展的情况。其次，考虑字典中存在ha和he。需要搜索ha是否符合题目要求时
// 显然，ha虽然和ha不满足要求，但可以由he修改一次字母得来。因此搜索到a/e结点层级，该子结点存在与否，都没有意义。
// 只要仍有一次修改机会，就要尝试修改。对children中所有存在结点(a/e)，且其不能是原本字母(a),对剩余可能存在字母继续搜索，返回可行性。
struct Trie1 {
  vector<Trie1*> children;
  bool isFinished;
  Trie1() {
    children.resize(26, nullptr);
    isFinished = false;
  }
};
class MagicDictionary1 {
 public:
  MagicDictionary1() { this->root = new Trie1(); }

  void buildDict(vector<string> dictionary) {
    Trie1* cur = this->root;
    for (const string& word : dictionary) {
      cur = root;
      for (const char& c : word) {
        if (!cur->children[c - 'a'])
          cur->children[c - 'a'] = new Trie1();
        cur = cur->children[c - 'a'];
      }
      cur->isFinished = true;
    }
  }

  bool search(string searchWord) {
    bool isMod = false;
    return dfs(root, searchWord, 0, isMod);
  }

  // 终止条件，到达最后一个字符。此时判断前缀树到达底层且修改过，为真，否则为假
  bool dfs(Trie1* cur, const string& searchWord, int pos, bool isMod) {
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
  Trie1* root;
};

// 暴力搜索。存储下字典，搜索字典中与searchWord等长的单词。依次序比较其每个字符是否相等。一旦不相等次数大于1，说明肯定不行，直接退出该单词比较
// 只有遍历完毕该单词，不等字符数等于1时，才返回真
class MagicDictionary2 {
 public:
  MagicDictionary2() {}

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

int main() {
  MagicDictionary* magicDictionary = new MagicDictionary();
  magicDictionary->buildDict({"hello", "leetcode"});
  cout << magicDictionary->search("hello") << " "
       << magicDictionary->search("hhllo") << " "
       << magicDictionary->search("hell") << " "
       << magicDictionary->search("leetcoded") << endl;
  magicDictionary->buildDict({"hello", "hallo", "leetcode"});
  cout << magicDictionary->search("hello") << " "
       << magicDictionary->search("hhllo") << " "
       << magicDictionary->search("hell") << " "
       << magicDictionary->search("leetcoded") << endl;
  cout << magicDictionary->search("hello") << " "
       << magicDictionary->search("hallo") << " "
       << magicDictionary->search("hell") << " "
       << magicDictionary->search("leetcodd") << endl;

  MagicDictionary1* magicDictionary1 = new MagicDictionary1();
  magicDictionary1->buildDict({"hello", "leetcode"});
  cout << magicDictionary1->search("hello") << " "
       << magicDictionary1->search("hhllo") << " "
       << magicDictionary1->search("hell") << " "
       << magicDictionary1->search("leetcoded") << endl;
  magicDictionary1->buildDict({"hello", "hallo", "leetcode"});
  cout << magicDictionary1->search("hello") << " "
       << magicDictionary1->search("hhllo") << " "
       << magicDictionary1->search("hell") << " "
       << magicDictionary1->search("leetcoded") << endl;
  cout << magicDictionary1->search("hello") << " "
       << magicDictionary1->search("hallo") << " "
       << magicDictionary1->search("hell") << " "
       << magicDictionary1->search("leetcodd") << endl;
  return 0;
}