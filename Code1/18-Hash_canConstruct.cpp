#include "head.h"
/* 383. 赎金信
给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine
里面的字符构成。如果可以，返回 true ；否则返回 false 。
magazine 中的每个字符只能在 ransomNote 中使用一次。
示例 1：
  输入：ransomNote = "a", magazine = "b"
  输出：false
示例 2：
  输入：ransomNote = "aa", magazine = "ab"
  输出：false
示例 3：
  输入：ransomNote = "aa", magazine = "aab"
  输出：true  */

bool canConstruct(string ransomNote, string magazine) {
  unordered_map<int, int> umap;
  for (char c : magazine) {
    umap[c]++;
  }
  for (char c : ransomNote) {
    if (umap.find(c) == umap.end() || umap[c] == 0)
      return false;
    umap[c]--;
  }
  return true;
}

// 小写字母只有26个，且字符不能重复使用。故使用数组，而非哈希表map，记录每个字母在magazine上出现次数。节省资源。
// 为提高效率，注意可以先验字符串大小，ransomNote>magazine，直接判假
bool canConstruct1(string ransomNote, string magazine) {
  if (ransomNote.length() > magazine.length())  // 特殊处理
    return false;
  int record[26] = {0};  // 字母有限长度，用数组而非map记录信息
  for (auto i : magazine)
    record[i - 'a']++;
  for (auto i : ransomNote) {
    record[i - 'a']--;
    if (record[i - 'a'] < 0)
      return false;
  }
  return true;
}

int main() {
  string s1 = "aa", s2 = "ab";
  string s3 = "aabb", s4 = "aabbc";
  cout << canConstruct(s1, s2) << " " << canConstruct(s3, s4) << endl;
  cout << canConstruct1(s1, s2) << " " << canConstruct1(s3, s4) << endl;
  return 0;
}