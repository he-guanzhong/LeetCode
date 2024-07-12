#include "head.h"
/*  kruskal算法精讲
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

// 基于并查集，保存边的信息
struct Edge {
  int l, r, val;
};
// 并查集总数量
int n = 10001;
vector<int> father(n, 0);
// 并查集初始化
void init() {
  for (int i = 0; i < n; i++)
    father[i] = i;
}
// 并查集寻根，包含路径压缩
int find(int u) {
  return father[u] == u ? u : father[u] = find(father[u]);
}
// 并查集相同集合
bool isSame(int u, int v) {
  u = find(u);
  v = find(v);
  return u == v;
}
// 并查集加入集合。
void join(int u, int v) {
  u = find(u);
  v = find(v);
  if (u == v)
    return;
  father[v] = u;
}

// 先按照边的权重排序，权重小的先入集合。若两节点不在同一集合，则考虑其权重，并二者新入集合。若已在同一集合，直接跳过
// 时间复杂度，快排nlog(n)快排+log(n)并查集
// prim算法适用稠密图，边几乎完全连接结点，时间复杂度O(n^2)，n为结点数，运行速度与边数无关
// kruskal算法使用稀疏图，边数量少于节点数，时间复杂度O(nlogn)，n为边数
int kruskal(vector<Edge>& edges) {
  int ans = 0;
  vector<Edge> result;  // 保存边
  init();
  sort(edges.begin(), edges.end(),
       [](const Edge& a, const Edge& b) { return a.val < b.val; });
  for (const Edge& edge : edges) {
    if (!isSame(edge.l, edge.r)) {
      result.push_back(edge);
      join(edge.l, edge.r);
      ans += edge.val;
    }
  }
  for (int i = 0; i < result.size(); i++)
    cout << result[i].l << "-" << result[i].r << ":" << result[i].val << "\t";
  cout << endl;
  return ans;
}

int main() {
  int V = 7, E = 11;
  vector<Edge> edges = {{1, 2, 1}, {1, 3, 1}, {1, 5, 2}, {2, 6, 1},
                        {2, 4, 2}, {2, 3, 2}, {3, 4, 1}, {4, 5, 1},
                        {5, 6, 2}, {5, 7, 1}, {6, 7, 1}};

  cout << kruskal(edges) << endl;
  return 0;
}