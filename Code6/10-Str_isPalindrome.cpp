#include "head.h"
/* 125. 验证回文串
如果在将所有大写字符转换为小写字符、并移除所有非字母数字字符之后，短语正着读和反着读都一样。则可以认为该短语是一个
回文串 。
字母和数字都属于字母数字字符。
给你一个字符串 s，如果它是 回文串 ，返回 true ；否则，返回 false 。
示例 1：
  输入: s = "A man, a plan, a canal: Panama"
  输出：true
  解释："amanaplanacanalpanama" 是回文串。
示例 2：
  输入：s = "race a car"
  输出：false
  解释："raceacar" 不是回文串。
示例 3：
  输入：s = " "
  输出：true
解释：在移除非字母数字字符之后，s 是一个空字符串 "" 。
  由于空字符串正着反着读都一样，所以是回文串。
提示：
    1 <= s.length <= 2 * 105
    s 仅由可打印的 ASCII 字符组成 */

bool isPalindrome(string s) {
  for (int i = 0; i < s.size(); i++) {
    s[i] = tolower(s[i]);
  }
  for (int i = 0, j = s.size() - 1; i < j;) {
    while (i < j && !isalnum(s[i]))
      i++;
    while (i < j && !isalnum(s[j]))
      j--;
    if (s[i] != s[j])
      return false;
    i++, j--;
  }
  return true;
}

// 考察内部API调用。islower()/isupper()判断是否大小写字母。tolower()和toupper()字符转换。
// isdigit()判断数字，isalptha()判断字母，isalnum()判断是否字母或数字
// ASCII码，数字0从48开始，A从65开始，a从97开始
// tolower()函数可以传入非字母字符，但函数仅对大写字母字符进行转换，对非字母字符（如数字、标点符号等）将保持原值不变
bool isPalindrome1(string s) {
  for (int i = 0; i < s.size(); i++) {
    if (isupper(s[i]))
      s[i] = tolower(s[i]);
  }
  for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
    while (i < j && !isalnum(s[i]))
      i++;
    while (i < j && !isalnum(s[j]))
      j--;
    if (s[i] != s[j])
      return false;
  }
  return true;
}

int main() {
  string s1 = "A man, a plan, a canal: Panama", s2 = "race a car", s3 = " ",
         s4 = "0P", s5 = ".,";
  cout << isPalindrome(s1) << " " << isPalindrome(s2) << " " << isPalindrome(s3)
       << " " << isPalindrome(s4) << " " << isPalindrome(s5) << endl;
  cout << isPalindrome1(s1) << " " << isPalindrome1(s2) << " "
       << isPalindrome1(s3) << " " << isPalindrome1(s4) << " "
       << isPalindrome1(s5) << endl;
  return 0;
}
