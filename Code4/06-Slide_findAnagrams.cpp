#include "head.h"
/* 438. 找到字符串中所有字母异位词
给定两个字符串 s 和 p，找到 s 中所有 p 的 异位词
的子串，返回这些子串的起始索引。不考虑答案输出的顺序。 异位词
指由相同字母重排列形成的字符串（包括相同的字符串）。
示例 1:
  输入: s = "cbaebabacd", p = "abc"
  输出: [0,6]
  解释: 起始索引等于 0 的子串是 "cba", 它是
    "abc" 的异位词。 起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。
示例 2:
  输入: s = "abab", p = "ab"
  输出: [0,1,2]
  解释:
    起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
    起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
    起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。
提示:
    1 <= s.length, p.length <= 3 * 104
    s 和 p 仅包含小写字母 */

vector<int> findAnagrams(string s, string p) {
  vector<int> pCount(26, 0);
  vector<int> sCount(26, 0);
  vector<int> ans;
  if (p.size() > s.size())
    return ans;
  for (const char& c : p)
    pCount[c - 'a']++;
  for (int i = 0; i < p.size(); i++)
    sCount[s[i] - 'a']++;
  if (pCount == sCount)
    ans.push_back(0);
  for (int i = p.size(); i < s.size(); i++) {
    sCount[s[i] - 'a']++;
    sCount[s[i - p.size()] - 'a']--;
    if (sCount == pCount)
      ans.push_back(i - p.size() + 1);
  }
  return ans;
}

// p的长度即为滑动窗口大小，比较是否字母异位词，实质是比较该窗口每个字母出现的频次是否相等，直接使用一个26个字母的数组记录。vector可以直接判断相等与否
// C++中，简单类型两个vector可以直接==,!=,>,<比较。先排除s比p短的特殊情况，设定每个字符串字符出现频率的数组sCount。
// 滑动窗口大小为pLen，首个滑动窗口要特殊处理，看是否相等。之后对sCount进行移动，如果s窗口等于p，则压入下标i+1
vector<int> findAnagrams1(string s, string p) {
  vector<int> ans;
  int sLen = s.size(), pLen = p.size();
  vector<int> sCount(26, 0);
  vector<int> pCount(26, 0);
  if (sLen < pLen)
    return ans;
  for (int i = 0; i < pLen; i++) {  // 必须先保证s长度大于等于p
    sCount[s[i] - 'a']++;
    pCount[p[i] - 'a']++;
  }
  if (sCount == pCount)  // 数组可以直接比较
    ans.push_back(0);
  for (int i = 0; i < sLen - pLen; i++) {
    sCount[s[i] - 'a']--;
    sCount[s[i + pLen] - 'a']++;
    if (sCount == pCount)
      ans.push_back(i + 1);
  }
  return ans;
}

int main() {
  string s1 = "cbaebabacd", p1 = "abc";
  string s2 = "abab", p2 = "ab";
  string s3 = "aaaaaaaaaa", p3 = "aaaaaaaaaaaaa";
  printVector(findAnagrams(s1, p1));
  printVector(findAnagrams(s2, p2));
  printVector(findAnagrams(s3, p3));
  printVector(findAnagrams1(s1, p1));
  printVector(findAnagrams1(s2, p2));
  printVector(findAnagrams1(s3, p3));

  return 0;
}