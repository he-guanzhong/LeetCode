#include "head.h"
/* 200. 岛屿数量
给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
此外，你可以假设该网格的四条边均被水包围。
示例 1：
  输入：grid = {
    {'1','1','1','1','0'},
    {'1','1','0','1','0'},
    {'1','1','0','0','0'},
    {'0','0','0','0','0'}
  }
  输出：1
示例 2：
  输入：grid = {
    {'1','1','0','0','0'},
    {'1','1','0','0','0'},
    {'0','0','1','0','0'},
    {'0','0','0','1','1'}
  }
  输出：3 */

int dfs(vector<vector<char>>& grid, int x, int y) {
  int area = 1;
  grid[x][y] = '0';
  int dir[] = {1, 0, -1, 0, 1};
  for (int k = 0; k < 4; k++) {
    int nextx = x + dir[k];
    int nexty = y + dir[k + 1];
    if (nextx < 0 || nextx >= grid.size() || nexty < 0 ||
        nexty >= grid[0].size() || grid[nextx][nexty] != '1')
      continue;
    area += dfs(grid, nextx, nexty);
  }
  return area;
}
int numIslands(vector<vector<char>>& grid) {
  int ans = 0, area = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      area = 0;
      if (grid[i][j] == '1')
        area = dfs(grid, i, j);
      if (area)
        ans++;
    }
  }
  return ans;
}

// 深度搜索版，官方推荐写法。使用visited矩阵，记录是否访问过。
// 是否新增岛屿的条件为，该处为陆地‘1’且未访问过。先标记该点访问过，然后进入递归。
// 是否越界检查，可以作为返回条件，或者直接就不入递归
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
void dfs1(vector<vector<char>>& grid,
          vector<vector<bool>>& visited,
          int x,
          int y) {
  for (int i = 0; i < 4; i++) {
    int nextX = x + dir[i][0];
    int nextY = y + dir[i][1];
    if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
        nextY >= grid[0].size())
      continue;
    if (grid[nextX][nextY] == '1' && visited[nextX][nextY] == false) {
      visited[nextX][nextY] = true;
      dfs1(grid, visited, nextX, nextY);
    }
  }
}
int numIslands1(vector<vector<char>>& grid) {
  vector<vector<bool>> visited(grid.size(),
                               vector<bool>(grid[0].size(), false));
  int num = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (visited[i][j] == false && grid[i][j] == '1') {
        visited[i][j] = true;
        num++;
        dfs1(grid, visited, i, j);
      }
    }
  }
  return num;
}

// 深度搜索版。自写法
int dfs3(vector<vector<char>>& grid,
         vector<vector<bool>>& visited,
         int x,
         int y) {
  if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() ||
      grid[x][y] == '0' || visited[x][y] == true)
    return 0;
  int area = 1;
  visited[x][y] = true;
  int directions[] = {0, 1, 0, -1, 0};
  for (int i = 0; i < 4; i++) {
    int new_x = x + directions[i];
    int new_y = y + directions[i + 1];
    area += dfs3(grid, visited, new_x, new_y);
  }
  return area;
}
int numIslands3(vector<vector<char>>& grid) {
  vector<vector<bool>> visited(grid.size(),
                               vector<bool>(grid[0].size(), false));
  int result = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (dfs3(grid, visited, i, j))
        result++;
    }
  }
  return result;
}

int main() {
  vector<vector<char>> grid1 = {{'1', '1', '1', '1', '0'},
                                {'1', '1', '0', '1', '0'},
                                {'1', '1', '0', '0', '0'},
                                {'0', '0', '0', '0', '0'}};
  vector<vector<char>> grid2 = {{'1', '1', '0', '0', '0'},
                                {'1', '1', '0', '0', '0'},
                                {'0', '0', '1', '0', '0'},
                                {'0', '0', '0', '1', '1'}};
  cout << numIslands(grid1) << " " << numIslands(grid2) << endl;
  grid1 = {{'1', '1', '1', '1', '0'},
           {'1', '1', '0', '1', '0'},
           {'1', '1', '0', '0', '0'},
           {'0', '0', '0', '0', '0'}};
  grid2 = {{'1', '1', '0', '0', '0'},
           {'1', '1', '0', '0', '0'},
           {'0', '0', '1', '0', '0'},
           {'0', '0', '0', '1', '1'}};
  cout << numIslands1(grid1) << " " << numIslands1(grid2) << endl;

  return 0;
}