#include "head.h"
/* LCR 138. 有效数字
有效数字（按顺序）可以分成以下几个部分：
    若干空格
    一个 小数 或者 整数
    （可选）一个 'e' 或 'E' ，后面跟着一个 整数
    若干空格
小数（按顺序）可以分成以下几个部分：
    （可选）一个符号字符（'+' 或 '-'）
    下述格式之一：
        至少一位数字，后面跟着一个点 '.'
        至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
        一个点 '.' ，后面跟着至少一位数字
整数（按顺序）可以分成以下几个部分：
    （可选）一个符号字符（'+' 或 '-'）
    至少一位数字
部分有效数字列举如下：["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10",
"-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"]
部分无效数字列举如下：["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3",
"95a54e53"]
给你一个字符串 s ，如果 s 是一个 有效数字 ，请返回 true 。
示例 1：
  输入：s = "0"
  输出：true
示例 2：
  输入：s = "e"
  输出：false
示例 3：
  输入：s = "."
  输出：false */

bool validNumber(string s) {
  int i = 0, j = s.size() - 1;
  while (i < j && s[i] == ' ')
    i++;
  while (i < j && s[j] == ' ')
    j--;
  if (i == j)
    return false;
  s = s.substr(i, j - i + 1);
  bool sign = false, dot = false, num = false, E = false;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] >= '0' && s[i] <= '9')
      num = true;
    else if ((s[i] == 'E' || s[i] == 'e') && num && !E) {
      E = true;
      num = false;
    } else if ((s[i] == '+' || s[i] == '-') && i == 0 || s[i - 1] == 'E' ||
               s[i - 1] == 'e') {
      sign = true;
    } else if (s[i] == '.' && !E && !dot) {
      dot = true;
    } else {
      return false;
    }
  }
  return num;
}

// 掐头去尾空格方法，可选两头向中央靠拢，保证处理后字符串至少一位。注意正负号的处理方式，只有首位，或e后首位才允许跳过本轮，否则应该报错
// 掐头去尾时，设置数字、点、E三个特殊标志位。以下分四种情况，一、数字，数字位置1。二、点，必须前方无e，无点。
// 三、E，必须前方有数，无E。注意，E后要重新计数，因为要保证E后有数。四、正负号，只有第一位，或者E后第一位才允许，此轮不赋值
// 剩余情况，全部为非法，返回假。遍历最终返回，数字是否出现过，防止无数字的情况。
bool validNumber1(string s) {
  int i = 0;
  while (i < s.size() && s[i] == ' ')  // 重点一，i不得超限
    i++;
  if (i == s.size())
    return false;   // 防止全是空格
  s = s.substr(i);  // 第二个参数不指定，则直接到末尾
  while (s.back() == ' ')
    s.pop_back();
  bool numFlg = false;
  bool dotFlg = false;
  bool eFlg = false;
  for (int i = 0; i < s.size(); i++) {
    if (isdigit(s[i]))  // 判断是否数字
      numFlg = true;
    else if (s[i] == '.' && !dotFlg && !eFlg)
      dotFlg = true;
    else if ((s[i] == 'e' || s[i] == 'E') && !eFlg && numFlg) {
      eFlg = true;
      numFlg = false;
    } else if ((s[i] == '+' || s[i] == '-') &&
               (i == 0 || s[i - 1] == 'e' || s[i - 1] == 'E'))
      continue;
    else
      return false;
  }
  return numFlg;
}

int main() {
  string s1 = "+100", s2 = " 05e2 ", s3 = "  -123 ", s4 = "-1E-16";
  string s5 = "12e", s6 = "1a3.14", s7 = "1.2.3", s8 = "12e+5.4", s9 = "+-5",
         s10 = " ", s11 = "e";
  cout << validNumber(s1) << " " << validNumber(s2) << " " << validNumber(s3)
       << " " << validNumber(s4) << endl;
  cout << validNumber(s5) << " " << validNumber(s6) << " " << validNumber(s7)
       << " " << validNumber(s8) << " " << validNumber(s9) << " "
       << validNumber(s10) << " " << validNumber(s11) << endl;
  cout << validNumber1(s1) << " " << validNumber1(s2) << " " << validNumber1(s3)
       << " " << validNumber1(s4) << endl;
  cout << validNumber1(s5) << " " << validNumber1(s6) << " " << validNumber1(s7)
       << " " << validNumber1(s8) << " " << validNumber1(s9) << " "
       << validNumber1(s10) << " " << validNumber1(s11) << endl;
  return 0;
}