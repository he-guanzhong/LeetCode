#include "head.h"
/* 844. 比较含退格的字符串
给定 s 和 t 两个字符串，当它们分别被输入到空白的文本编辑器后，如果两者相等，返回
true 。# 代表退格字符。
注意：如果对空文本输入退格字符，文本继续为空。
示例 1：
输入：s = "ab#c", t = "ad#c"
输出：true
解释：s 和 t 都会变成 "ac"。
示例 2：
输入：s = "ab##", t = "c#d#"
输出：true
解释：s 和 t 都会变成 ""。
示例 3：
输入：s = "a#c", t = "b"
输出：false
解释：s 会变成 "c"，但 t 仍然是 "b"。
    你可以用 O(n) 的时间复杂度和 O(1) 的空间复杂度解决该问题吗？*/

bool backspaceCompare(string s, string t) {
  int s1 = -1, t1 = -1;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '#')
      s1 = max(-1, s1 - 1);
    else
      s[++s1] = s[i];
  }
  for (int i = 0; i < t.size(); i++) {
    if (t[i] == '#')
      t1 = max(-1, t1 - 1);
    else
      t[++t1] = t[i];
  }
  while (s1 >= 0 && t1 >= 0) {
    if (s[s1] != t[t1])
      return false;
    s1--;
    t1--;
  }
  return s1 == -1 && t1 == -1;
}

int main() {
  string s1 = "ab#c", t1 = "ad#c";
  string s2 = "ab##", t2 = "c#d#";
  string s3 = "a#c", t3 = "b";
  string s4 = "bxj##tw", t4 = "bxj###tw";
  cout << backspaceCompare(s1, t1) << " " << backspaceCompare(s2, t2) << " "
       << backspaceCompare(s3, t3) << " " << backspaceCompare(s4, t4) << endl;

  return 0;
}