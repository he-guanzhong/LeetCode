#include "head.h"
/* 62. 不同路径
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为
“Finish” ）。
问总共有多少条不同的路径？
  示例 1：
输入：m = 3, n = 7
输出：28
  示例 2：
输入：m = 3, n = 2
输出：3
解释：
从左上角开始，总共有 3 条路径可以到达右下角。
1. 向右 -> 向下 -> 向下
2. 向下 -> 向下 -> 向右
3. 向下 -> 向右 -> 向下
  示例 3：
输入：m = 7, n = 3
输出：28
  示例 4：
输入：m = 3, n = 3
输出：6 */

// dp[i][j]表示i-1行j-1列路径数，初始化第一行、第一列全部为1，递推公式为，本格路径值为上和左两个格路径之和。
// 节省空间复杂度，可以只设置一行，从第二列开始，本格路径值，为原本格（即上一层）和左格之和。
// 数论方法。m+n-2个路径中，找m-1个的组合 C(m-1)(m+n-2)=
int uniquePaths(int m, int n) {}

// dp[i][j]表示从零点到此坐标的路径总数。到此坐标只可能从上来或从左来，故状态转移方程为上和左的和。初始化最左边和最上边值为1
// 遍历方向为从左到右，一层层遍历即可。时间复杂度m*n，空间复杂度m*n
int uniquePaths1(int m, int n) {
  vector<vector<int>> dp(m, vector<int>(n));
  for (int i = 0; i < m; i++)
    dp[i][0] = 1;
  for (int j = 0; j < n; j++)
    dp[0][j] = 1;
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    }
  }
  return dp[m - 1][n - 1];
}

// 一维数组可以节省空间，固定行，然后不断从做向右更新列。空间复杂度降级为n，时间复杂度不变
int uniquePaths2(int m, int n) {
  vector<int> dp(n);
  for (int j = 0; j < n; j++)
    dp[j] = 1;
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++)
      dp[j] += dp[j - 1];
  }
  return dp[n - 1];
}

// 数论方法。左上到右下，必有m+n-2步，其中有m-1步必为向下走。问题转化为m+n-2步中，m-1有多少种取法
// Cm/n = n! / m!(n-m)!。即分子为，n-m次n从上往下的阶乘。分母为m的阶乘
// 注意不能全部分子分母算出来再出，否则溢出。
// 时间复杂度降级为m，空间复杂度降级为1
int uniquePaths3(int m, int n) {
  int t = m + n - 2;       // 下部数字记为t
  int count = m - 1;       // 上部数字可以化为多少次
  long long numerator = 1; // 必须为long long 类型
  int denominator = m - 1; // 初始值定位count的值
  while (count--) {
    numerator *= (t--); // 分子为t从上到下阶乘count次
    while (denominator != 0 &&
           numerator % denominator == 0) { // 只要发现能整除，就除
      numerator /= denominator;
      denominator--; // 分母为m-1的不断向下阶乘
    }
  }
  return numerator;
}

int main() {
  int m1 = 3, n1 = 7;
  int m2 = 3, n2 = 2;
  int m3 = 7, n3 = 3;
  int m4 = 3, n4 = 3;
  cout << uniquePaths(m1, n1) << " " << uniquePaths(m2, n2) << " "
       << uniquePaths(m3, n3) << " " << uniquePaths(m4, n4) << " " << endl;
  cout << uniquePaths1(m1, n1) << " " << uniquePaths1(m2, n2) << " "
       << uniquePaths1(m3, n3) << " " << uniquePaths1(m4, n4) << " " << endl;
  return 0;
}