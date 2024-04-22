#include "head.h"
/* 1020. 飞地的数量
给你一个大小为 m x n 的二进制矩阵 grid ，其中 0 表示一个海洋单元格、1
表示一个陆地单元格。
一次 移动 是指从一个陆地单元格走到另一个相邻（上、下、左、右）的陆地单元格或跨过
grid 的边界。
返回网格中 无法 在任意次数的移动中离开网格边界的陆地单元格的数量。
示例 1：
输入：grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
输出：3
解释：有三个 1 被 0 包围。一个 1 没有被包围，因为它在边界上。
示例 2：
输入：grid = [[0,1,1,0],[0,0,1,0],[0,0,1,0],[0,0,0,0]]
输出：0
解释：所有 1 都在边界上或可以到达边界。
 */

// DFS，遍历四周围边界，且岛屿‘1’的节点，将其相邻变为水‘0’。入dfs之后，再标记0。剩下岛屿即为飞地数量
void bfs(vector<vector<int>>& grid, int x, int y) {
  queue<pair<int, int>> que;
  que.push({x, y});
  grid[x][y] = 0;
  int dir[] = {1, 0, -1, 0, 1};
  while (!que.empty()) {
    int curX = que.front().first;
    int curY = que.front().second;
    que.pop();
    for (int i = 0; i < 4; i++) {
      int nextX = curX + dir[i];
      int nextY = curY + dir[i + 1];
      if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
          nextY >= grid[0].size() || grid[nextX][nextY] == 0)
        continue;
      que.push({nextX, nextY});
      grid[nextX][nextY] = 0;
    }
  }
}
int numEnclaves(vector<vector<int>>& grid) {
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 1 &&
          (i == 0 || i == grid.size() - 1 || j == 0 || j == grid[0].size() - 1))
        bfs(grid, i, j);
    }
  }
  int cnt = 0;
  for (int i = 1; i < grid.size() - 1; i++) {
    for (int j = 1; j < grid[0].size() - 1; j++) {
      if (grid[i][j] == 1)
        cnt++;
    }
  }
  return cnt;
}

// 先从上下左右四个边界遍历，将岛屿全部变为海水，剩下的岛屿，即为飞地数量
// 只要是图内的岛屿。可以先压入dfs，再修改地图，增加计数。
int direction[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
int cnt1 = 0;
void dfs2(vector<vector<int>>& grid, int x, int y) {
  grid[x][y] = 0;
  cnt1++;
  for (int i = 0; i < 4; i++) {
    int nextX = x + direction[i][0];
    int nextY = y + direction[i][1];
    if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
        nextY >= grid[0].size())
      continue;
    if (grid[nextX][nextY] == 0)
      continue;
    dfs2(grid, nextX, nextY);
  }
}
int numEnclaves2(vector<vector<int>>& grid) {
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 1 && (i == 0 || i == grid.size() - 1 || j == 0 ||
                              j == grid[0].size() - 1)) {
        dfs2(grid, i, j);
      }
    }
  }
  cnt1 = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 1)
        dfs2(grid, i, j);
    }
  }
  return cnt1;
}

// 广度优先搜索解法。注意压入的同时，就要置为海水
void bfs1(vector<vector<int>>& grid, int x, int y) {
  queue<pair<int, int>> que;
  que.push({x, y});
  grid[x][y] = 0;
  cnt1++;  // 这里不可以写cnt = 1，因为内部不连通者可以有很多岛屿
  while (!que.empty()) {
    int curX = que.front().first;
    int curY = que.front().second;
    que.pop();
    for (int i = 0; i < 4; i++) {
      int nextX = curX + direction[i][0];
      int nextY = curY + direction[i][1];
      if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
          nextY >= grid[0].size())
        continue;
      if (grid[nextX][nextY] == 0)
        continue;
      que.push({nextX, nextY});
      grid[nextX][nextY] = 0;
      cnt1++;
    }
  }
}
int numEnclaves1(vector<vector<int>>& grid) {
  int m = grid.size(), n = grid[0].size();
  for (int i = 0; i < m; i++) {
    if (grid[i][0] == 1)
      bfs1(grid, i, 0);
    if (grid[i][n - 1] == 1)
      bfs1(grid, i, n - 1);
  }
  for (int j = 0; j < n; j++) {
    if (grid[0][j] == 1)
      bfs1(grid, 0, j);
    if (grid[m - 1][j] == 1)
      bfs1(grid, m - 1, j);
  }
  cnt1 = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 1)
        bfs1(grid, i, j);
    }
  }
  return cnt1;
}
int main() {
  vector<vector<int>> grid1 = {
      {0, 0, 0, 0}, {1, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}};
  vector<vector<int>> grid2 = {
      {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}};
  vector<vector<int>> grid3 = grid1;
  vector<vector<int>> grid4 = grid2;

  cout << numEnclaves(grid1) << " " << numEnclaves(grid2) << endl;
  cout << numEnclaves1(grid3) << " " << numEnclaves1(grid4) << endl;

  return 0;
}