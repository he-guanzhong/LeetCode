#include "head.h"
/* LCR 192. 把字符串转换成整数 (atoi)
请你来实现一个 myAtoi(string s) 函数，使其能将字符串转换成一个 32
位有符号整数（类似 C/C++ 中的 atoi 函数）。
函数 myAtoi(string s) 的算法如下：
    读入字符串并丢弃无用的前导空格
    检查下一个字符（假设还未到字符末尾）为正还是负号，读取该字符（如果有）。
确定最终结果是负数还是正数。 如果两者都不存在，则假定结果为正。
    读入下一个字符，直到到达下一个非数字字符或到达输入的结尾。字符串的其余部分将被忽略。
    将前面步骤读入的这些数字转换为整数（即，"123" -> 123， "0032" ->
32）。如果没有读入数字，则整数为 0 。必要时更改符号（从步骤 2 开始）。
    如果整数数超过 32 位有符号整数范围 [−231,  231 − 1]
，需要截断这个整数，使其保持在这个范围内。具体来说，小于 −231 的整数应该被固定为
−231 ，大于 231 − 1 的整数应该被固定为 231 − 1 。 返回整数作为最终结果。
注意：
    本题中的空白字符只包括空格字符 ' ' 。
    除前导空格或数字后的其余字符串外，请勿忽略 任何其他字符。
示例 1：
  输入：s = "42"
  输出：42
  解释：加粗的字符串为已经读入的字符，插入符号是当前读取的字符。
    第 1 步："42"（当前没有读入字符，因为没有前导空格）
             ^
    第 2 步："42"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
             ^
    第 3 步："42"（读入 "42"）
               ^
    解析得到整数 42 。
    由于 "42" 在范围 [-231, 231 - 1] 内，最终结果为 42 。
示例 2：
  输入：s = "   -42"
  输出：-42
  解释：
    第 1 步："   -42"（读入前导空格，但忽视掉）
                ^
    第 2 步："   -42"（读入 '-' 字符，所以结果应该是负数）
                 ^
    第 3 步："   -42"（读入 "42"）
                   ^
    解析得到整数 -42 。
    由于 "-42" 在范围 [-231, 231 - 1] 内，最终结果为 -42 。
示例 3：
  输入：s = "4193 with words"
  输出：4193
  解释：
    第 1 步："4193 with words"（当前没有读入字符，因为没有前导空格）
             ^
    第 2 步："4193 with words"（当前没有读入字符，因为这里不存在 '-' 或者 '+'）
             ^
    第 3 步："4193 with words"（读入
    "4193"；由于下一个字符不是一个数字，所以读入停止）
                 ^
    解析得到整数 4193 。
    由于 "4193" 在范围 [-231, 231 - 1] 内，最终结果为 4193 。
提示：
    0 <= s.length <= 200
    s 由英文字母（大写和小写）、数字（0-9）、' '、'+'、'-' 和 '.' 组成 */

int myAtoi(string s) {
  int sign = 1;
  bool charac = false;
  int ans = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == ' ' && !charac)
      continue;
    else if (s[i] == '+' && !charac) {
      sign = 1;
      charac = true;
    } else if (s[i] == '-' && !charac) {
      sign = -1;
      charac = true;
    } else if (s[i] >= '0' && s[i] <= '9') {
      charac = true;
      if (sign * ans > INT_MAX / 10 ||
          sign * ans == INT_MAX / 10 && s[i] >= '7')
        return INT_MAX;
      else if (sign * ans < INT_MIN / 10 ||
               sign * ans == INT_MIN / 10 && s[i] >= '8')
        return INT_MIN;
      ans *= 10;
      ans += s[i] - '0';
    } else {
      break;
    }
  }
  return ans * sign;
}

// 先排除零，尤其时全零情况。然后直接排除+-号影响，设置单独sign为+-1。进入数字区间后，先判断当前ans是否大于limit，是则直接根据sign号返回INT_MIN和INT_MAX
// 不得使用sign*INT_MAX，因为二者不相等。而最终返回结果则需要sign_ans

// 三个整型变量，返回值，正负号，遍历下标i。空间复杂度O(1)。INT_MAX最大值是2147483647，超限边界INT_MAX/10=214748364。
// 先去除头部空格，注意排除所有均为空格情况。对首个元素为空格，则再进一位，并记录正负号，其下一位必为数字。只考虑是数字的情况。
int myAtoi1(string str) {
  int i = 0, num = 0, sign = 1;
  int boundary = INT_MAX / 10;
  int len = str.size();
  while (i < len && str[i] == ' ')
    i++;
  if (i == len)
    return 0;
  if (str[i] == '-')
    sign = -1;
  if (str[i] == '+' || str[i] == '-')
    i++;
  for (int j = i; j < len; j++) {
    if (str[j] < '0' || str[j] > '9')
      break;
    if (num > boundary || num == boundary && str[j] > '7')
      return sign == 1 ? INT_MAX : INT_MIN;
    num = num * 10 + (str[j] - '0');  // 此处必须加括号，否则超限
  }
  return sign * num;
}

int main() {
  string s1 = "42", s2 = "   -42", s3 = "4193 with words", s4 = "words and 987",
         s5 = "-91283472332", s6 = "+-2", s7 = "0-1", s8 = "   +0 123";
  cout << myAtoi(s1) << " " << myAtoi(s2) << " " << myAtoi(s3) << " "
       << myAtoi(s4) << " " << myAtoi(s5) << " " << myAtoi(s6) << " "
       << myAtoi(s7) << " " << myAtoi(s8) << endl;
  cout << myAtoi1(s1) << " " << myAtoi1(s2) << " " << myAtoi1(s3) << " "
       << myAtoi1(s4) << " " << myAtoi1(s5) << " " << myAtoi1(s6) << " "
       << myAtoi1(s7) << " " << myAtoi1(s8) << endl;
  return 0;
}