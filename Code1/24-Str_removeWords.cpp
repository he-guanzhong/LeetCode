#include "head.h"
/* 151. 反转字符串中的单词
给你一个字符串 s ，请你反转字符串中 单词 的顺序。
单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。
返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。
注意：输入字符串
s中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。
示例 1：
  输入：s = "the sky is blue"
  输出："blue is sky the"
示例 2：
  输入：s = "  hello world  "
  输出："world hello"
  解释：反转后的字符串中不能存在前导空格和尾随空格。
示例 3：
  输入：s = "a good   example"
  输出："example good a"
  解释：如果两个单词间有多余的空格，反转后的字符串需要将单词间的空格减少到仅有一个。*/

string reverseWords(string s) {
  string ans;
  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] != ' ') {
      int j = i;
      while (s[j] != ' ') {
        j--;
        if (j < 0)
          break;
      }
      ans += s.substr(j + 1, i - j) + " ";
      i = j;
    }
  }
  return ans.substr(0, ans.size() - 1);
}

// 核心思路：前中后整体去重+整体反转+正向遍历反转单词。不得新增字符串，从后向前遍历老字符串，每遇到空格就加入
// 注意细节：整体去重中，每次要整体单词一并赋值，非首次赋值，还要额外补充空格。反转单词中，注意考虑reverse左闭右开区间，要包括i==size
// 第一步，删除所有空格，包括前、中、后，故不可使用前后双指针缩进的办法。
// 快慢指针法，快指针遍历到非空格时，慢指针一次就要赋值整体单词长度，故使用while。否则只赋值了一个字母。
// 对于慢指针，由于其一直在赋值，故如果不是第一次slow=0，每次赋值单词前，要额外插入一个空格。
// 第二步，反转整个字符串。设置慢指针，遍历时发现空格或者到终止，即反转单词。更新慢指针位置。注意reverse是左闭右开区间，故i<=size()
string reverseWords2(string s) {
  int slow = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] != ' ') {
      if (slow != 0)
        s[slow++] = ' ';
      while (s[i] != ' ' && i < s.size())
        s[slow++] = s[i++];
    }
  }
  s.resize(slow);
  reverse(s.begin(), s.end());
  slow = 0;
  for (int i = 0; i <= s.size(); i++) {
    if (s[i] == ' ' || i == s.size()) {
      reverse(s.begin() + slow, s.begin() + i);
      slow = i + 1;
    }
  }
  return s;
}

// 先除去所有多余空格，利用双指针，只考虑有字母的位置，若慢指针起始点不为0则补空格，其余直接拷贝整个单词
// 然后翻转所有，再用双指针，分别反转每个单词
void removeExtraSpaces(string& s) {
  int slow = 0;
  for (int i = 0; i < s.length(); i++) {
    if (s[i] != ' ') {  // 删除所有空格，只考虑有字母部分
      if (slow != 0)    // 若不是首个单词，补空格
        s[slow++] = ' ';
      while (i < s.length() && s[i] != ' ')  // 正常情况，填充整个单词
        s[slow++] = s[i++];
    }
  }
  s.resize(slow);  // slow指向了最末字符之外
}
string reverseWords1(string& s) {
  removeExtraSpaces(s);
  reverse(s.begin(), s.end());
  int start = 0;
  for (int i = 0; i <= s.size(); i++) {  // 左闭右开区间
    if (s[i] == ' ' || i == s.size()) {
      reverse(s.begin() + start, s.begin() + i);
      start = i + 1;
    }
  }
  return s;
}

// 使用C++特性的做法。从后向前，找到第一个非空元素后，以此为right，i继续前移拓展非空元素，直至第一个空元素，或首元素。结果字符串叠加之，并叠加空格
// 最终返回结果字符串，除去最后一个空格的结果
string reverseWords3(string message) {
  int n = message.size();
  string res = "";
  for (int i = n - 1; i >= 0; i--) {
    if (message[i] != ' ') {
      int j = i;
      while (i >= 0 && message[i] != ' ') {
        i--;
        if (i < 0)
          break;
      }
      res += message.substr(i + 1, j - i) + " ";
    }
  }
  return res.substr(0, res.size() - 1);
}

int main() {
  string str1 = "the sky is blue";
  string str2 = "  hello world!  ";
  string str3 = "a good   example";
  cout << reverseWords(str1) << endl;
  cout << reverseWords(str2) << endl;
  cout << reverseWords(str3) << endl;
  str1 = "the sky is blue";
  str2 = "  hello world!  ";
  str3 = "a good   example";
  cout << reverseWords3(str1) << endl;
  cout << reverseWords3(str2) << endl;
  cout << reverseWords3(str3) << endl;
  return 0;
}