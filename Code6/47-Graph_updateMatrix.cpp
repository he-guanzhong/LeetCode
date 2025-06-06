#include "head.h"

/* 542. 01 矩阵
给定一个由 0 和 1 组成的矩阵 mat ，请输出一个大小相同的矩阵，其中每一个格子是
mat 中对应位置元素到最近的 0 的距离。 两个相邻元素间的距离为 1 。
示例 1：
  输入：mat = [[0,0,0],
              [0,1,0],
              [0,0,0]]
  输出：[[0,0,0],
        [0,1,0],
        [0,0,0]]
示例 2：
  输入：mat = [[0,0,0],
              [0,1,0],
              [1,1,1]]
  输出：[[0,0,0],
        [0,1,0],
        [1,2,1]]
提示：
  m == mat.length
  n == mat[i].length
  1 <= m, n <= 104
  1 <= m * n <= 104
  mat[i][j] is either 0 or 1.
  mat 中至少有一个 0  */

// 优选动态规划。每一个1节点[i][j]答案，可能来自于上、下、左、右四个方向的0而推出
// dp[i][j]矩阵意为最靠近的0节点，到该节点的曼哈顿距离。由于要不断更新最小距离，故初始化为INT_MAX/2
// 对0节点，初始化dp[i][j]=0。然后依次从左上角、右下角，两个方向，对全矩阵遍历两次
// 如此空间复杂度O(1)，因为返回值不算入空间复杂度。时间复杂度O(mn)
vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
  int m = mat.size(), n = mat[0].size();
  vector<vector<int>> dp(m, vector<int>(n, INT_MAX / 2));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (mat[i][j] == 0)
        dp[i][j] = 0;
    }
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (i > 0)
        dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
      if (j > 0)
        dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
    }
  }
  for (int i = m - 1; i >= 0; i--) {
    for (int j = n - 1; j >= 0; j--) {
      if (i < m - 1)
        dp[i][j] = min(dp[i][j], dp[i + 1][j] + 1);
      if (j < n - 1)
        dp[i][j] = min(dp[i][j], dp[i][j + 1] + 1);
    }
  }
  return dp;
}

// BFS广度优先搜索。现将所有的0节点压入队列，然后逐圈向外拓展。另设置visited矩阵保留每个节点是否访问过
// ans[i][j]即为该轮轮次数，可以直接由cur节点的轮次数+1获得
// 时间复杂度O(mn)，空间复杂度O(mn)
vector<vector<int>> updateMatrix1(vector<vector<int>>& mat) {
  int m = mat.size(), n = mat[0].size();
  vector<vector<bool>> visit(m, vector<bool>(n, 0));
  vector<vector<int>> ans(m, vector<int>(n, 0));
  queue<pair<int, int>> que;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (mat[i][j] == 0) {
        visit[i][j] = true;
        que.push({i, j});
      }
    }
  }
  int dir[5] = {1, 0, -1, 0, 1};
  while (!que.empty()) {
    int curx = que.front().first;
    int cury = que.front().second;
    que.pop();
    for (int k = 0; k < 4; k++) {
      int nextx = curx + dir[k];
      int nexty = cury + dir[k + 1];
      if (nextx < 0 || nextx >= m || nexty < 0 || nexty >= n ||
          visit[nextx][nexty])
        continue;
      visit[nextx][nexty] = true;
      ans[nextx][nexty] = ans[curx][cury] + 1;
      que.push({nextx, nexty});
    }
  }
  return ans;
}

int main() {
  vector<vector<int>> mat1 = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}},
                      mat2 = {{0, 0, 0}, {0, 1, 0}, {1, 2, 1}};
  printMat(updateMatrix(mat1));
  printMat(updateMatrix(mat2));
  return 0;
}