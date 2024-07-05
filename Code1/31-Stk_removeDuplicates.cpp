#include "head.h"
/* 1047. 删除字符串中的所有相邻重复项
给出由小写字母组成的字符串S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。
在 S上反复执行重复项删除操作，直到无法继续删除。
在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。
  输入："abbaca"
  输出："ca"
  解释：
    例如，在 "abbaca" 中，我们可以删除 "bb"
    由于两字母相邻且相同，这是此时唯一可以执行删除操作的重复项。之后我们得到字符串
    "aaca"，其中又只有 "aa" 可以执行重复项删除操作，所以最后的字符串为 "ca"。 */

string removeDuplicates(string s) {
  stack<int> st;
  string ans;
  for (char c : s) {
    if (!st.empty() && c == st.top())
      st.pop();
    else
      st.push(c);
  }
  ans.resize(st.size());
  int i = ans.size() - 1;
  while (!st.empty()) {
    ans[i--] = st.top();
    st.pop();
  }
  return ans;
}

// 核心思路是利用栈，如果碰到栈不空，且栈顶元素等于下一压入元素时，弹出栈顶元素。若栈为空、或栈顶元素不等，则压入新元素。
// 结果字符串的back\pop_back可以替代栈的操作，如此不必使用额外的栈，和额外的反转操作。
// 直接把字符串当栈，节省资源。其具有front back push_back pop_back功能
string removeDuplicates1(string S) {
  string result = "";
  for (char ch : S) {
    if (result.empty() || result.back() != ch)
      result.push_back(ch);
    else
      result.pop_back();
  }
  return result;
}

string removeDuplicates2(string S) {
  stack<char> st;
  for (int i = 0; i < S.size(); i++) {
    if (!st.empty() && S[i] == st.top())
      st.pop();
    else
      st.push(S[i]);
  }
  string result = "";
  while (!st.empty()) {
    result += st.top();
    st.pop();
  }
  reverse(result.begin(), result.end());
  return result;
}

int main() {
  string s = "abbaca";
  cout << removeDuplicates(s) << endl;
  cout << removeDuplicates1(s) << endl;
}
