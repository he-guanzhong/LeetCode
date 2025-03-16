#include "head.h"
/* 680. 验证回文串 II
给你一个字符串 s，最多 可以从中删除一个字符。
请你判断 s 是否能成为回文字符串：如果能，返回 true ；否则，返回 false 。
示例 1：
  输入：s = "aba"
  输出：true
示例 2：
  输入：s = "abca"
  输出：true
  解释：你可以删除字符 'c' 。
示例 3：
  输入：s = "abc"
  输出：false
提示：
    1 <= s.length <= 105
    s 由小写英文字母组成 */

// 贪心算法。只有一次跳过字符的机会。双指针向中央收敛，主函数一旦发现不回文，左指针或右指针进一，任意一个满足剩下向中央的子串回文即可
bool check(const string& s, int left, int right) {
  for (int i = left, j = right; i < j; i++, j--) {
    if (s[i] != s[j])
      return false;
  }
  return true;
}

bool validPalindrome(string s) {
  for (int i = 0, j = s.size() - 1; i < j; i++, j--) {
    if (s[i] != s[j]) {
      return check(s, i + 1, j) || check(s, i, j - 1);
    }
  }
  return true;
}

int main() {
  string s1 = "aba", s2 = "abca", s3 = "abc", s4 = "zryxeededexyz";
  cout << validPalindrome(s1) << " " << validPalindrome(s2) << " "
       << validPalindrome(s3) << " " << validPalindrome(s4) << endl;
  return 0;
}