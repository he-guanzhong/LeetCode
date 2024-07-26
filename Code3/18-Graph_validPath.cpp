#include <cstring>
#include "head.h"
/* 1971. 寻找图中是否存在路径
有一个具有 n1 个顶点的 双向 图，其中每个顶点标记从 0 到 n1 - 1（包含 0 和 n1 -
1）。图中的边用一个二维整数数组 edges 表示，其中 edges[i] = [ui, vi] 表示顶点 ui
和顶点 vi 之间的双向边。 每个顶点对由 最多一条
边连接，并且没有顶点存在与自身相连的边。
请你确定是否存在从顶点 source 开始，到顶点 destination 结束的 有效路径 。
给你数组 edges 和整数 n、source 和 destination，如果从 source 到 destination
存在 有效路径 ，则返回 true，否则返回 false 。
示例 1：
  输入：n = 3, edges = [[0,1],[1,2],[2,0]], source = 0, destination = 2
  输出：true
  解释：存在由顶点 0 到顶点 2 的路径:
    - 0 → 1 → 2
    - 0 → 2
示例 2：
  输入：n = 6, edges = [[0,1],[0,2],[3,5],[5,4],[4,3]], source = 0,
        destination = 5
  输出：false
  解释：不存在由顶点 0 到顶点 5 的路径.
提示：
    1 <= n <= 2 * 105
    0 <= edges.length <= 2 * 105*/
int father[20005];
void init() {
  for (int i = 0; i < 20005; i++)
    father[i] = i;
}
int find(int u) {
  return father[u] == u ? u : father[u] = find(father[u]);
}
bool isSame(int u, int v) {
  u = find(u);
  v = find(v);
  return u == v;
}
void join(int u, int v) {
  u = find(u);
  v = find(v);
  if (u == v)
    return;
  father[v] = u;
}
bool validPath(int n, vector<vector<int>>& edges, int source, int destination) {
  memset(father, 0, sizeof(father));
  init();
  for (int i = 0; i < edges.size(); i++) {
    join(edges[i][0], edges[i][1]);
  }
  return isSame(source, destination);
}

// 并查集基础题目，题目中n无用。find()函数中最终返回的是父节点
// 无向图，可以使用并查集来判断是否联通。查并集标准题目。注意外部定义最大结点数
// 对于每一个edges，将对应两个结点joint，最后判断起始两结点是否isSame
// 结点总数，一定要外部定义，比最大的大一些即可。father要特殊初始化
int n1 = 200005;
vector<int> father1 = vector<int>(n1, 0);
void init1() {
  for (int i = 0; i < n1; i++)
    father1[i] = i;
}
int find1(int u) {
  if (father1[u] == u)
    return u;
  else
    return father1[u] = find(father1[u]);
}
void join1(int u, int v) {
  u = find(u);
  v = find(v);
  if (u == v)
    return;
  else
    father1[u] = v;
}
bool isSame1(int u, int v) {
  u = find(u);
  v = find(v);
  return u == v;
}
bool validPath1(int n1,
                vector<vector<int>>& edges,
                int source,
                int destination) {
  init1();
  for (int i = 0; i < edges.size(); i++) {
    join1(edges[i][0], edges[i][1]);
  }
  return isSame1(source, destination);
}

int main() {
  int n1 = 3, n2 = 6;
  vector<vector<int>> edges1 = {{0, 1}, {1, 2}, {2, 0}};
  vector<vector<int>> edges2 = {{0, 1}, {0, 2}, {3, 5}, {5, 4}, {4, 3}};
  cout << validPath(n1, edges1, 0, 2) << " " << validPath(n2, edges2, 0, 5)
       << endl;
  cout << validPath1(n1, edges1, 0, 2) << " " << validPath1(n2, edges2, 0, 5)
       << endl;
  return 0;
}