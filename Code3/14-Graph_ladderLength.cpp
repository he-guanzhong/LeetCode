#include "head.h"
/* 127. 单词接龙
字典 wordList 中从单词 beginWord 和 endWord 的 转换序列
是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk：
    每一对相邻的单词只差一个字母。
     对于 1 <= i <= k 时，每个 si 都在 wordList 中。注意， beginWord 不需要在
wordList 中。 sk == endWord
给你两个单词 beginWord 和 endWord 和一个字典 wordList ，返回 从 beginWord 到
endWord 的 最短转换序列 中的 单词数目 。如果不存在这样的转换序列，返回 0 。
示例 1：
  输入：beginWord = "hit", endWord = "cog", wordList =
    ["hot","dot","dog","lot","log","cog"]
  输出：5
  解释：一个最短转换序列是 "hit" ->
  "hot" -> "dot" -> "dog" -> "cog", 返回它的长度 5。
示例 2：
  输入：beginWord = "hit", endWord = "cog", wordList =
    ["hot","dot","dog","lot","log"]
  输出：0
  解释：endWord "cog"不在字典中，所以无法进行转换。 */

int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
  unordered_set<string> uset(wordList.begin(), wordList.end());
  if (uset.find(endWord) == uset.end())
    return 0;
  queue<string> que;
  que.push(beginWord);
  int cnt = 0;
  unordered_set<string> visited;
  while (que.size()) {
    int size = que.size();
    cnt++;
    while (size--) {
      string cur = que.front();
      que.pop();
      for (int i = 0; i < cur.size(); i++) {
        string ori = cur;
        for (char j = 'a'; j <= 'z'; j++) {
          cur[i] = j;
          // cout << cur << "\t";
          if (cur == ori || visited.find(cur) != visited.end())
            continue;
          if (cur == endWord)
            return cnt + 1;
          if (uset.find(cur) != uset.end()) {
            que.push(cur);
            visited.insert(cur);
          }
        }
        cur = ori;
      }
    }
  }
  return 0;
}

// uset记录新单词是否在字典中，umap记录每个单词的路径长度，便于回溯。广度优先搜索，队列首单词，记录其路径长。
// 单词变每一位前，先生成临时单词，再分别替换26个字母。找到末尾单词即返回长度+1，找不到末尾单词，且在字典中，且未访问过，压入新结点
// 对每一个单词，每一个字母，分别替换，如果发现在wordlist找到，则广度优先搜索，压入队列中。
// 使用unordered_set提高查找单词效率，使用unordered_map记录每一个单词的路径长度
int ladderLength1(string beginWord, string endWord, vector<string>& wordList) {
  unordered_set<string> wordSet(wordList.begin(), wordList.end());
  // 终止字母就不在范围内，必不可能，返回0
  if (wordSet.find(endWord) == wordSet.end())
    return 0;
  unordered_map<string, int> visitMap;
  queue<string> que;
  que.push(beginWord);
  visitMap.insert(pair<string, int>(beginWord, 1));
  while (!que.empty()) {
    string word = que.front();
    que.pop();
    int path = visitMap[word];
    for (int i = 0; i < word.size(); i++) {
      string newWord = word;
      for (int j = 0; j < 26; j++) {  // 注意，这里是j
        newWord[i] = j + 'a';
        if (newWord == endWord)
          return path + 1;
        if (wordSet.find(newWord) != wordSet.end() &&
            visitMap.find(newWord) == visitMap.end()) {
          visitMap.insert(pair<string, int>(newWord, path + 1));
          que.push(newWord);
        }
      }
    }
  }
  return 0;
}

int main() {
  string beginWord = "hit", endWord = "cog";
  vector<string> wordList1 = {"hot", "dot", "dog", "lot", "log", "cog"};
  vector<string> wordList2 = {"hot", "dot", "dog", "lot", "log"};
  cout << ladderLength(beginWord, endWord, wordList1) << " "
       << ladderLength(beginWord, endWord, wordList2) << endl;
  cout << ladderLength1(beginWord, endWord, wordList1) << " "
       << ladderLength1(beginWord, endWord, wordList2) << endl;
  return 0;
}