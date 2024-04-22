#include "head.h"
/* LCR 165. 解密数字
现有一串神秘的密文 ciphertext，经调查，密文的特点和规则如下：
    密文由非负整数组成
    数字 0-25 分别对应字母 a-z
请根据上述规则将密文 ciphertext 解密为字母，并返回共有多少种解密结果。
示例 1:
输入: ciphertext = 216612
输出: 6
解释: 216612 解密后有 6 种不同的形式，分别是
"cbggbc"，"vggbc"，"vggm"，"cbggm"，"cqggbc" 和 "cqggm"  */

int crackNumber(int ciphertext) {
  int dp0 = 1, dp1 = 1, x, y = ciphertext % 10;
  while (ciphertext > 9) {
    ciphertext /= 10;
    x = ciphertext % 10;
    int tmp = 10 * x + y;
    int dp2 = (tmp >= 10 && tmp <= 25) ? dp1 + dp0 : dp1;
    dp0 = dp1;
    dp1 = dp2;
    y = x;
  }
  return dp1;
}

// 字符串，整数转化位字符串，方便切割当前位i的前两位数字[i-2,i)，直接利用string的字符串比较函数。其范围[00,99]，只接受[10,25]
// dp[i]记录第i位结尾的解密结果数。初始化dp0=dp1=1，因为无数字和只有一位数字，各有一种办法string
// 时间复杂度O(n)，空间复杂度O(n)
// compare函数，str1.compare(str2)，当str1>str2返回1，str1<str2返回-1，str1==str2返回0。字符串比较abc<adc,abc<abcd
int crackNumber1(int ciphertext) {
  string text = to_string(ciphertext);
  int dp0 = 1, dp1 = 1;
  for (int i = 2; i <= text.size(); i++) {
    string tmp = text.substr(i - 2, 2);
    int dp2 =
        tmp.compare("10") >= 0 && tmp.compare("25") <= 0 ? dp0 + dp1 : dp1;
    dp0 = dp1;
    dp1 = dp2;
  }
  return dp1;
}

// 从右至左遍历，求余，免除转换字符串，空间复杂度O(1)。dp0代表最后一位，dp1位倒数第二位，逆求余
int crackNumber2(int ciphertext) {
  int dp0 = 1, dp1 = 1, x, y = ciphertext % 10;  // 个位上数字y
  while (ciphertext > 9) {                       // 剩余必须两位
    ciphertext /= 10;
    x = ciphertext % 10;  // 十位上数字
    int tmp = 10 * x + y;
    int dp2 = tmp >= 10 && tmp <= 25 ? dp1 + dp0 : dp1;
    dp0 = dp1;
    dp1 = dp2;
    y = x;  // 个位数字更新为当前十位
  }
  return dp1;
}

int main() {
  int ciphertext1 = 216612;
  cout << crackNumber(ciphertext1) << " " << crackNumber(24547) << endl;
  cout << crackNumber2(ciphertext1) << " " << crackNumber2(24547) << endl;

  return 0;
}