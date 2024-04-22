#include "head.h"
/* 827. 最大人工岛
给你一个大小为 n x n 二进制矩阵 grid 。最多 只能将一格 0 变成 1 。
返回执行此操作后，grid 中最大的岛屿面积是多少？
岛屿 由一组上、下、左、右四个方向相连的 1 形成。
示例 1:
输入: grid = [[1, 0], [0, 1]]
输出: 3
解释: 将一格0变成1，最终连通两个小岛得到面积为 3 的岛屿。
示例 2:
输入: grid = [[1, 1], [1, 0]]
输出: 4
解释: 将一格0变成1，岛屿的面积扩大为 4。
示例 3:
输入: grid = [[1, 1], [1, 1]]
输出: 4
解释: 没有0可以让我们变成1，面积依然为 4。 */

// 一轮遍历，记录岛屿名称及其面积。二轮遍历，对任意'0'海水向四周拓展，如遇到岛屿即加上其面积。
// 注意：全图均为陆地，在两轮遍历之间，作为特殊情况考虑。否则第二轮找不到海水0无输出。第二轮遍历中，需使用uset记录该岛屿是否以加过，否则易重复
int dfs(vector<vector<int>>& grid,
        vector<vector<int>>& flg,
        int x,
        int y,
        int index) {
  int dir[] = {1, 0, -1, 0, 1};
  int area = 1;
  flg[x][y] = index;
  for (int i = 0; i < 4; i++) {
    int nextX = x + dir[i];
    int nextY = y + dir[i + 1];
    if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
        nextY >= grid[0].size() || grid[nextX][nextY] == 0 ||
        flg[nextX][nextY] <= index)
      continue;
    area += dfs(grid, flg, nextX, nextY, index);
  }
  return area;
}
int largestIsland(vector<vector<int>>& grid) {
  vector<int> result;
  int maxVal = 0;
  vector<vector<int>> flg(grid.size(), vector<int>(grid[0].size(), 0));
  int index = 1;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 1 && flg[i][j] == 0) {
        int area = dfs(grid, flg, i, j, index);
        result.push_back(area);
        index++;
      }
    }
  }
  if (!result.empty() && result[0] == grid.size() * grid[0].size())
    maxVal = grid.size() * grid[0].size();
  int dir[] = {1, 0, -1, 0, 1};
  int val = 0;
  unordered_set<int> uset;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 0) {
        val = 1;
        uset.clear();
        for (int k = 0; k < 4; k++) {
          int nextX = i + dir[k];
          int nextY = j + dir[k + 1];
          if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
              nextY >= grid[0].size() || grid[nextX][nextY] == 0 ||
              flg[nextX][nextY] == 0)
            continue;
          if (uset.count(flg[nextX][nextY]) > 0)
            continue;
          uset.insert(flg[nextX][nextY]);
          val += result[flg[nextX][nextY] - 1];
        }
        maxVal = max(val, maxVal);
      }
    }
  }
  return maxVal;
}

// 第一步，遍历所有岛，使用grid[i][j]=2\3\4..标记每个岛，计算每个岛的面积，存于unordered_map中
// 第二步，对剩余每个gird[i][j]=0的海水结点，四周搜索是否由岛，如果有则加上岛屿面积。最终输出最大值
// 注意：1.额外需要判断是否全为岛的变量；unordered_set记录每个0海水，周围的岛屿面积加过与否。故每一个0海水初始必须clear
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
int cnt1 = 0;
void dfs1(vector<vector<int>>& grid,
          vector<vector<bool>>& visited,
          int x,
          int y,
          int mark) {
  if (grid[x][y] != 1 || visited[x][y] == true)  // visited可删除
    return;
  visited[x][y] = true;
  grid[x][y] = mark;
  cnt1++;
  for (int i = 0; i < 4; i++) {
    int nextX = x + dir[i][0];
    int nextY = y + dir[i][1];
    if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
        nextY >= grid[0].size())
      continue;
    dfs1(grid, visited, nextX, nextY, mark);
  }
}
int largestIsland1(vector<vector<int>>& grid) {
  int m = grid.size(), n = grid[0].size();
  vector<vector<bool>> visited(m, vector<bool>(n, false));  // 也可以不用visited
  unordered_map<int, int> gridNum;
  bool isAllGrid = true;
  int mark = 2;  // 原岛屿数值为1，标记从2 开始
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 0)
        isAllGrid = false;
      // 此处if (grid[i][j] == 1 && !visited[i][j])可加可不加
      cnt1 = 0;
      dfs1(grid, visited, i, j, mark);
      gridNum[mark] = cnt1;
      mark++;
    }
  }
  if (isAllGrid)
    return m * n;
  int result = 0;
  unordered_set<int> visitedGrid;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 0) {
        cnt1 = 1;
        visitedGrid.clear();  // 每次使用时必清空!
        for (int k = 0; k < 4; k++) {
          int nextX = i + dir[k][0];
          int nextY = j + dir[k][1];
          if (nextX < 0 || nextX >= grid.size() || nextY < 0 ||
              nextY >= grid[0].size())
            continue;
          if (visitedGrid.count(grid[nextX][nextY]) > 0)  // 岛屿出现过
            continue;
          cnt1 += gridNum[grid[nextX][nextY]];
          visitedGrid.insert(grid[nextX][nextY]);
        }
        result = max(result, cnt1);
      }
    }
  }
  return result;
}

int main() {
  vector<vector<int>> grid1 = {{1, 0}, {0, 1}};
  vector<vector<int>> grid2 = {{1, 1}, {0, 1}};
  vector<vector<int>> grid3 = {{1, 1}, {1, 1}};
  cout << largestIsland(grid1) << " " << largestIsland(grid2) << " "
       << largestIsland(grid3) << endl;
  cout << largestIsland1(grid1) << " " << largestIsland1(grid2) << " "
       << largestIsland1(grid3) << endl;
  return 0;
}