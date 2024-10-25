#include "head.h"
/* 463. 岛屿的周长
给定一个 row x col 的二维网格地图 grid ，其中：grid[i][j] = 1 表示陆地，
grid[i][j] = 0 表示水域。
网格中的格子 水平和垂直
方向相连（对角线方向不相连）。整个网格被水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格子相连组成的岛屿）。
岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格子是边长为 1
的正方形。网格为长方形，且宽度和高度均不超过 100 。计算这个岛屿的周长。
示例 1：
  输入：grid = [[0,1,0,0],
                [1,1,1,0],
                [0,1,0,0],
                [1,1,0,0]]
  输出：16
  解释：它的周长是上面图片中的 16 个黄色的边
示例 2：
  输入：grid = [[1]]
  输出：4
示例 3：
  输入：grid = [[1,0]]
  输出：4 */

int islandPerimeter(vector<vector<int>>& grid) {
  int dir[] = {1, 0, -1, 0, 1};
  int cnt = 0, edge = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 0)
        continue;
      cnt++;
      grid[i][j] = 0;
      for (int k = 0; k < 4; k++) {
        int nextx = i + dir[k];
        int nexty = j + dir[k + 1];
        if (nextx < 0 || nextx >= grid.size() || nexty < 0 ||
            nexty >= grid[0].size() || grid[nextx][nexty] == 0)
          continue;
        edge++;
      }
    }
  }
  return 4 * cnt - 2 * edge;
}

// 方法一，不必求岛屿数量，边定义为1对0，或1对边界的跨越。故对每一个岛屿点四周搜索，遇到海水或者边界，周长直接加一。
// 方法二，边长=岛屿数量*4-相邻岛屿对数*2，遍历方向是左上到右下，故每节点的对数计算，只能考虑其左、上两个方向，而且要分别记对
// 方法一，不适用DFS和BFS，直接对每一个岛结点，四周如果碰到边界，或者海水，就加一
int islandPerimeter1(vector<vector<int>>& grid) {
  int m = grid.size(), n = grid[0].size();
  int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
  int result = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 1) {
        for (int k = 0; k < 4; k++) {
          int x = i + dir[k][0];
          int y = j + dir[k][1];
          if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 0)
            result++;
        }
      }
    }
  }
  return result;
}

// 方法二，边数=岛屿数量*4-相邻岛屿对数*2。计算相邻岛屿对数时，只考虑左、上两个方向。避免重复计算
int islandPerimeter2(vector<vector<int>>& grid) {
  int m = grid.size(), n = grid[0].size();
  int result = 0;
  int cover = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 1) {
        result++;
        if (i - 1 >= 0 && grid[i - 1][j] == 1)
          cover++;
        if (j - 1 >= 0 && grid[i][j - 1] == 1)
          cover++;
      }
    }
  }
  return result * 4 - cover * 2;
}

int main() {
  vector<vector<int>> grid1 = {
      {0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}};
  vector<vector<int>> grid2 = {{1}};
  vector<vector<int>> grid3 = {{1, 0}};
  vector<vector<int>> grid4 = {{1, 1}, {1, 1}};
  cout << islandPerimeter(grid1) << " " << islandPerimeter(grid2) << " "
       << islandPerimeter(grid3) << " " << islandPerimeter(grid4) << endl;
  grid1 = {{0, 1, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}};
  grid2 = {{1}};
  grid3 = {{1, 0}};
  grid4 = {{1, 1}, {1, 1}};
  cout << islandPerimeter1(grid1) << " " << islandPerimeter1(grid2) << " "
       << islandPerimeter1(grid3) << " " << islandPerimeter1(grid4) << endl;
  return 0;
}