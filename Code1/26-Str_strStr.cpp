#include "head.h"
/* 28. 找出字符串中第一个匹配项的下标
实现 strStr() 函数。
给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle
字符串出现的第一个位置 (从0开始)。如果不存在，则返回  -1。
示例 1: 输入: haystack = "hello", needle = "ll" 输出: 2
示例 2: 输入: haystack = "aaaaa", needle = "bba" 输出: -1
说明: 当 needle 是空字符串时，我们应当返回什么值呢？这是一个在面试中很好的问题。
对于本题而言，当 needle 是空字符串时我们应当返回 0 。这与C语言的 strstr() 以及
Java的 indexOf() 定义相符。*/

void getNext(string s, int next[]) {
  int j = -1;
  next[j + 1] = j;
  for (int i = 1; i < s.size(); i++) {
    while (j >= 0 && s[i] != s[j + 1])
      j = next[j];
    if (s[i] == s[j + 1])
      j++;
    next[i] = j;
  }
}
int strStr(string haystack, string needle) {
  int n = needle.size();
  if (n == 0)
    return 0;
  int next[n] = {0};
  getNext(needle, next);
  int j = -1;
  for (int i = 0; i < haystack.size(); i++) {
    while (j >= 0 && haystack[i] != needle[j + 1])
      j = next[j];
    if (haystack[i] == needle[j + 1])
      j++;
    if (j == n - 1)
      return i - n + 1;
  }
  return -1;
}

// 典型kmp算法。前缀表记录了相等前后缀的长度。next数组可以记录的是前缀长度-1。i记录后缀，从1开始遍历。j+1记录前缀长度
// j初始化为-1.
void getNext1(int* next, const string& s) {  // 求前缀表
  int j = -1;                                // 前缀末尾下标-1
  next[0] = j;
  for (int i = 1; i < s.size(); i++) {  // 后缀末尾下标从1开始遍历
    while (j >= 0 && s[i] != s[j + 1])  // 一旦前后缀末尾，前缀取前缀表记录下标
      j = next[j];
    if (s[i] == s[j + 1])
      j++;
    next[i] = j;  // 实时更新前缀表下标
  }
}
int strStr1(string haystack, string needle) {
  if (needle.size() == 0)  // 排除特殊情况
    return 0;
  int next[needle.size()];
  getNext1(next, needle);  // 求模式串的前缀表
  int j = -1;              // next数组记录起始位置为-1
  for (int i = 0; i < haystack.size(); i++) {
    while (j >= 0 && haystack[i] != needle[j + 1])
      j = next[j];
    if (haystack[i] == needle[j + 1])
      j++;
    if (j == needle.size() - 1)  // 模式串遍历到最末端
      return i - needle.size() + 1;
  }
  return -1;
}

// 前缀表不减1方案
void getNext2(int* next, const string& s) {
  int j = 0;
  next[0] = j;
  for (int i = 1; i < s.size(); i++) {
    while (j > 0 && s[i] != s[j])
      j = next[j - 1];
    if (s[i] == s[j])
      j++;
    next[i] = j;
  }
}
int strStr2(string haystack, string needle) {
  if (needle.size() == 0)
    return 0;
  int next[needle.size()];
  getNext2(next, needle);  // 求模式串的前缀表
  int j = 0;
  for (int i = 0; i < haystack.size(); i++) {
    while (j > 0 && haystack[i] != needle[j])
      j = next[j - 1];
    if (haystack[i] == needle[j])
      j++;
    if (j == needle.size())
      return i - needle.size() + 1;
  }
  return -1;
}

void getNext10(int* next, const string& s) {
  int j = 0;
  next[0] = j;
  for (int i = 1; i < s.size(); i++) {
    while (j > 0 && s[i] != s[j]) {
      cout << "不相等, j before = " << j;
      j = next[j - 1];
      cout << ", j after = " << j << endl;
    }
    if (s[i] == s[j]) {
      j++;
      cout << "相等 j = " << j << endl;
    }
    next[i] = j;
    cout << "i = " << i << "     (j) next[i] = " << j << endl;
  }
}

int main() {
  string haystack1 = "hello", needle1 = "ll";
  string haystack2 = "aaaaa", needle2 = "bba";
  string test = "aabaaf";
  cout << strStr(haystack1, needle1) << " " << strStr(haystack2, needle2)
       << endl;
  cout << strStr1(haystack1, needle1) << " " << strStr1(haystack2, needle2)
       << endl;
  int next[test.size()];
  // getNext10(next, test);
}