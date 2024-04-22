#include "head.h"
/* 301. 删除无效的括号
给你一个由若干括号和字母组成的字符串 s
，删除最小数量的无效括号，使得输入的字符串有效。 返回所有可能的结果。答案可以按
任意顺序 返回。
示例 1：
输入：s = "()())()"
输出：["(())()","()()()"]
示例 2：
输入：s = "(a)())()"
输出：["(a())()","(a)()()"]
示例 3：
输入：s = ")("
输出：[""] */
bool isValid(string s) {
  int left = 0;
  for (char c : s) {
    if (c == '(')
      left++;
    else if (c == ')') {
      if (--left < 0)
        return false;
    }
  }
  return left == 0;
}
vector<string> removeInvalidParentheses(string s) {
  unordered_set<string> cur;
  cur.insert(s);
  vector<string> ans;
  while (1) {
    for (string str : cur) {
      if (isValid(str))
        ans.push_back(str);
    }
    if (ans.size())
      break;
    unordered_set<string> next;
    for (string str : cur) {
      for (int i = 0; i < str.size(); i++) {
        if (i > 0 && str[i] == str[i - 1] || str[i] != '(' && str[i] != ')')
          continue;
        string tmp = str.substr(0, i) + str.substr(i + 1);
        if (next.find(tmp) == next.end())
          next.insert(tmp);
      }
    }
    cur = next;
  }
  return ans;
}

// 回溯法+剪枝。时间复杂度O(n)=n*2^n，因为字符串长度n，其
// 主体函数，统计待删除左右括号个数，其为二者绝对数量之差，其中一个必为0。两个辅助函数。一为判断字符串是否有效，注意字符串含有字母，故要写明判断左右括号
// 二为回溯主体，传参包括起始位、待删除左、右括号数。退出条件是，左、右待删除括号数均为0（其中一个初始值就已经为0）。判断是否满足顺序条件，若是就压入结果。
// 回溯函数，要横向树层去重，具体表现为(((()只需要保留一个左括号结果即可，需判断s[i]==s[i-1]就跳过
// 剪枝操作，若s剩余数量，比待左右括号待删除的数量总和还小，则直接退出。回溯删除括号时，注意只有左右括号确认时才能删，且删后新字符串从0开始，而非start
inline bool isValid1(const string& s) {
  int cnt = 0;
  for (char c : s) {
    if (c == '(')
      cnt++;
    else if (c == ')') {
      if (--cnt < 0)
        return false;
    }
  }
  return cnt == 0;
}
void helper1(string s,
             int start,
             int lremove,
             int rremove,
             vector<string>& ans) {
  if (lremove == 0 && rremove == 0) {
    if (isValid1(s))
      ans.push_back(s);
    return;
  }
  if (lremove + rremove > s.size() - 1)
    return;
  for (int i = start; i < s.size(); i++) {
    if (i > start && s[i] == s[i - 1])  // 树层去重
      continue;
    if (lremove > 0 &&
        s[i] == '(')  // 当前是左括号，才能删。新字符串从0开始，而不是start
      helper1(s.substr(0, i) + s.substr(i + 1), i, lremove - 1, rremove, ans);
    if (rremove > 0 && s[i] == ')')  // 当前是右括号，才能删
      helper1(s.substr(0, i) + s.substr(i + 1), i, lremove, rremove - 1, ans);
  }
}
vector<string> removeInvalidParentheses1(string s) {
  int lremove = 0, rremove = 0;
  for (char c : s) {
    if (c == '(')
      lremove++;
    else if (c == ')') {
      if (lremove == 0)
        rremove++;
      else
        lremove--;
    }
  }
  vector<string> ans;
  helper1(s, 0, lremove, rremove, ans);
  return ans;
}

// 广度优先搜索BFS。每一轮，使用哈希表记录当前字符串。对该串遍历每个字符，只要时括号，就删除，并保存成下一轮字符串哈希表。
// 每一轮开始后判断，如果该轮存在有效值，则压入结果，直接返回，即为最少删除括号结果。
// 时间复杂度O(n)=n*2^n，空间复杂度O(n)=n*C (n/2) n
vector<string> removeInvalidParentheses2(string s) {
  vector<string> ans;
  unordered_set<string> curSet;
  curSet.insert(s);
  while (1) {
    for (auto& str : curSet) {
      if (isValid1(str))
        ans.push_back(str);
    }
    if (ans.size() > 0)
      break;
    unordered_set<string> nextSet;
    for (auto& str : curSet) {
      for (int i = 0; i < str.size(); i++) {
        if (i > 0 && str[i] == str[i - 1])
          continue;
        if (str[i] == '(' || str[i] == ')')
          nextSet.insert(str.substr(0, i) + str.substr(i + 1));
      }
    }
    curSet = nextSet;
  }
  return ans;
}

int main() {
  string s1 = "()())()", s2 = "(a)())()", s3 = ")(", s4 = ")d))", s5 = "n";
  printVector(removeInvalidParentheses(s1));
  printVector(removeInvalidParentheses(s2));
  printVector(removeInvalidParentheses(s3));
  printVector(removeInvalidParentheses(s4));
  printVector(removeInvalidParentheses(s5));

  printVector(removeInvalidParentheses1(s1));
  printVector(removeInvalidParentheses1(s2));
  printVector(removeInvalidParentheses1(s3));
  printVector(removeInvalidParentheses1(s4));
  printVector(removeInvalidParentheses1(s5));

  return 0;
}