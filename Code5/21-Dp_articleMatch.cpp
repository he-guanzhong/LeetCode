#include "head.h"
/* LCR 137. 模糊搜索验证
请设计一个程序来支持用户在文本编辑器中的模糊搜索功能。用户输入内容中可能使用到如下两种通配符：
    '.' 匹配任意单个字符。
    '*' 匹配零个或多个前面的那一个元素。
请返回用户输入内容 input 所有字符是否可以匹配原文字符串 article。
示例 1:
  输入: article = "aa", input = "a"
  输出: false
  解释: "a" 无法匹配 "aa" 整个字符串。
示例 2:
  输入: article = "aa", input = "a*"
  输出: true
  解释: 因为 '*' 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是
    'a'。因此，字符串 "aa" 可被视为 'a' 重复了一次。
示例 3:
  输入: article = "ab", input = ".*"
  输出: true
  解释: ".*" 表示可匹配零个或多个（'*'）任意字符（'.'）。
提示：
    1 <= article.length <= 20
    1 <= input.length <= 20
    article 只包含从 a-z 的小写字母。
    input 只包含从 a-z 的小写字母，以及字符 . 和 * 。
    保证每次出现字符 * 时，前面都匹配到有效的字符 */

bool articleMatch(string s, string p) {
  if (p.empty())
    return s.empty();
  bool matched = s.size() && (p[0] == s[0] || p[0] == '.');
  if (p.size() > 1 && p[1] == '*')
    return matched && articleMatch(s.substr(1), p) ||
           articleMatch(s, p.substr(2));
  else
    return matched && articleMatch(s.substr(1), p.substr(1));
}

// 递归做法，易于理解。当p为空时，看s为空状态。首字母匹配状态有二，1.s不空且s和p首字母相同，2.p首字母为'.'
// 向下递归，如果p后一位存在'*'，返回任意一种，1.p忽略*及之前两个元素，p退后两位。2.首字母匹配+s元素后有若干相等元素后退一位
// 如果p后不存在*，返回首字母相等状态+s和p均后退一元素。
bool articleMatch1(string s, string p) {
  if (p.empty())
    return s.empty();
  bool first_match = !s.empty() && (s[0] == p[0] || p[0] == '.');
  if (p.size() > 1 && p[1] == '*')
    return first_match && articleMatch1(s.substr(1), p) ||
           articleMatch1(s, p.substr(2));
  else
    return first_match && articleMatch1(s.substr(1), p.substr(1));
}

int main() {
  cout << articleMatch("aa", "a") << " " << articleMatch("aa", "a*") << " "
       << articleMatch("ab", ".*") << endl;
  cout << articleMatch1("aa", "a") << " " << articleMatch1("aa", "a*") << " "
       << articleMatch1("ab", ".*") << endl;
  return 0;
}