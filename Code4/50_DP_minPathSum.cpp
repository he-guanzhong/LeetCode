#include "head.h"
/* 64. 最小路径和
给定一个包含非负整数的 m x n 网格 grid
，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。
说明：每次只能向下或者向右移动一步。
示例 1：
  输入：grid = [[1,3,1],[1,5,1],[4,2,1]]
  输出：7
  解释：因为路径 1→3→1→1→1 的总和最小。
示例 2：
  输入：grid = [[1,2,3],[4,5,6]]
  输出：12 */

int minPathSum(vector<vector<int>>& grid) {
  int m = grid.size(), n = grid[0].size();
  vector<int> dp(n + 1, INT_MAX);
  dp[1] = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 1; j <= n; j++) {
      dp[j] = min(dp[j], dp[j - 1]) + grid[i][j - 1];
    }
  }
  return dp[n];
}

// 一维数组动态规划，以节省空间。dp[j]表示下标i行位置的路径总和，第一行和第一列要特殊处理。因为dp[i][j]取决于dp[i-1][j]和dp[i][j-1]即上和右两个方向
int minPathSum1(vector<vector<int>>& grid) {
  vector<int> dp(grid[0].size(), 0);
  dp[0] = grid[0][0];
  for (int j = 1; j < grid[0].size(); j++)
    dp[j] = dp[j - 1] + grid[0][j];
  for (int i = 1; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (j == 0)
        dp[j] += grid[i][0];
      else
        dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
    }
  }
  return dp[grid[0].size() - 1];
}

// 额外添加第0行，如此可不做特殊处理。注意一、虚拟首行元素必须初始化为INT_MAX，否则赋值dp[j]时，取上、左二者最小值时，取上为0，就没有计入真首行元素权重
// 注意二、虚拟首行首元素dp[1]=0，如此虚拟首列全部为INT_MAX，才能在计入真首列dp[1]时，为真实值
int minPathSum2(vector<vector<int>>& grid) {
  int m = grid.size(), n = grid[0].size();
  vector<int> dp(n + 1, INT_MAX);
  dp[1] = 0;  // 核心
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      dp[j] = min(dp[j], dp[j - 1]) + grid[i - 1][j - 1];
    }
  }
  return dp[n];
}
int main() {
  vector<vector<int>> grid1 = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
  vector<vector<int>> grid2 = {{1, 2, 3}, {4, 5, 6}};
  cout << minPathSum(grid1) << "       " << minPathSum(grid2) << endl;
  cout << minPathSum1(grid1) << "       " << minPathSum1(grid2) << endl;

  return 0;
}