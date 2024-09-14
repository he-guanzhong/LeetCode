#include "head.h"
/* LCR 190. 加密运算
计算机安全专家正在开发一款高度安全的加密通信软件，需要在进行数据传输时对数据进行加密和解密操作。假定
dataA 和 dataB 分别为随机抽样的两次通信的数据量：
    正数为发送量
    负数为接受量
    0 为数据遗失
请不使用四则运算符的情况下实现一个函数计算两次通信的数据量之和（三种情况均需被统计），
以确保在数据传输过程中的高安全性和保密性。
示例 1:
  输入：dataA = 5, dataB = -1
  输出：4 */

int encryptionCalculate(int dataA, int dataB) {
  while (dataB) {
    int tmp = (dataB & dataA) << 1;
    dataA ^= dataB;
    dataB = tmp;
  }
  return dataA;
}

// 注意到,00+00=00,00+01=01,01+01=10，对于非进位项，运算类似异或，对进位项，运算类似按位与，且左移一位。
// 每一轮，c保存进位，为a和b按位与&运算再左移一位。注意只有无符号整型，才能左移。之后，a保存a、b按位异或值，得到无进位上的值
// b保存为该轮进位值，直至无进位后，循环终止。
int encryptionCalculate1(int dataA, int dataB) {
  while (dataB) {
    int c = (unsigned int)(dataA & dataB) << 1;
    dataA ^= dataB;
    dataB = c;
  }
  return dataA;
}

int main() {
  cout << encryptionCalculate(5, -1) << endl;
  cout << encryptionCalculate1(5, -1) << endl;

  return 0;
}