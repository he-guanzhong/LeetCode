#include "head.h"
/* LCR 130. 衣橱整理
家居整理师将待整理衣橱划分为 m x n 的二维矩阵 grid，其中 grid[i][j]
代表一个需要整理的格子。整理师自 grid[0][0] 开始 逐行逐列 地整理每个格子。
整理规则为：在整理过程中，可以选择 向右移动一格 或
向下移动一格，但不能移动到衣柜之外。同时，不需要整理 digit(i) + digit(j) > cnt
的格子，其中 digit(x) 表示数字 x 的各数位之和。
请返回整理师 总共需要整理多少个格子。
示例 1：
输入：m = 4, n = 7, cnt = 5
输出：18
提示：
    1 <= n, m <= 100
    0 <= cnt <= 20 */

// si,sj表示各数位之和
int wardrobeFinishing(int m, int n, int cnt) {
  int ans = 0;
  vector<vector<bool>> visited(m, vector<bool>(n, false));
  queue<vector<int>> que;
  que.push({0, 0, 0, 0});
  while (!que.empty()) {
    int i = que.front()[0];
    int j = que.front()[1];
    int si = que.front()[2];
    int sj = que.front()[3];
    que.pop();
    if (i >= m || j >= n || si + sj > cnt || visited[i][j])
      continue;
    ans++;
    visited[i][j] = true;
    int si_1 = (i + 1) % 10 ? si + 1 : si - 8;
    int sj_1 = (j + 1) % 10 ? sj + 1 : sj - 8;
    que.push({i + 1, j, si_1, sj});
    que.push({i, j + 1, si, sj_1});
  }
  return ans;
}

// dfs解法，数位和的增量公式，如果数字i+1逢10进位，则s[i]减8，其余情况s[i]加一。s[i+1]==(i+1)%10?s[i]-8:s[i]+1
// 退出条件是，超过矩阵边界，或者数位和大于定值，或结点已经访问过。
int dfs1(int i,
         int j,
         int si,
         int sj,
         int m,
         int n,
         int cnt,
         vector<vector<bool>>& visited) {
  if (i >= m || j >= n || si + sj > cnt || visited[i][j])
    return 0;
  visited[i][j] = true;
  int si_1 = (i + 1) % 10 ? si + 1 : si - 8;
  int sj_1 = (j + 1) % 10 ? sj + 1 : sj - 8;
  return 1 + dfs1(i + 1, j, si_1, sj, m, n, cnt, visited) +
         dfs1(i, j + 1, si, sj_1, m, n, cnt, visited);
}
int wardrobeFinishing1(int m, int n, int cnt) {
  vector<vector<bool>> visited(m, vector<bool>(n, false));
  return dfs1(0, 0, 0, 0, m, n, cnt, visited);
}

// BFS解法。队列内保存{i,j,si,sj}四个值
int wardrobeFinishing2(int m, int n, int cnt) {
  vector<vector<bool>> visited(m, vector<bool>(n, false));
  int ans = 0;
  queue<vector<int>> que;
  que.push({0, 0, 0, 0});
  while (!que.empty()) {
    vector<int> point = que.front();
    que.pop();
    int i = point[0], j = point[1], si = point[2], sj = point[3];
    if (i >= m || j >= n || sj + si > cnt || visited[i][j])
      continue;
    visited[i][j] = true;
    ans++;
    int si_1 = (i + 1) % 10 ? si + 1 : si - 8;
    int sj_1 = (j + 1) % 10 ? sj + 1 : sj - 8;
    que.push({i + 1, j, si_1, sj});
    que.push({i, j + 1, si, sj_1});
  }
  return ans;
}

int main() {
  cout << wardrobeFinishing(4, 7, 5) << " " << wardrobeFinishing(4, 7, 5)
       << endl;
  cout << wardrobeFinishing1(4, 7, 5) << " " << wardrobeFinishing1(4, 7, 5)
       << endl;
  return 0;
}