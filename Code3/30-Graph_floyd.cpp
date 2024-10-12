#include "head.h"
/*   Floyd 算法精讲
题目描述：
  小明喜欢去公园散步，公园内布置了许多的景点，相互之间通过小路连接，小明希望在观看景点的同时，能够节省体力，走最短的路径。
  给定一个公园景点图，图中有 N 个景点（编号为 1 到 N），以及 M
  条双向道路连接着这些景点。每条道路上行走的距离都是已知的。
  小明有 Q 个观景计划，每个计划都有一个起点 start 和一个终点 end，表示他想从景点
  start前往景点end。由于小明希望节省体力，他想知道每个观景计划中从起点到终点的最短路径长度。
  请你帮助小明计算出每个观景计划的最短路径长度。
输入描述：
  第一行包含两个整数 N, M, 分别表示景点的数量和道路的数量。
  接下来的 M 行，每行包含三个整数 u, v, w，表示景点 u 和景点 v 之间有一条长度为w
  的双向道路。接下里的一行包含一个整数 Q，表示观景计划的数量。 接下来的 Q
  行，每行包含两个整数 start, end，表示一个观景计划的起点和终点。
输出描述：
  对于每个观景计划，输出一行表示从起点到终点的最短路径长度。如果两个景点之间不存在路径，则输出-1。
输入示例：
7 3
2 3 4
3 6 6
4 7 8
2
2 3
3 4
输出示例：
  4 -1
提示信息
  从 1 到 2 的路径长度为 4，2 到 3 之间并没有道路。1 <= N, M, Q <= 1000. */

int floyd(vector<vector<int>>& grid, int n, int src, int dst) {
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        grid[i][j] = min(grid[i][j], grid[i][k] + grid[k][j]);
      }
    }
  }
  return grid[src][dst] == 10005 ? -1 : grid[src][dst];
}

// 三维数组dp[i][j][k]记录从i到j，经过[1,k]的代价。初始化所有代价最大（以10005为例）。有双向路的，不经过任何点k==0，grid矩阵初始化为确定值。
// 遍历主顺序是是否必须以此经过[1,k]点，故其在最外。递推公式，grid[i][j]代价，分必然经过[1,k]和不经过[1,k]两种情况最小值
int floyd1(vector<vector<vector<int>>>& grid, int n, int src, int dst) {
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        grid[i][j][k] =
            min(grid[i][j][k - 1], grid[i][k][k - 1] + grid[k][j][k - 1]);
      }
    }
  }
  return grid[src][dst][n] == 10005 ? -1 : grid[src][dst][n];
}

// 节省空间做法，k只与k-1帧有关，甚至可以在k本帧内更新，对求最小值也无影响
int floyd2(vector<vector<int>>& grid, int n, int src, int dst) {
  for (int k = 1; k <= n; k++) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        grid[i][j] = min(grid[i][j], grid[i][k] + grid[k][j]);
      }
    }
  }
  return grid[src][dst] == 10005 ? -1 : grid[src][dst];
}

int main() {
  int N = 7, M = 3;
  vector<vector<vector<int>>> grid1(
      N + 1, vector<vector<int>>(N + 1, vector<int>(N + 1, 10005)));
  grid1[2][3][0] = grid1[3][2][0] = 4;
  grid1[3][6][0] = grid1[6][3][0] = 6;
  grid1[4][7][0] = grid1[7][4][0] = 8;
  cout << floyd1(grid1, N, 2, 3) << ", " << floyd1(grid1, N, 3, 4) << endl;

  vector<vector<int>> grid2(N + 1, vector<int>(N + 1, 10005));
  grid2[2][3] = grid2[3][2] = 4;
  grid2[3][6] = grid2[6][3] = 6;
  grid2[4][7] = grid2[7][4] = 8;
  cout << floyd(grid2, N, 2, 3) << ", " << floyd(grid2, N, 3, 4) << endl;
  cout << floyd2(grid2, N, 2, 3) << ", " << floyd2(grid2, N, 3, 4) << endl;

  return 0;
}