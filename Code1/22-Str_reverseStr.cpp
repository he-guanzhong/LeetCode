#include "head.h"
/* 541. 反转字符串 II
给定一个字符串 s 和一个整数 k，从字符串开头算起, 每计数至 2k 个字符，就反转这
2k 个字符中的前 k 个字符。
如果剩余字符少于 k 个，则将剩余字符全部反转。
如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
示例:
输入: s = "abcdefg", k = 2
输出: "bacdfeg"
示例 2：
输入：s = "abcd", k = 2
输出："bacd" */

string reverseStr(string s, int k) {
  for (int i = 0; i < s.size(); i += 2 * k) {
    if (i + k >= s.size())
      reverse(s.begin() + i, s.end());
    else
      reverse(s.begin() + i, s.begin() + i + k);
  }
  return s;
}

// 每隔2k，就反转k，所以一遍遍历，i每次增长2k，自然将字符串划分为2k的区间。不必求划分2k区间的个数。
// 至于队尾，判断i+k是否小于队尾，小于则反转i+k区间；大于则反转到end。
string reverseStr1(string& s, int k) {
  for (int i = 0; i < s.length(); i += 2 * k) {
    if (i + k <= s.size())
      reverse(s.begin() + i, s.begin() + i + k);
    else
      reverse(s.begin() + i, s.end());
  }
  return s;
}
string reverseStr2(string& s, int k) {
  int pos = 0, n = s.size();
  while (pos < n) {
    if (pos + k <= n)
      reverse(s.begin() + pos, s.begin() + pos + k);
    else
      reverse(s.begin() + pos, s.end());
    pos += 2 * k;
  }
  return s;
}

int main() {
  string s1 = "abcdefg", s2 = "abcd", s3 = "abcdefg";
  int k1 = 2, k2 = 4, k3 = 8;
  cout << reverseStr(s1, k1) << " " << reverseStr(s2, k2) << " "
       << reverseStr(s3, k3) << endl;
  s1 = "abcdefg", s2 = "abcd", s3 = "abcdefg";
  cout << reverseStr1(s1, k1) << " " << reverseStr1(s2, k2) << " "
       << reverseStr1(s3, k3) << endl;

  return 0;
}