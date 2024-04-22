#include "head.h"
/* 509. 斐波那契数
斐波那契数 （通常用 F(n) 表示）形成的序列称为 斐波那契数列 。该数列由 0 和 1
开始，后面的每一项数字都是前面两项数字的和。也就是：
 F(0) = 0，F(1) = 1 F(n) = F(n - 1) + F(n - 2)，
 其中 n > 1 给定 n ，请计算 F(n) 。 示例 1： 输入：n = 2
输出：1
解释：F(2) = F(1) + F(0) = 1 + 0 = 1
示例 2：
输入：n = 3
输出：2
解释：F(3) = F(2) + F(1) = 1 + 1 = 2
示例 3：
输入：n = 4
输出：3
解释：F(4) = F(3) + F(2) = 2 + 1 = 3
 */

// 尽量不使用递归，效率低。0和1特殊处理。只需维护i-1和i-2两个值即可
int fib(int n) {
  if (n == 0 || n == 1)
    return n;
  int dp[2];
  dp[0] = 0;
  dp[1] = 1;
  for (int i = 2; i <= n; i++) {
    int tmp = dp[0] + dp[1];
    dp[0] = dp[1];
    dp[1] = tmp;
  }
  return dp[1];
}

// 动态规划，时间复杂度n，空间复杂度n。注意初始的0和1，一定要做特殊处理返回。否则报错
// 1.dp含义为第i个的数值。3.确定递归公式。2.初始化，设定0和1。4.确定遍历顺序。5.举例推导dp数组
int fib1(int n) {
  if (n <= 1)  // 此处必不可少
    return n;
  int dp[n + 1];
  dp[0] = 0;
  dp[1] = 1;
  for (int i = 2; i <= n; i++)
    dp[i] = dp[i - 1] + dp[i - 2];
  return dp[n];
}

// 优化的动态规划。只记录两个数，时间复杂度n，空间复杂度1。
int fib2(int n) {
  if (n <= 1)  // 此处必不可少
    return n;
  int dp[2];
  dp[0] = 0;
  dp[1] = 1;
  for (int i = 2; i <= n; i++) {
    int sum = dp[0] + dp[1];
    dp[0] = dp[1];
    dp[1] = sum;
  }
  return dp[1];
}
// 递归，时间复杂度2^n，空间复杂度n(算上了系统栈占用的空间)
int fib3(int n) {
  if (n < 2)
    return n;
  return fib3(n - 1) + fib3(n - 2);
}

int main() {
  for (int i = 0; i <= 10; i++)
    cout << fib(i) << " ";
  cout << endl;
  for (int i = 0; i <= 10; i++)
    cout << fib1(i) << " ";
  cout << endl;
  return 0;
}