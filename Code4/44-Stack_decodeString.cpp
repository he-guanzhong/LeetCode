#include "head.h"
/* 394. 字符串解码
给定一个经过编码的字符串，返回它解码后的字符串。
编码规则为: k[encoded_string]，表示其中方括号内部的 encoded_string 正好重复 k
次。注意 k 保证为正整数。
你可以认为输入字符串总是有效的；输入字符串中没有额外的空格，且输入的方括号总是符合格式要求的。
此外，你可以认为原始数据不包含数字，所有的数字只表示重复的次数 k
，例如不会出现像 3a 或 2[4] 的输入。
示例 1：
输入：s = "3[a]2[bc]"
输出："aaabcbc"
示例 2：
输入：s = "3[a2[c]]"
输出："accaccacc"
示例 3：
输入：s = "2[abc]3[cd]ef"
输出："abcabccdcdcdef"
示例 4：
输入：s = "abc3[cd]xyz"
输出："abccdcdcdxyz" */

string decodeString(string s) {
  stack<pair<string, int>> st;
  string tmp;
  int num = 0;
  for (char c : s) {
    if (c <= '9' && c >= '0')
      num = num * 10 + (c - '0');
    else if (c >= 'a' && c <= 'z')
      tmp += c;
    else if (c == '[') {
      st.push(make_pair(tmp, num));
      tmp.clear();
      num = 0;
    } else {
      int n = st.top().second;
      string pre = st.top().first;
      st.pop();
      while (n--)
        pre += tmp;
      tmp = pre;
    }
  }
  return tmp;
}

// 核心是利用栈，分四种情况。遇到字符、数字则分别记录。遇到[，立刻临时保存当前的str和num入栈，并清除当前str和num。
// 遇到]，即取出栈顶的str和num，作为上一周期值pre，不断累积叠加[]之内str，最终作为当前str记录。最终返回当前str。
// 多个数字字符组成大于等于两位数的情况，使用string临时保存字符串，并使用atoi(c_str())返回整型（或使用stoi）
string decodeString1(string s) {
  stack<string> st;
  string strChar;
  string strNum;
  for (char c : s) {
    if (c >= '0' && c <= '9') {
      strNum += c;
    } else if (c >= 'a' && c <= 'z') {
      strChar += c;
    } else if (c == '[') {
      st.push(strNum);
      strNum.clear();
      st.push(strChar);
      strChar.clear();
    } else if (c == ']') {
      string preChar = st.top();
      st.pop();
      string preNum = st.top();
      st.pop();
      int n = atoi(preNum.c_str());  // c_str生成一个const char*指针
      // int n = stoi(preNum); // 可选
      while (n--)
        preChar += strChar;
      strChar = preChar;  // 更新当前未存入的
    }
  }
  return strChar;
}

int main() {
  string s1 = "3[a]2[bc]", s2 = "3[a2[c]]", s3 = "2[abc]3[cd]ef",
         s4 = "abc3[cd]xyz";
  cout << decodeString(s1) << " " << decodeString(s2) << " " << decodeString(s3)
       << " " << decodeString(s4) << endl;
  cout << decodeString1(s1) << " " << decodeString1(s2) << " "
       << decodeString1(s3) << " " << decodeString1(s4) << endl;
  return 0;
}