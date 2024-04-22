#include "head.h"
/* 383. 赎金信
给定一个赎金信 (ransom)
字符串和一个杂志(magazine)字符串，判断第一个字符串 ransom 能不能由第二个字符串
magazines 里面的字符构成。如果可以构成，返回 true ；否则返回 false。
(题目说明：为了不暴露赎金信字迹，要从杂志上搜索各个需要的字母，组成单词来表达意思。杂志字符串中的每个字符只能在赎金信字符串中使用一次。)
注意：
你可以假设两个字符串均只含有小写字母。
canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true */

// 小写字母只有26个，且字符不能重复使用。故使用数组，而非哈希表map，记录每个字母在magazine上出现次数。节省资源。
// 为提高效率，注意可以先验字符串大小，ransomNote>magazine，直接判假
bool canConstruct(string ransomNote, string magazine) {
  int record[26] = {0};
  for (char c : magazine)
    record[c - 'a']++;
  for (char c : ransomNote) {
    record[c - 'a']--;
    if (record[c - 'a'] < 0)
      return false;
  }
  return true;
}

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