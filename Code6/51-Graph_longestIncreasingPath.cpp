#include "head.h"

/* 329. 矩阵中的最长递增路径
给定一个 m x n 整数矩阵 matrix ，找出其中 最长递增路径 的长度。
对于每个单元格，你可以往上，下，左，右四个方向移动。 你 不能 在 对角线
方向上移动或移动到 边界外（即不允许环绕）。
示例 1：
  输入：matrix = [[9,9,4],[6,6,8],[2,1,1]]
  输出：4
  解释：最长递增路径为 [1, 2, 6, 9]。
示例 2：
  输入：matrix = [[3,4,5],[3,2,6],[2,2,1]]
  输出：4
  解释：最长递增路径是 [3, 4, 5, 6]。注意不允许在对角线方向上移动。
示例 3：
  输入：matrix = [[1]]
  输出：1
提示：
  m == matrix.length
  n == matrix[i].length
  1 <= m, n <= 200
  0 <= matrix[i][j] <= 231 - 1 */

// 拓扑排序。将矩阵看成有向图。若由低向高指，则最长路径的终端结点，其出度为0。若路径是从高向低指，则最长路径终端结点，入度为0
// 以出度为例，一轮遍历统计出度。二轮遍历将所有出度为0结点压入队列。三轮遍历，每一层即为所有出度为0的结点删除操作
// 即对所有周围点，其值小于该点的。出度减一。如此出度为0的，压入下一层结点。最终，层数就是所求最长路径
int longestIncreasingPath(vector<vector<int>>& matrix) {
  int m = matrix.size(), n = matrix[0].size();
  vector<vector<int>> outDeg(m, vector<int>(n, 0));
  int dir[5] = {1, 0, -1, 0, 1};
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < 4; k++) {
        int nextx = i + dir[k];
        int nexty = j + dir[k + 1];
        if (nextx < 0 || nextx >= m || nexty < 0 || nexty >= n ||
            matrix[nextx][nexty] <= matrix[i][j])
          continue;
        outDeg[i][j]++;
      }
    }
  }
  queue<pair<int, int>> que;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (outDeg[i][j] == 0)
        que.push({i, j});
    }
  }
  int ans = 0;
  while (!que.empty()) {
    ans++;
    int size = que.size();
    while (size--) {
      int curx = que.front().first;
      int cury = que.front().second;
      que.pop();
      for (int k = 0; k < 4; k++) {
        int nextx = curx + dir[k];
        int nexty = cury + dir[k + 1];
        if (nextx < 0 || nextx >= m || nexty < 0 || nexty >= n ||
            matrix[nextx][nexty] >= matrix[curx][cury])
          continue;
        if (--outDeg[nextx][nexty] == 0)
          que.push({nextx, nexty});
      }
    }
  }
  return ans;
}

// 记忆化深度优先搜索。记忆矩阵memo[i][j]代表此位置为起点，最长递增路径的长度。因此某点一旦算过一次，就无需再算第二次
// 深度递归的返回值是memo[i][j]，主函数中，遍历所有结点，取其返回值中最大的，即为答案
// 递归辅助函数中，退出条件是，该点一旦有值，即计算过，直接返回。否则即为从0开始的起点，赋值为1
// 对上下左右四个方向，按值升序的状态，依次递归。本结点最长路径，是子结点最长路径+1
int dfs(vector<vector<int>>& matrix, int x, int y, vector<vector<int>>& memo) {
  if (memo[x][y])
    return memo[x][y];
  memo[x][y] = 1;
  int dir[5] = {1, 0, -1, 0, 1};
  for (int k = 0; k < 4; k++) {
    int nextx = x + dir[k];
    int nexty = y + dir[k + 1];
    if (nextx < 0 || nextx >= matrix.size() || nexty < 0 ||
        nexty >= matrix[0].size() || matrix[nextx][nexty] <= matrix[x][y])
      continue;
    memo[x][y] = max(memo[x][y], dfs(matrix, nextx, nexty, memo) + 1);
  }
  return memo[x][y];
}
int longestIncreasingPath1(vector<vector<int>>& matrix) {
  int m = matrix.size(), n = matrix[0].size();
  int ans = 0;
  vector<vector<int>> memo(m, vector<int>(n, 0));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      ans = max(ans, dfs(matrix, i, j, memo));
    }
  }
  return ans;
}

int main() {
  vector<vector<int>> mat1 = {{9, 9, 4}, {6, 6, 8}, {2, 1, 1}},
                      mat2 = {{3, 4, 5}, {3, 2, 6}, {2, 2, 1}}, mat3 = {{1}};
  cout << longestIncreasingPath(mat1) << " " << longestIncreasingPath(mat2)
       << " " << longestIncreasingPath(mat3) << endl;
  return 0;
}