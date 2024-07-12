#include "head.h"
/*  prim算法精讲
在世界的某个区域，有一些分散的神秘岛屿，每个岛屿上都有一种珍稀的资源或者宝藏。国王打算在这些岛屿上建公路，方便运输。
不同岛屿之间，路途距离不同，国王希望你可以规划建公路的方案，如何可以以最短的总公路距离将
所有岛屿联通起来。给定一张地图，其中包括了所有的岛屿，以及它们之间的距离。以最小化公路建设长度，确保可以链接到所有岛屿。
输入描述：
  第一行包含两个整数V和E，V代表顶点数，E代表边数。顶点编号是从1到V。例如：V=2，一个有两个顶点，分别是1和2。
  接下来共有E行，每行三个整数v1，v2和val，v1和v2为边的起点和终点，val代表边的权值。
输出描述：
  输出联通所有岛屿的最小路径总距离
输入示例：
  7 11
  1 2 1
  1 3 1
  1 5 2
  2 6 1
  2 4 2
  2 3 2
  3 4 1
  4 5 1
  5 6 2
  5 7 1
  6 7 1
输出示例：6 */

int prim(vector<vector<int>>& grid, int V, int E) {
  vector<int> minDist(V + 1, 10001);
  vector<bool> isInTree(V + 1, false);
  vector<int> parent(V + 1, -1);  // 一维数组记录边
                                  // 从第一结点开始，循环V-1次
  for (int i = 1; i < V; i++) {
    // 1. 选距最小生成树最近的结点，首轮必选结点1
    int cur = -1;
    int minVal = INT_MAX;
    for (int j = 1; j <= V; j++) {
      if (!isInTree[j] && minDist[j] < minVal) {
        minVal = minDist[j];
        cur = j;
      }
    }
    // 2. cur加入到已访问结点
    isInTree[cur] = true;
    // 3. 拓展更新minDist，即非生成树结点，到生成树的最短距离
    // parent[j]=cur记录新拓展点j->当前点cur的连接关系，注意不得反写，因为会被覆盖
    for (int j = 1; j <= V; j++) {
      if (!isInTree[j] && grid[cur][j] < minDist[j]) {
        minDist[j] = grid[cur][j];
        parent[j] = cur;
      }
    }
  }
  for (int i = 1; i < parent.size(); i++)
    cout << i << "->" << parent[i] << "\t";
  cout << endl;
  // 收集最小生成树边的权值，不计第一个结点，因为只有其余v-1个边有值
  int ans = 0;
  for (int i = 2; i <= V; i++)
    ans += minDist[i];
  return ans;
}

int main() {
  int V = 7, E = 11;
  vector<vector<int>> grid(V + 1, vector<int>(V + 1, 10001));
  grid[1][2] = grid[2][1] = 1, grid[1][3] = grid[3][1] = 1;
  grid[1][5] = grid[5][1] = 2, grid[2][6] = grid[6][2] = 1;
  grid[2][4] = grid[4][2] = 2, grid[2][3] = grid[3][2] = 2;
  grid[3][4] = grid[4][3] = 1, grid[4][5] = grid[5][4] = 1;
  grid[5][6] = grid[6][5] = 2, grid[5][7] = grid[7][5] = 1;
  grid[6][7] = grid[7][6] = 1;
  cout << prim(grid, V, E) << endl;
  return 0;
}