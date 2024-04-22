#include "head.h"
/* LCR 177. 撞色搭配
整数数组 sockets 记录了一个袜子礼盒的颜色分布情况，其中 sockets[i]
表示该袜子的颜色编号。礼盒中除了一款撞色搭配的袜子，每种颜色的袜子均有两只。请设计一个程序，在时间复杂度
O(n)，空间复杂度O(1) 内找到这双撞色搭配袜子的两个颜色编号。
示例 1：
输入：sockets = [4, 5, 2, 4, 6, 6]
输出：[2,5] 或 [5,2]
示例 2：
输入：sockets = [1, 2, 4, 1, 4, 3, 12, 3]
输出：[2,12] 或 [12,2]  */

vector<int> sockCollocation(vector<int>& sockets) {
  int n = 0;
  for (int i : sockets)
    n ^= i;
  int m = 1;
  while ((m & n) == 0)
    m <<= 1;
  int x = 0, y = 0;
  for (int i : sockets) {
    if (i & m)
      x ^= i;
    else
      y ^= i;
  }
  return {x, y};
}

// 分成两组，每组只有一个不重复元素x,y。先便利异或所有sockets，得到x^y=n，如此n的二进制每一位1，都是x和y不同位。
// 初始化m=1，从右往左按位与&，直至n&m!=0，说明找到了x和y第一个不同位。以此为基准，二次遍历sockets，num&m等于0和等于1的各一堆，分别对x和y不断异或
// 最终返回x、y的结果。注意，符号优先级，按位移动>比较>按位与>赋值。时间复杂度由于遍历过一次sockets，O(n),空间复杂度常量级O(1)
vector<int> sockCollocation1(vector<int>& sockets) {
  int x = 0, y = 0, m = 1, n = 0;
  for (int& num : sockets)
    n ^= num;
  while ((m & n) == 0)  // 按位与&优先级小于比较==
    m <<= 1;
  for (int& num : sockets) {
    if (num & m)
      x ^= num;
    else
      y ^= num;
  }
  return vector<int>({x, y});
}

int main() {
  vector<int> sockets1 = {4, 5, 2, 4, 6, 6},
              sockets2 = {1, 2, 4, 1, 4, 3, 12, 3};
  printVector(sockCollocation(sockets1));
  printVector(sockCollocation(sockets2));
  printVector(sockCollocation1(sockets1));
  printVector(sockCollocation1(sockets2));
  return 0;
}