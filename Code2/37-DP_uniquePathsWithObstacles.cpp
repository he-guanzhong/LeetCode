#include "head.h"
/* 63. 不同路径 II
一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为
“Finish”）。
现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
网格中的障碍物和空位置分别用 1 和 0 来表示。
示例 1：
  输入：obstacleGrid = {{0,0,0},{0,1,0},{0,0,0}}
  输出：2
  解释：3x3 网格的正中间有一个障碍物。
    从左上角到右下角一共有 2 条不同的路径：
    1. 向右 -> 向右 -> 向下 -> 向下
    2. 向下 -> 向下 -> 向右 -> 向右
示例 2：
  输入：obstacleGrid = {{0,1},{0,0}}
  输出：1 */

int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
  int m = obstacleGrid.size(), n = obstacleGrid[0].size();
  vector<int> dp(n, 0);
  for (int j = 0; j < n && obstacleGrid[0][j] != 1; j++)
    dp[j] = 1;
  for (int i = 1; i < m; i++) {
    if (obstacleGrid[i][0] == 1)
      dp[0] = 0;
    for (int j = 1; j < n; j++) {
      if (obstacleGrid[i][j] == 1)
        dp[j] = 0;
      else
        dp[j] += dp[j - 1];
    }
  }
  return dp[n - 1];
}

// dp[i][j]表示坐标i,j的路径数。初始化全部路径值为0，第一行、第一列路径值为1，遇到障碍物1break可以简写到for循环内。正常递推遇到障碍物1要跳过continue
// 节省空间复杂度方法，dp[j]初始化第一行。递推从第二行开始，遇到障碍物，直接置零而非跳过。递推自j=0开始，但j>0时才适配递推公式。

// 必须首先对起点终点排除。dp[i][j]表示到达此处的路方法，堵塞处值为0。初始化时左边一列和上面一行遇堵塞后均为0
// 时间复杂度和空间复杂度均为m*n
int uniquePathsWithObstacles1(vector<vector<int>>& obstacleGrid) {
  int m = obstacleGrid.size();
  int n = obstacleGrid[0].size();
  if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1)  // 必须先判断
    return 0;
  vector<vector<int>> dp(m, vector<int>(n, 0));
  for (int i = 0; i < m && obstacleGrid[i][0] == 0; i++)  // 可以判断条件简写
    dp[i][0] = 1;
  for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++)
    dp[0][j] = 1;
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      if (obstacleGrid[i][j] == 1)
        continue;
      dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
    }
  }
  return dp[m - 1][n - 1];
}

// 空间复杂度简写写法，m。还是先判断赋予首行状态。然后不断向下遍历。遇到障碍物dp=0，首列不处理。其余列叠加前一列结果
int uniquePathsWithObstacles2(vector<vector<int>>& obstacleGrid) {
  int m = obstacleGrid.size();
  int n = obstacleGrid[0].size();
  if (obstacleGrid[0][0] == 1)
    return 0;
  vector<int> dp(n, 0);
  for (int j = 0; j < n && obstacleGrid[0][j] == 0; j++)
    dp[j] = 1;
  for (int i = 1; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (obstacleGrid[i][j] == 1)
        dp[j] = 0;
      else if (j != 0)
        dp[j] += dp[j - 1];
    }
  }
  return dp.back();  // 最后一个元素的写法
}

int main() {
  vector<vector<int>> obstacleGrid1 = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
  vector<vector<int>> obstacleGrid2 = {{0, 1}, {0, 0}};
  vector<vector<int>> obstacleGrid3 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  vector<vector<int>> obstacleGrid4 = {{0}, {1}};
  cout << uniquePathsWithObstacles(obstacleGrid1) << " "
       << uniquePathsWithObstacles(obstacleGrid2) << " "
       << uniquePathsWithObstacles(obstacleGrid3) << " "
       << uniquePathsWithObstacles(obstacleGrid4) << endl;
  cout << uniquePathsWithObstacles1(obstacleGrid1) << " "
       << uniquePathsWithObstacles1(obstacleGrid2) << " "
       << uniquePathsWithObstacles1(obstacleGrid3) << " "
       << uniquePathsWithObstacles1(obstacleGrid4) << endl;
  return 0;
}