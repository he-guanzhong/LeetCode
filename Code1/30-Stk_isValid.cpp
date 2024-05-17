#include "head.h"
/* 20. 有效的括号
给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
有效字符串需满足：
    左括号必须用相同类型的右括号闭合。
    左括号必须以正确的顺序闭合。
    每个右括号都有一个对应的相同类型的左括号。
示例 1：
输入：s = "()"      输出：true
示例 2：
输入：s = "()[]{}"  输出：true
示例 3：
输入：s = "(]"      输出：false */

bool isValid(string s) {
  stack<char> st;
  for (char c : s) {
    if (c == '(')
      st.push(')');
    else if (c == '[')
      st.push(']');
    else if (c == '{')
      st.push('}');
    else if (!st.empty() && c == st.top())
      st.pop();
    else
      return false;
  }
  return st.empty();
}

// 利用栈，对每一个左括号，压入其匹配的右括号。如此，当栈不空且栈顶元素与右括号相等时，弹出栈顶元素。
// 返回false分三种情况，1、栈空（右括号多了）；2、栈顶元素与右括号不相等；3、最终栈是不为空（左括号多）
// 可额外添加剪支，开头判断，字符串s长度如果是奇数，必为false
bool isValid1(string s) {
  if (s.size() % 2 == 1)
    return false;
  stack<char> st;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '(')
      st.push(')');
    else if (s[i] == '[')
      st.push(']');
    else if (s[i] == '{')
      st.push('}');
    else if (st.empty() || st.top() != s[i])  // 右括号多 左右括号不等
      return false;
    else  // 栈非空 + 左右括号相等，才弹出
      st.pop();
  }
  return st.empty();
}

// 利用栈，三种返回假情况。左括号多（栈剩余）、左右括号不等、右括号多（栈提前为空）。
// 两种方法，一是在遇到左括号时将右括号压入，然后比较右括号相等。二是非空栈，且遇到相等的右括号，再弹出
bool isValid2(string s) {
  if (s.size() % 2 == 1)
    return false;
  stack<char> st;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '(' || s[i] == '[' || s[i] == '{')
      st.push(s[i]);
    else if (!st.empty() &&
             (s[i] == ')' && st.top() == '(' ||
              s[i] == ']' && st.top() == '[' || s[i] == '}' && st.top() == '{'))
      st.pop();
    else
      return false;  // 此项不可少，否则对右括号多的情况无法处理
  }
  return st.empty();
}

int main() {
  string s1 = "()", s2 = "()[]{}", s3 = "(]", s4 = "]]";
  cout << isValid(s1) << " " << isValid(s2) << " " << isValid(s3) << " "
       << isValid(s4) << endl;
  cout << isValid1(s1) << " " << isValid1(s2) << " " << isValid1(s3) << " "
       << isValid1(s4) << endl;
  return 0;
}