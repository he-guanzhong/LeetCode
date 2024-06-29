#include "head.h"
/* 695. 岛屿的最大面积
给你一个大小为 m x n 的二进制矩阵 grid 。
岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求两个 1 必须在
水平或者竖直的四个方向上 相邻。你可以假设 grid 的四个边缘都被
0（代表水）包围着。
岛屿的面积是岛上值为 1 的单元格的数目。
计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。
示例 1：
输入：grid =
{{0,0,1,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,1,1,0,1,0,0,0,0,0,0,0,0},{0,1,0,0,1,1,0,0,1,0,1,0,0},{0,1,0,0,1,1,0,0,1,1,1,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0},{0,0,0,0,0,0,0,1,1,1,0,0,0},{0,0,0,0,0,0,0,1,1,0,0,0,0}}
输出：6
解释：答案不应该是 11 ，因为岛屿只能包含水平或垂直这四个方向上的 1 。
示例 2：
输入：grid = {{0,0,0,0,0,0,0,0}}
输出：0
 */

// BFS注意，一、压结点和标识visited同步。二、四方拓展节点，要以curX,curY为基准，而不是x,y
// DFS注意。可以主函数标记visited，dfs中以返回值为计算面积。二、dfs外部设置退出条件，通过后即标记，for循环计算面积
int dfs(vector<vector<int>>& grid,
        vector<vector<bool>>& visited,
        int x,
        int y) {
  int dir[] = {0, 1, 0, -1, 0};
  int surface = 1;
  for (int i = 0; i < 4; i++) {
    int nextX = x + dir[i];
    int nextY = y + dir[i + 1];
    if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
        nextY >= grid[0].size() || visited[nextX][nextY] == true ||
        grid[nextX][nextY] == 0)
      continue;
    visited[nextX][nextY] = true;
    surface += dfs(grid, visited, nextX, nextY);
  }
  return surface;
}
int maxAreaOfIsland(vector<vector<int>>& grid) {
  vector<vector<bool>> visited(grid.size(),
                               vector<bool>(grid[0].size(), false));
  int maxArea = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 1 && visited[i][j] == false) {
        visited[i][j] = true;
        int m = dfs(grid, visited, i, j);
        maxArea = max(maxArea, m);
      }
    }
  }
  return maxArea;
}

// 广度优先搜索。注意，一旦满足条件，要立刻将计数置为1，本结点已访问，并使用bfs进行拓展cnt
// bfs函数内部，也四个新方向结点，一旦满足条件，先修改visited，然后cnt++，最后再压入
int dir1[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
int cnt;
void bfs1(vector<vector<int>>& grid,
          vector<vector<bool>>& visited,
          int x,
          int y) {
  queue<pair<int, int>> que;
  que.push({x, y});
  while (!que.empty()) {
    int curX = que.front().first;
    int curY = que.front().second;
    que.pop();
    for (int i = 0; i < 4; i++) {
      int nextX = curX + dir1[i][0];
      int nextY = curY + dir1[i][1];
      if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
          nextY >= grid[0].size())
        continue;
      if (grid[nextX][nextY] == 1 && visited[nextX][nextY] == false) {
        cnt++;
        visited[nextX][nextY] = true;
        que.push({nextX, nextY});
      }
    }
  }
}
int maxAreaOfIsland1(vector<vector<int>>& grid) {
  vector<vector<bool>> visited(grid.size(),
                               vector<bool>(grid[0].size(), false));
  int result = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (visited[i][j] == false && grid[i][j] == 1) {
        visited[i][j] = true;
        cnt = 1;
        bfs1(grid, visited, i, j);
        result = max(result, cnt);
      }
    }
  }
  return result;
}

// 注意不能使用count作为变量名，否则与系统内部变量名重复。
void dfs2(vector<vector<int>>& grid,
          vector<vector<bool>>& visited,
          int x,
          int y) {
  for (int i = 0; i < 4; i++) {
    int nextX = x + dir1[i][0];
    int nextY = y + dir1[i][1];
    if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
        nextY >= grid[0].size())
      continue;
    if (grid[nextX][nextY] == 1 && visited[nextX][nextY] == false) {
      cnt++;
      visited[nextX][nextY] = true;
      dfs2(grid, visited, nextX, nextY);
    }
  }
}
int maxAreaOfIsland2(vector<vector<int>>& grid) {
  vector<vector<bool>> visited(grid.size(),
                               vector<bool>(grid[0].size(), false));
  int result = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (visited[i][j] == false && grid[i][j] == 1) {
        visited[i][j] = true;
        cnt = 1;
        dfs2(grid, visited, i, j);
        result = max(result, cnt);
      }
    }
  }
  return result;
}

// 自有写法，使用返回值作为岛屿的面积
int dfs3(vector<vector<int>>& grid,
         vector<vector<bool>>& visited,
         int x,
         int y) {
  int area = 1;
  for (int i = 0; i < 4; i++) {
    int nextX = x + dir1[i][0];
    int nextY = y + dir1[i][1];
    if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
        nextY >= grid[0].size())
      continue;
    if (grid[nextX][nextY] == 1 && visited[nextX][nextY] == false) {
      visited[nextX][nextY] = true;
      area += dfs3(grid, visited, nextX, nextY);
    }
  }
  return area;
}
int maxAreaOfIsland3(vector<vector<int>>& grid) {
  vector<vector<bool>> visited(grid.size(),
                               vector<bool>(grid[0].size(), false));
  int result = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (visited[i][j] == false && grid[i][j] == 1) {
        visited[i][j] = true;
        int area = dfs3(grid, visited, i, j);
        result = max(result, area);
      }
    }
  }
  return result;
}

int main() {
  vector<vector<int>> grid1 = {{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                               {0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                               {0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0},
                               {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
                               {0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}};
  vector<vector<int>> grid2 = {{0, 0, 0, 0, 0, 0, 0, 0}};
  cout << maxAreaOfIsland(grid1) << " " << maxAreaOfIsland(grid2) << endl;
  cout << maxAreaOfIsland1(grid1) << " " << maxAreaOfIsland1(grid2) << endl;

  return 0;
}