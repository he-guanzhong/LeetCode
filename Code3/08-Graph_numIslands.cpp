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

// BFS核心在设置visited数组，二维遍历，先找到一个未访问过且‘1’岛屿，然后不断拓展求得面积。发现未访问的‘1’的次数就是岛屿数量。
// 队列压入结点时，必须同步visited置为true。一定是先标记再压入。不能弹出的时候再标记，否则会重复
int bfs(vector<vector<char>>& grid,
        vector<vector<bool>>& visited,
        int i,
        int j) {
  queue<pair<int, int>> que;
  que.push({i, j});
  visited[i][j] = true;
  int dir[] = {1, 0, -1, 0, 1};
  int area = 1;
  while (!que.empty()) {
    int curX = que.front().first;
    int curY = que.front().second;
    que.pop();
    for (int i = 0; i < 4; i++) {
      int nextX = curX + dir[i];
      int nextY = curY + dir[i + 1];
      if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
          nextY >= grid[0].size() || grid[nextX][nextY] == '0' ||
          visited[nextX][nextY] == true)
        continue;
      visited[nextX][nextY] = true;
      que.push({nextX, nextY});
      area++;
    }
  }
  return area;
}
int numIslands(vector<vector<char>>& grid) {
  vector<vector<bool>> visited(grid.size(),
                               vector<bool>(grid[0].size(), false));
  int cnt = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == '1' && visited[i][j] == false) {
        bfs(grid, visited, i, j);
        cnt++;
      }
    }
  }
  return cnt;
}

// 官方推荐解法。一定要先标记，在压入队列，不能取出元素的时候再标记。
// bfs单独函数。岛屿成立的标致为，某点时陆地‘1’且未访问过。先标记其已经访问，然后将与之串联的全部visited
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
void bfs1(vector<vector<char>>& grid,
          vector<vector<bool>>& visited,
          int x,
          int y) {
  queue<pair<int, int>> que;
  que.push({x, y});
  visited[x][y] = true;
  while (!que.empty()) {
    int curX = que.front().first;
    int curY = que.front().second;
    que.pop();
    for (int i = 0; i < 4; i++) {
      int nextX = curX + dir[i][0];
      int nextY = curY + dir[i][1];
      if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
          nextY >= grid[0].size())
        continue;
      if (grid[nextX][nextY] == '1' && visited[nextX][nextY] == false) {
        visited[nextX][nextY] = true;
        que.push({nextX, nextY});
      }
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
        num++;
        bfs1(grid, visited, i, j);
      }
    }
  }
  return num;
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
  cout << numIslands1(grid1) << " " << numIslands1(grid2) << endl;

  return 0;
}