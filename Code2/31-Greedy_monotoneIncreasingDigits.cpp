#include "head.h"
/* 738. 单调递增的数字
当且仅当每个相邻位数上的数字 x 和 y 满足 x <= y 时，我们称这个整数是单调递增的。
给定一个整数 n ，返回 小于或等于 n 的最大数字，且数字呈 单调递增 。
示例 1:
  输入: n = 10 输出: 9
示例 2:
  输入: n = 1234 输出: 1234
示例 3:
  输入: n = 332 输出: 299
示例 4:
  输入:n = 101  输出: 99 */

int monotoneIncreasingDigits(int n) {
  string str = to_string(n);
  int index = str.size();
  for (int i = str.size() - 2; i >= 0; i--) {
    if (str[i] > str[i + 1]) {
      index = i + 1;
      str[i]--;
    }
  }
  for (int j = index; j < str.size(); j++)
    str[j] = '9';
  return stoi(str);
}

// 转为字符串，从后向前遍历，前位数字大于本位数字（不能等于），记录改9本位，前位减1。
// 避免例子101类似情况，记录改9起始位，其初始化位size()，二次循环遍历，再统一改9
// 使用字符串转化to_string和stoi，方便按位操作。从后向前遍历，如果前数字大于当前数字，则前数字-1，当前数字改9
// 时间复杂度n，空间复杂度n，因为转化了字符串，n均为字符串长度
int monotoneIncreasingDigits1(int n) {
  string strNum = to_string(n);
  int flag =
      strNum.size();  // 标记赋值9开始的地方，初始化为此值，防止进入第二个for
  for (int i = strNum.size() - 1; i > 0; i--) {
    if (strNum[i - 1] > strNum[i]) {
      flag = i;
      strNum[i - 1]--;
    }
  }
  for (int i = flag; i < strNum.size(); i++)
    strNum[i] = '9';
  return stoi(strNum);
}

// 暴力解法，时间复杂度 n*m(数字位数)
bool checkNum2(int n) {
  int pre = n % 10;
  while (n) {
    n /= 10;
    int cur = n % 10;
    if (cur > pre)
      return false;
    pre = cur;
  }
  return true;
}
int monotoneIncreasingDigits2(int n) {
  for (int i = n; i >= 0; i--) {
    if (checkNum2(i))
      return i;
  }
  return 0;
}

int main() {
  int n1 = 10, n2 = 1234, n3 = 332, n4 = 101, n5 = 120;
  cout << monotoneIncreasingDigits(n1) << " " << monotoneIncreasingDigits(n2)
       << " " << monotoneIncreasingDigits(n3) << " "
       << monotoneIncreasingDigits(n4) << " " << monotoneIncreasingDigits(n5)
       << endl;
  cout << monotoneIncreasingDigits1(n1) << " " << monotoneIncreasingDigits1(n2)
       << " " << monotoneIncreasingDigits1(n3) << " "
       << monotoneIncreasingDigits1(n4) << " " << monotoneIncreasingDigits1(n5)
       << endl;

  return 0;
}