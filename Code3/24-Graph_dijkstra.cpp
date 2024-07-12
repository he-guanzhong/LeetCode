#include "head.h"
/*  dijkstra（朴素版）精讲
题目描述：
  小明是一位科学家，他需要参加一场重要的国际科学大会，以展示自己的最新研究成果。
  小明的起点是第一个车站，终点是最后一个车站。然而，途中的各个车站之间的道路状况、交通拥堵程度以及可能的自然因素（如天气变化）等不同，
  这些因素都会影响每条路径的通行时间。
  小明希望能选择一条花费时间最少的路线，以确保他能够尽快到达目的地。
输入描述：
  第一行包含两个正整数，第一个正整数 N 表示一共有 N 个公共汽车站，第二个正整数
  M表示有 M 条公路。 接下来为 M 行，每行包括三个整数，S、E 和 V，代表了从 S
  车站可以单向直达 E 车站，并且需要花费 V 单位的时间。
输出描述：
  输出一个整数，代表小明从起点到终点所花费的最小时间。
输入示例：
  7 9
  1 2 1
  1 3 4
  2 3 2
  2 4 5
  3 4 2
  4 5 3
  2 6 4
  5 7 4
  6 7 9
输出示例：
  12。*/

int dijkstra(vector<vector<int>>& grid, int n) {
  vector<int> minDist(n + 1, INT_MAX);  // 每个点距离源点代价
  vector<bool> visited(n + 1, false);   // 每个点是否访问过
  minDist[1] = 0;                       // 起始点从1开始
  for (int i = 1; i <= n; i++) {
    // 1.寻找未访问的，且代价最小的，作为处理结点
    int cur = 1;  // 这里不能初始化为-1
    int minVal = INT_MAX;
    for (int j = 1; j <= n; j++) {
      if (!visited[j] && minDist[j] < minVal) {
        minVal = minDist[j];
        cur = j;
      }
    }
    // 2.将该结点标记访问
    visited[cur] = true;
    // 3.更新非访问的，剩余的可连接的结点，更新距离源点代价
    for (int j = 1; j <= n; j++) {
      if (!visited[j] && grid[cur][j] != INT_MAX &&
          minDist[cur] + grid[cur][j] < minDist[j]) {
        minDist[j] = minDist[cur] + grid[cur][j];
      }
    }
  }
  // 最后一点代价无穷大，说明无法到达
  return minDist[n] == INT_MAX ? -1 : minDist[n];
}
int main() {
  int N = 7, M = 9;
  vector<vector<int>> grid(N + 1, vector<int>(N + 1, INT_MAX));
  grid[1][2] = 1, grid[1][3] = 4, grid[2][3] = 2, grid[2][4] = 5,
  grid[3][4] = 2, grid[4][5] = 3, grid[2][6] = 4, grid[5][7] = 4,
  grid[6][7] = 9;
  cout << dijkstra(grid, N) << endl;
  return 0;
}