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
提示：
    1 <= s.length, t.length <= 200
    s 和 t 只含有小写字母以及字符 '#'
进阶：
    你可以用 O(n) 的时间复杂度和 O(1) 的空间复杂度解决该问题吗？*/

string helper(string s) {
  int i = 0, j = 0;
  while (i < s.size()) {
    if (s[i] >= 'a' && s[i] <= 'z')
      s[j++] = s[i];
    else
      j = max(0, --j);
    i++;
  }
  return s.substr(0, j);
}
bool backspaceCompare(string s, string t) {
  s = helper(s);
  t = helper(t);
  return s == t;
}

// 双指针，从后向前遍历，空间复杂度O(1)。遇到#，跳步计数加一，指针前移，跳步计数不为0，指针前移。直至找到无需跳步的元素停止
// 比较双指针位置。二者都有值且不相等，为假。两方之一已经超限，为假。如双方共同一起超限，则为真
bool backspaceCompare1(string s, string t) {
  int i = s.size() - 1, j = t.size() - 1;
  int skipS = 0, skipT = 0;
  while (i >= 0 || j >= 0) {  // 注意此处是或，不是与
    while (i >= 0) {  // 此处不能加skipS>0条件，因为其默认值是0。不会进入该循环
      if (s[i] == '#') {
        skipS++, i--;
      } else if (skipS > 0) {
        skipS--, i--;
      } else {  // 只能通过skip==0时跳出
        break;
      }
    }
    while (j >= 0) {
      if (t[j] == '#') {
        skipT++, j--;
      } else if (skipT > 0) {
        skipT--, j--;
      } else {
        break;
      }
    }
    if (i >= 0 && j >= 0) {
      if (s[i] != t[j]) {
        return false;
      }
    } else {
      if (i >= 0 || j >= 0) {
        return false;
      }
    }
    i--, j--;
  }
  return true;  // 两个一起到终点，为真
}

// 栈处理。string直接模拟，但是生成了临时字符串，空间复杂度O(n+m)
string getString2(string s) {
  int j = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] != '#')
      s[j++] = s[i];
    else if (j > 0)
      --j;
  }
  return s.substr(0, j);
}
bool backspaceCompare2(string s, string t) {
  return getString2(s) == getString2(t);
}

int main() {
  string s1 = "ab#c", t1 = "ad#c";
  string s2 = "ab##", t2 = "c#d#";
  string s3 = "a#c", t3 = "b";
  string s4 = "y#fo##f", t4 = "y#f#o##f";
  string s5 = "bbbextm", t5 = "bbb#extm";
  cout << backspaceCompare(s1, t1) << " " << backspaceCompare(s2, t2) << " "
       << backspaceCompare(s3, t3) << " " << backspaceCompare(s4, t4) << " "
       << backspaceCompare(s5, t5) << endl;
  cout << backspaceCompare1(s1, t1) << " " << backspaceCompare1(s2, t2) << " "
       << backspaceCompare1(s3, t3) << " " << backspaceCompare1(s4, t4) << " "
       << backspaceCompare1(s5, t5) << endl;
  return 0;
}