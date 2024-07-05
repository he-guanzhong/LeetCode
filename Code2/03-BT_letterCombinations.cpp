#include "head.h"
/* 17. 电话号码的字母组合
给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按
任意顺序返回。 给出数字到字母的映射如下（与电话按键相同）。注意 1
不对应任何字母。 示例 1： 输入：digits = "23"
  输出：["ad","ae","af","bd","be","bf","cd","ce","cf"]
示例 2：
  输入：digits = ""
  输出：[]
示例 3：
  输入：digits = "2"
  输出：["a","b","c"] */

vector<string> letterMap = {"",    "",    "abc",  "def", "ghi",
                            "jkl", "mno", "pqrs", "tuv", "wxyz"};
void backtracking(string digits, int index, string path, vector<string>& ans) {
  if (index == digits.size()) {
    ans.push_back(path);
    return;
  }
  string letter = letterMap[digits[index] - '0'];
  for (int i = 0; i < letter.size(); i++) {
    backtracking(digits, index + 1, path + letter[i], ans);
  }
}
vector<string> letterCombinations(string digits) {
  vector<string> ans;
  if (digits.empty())
    return ans;
  string path;
  backtracking(digits, 0, path, ans);
  return ans;
}

// 二维数组，记录数字和字符的映射关系，注意0，1空着，大小为10，则下标可于数字直接对应
// index表示字符串即将访问的位数，即回溯深度。退出条件为路径s大小到最深
// 利用-'0'方法将源字符转化为实际数字，不得使用stoi，因为是char。以此访问map库，得到目标字母序列
// 横向遍历目标字母序列，回溯时不得使用-=，递归时深度加一
const string letterMap1[10] = {"",    "",    "abc",  "def", "ghi",
                               "jkl", "mno", "pqrs", "tuv", "wxyz"};
vector<string> result1;
string s1;
void backtracking1(const string& digits, int index) {
  if (digits.size() == index) {
    result1.push_back(s1);
    return;
  }
  int digit = digits[index] - '0';  // 字符和数字转换
  string letters = letterMap1[digit];
  // int digit = stoi(digits[index]);
  for (int i = 0; i < letters.size(); i++) {
    s1 += letters[i];
    backtracking1(digits, index + 1);
    s1.pop_back();
  }
}
vector<string> letterCombinations1(string digits) {
  result1.clear();
  s1.clear();
  if (digits.empty())  // 一定要判断，否则报错
    return result1;
  backtracking1(digits, 0);
  return result1;
}

// 先创立常量的映射字符串数组，也可以为动态数组，注意下标对应，空开0和1。深度为数字字符串位数index，其到达最后一位即退出
// 广度为每一个数字对应的字母字符串长度。故要先对数字字符串的指定index位字符转化为int整型，再引用映射字符串
// 临时字符串可以外置，也可以作为传参，但必须conststring&或string。如此回溯可以在参数中做
// 注意额外判断传入digit是否为空
// 递归也可以藏在回溯中，此时临时路径s必须作为参数，但传入格式必须为const否则报错
void getCombinations2(const string& digits, int index, const string& s1) {
  if (index == digits.size()) {
    result1.push_back(s1);
    return;
  }
  int digit = digits[index] - '0';
  string letters = letterMap1[digit];
  for (int i = 0; i < letters.size(); i++)
    getCombinations2(digits, index + 1, s1 + letters[i]);
}
vector<string> letterCombinations2(string digits) {
  result1.clear();
  if (digits.empty())
    return result1;
  getCombinations2(digits, 0, "");
  return result1;
}

int main() {
  string s1 = "23", s2 = "", s3 = "2";
  printVector(letterCombinations(s1));
  printVector(letterCombinations(s2));
  printVector(letterCombinations(s3));
  printVector(letterCombinations1(s1));
  printVector(letterCombinations1(s2));
  printVector(letterCombinations1(s3));
  return 0;
}