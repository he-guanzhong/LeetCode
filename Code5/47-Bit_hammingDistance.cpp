#include "head.h"
/* 461. 汉明距离
两个整数之间的 汉明距离 指的是这两个数字对应二进制位不同的位置的数目。
给你两个整数 x 和 y，计算并返回它们之间的汉明距离。
示例 1：
  输入：x = 1, y = 4
  输出：2
  解释：
    1   (0 0 0 1)
    4   (0 1 0 0)
           ↑   ↑
    上面的箭头指出了对应二进制位不同的位置。
示例 2：
  输入：x = 3, y = 1
  输出：1 */

int hammingDistance(int x, int y) {
  int n = x ^ y;
  int ans = 0;
  while (n) {
    n &= n - 1;
    ans++;
  }

  return ans;
}

// x和y按位异或，统计结果中等于1的位数。可以使用C和C++共有的内置函数__builtin_popcount，时间复杂度O(1)。
// 或Brian Kernighan算法，时间复杂度O(logC)。注意其是按位与，而非按位异或
int hammingDistance1(int x, int y) {
  int ans = 0;
  int z = x ^ y;
  while (z) {
    z &= z - 1;
    ans++;
  }
  return ans;
}

int hammingDistance2(int x, int y) {
  return __builtin_popcount(x ^ y);
}
int main() {
  cout << hammingDistance(1, 4) << " " << hammingDistance(3, 1) << endl;
  cout << hammingDistance1(1, 4) << " " << hammingDistance1(3, 1) << endl;

  return 0;
}