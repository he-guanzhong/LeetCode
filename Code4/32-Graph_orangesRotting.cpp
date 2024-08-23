#include "head.h"
/* 994. 腐烂的橘子
在给定的 m x n 网格 grid 中，每个单元格可以有以下三个值之一：
    值 0 代表空单元格；
    值 1 代表新鲜橘子；
    值 2 代表腐烂的橘子。
每分钟，腐烂的橘子 周围 4 个方向上相邻 的新鲜橘子都会腐烂。
返回 直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 -1 。
示例 1：
  输入：grid =
    [[2,1,1],
    [1,1,0],
    [0,1,1]]
  输出：4
示例 2：
  输入：grid = [[2,1,1],[0,1,1],[1,0,1]]
  输出：-1
  解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4
    个方向上。
示例 3：
  输入：grid = [[0,2]]
  输出：0
  解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。*/

int orangesRotting(vector<vector<int>>& grid) {
  queue<pair<int, int>> que;
  int sum = 0;
  int m = grid.size(), n = grid[0].size();
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 1)
        sum++;
      if (grid[i][j] == 2)
        que.push({i, j});
    }
  }
  if (sum == 0)
    return 0;
  int ans = -1;
  int dir[] = {1, 0, -1, 0, 1};
  while (que.size()) {
    int size = que.size();
    ans++;
    while (size--) {
      int x = que.front().first;
      int y = que.front().second;
      que.pop();
      for (int k = 0; k < 4; k++) {
        int nextx = x + dir[k];
        int nexty = y + dir[k + 1];
        if (nextx < 0 || nextx >= m || nexty < 0 || nexty >= n ||
            grid[nextx][nexty] != 1)
          continue;
        grid[nextx][nexty] = 2;
        sum--;
        que.push({nextx, nexty});
      }
    }
  }
  return sum == 0 ? ans : -1;
}

// 多起点层序遍历，-1时刻原始腐烂橘子。一次遍历，压入0时刻为各个真实腐烂橘子，并统计新鲜橘子数量。注意若无腐烂橘子，特殊情况起始时刻ans=0。
// 对每一层遍历，步数+1。四方拓展。如果遇到新鲜橘子，压入队列+橘子腐烂+新鲜数量减一。最终返回若还有新鲜则-1，无新鲜则返回步数ans
int orangesRotting1(vector<vector<int>>& grid) {
  int m = grid.size(), n = grid[0].size();
  int dir[] = {1, 0, -1, 0, 1};
  queue<pair<int, int>> que;
  int countNew = 0, ans = -1;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 2)
        que.push({i, j});
      if (grid[i][j] == 1)
        countNew++;
    }
  }
  if (que.empty())  // 没新鲜橘子，应该是countNew==0
    ans = 0;
  while (!que.empty()) {
    ans++;
    int size = que.size();
    while (size--) {
      int curX = que.front().first;
      int curY = que.front().second;
      que.pop();
      for (int i = 0; i < 4; i++) {
        int newX = curX + dir[i];
        int newY = curY + dir[i + 1];
        if (newX < 0 || newX >= m || newY < 0 || newY >= n ||
            grid[newX][newY] == 0 || grid[newX][newY] == 2)
          continue;
        que.push({newX, newY});
        grid[newX][newY] = 2;
        countNew--;
      }
    }
  }
  return countNew > 0 ? -1 : ans;
}

int main() {
  vector<vector<int>> grid1 = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
  vector<vector<int>> grid2 = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
  vector<vector<int>> grid3 = {{0, 2}};
  vector<vector<int>> grid4 = {{0}};

  cout << orangesRotting(grid1) << " " << orangesRotting(grid2) << " "
       << orangesRotting(grid3) << " " << orangesRotting(grid4) << endl;
  grid1 = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};
  grid2 = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};
  grid3 = {{0, 2}};
  grid4 = {{0}};
  cout << orangesRotting1(grid1) << " " << orangesRotting1(grid2) << " "
       << orangesRotting1(grid3) << " " << orangesRotting1(grid4) << endl;
  return 0;
}