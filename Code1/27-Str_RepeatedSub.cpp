#include "head.h"
/* 给定一个非空的字符串，判断它是否可以由它的一个子串重复多次构成。给定的字符串只含有小写英文字母，并且长度不超过10000。
示例 1:
    输入: "abab"
    输出: True
    解释: 可由子字符串 "ab" 重复两次构成。
示例 2:
    输入: "aba"
    输出: False
示例 3:
    输入: "abcabcabcabc"
    输出: True
    解释: 可由子字符串 "abc" 重复四次构成。 (或者子字符串 "abcabc"
重复两次构成。) */

// 优选移动匹配，如果存在重复子数组，则两个s组成的t内，必可以找到s，注意要掐头去尾，避免找到原来的s。
// 次选kmp算法，next数组前缀表，表示了i位前相等前后缀的长度
void getNext(string s, int* next) {
  int j = -1;
  next[0] = j;
  for (int i = 1; i < s.size(); i++) {
    while (j >= 0 && s[i] != s[j + 1])
      j = next[j];
    if (s[i] == s[j + 1])
      j++;
    next[i] = j;
  }
}
bool repeatedSubstringPattern(string s) {
  int next[s.size()];
  getNext(s, next);
  int len = s.size();
  if (next[len - 1] != -1 && len % (len - (next[len - 1] + 1)) == 0)
    return true;
  return false;
}

// 移动匹配，若字符串s由多重复子串构成，则s+s后，掐头去尾，必能在中央找到s。对于string，找不到的位置为npos
bool repeatedSubstringPattern1(string s) {
  string t = s + s;
  t.erase(t.begin());
  t.erase(t.end() - 1);
  return (t.find(s) != string::npos) ? true : false;
}

// KMP算法，减一
void getNext2(int* next, const string& s) {
  int j = -1;
  next[0] = j;
  for (int i = 1; i < s.size(); i++) {
    while (j >= 0 && s[j + 1] != s[i])
      j = next[j];
    if (s[j + 1] == s[i])
      j++;
    next[i] = j;
  }
}
bool repeatedSubstringPattern2(string s) {
  if (s.size() == 0)
    return false;
  int next[s.size()];
  getNext2(next, s);
  int len = s.size();
  if (next[len - 1] != -1 && len % (len - next[len - 1] - 1) == 0)
    return true;
  else
    return false;
}
// KMP算法，正常前缀
void getNext3(int* next, const string s) {
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
bool repeatedSubstringPattern3(string s) {
  int len = s.size();
  int next[len];
  getNext3(next, s);
  if (next[len - 1] != 0 && len % (len - next[len - 1]) == 0)
    return true;
  else
    return false;
}
int main() {
  string s1 = "abac", s2 = "aba", s3 = "abcabcabcabc";
  cout << repeatedSubstringPattern(s1) << " " << repeatedSubstringPattern(s2)
       << " " << repeatedSubstringPattern1(s3) << endl;
  cout << repeatedSubstringPattern2(s1) << " " << repeatedSubstringPattern2(s2)
       << " " << repeatedSubstringPattern2(s3) << endl;
  return 0;
}