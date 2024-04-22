#include "head.h"
/* 131. 分割回文串
给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s
所有可能的分割方案。
示例 1：
输入：s = "aab"
输出：[["a","a","b"],["aa","b"]]

回文串 是正着读和反着读都一样的字符串。 */

// 额外函数双指针判断是否回文。横向遍历start为起点，i为终点。不是回文，直接跳过后序纵向遍历流程。终止条件为start已到末端
// 但是判断字符串是否回文，可以提前计算出表格查询。
vector<vector<string>> result;
vector<string> path;
void calcPalindrome(string s, vector<vector<bool>>& Palindrome) {
  for (int i = s.size() - 1; i >= 0; i--) {
    for (int j = i; j < s.size(); j++) {
      if (i == j)
        Palindrome[i][j] = true;
      else if (j - i == 1)
        Palindrome[i][j] = s[i] == s[j];
      else
        Palindrome[i][j] = Palindrome[i + 1][j - 1] && s[i] == s[j];
    }
  }
}
void backtracking(string s, int start, vector<vector<bool>>& Palindrome) {
  if (start == s.size()) {
    result.push_back(path);
    return;
  }
  for (int i = start; i < s.size(); i++) {
    if (Palindrome[start][i])
      path.push_back(s.substr(start, i - start + 1));
    else
      continue;
    backtracking(s, i + 1, Palindrome);
    path.pop_back();
  }
}
vector<vector<string>> partition(string s) {
  result.clear();
  path.clear();
  vector<vector<bool>> Palindrome(s.size(), vector<bool>(s.size(), false));
  calcPalindrome(s, Palindrome);
  backtracking(s, 0, Palindrome);
  return result;
}

// 关键在于切割的坐标，可以转化为组合问题。设置判断回文函数，startIndex是切割起点，i是切割终点。
// 如果子串回文，才压入，否则跳过。
vector<vector<string>> result1;
vector<string> path1;
bool isPalindrome1(string s, int start, int end) {
  for (int i = start, j = end; i < j; i++, j--) {
    if (s[i] != s[j])
      return false;
  }
  return true;
}
void backtracking1(string s, int startIndex) {
  if (startIndex >= s.size()) {
    result1.push_back(path1);
    return;
  }
  for (int i = startIndex; i < s.size(); i++) {
    if (isPalindrome1(s, startIndex, i)) {
      string str = s.substr(startIndex, i - startIndex + 1);
      path1.push_back(str);
    } else
      continue;
    backtracking1(s, i + 1);
    path1.pop_back();
  }
}
vector<vector<string>> partition1(string s) {
  result1.clear();
  path1.clear();
  backtracking1(s, 0);
  return result1;
}

// 使用二维数组记录是否回文的结果，斜方矩阵填充右上角，自右下角开始填，i--,j++完成矩阵
vector<vector<bool>> Palindrome2;
void computePalindrome2(string s) {
  Palindrome2.resize(s.size(), vector<bool>(s.size(), false));
  for (int i = s.size() - 1; i >= 0; i--) {
    for (int j = i; j < s.size(); j++) {
      if (j == i)
        Palindrome2[i][j] = true;
      else if (j - i == 1)
        Palindrome2[i][j] = (s[i] == s[j]);
      else
        Palindrome2[i][j] = (s[i] == s[j] && Palindrome2[i + 1][j - 1]);
    }
  }
}
void backtracking2(string s, int startIndex) {
  if (startIndex >= s.size()) {
    result1.push_back(path1);
    return;
  }
  for (int i = startIndex; i < s.size(); i++) {
    if (Palindrome2[startIndex][i] == true) {
      string str = s.substr(startIndex, i - startIndex + 1);
      path1.push_back(str);
    } else
      continue;
    backtracking2(s, i + 1);
    path1.pop_back();
  }
}
vector<vector<string>> partition2(string s) {
  result1.clear();
  path1.clear();
  computePalindrome2(s);
  backtracking2(s, 0);
  return result1;
}

void printMat(vector<vector<string>>& res) {
  for (auto i : res) {
    for_each(i.begin(), i.end(), [](const auto& val) { cout << val << " , "; });
    cout << "\t";
  }
  cout << endl;
}
int main() {
  string s1 = "aab";
  string s2 = "a";
  string s3 = "";
  printMat(partition(s1));
  printMat(partition(s2));
  printMat(partition(s3));
  printMat(partition1(s1));
  printMat(partition1(s2));
  printMat(partition1(s3));
  return 0;
}
