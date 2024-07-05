#include "head.h"
/* LCR 122. 路径加密
请实现一个函数，把字符串 s 中的每个空格替换成"%20"。
示例 1：
  输入：s = "We are happy."
  输出："We%20are%20happy." */

string replaceSpace(string s) {
  int n = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == ' ')
      n++;
  }
  int j = s.size() - 1;
  s.resize(s.size() + 2 * n);
  int i = s.size() - 1;
  while (j >= 0) {
    if (s[j] != ' ')
      s[i--] = s[j--];
    else {
      s[i--] = '0';
      s[i--] = '2';
      s[i--] = '%';
      j--;
    }
  }
  return s;
}

// 先统计有多少个空格，记录原字符串长度，扩大字符串置新长度。然后从后向前，从老末尾、新末尾遍历，直至新末尾赶上老末尾为止
// 若老末尾指针元素不为空格，则新末尾直接赋值。若老末尾指针元素为空格，则新末尾赋值"%20"
// 先判断空格个数，然后resize,确定新老长度指针尾部位置，由后向前,结束条件是二者相遇，不同则赋值，相同则特殊处理
string replaceSpace1(string s) {
  int count = 0;
  for (char i : s) {
    if (i == ' ')
      count++;
  }
  int sOldSize = s.size();
  s.resize(s.size() + 2 * count);
  int sNewSize = s.size();
  for (int i = sNewSize - 1, j = sOldSize - 1; j < i; i--, j--) {
    if (s[j] != ' ') {
      s[i] = s[j];
    } else {
      s[i] = '0';
      s[--i] = '2';
      s[--i] = '%';
    }
  }
  return s;
}

// 传统办法。replace(起始位置整数，要替换的长度整数，新字符串)。或replace(起始迭代器，终止迭代器，新起始迭代器，新终止迭代器)
string replaceSpace2(string s) {
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == ' ')
      s.replace(i, 1, "%20");
  }
  return s;
}
int main() {
  string str1 = "we are happy. ";
  cout << replaceSpace(str1) << endl;
  str1 = "we are happy. ";
  cout << replaceSpace1(str1) << endl;
  return 0;
}