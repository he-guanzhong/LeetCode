#include "head.h"

/* 二进制求和
给你两个二进制字符串 a 和 b ，以二进制字符串的形式返回它们的和。
示例 1：
  输入:a = "11", b = "1"
  输出："100"
示例 2：
  输入：a = "1010", b = "1011"
  输出："10101"
提示：
  1 <= a.length, b.length <= 104
  a 和 b 仅由字符 '0' 或 '1' 组成
  字符串如果不是 "0" ，就不含前导零 */

string addBinary(string a, string b) {
  string ans;
  int carry = 0;
  for (int i = a.size() - 1, j = b.size() - 1; i >= 0 || j >= 0 || carry;
       i--, j--) {
    int bitA = i >= 0 ? a[i] - '0' : 0;
    int bitB = j >= 0 ? b[j] - '0' : 0;
    carry += bitA + bitB;
    ans.push_back(carry % 2 + '0');
    carry /= 2;
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

// carry代表进位，从后向前遍历a、b字符串，注意if判断整型，0值为假，非0值包括正负数均为真
// 符号优先级，*/% 大于 += 大于 <<、>> 大于 关系比较符号==
// 大于按位与&。最后反转字符串不可避免
string addBinary1(string a, string b) {
  int carry = 0;
  string ans;
  for (int i = a.size() - 1, j = b.size() - 1; carry || i >= 0 || j >= 0;
       i--, j--) {
    int val1 = i < 0 ? 0 : a[i] - '0';
    int val2 = j < 0 ? 0 : b[j] - '0';
    carry += val1 + val2;
    ans.push_back(carry % 2 + '0');
    carry /= 2;
  }
  reverse(ans.begin(), ans.end());
  return ans;
}

int main() {
  cout << addBinary("11", "1") << " " << addBinary("1010", "1011") << " "
       << addBinary("1", "111") << endl;
  cout << addBinary1("11", "1") << " " << addBinary1("1010", "1011") << " "
       << addBinary1("1", "111") << endl;
  return 0;
}