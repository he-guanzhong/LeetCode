#include "head.h"
/* LCR 187. 破冰游戏
社团共有 num 位成员参与破冰游戏，编号为 0 ~
num-1。成员们按照编号顺序围绕圆桌而坐。社长抽取一个数字 target，从 0
号成员起开始计数，排在第 target
位的成员离开圆桌，且成员离开后从下一个成员开始计数。请返回游戏结束时最后一位成员的编号。
示例 1：
输入：num = 7, target = 4
输出：1
示例 2：
输入：num = 12, target = 5
输出：0 */

int iceBreakingGame(int num, int target) {
  int pre = 0;
  for (int i = 2; i <= num; i++) {
    int cur = (pre + target) % i;
    pre = cur;
  }
  return pre;
}

// 约瑟夫环问题。熟记动态规划公式f(n)=(f(n-1)+m)%n。其中，n为元素个数，m为每次要移动位数。从1开始，f(n)为该轮要删除元素的下标。初始化f(1)=0
int iceBreakingGame1(int num, int target) {
  int x = 0;
  for (int i = 2; i <= num; i++) {
    x = (x + target) % i;
  }
  return x;
}

int main() {
  cout << iceBreakingGame(7, 4) << " " << iceBreakingGame(12, 5) << endl;
  cout << iceBreakingGame1(7, 4) << " " << iceBreakingGame1(12, 5) << endl;

  return 0;
}