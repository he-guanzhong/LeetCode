#include "head.h"
/* 32. 最长有效括号
给你一个只包含 '(' 和 ')'
的字符串，找出最长有效（格式正确且连续）括号子串的长度。
示例 1：
输入：s = "(()"
输出：2
解释：最长有效括号子串是 "()"
示例 2：
输入：s = ")()())"
输出：4
解释：最长有效括号子串是 "()()"
示例 3：
输入：s = ""
输出：0 */

int longestValidParentheses(string s) {
  stack<int> st;
  st.push(-1);
  int ans = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '(')
      st.push(i);
    else {
      st.pop();
      if (st.empty())
        st.push(i);
      else
        ans = max(ans, i - st.top());
    }
  }
  return ans;
}

// 首选利用栈，栈内存储定义是，最后一个未匹配的')'下标，其实质是截断点。为避免首元素为'('导致无右括号特殊情况。栈内先压入一个-1.
// 遍历元素，如果为'('，压入栈下标。如果为')'，先弹栈首，作为(的配对，或)的更新。若此时栈已空，则说明该)未匹配，下标压入栈内。
// 如果栈不空，则说明与栈首配对，此时长度即为i-新栈首下标
int longestValidParentheses1(string s) {
  stack<int> st;
  int ans = 0;
  st.push(-1);
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '(') {
      st.push(i);
    } else {
      st.pop();
      if (st.empty())
        st.push(i);
      else
        ans = max(ans, i - st.top());
    }
  }
  return ans;
}

// 时间复杂度O(n),空间复杂度O(1)。贪心，左右两遍遍历，记录(、)分别出现次数，若相等就求长度，左向右遍历时，若right>left则截断，计数归零
// 从右向左遍历时，若left>right时截断，计数归零。统计两遍遍历最大值
int longestValidParentheses2(string s) {
  int left = 0, right = 0, ans = 0;
  for (char c : s) {
    if (c == '(')
      left++;
    else
      right++;
    if (left == right)
      ans = max(ans, right * 2);
    else if (right > left)
      left = right = 0;
  }
  left = right = 0;
  for (int i = s.size() - 1; i >= 0; i--) {
    if (s[i] == '(')
      left++;
    else
      right++;
    if (left == right)
      ans = max(ans, left * 2);
    else if (left > right)
      left = right = 0;
  }
  return ans;
}

int main() {
  string s1 = "(()", s2 = ")()())", s3 = "", s4 = "()(()";
  cout << longestValidParentheses(s1) << " " << longestValidParentheses(s2)
       << " " << longestValidParentheses(s3) << " "
       << longestValidParentheses(s4) << endl;
  cout << longestValidParentheses1(s1) << " " << longestValidParentheses1(s2)
       << " " << longestValidParentheses1(s3) << " "
       << longestValidParentheses1(s4) << endl;
  return 0;
}