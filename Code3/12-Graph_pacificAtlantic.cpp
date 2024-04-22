#include "head.h"
/* 417. 太平洋大西洋水流问题
有一个 m × n 的矩形岛屿，与 太平洋 和 大西洋 相邻。 “太平洋”
处于大陆的左边界和上边界，而 “大西洋” 处于大陆的右边界和下边界。
这个岛被分割成一个由若干方形单元格组成的网格。给定一个 m x n 的整数矩阵 heights
， heights[r][c] 表示坐标 (r, c) 上单元格 高于海平面的高度 。
岛上雨水较多，如果相邻单元格的高度 小于或等于
当前单元格的高度，雨水可以直接向北、南、东、西流向相邻单元格。水可以从海洋附近的任何单元格流入海洋。
返回网格坐标 result 的 2D 列表 ，其中 result[i] = [ri, ci] 表示雨水从单元格 (ri,
ci) 流动 既可流向太平洋也可流向大西洋 。
示例 1：
输入: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
输出: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
示例 2：
输入: heights = [[2,1],[1,2]]
输出: [[0,0],[0,1],[1,0],[1,1]]
 */

// 遍历左上边界太平洋，右下边界大西洋。标记逆流能走到的所有结点。最后全图遍历，两洋同时能到达的即压入结果。时间和空间复杂度均为2*m*n
void dfs(vector<vector<int>>& heights,
         vector<vector<int>>& ocean,
         int x,
         int y) {
  ocean[x][y] = 1;
  int dir[] = {1, 0, -1, 0, 1};
  for (int i = 0; i < 4; i++) {
    int nextX = x + dir[i];
    int nextY = y + dir[i + 1];
    if (nextX < 0 || nextX >= heights.size() || nextY < 0 ||
        nextY >= heights[0].size() || ocean[nextX][nextY] == 1)
      continue;
    if (heights[nextX][nextY] >= heights[x][y]) {
      dfs(heights, ocean, nextX, nextY);
    }
  }
}
vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
  int m = heights.size(), n = heights[0].size();
  vector<vector<int>> result;
  vector<vector<int>> pac(m, vector<int>(n, 0));
  vector<vector<int>> alt = pac;
  for (int i = 0; i < m; i++) {
    dfs(heights, pac, i, 0);      // 左边界太平洋
    dfs(heights, alt, i, n - 1);  // 右边界大西洋
  }
  for (int j = 0; j < n; j++) {
    dfs(heights, pac, 0, j);      // 上边界太平洋
    dfs(heights, alt, m - 1, j);  // 下边界大西洋
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (pac[i][j] == 1 && alt[i][j] == 1)
        result.push_back({i, j});
    }
  }
  return result;
}

// 不能对每一个结点，进行横向和纵向搜索，如果同时触碰到了海边为为真，时间复杂度O(n^2*m^2)
// 反向思考，从四条海边向内陆搜索，使用两个矩阵保存两个大洋能到达的结果，如果内陆某个点同时来自大西洋和太平洋，即为所求结点。
// dfs中的visited为形参，已访问矩阵，实参为大西洋和太平洋矩阵。超出界外跳过。由于从低向高搜索，碰到更低洼的地即跳过。
// 时间复杂度不是(n+m)*m*n，注意到结点，对于大西洋和太平洋两个矩阵访问一次，之后不会再次访问，故时间复杂度2*m*n，空间复杂度2*m*n
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
void dfs1(vector<vector<int>>& heights,
          vector<vector<bool>>& visited,
          int x,
          int y) {
  if (visited[x][y] ==
      true)  // 可以在递归内部返回，并设置已经访问，或在递归外设置
    return;
  visited[x][y] = true;
  for (int i = 0; i < 4; i++) {
    int nextX = x + dir[i][0];
    int nextY = y + dir[i][1];
    if (nextX < 0 || nextX >= heights.size() || nextY < 0 ||
        nextY >= heights[0].size())
      continue;
    if (heights[nextX][nextY] < heights[x][y])
      continue;
    dfs1(heights, visited, nextX, nextY);
  }
}

vector<vector<int>> pacificAtlantic1(vector<vector<int>>& heights) {
  vector<vector<int>> result;
  int m = heights.size(), n = heights[0].size();
  vector<vector<bool>> pacific(m, vector<bool>(n, false));
  vector<vector<bool>> atlantic(m, vector<bool>(n, false));
  for (int j = 0; j < n; j++) {
    dfs1(heights, pacific, 0, j);       // 上边界太平洋
    dfs1(heights, atlantic, m - 1, j);  // 下边界大西洋
  }
  for (int i = 0; i < m; i++) {
    dfs1(heights, pacific, i, 0);       // 左边界太平洋
    dfs1(heights, atlantic, i, n - 1);  // 有边界大西洋
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (pacific[i][j] == true && atlantic[i][j] == true)
        result.push_back({i, j});
    }
  }
  return result;
}

int main() {
  vector<vector<int>> height1 = {{1, 2, 2, 3, 5},
                                 {3, 2, 3, 4, 4},
                                 {2, 4, 5, 3, 1},
                                 {6, 7, 1, 4, 5},
                                 {5, 1, 1, 2, 4}};
  vector<vector<int>> height2 = {{2, 1}, {1, 2}};
  vector<vector<int>> height3 = {{0}};

  printMat(pacificAtlantic(height1));
  printMat(pacificAtlantic(height2));
  printMat(pacificAtlantic(height3));
  printMat(pacificAtlantic1(height1));
  printMat(pacificAtlantic1(height2));
  printMat(pacificAtlantic1(height3));
  return 0;
}