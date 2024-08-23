#include "head.h"
/* 22. 括号生成
数字 n 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 有效的
括号组合。
示例 1：
  输入：n = 3
  输出：["((()))","(()())","(())()","()(())","()()()"]
示例 2：
  输入：n = 1
  输出：["()"] */

void dfs(int n, int l, int r, string path, vector<string>& ans) {
  if (path.size() == 2 * n) {
    ans.push_back(path);
    return;
  }
  if (l < n) {
    path += '(';
    dfs(n, l + 1, r, path, ans);
    path.pop_back();
  }
  if (r < l) {
    path += ')';
    dfs(n, l, r + 1, path, ans);
    path.pop_back();
  }
}
vector<string> generateParenthesis(int n) {
  vector<string> ans;
  string path;
  dfs(n, 0, 0, path, ans);
  return ans;
}

// 传参为左、右括号数量。退出条件时path.size==2n。本层广度为，压左还是压右两种情况。
// 剪支，左括号数必须小于n才可压。右括号数必须小于left个才可压。顺序为先压左，再压右。
void backtracking1(int n,
                   int left,
                   int right,
                   vector<string>& ans,
                   string& path) {
  if (path.size() == n * 2) {
    ans.push_back(path);
    return;
  }
  if (left < n) {
    path.push_back('(');
    backtracking1(n, left + 1, right, ans, path);
    path.pop_back();
  }
  if (right < left) {
    path.push_back(')');
    backtracking1(n, left, right + 1, ans, path);
    path.pop_back();
  }
}

vector<string> generateParenthesis1(int n) {
  vector<string> ans;
  string path;
  backtracking1(n, 0, 0, ans, path);
  return ans;
}

// 动态规划。一个vector存放n的结果
vector<string> generateParenthesis2(int n) {
  vector<vector<string>> dp(n + 1);
  dp[0] = {""};
  dp[1] = {"()"};
  for (int i = 2; i <= n; i++) {   // n拓展边界i
    for (int j = 0; j < i; j++) {  // 切分点j
      for (const string& p : dp[j]) {
        for (const string& q : dp[i - 1 - j]) {
          string str = "(" + p + ")" + q;
          dp[i].push_back(str);
        }
      }
    }
  }
  return dp[n];
}

int main() {
  printVector(generateParenthesis(3));
  printVector(generateParenthesis(1));
  printVector(generateParenthesis1(3));
  printVector(generateParenthesis1(1));
  return 0;
}