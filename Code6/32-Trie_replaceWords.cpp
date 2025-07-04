#include "head.h"

/* 648. 单词替换
在英语中，我们有一个叫做 词根(root) 的概念，可以词根 后面
添加其他一些词组成另一个较长的单词——我们称这个词为 衍生词
(derivative)。例如，词根 help，跟随着 继承词 "ful"，可以形成新的单词 "helpful"。
现在，给定一个由许多 词根 组成的词典 dictionary 和一个用空格分隔单词形成的句子
sentence。你需要将句子中的所有 衍生词 用 词根 替换掉。如果 衍生词
有许多可以形成它的 词根，则用 最短 的 词根 替换它。
你需要输出替换之后的句子。
示例 1：
  输入：dictionary = ["cat","bat","rat"], sentence = "the cattle was rattled by
the battery"
  输出："the cat was rat by the bat"
示例 2：
  输入：dictionary = ["a","b","c"], sentence = "aadsfasf absbs bbab cadsfafs"
  输出："a a b c"
提示：
    1 <= dictionary.length <= 1000
    1 <= dictionary[i].length <= 100
    dictionary[i] 仅由小写字母组成。
    1 <= sentence.length <= 106
    sentence 仅由小写字母和空格组成。
    sentence 中单词的总量在范围 [1, 1000] 内。
    sentence 中每个单词的长度在范围 [1, 1000] 内。
    sentence 中单词之间由一个空格隔开。
    sentence 没有前导或尾随空格。 */

struct Trie {
  vector<Trie*> children;
  bool isEnd;
  Trie() {
    isEnd = false;
    children.resize(26, nullptr);
  }
};
string replaceWords(vector<string>& dictionary, string sentence) {
  vector<string> words;
  string ans;
  for (int i = 0, j = 0; i <= sentence.size(); i++) {
    if (i == sentence.size() || sentence[i] == ' ') {
      words.push_back(sentence.substr(j, i - j));
      j = i + 1;
    }
  }
  Trie* root = new Trie();
  for (const string& dic : dictionary) {
    Trie* node = root;
    for (const char& c : dic) {
      int index = c - 'a';
      if (node->children[index] == nullptr)
        node->children[index] = new Trie();
      node = node->children[index];
    }
    node->isEnd = true;
  }
  for (const string& word : words) {
    Trie* node = root;
    string tmp;
    for (const char& c : word) {
      int index = c - 'a';
      if (node->children[index] == nullptr)
        break;
      if (node->isEnd)
        break;
      tmp.push_back(c);
      node = node->children[index];
    }
    ans += (node->isEnd ? tmp : word) + " ";
  }
  if (!ans.empty())
    ans.pop_back();
  return ans;
}

// 字典树经典题。辅助函数一，双指针将sentence转化为vector。左指针永远停在单词首字母，右指针永远停在单词后的第一空格
// 辅助函数二、根据字典树查单词前缀。从首节点依次看起对应孩子节点是否存在。若发现终止符，说明该层节点已经为前缀末尾，直接返回前缀
// 若发现某字符节点不存在，则所有前缀均不满足条件，返回该单词。剩余情况，将该轮字符暂存，移动至下一下标。
// 主函数。首先创建前缀树根节点，对字典内每个元素依次加入前缀树。注意到最后一个字符后，人为添加#作为终止标记
// 对vector的每一个单词，寻找前缀，并添加单词间空格，作为最终答案
// 时间复杂度O(d+s)，d和s分别为dict和sentence字符数。因为每个字符都要入树，每个字符都要被检索。空间复杂度O(d+s)，因为临时变量储存
struct Trie1 {
  unordered_map<char, Trie1*> children;
};
vector<string> split1(const string& s, char ch) {
  vector<string> ans;
  for (int i = 0, j = 0; i < s.size() && j < s.size();) {
    while (j < s.size() && s[j] == ch)
      j++;
    i = j;
    while (j < s.size() && s[j] != ch)
      j++;
    if (i < s.size())
      ans.push_back(s.substr(i, j - i));
  }
  return ans;
}
string searchPrefix1(const string& word, Trie1* trie) {
  string ans;
  Trie1* root = trie;
  for (const auto& c : word) {
    if (root->children['#'])  // 必须先判终止符，再判不存在
      return ans;
    if (!root->children[c])
      return word;
    ans.push_back(c);
    root = root->children[c];
  }
  return ans;
}
string replaceWords1(vector<string>& dictionary, string sentence) {
  Trie1* trie = new Trie1();
  for (const string& prefix : dictionary) {
    Trie1* cur = trie;
    for (const char& c : prefix) {
      if (!cur->children.count(c))
        cur->children[c] = new Trie1();
      cur = cur->children[c];
    }
    cur->children['#'] = new Trie1();  // 终止标记
  }
  vector<string> words = split1(sentence, ' ');
  string ans;
  for (const auto& word : words) {
    string tmp = searchPrefix1(word, trie);
    ans += tmp + " ";
  }
  if (!ans.empty())
    ans.pop_back();
  return ans;
}

int main() {
  vector<string> dic1 = {"cat", "bat", "rat"}, dic2 = {"a", "b", "c"},
                 dic3 = {"a", "aa", "aaa", "aaaa"},
                 dic4 = {"catt", "cat", "bat", "rat"};
  string sen1 = "the cattle was rattled by the battery ",
         sen2 = "aadsfasf absbs bbab cadsfafs",
         sen3 = {"a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa"},
         sen4 = {"the cattle was rattled by the battery"};

  cout << replaceWords(dic1, sen1) << "\t" << replaceWords(dic2, sen2) << " \t"
       << replaceWords(dic3, sen3) << "\t" << replaceWords(dic4, sen4) << endl;
  cout << replaceWords1(dic1, sen1) << "\t" << replaceWords1(dic2, sen2)
       << " \t" << replaceWords1(dic3, sen3) << "\t"
       << replaceWords1(dic4, sen4) << endl;
  return 0;
}