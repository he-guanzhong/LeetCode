#include <cstring>
#include "head.h"
/* 684. 冗余连接
树可以看成是一个连通且 无环 的 无向 图。
给定往一棵 n 个节点 (节点值 1～n)
的树中添加一条边后的图。添加的边的两个顶点包含在 1 到 n
中间，且这条附加的边不属于树中已存在的边。图的信息记录于长度为 n 的二维数组
edges ，edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。
请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n
个节点的树。如果有多个答案，则返回数组 edges 中最后出现的那个。
示例 1：
  输入: edges = [[1,2], [1,3], [2,3]]
  输出: [2,3]
示例 2：
  输入: edges = [[1,2], [2,3], [3,4], [1,4], [1,5]]
  输出: [1,4]
提示:
  n == edges.length
  3 <= n <= 1000 */

int m = 1005;
int father[1005];
void init() {
  for (int i = 0; i < 1005; i++)
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
vector<int> findRedundantConnection(vector<vector<int>>& edges) {
  memset(father, 0, sizeof(father));
  init();
  for (int i = 0; i < edges.size(); i++) {
    if (isSame(edges[i][0], edges[i][1]))
      return {edges[i][0], edges[i][1]};
    join(edges[i][0], edges[i][1]);
  }
  return {};
}

// 遍历每一条边，如果已经在同一并查集内，直接返回，否则相连接。
// 判断每一条边，如果不是同一集合就链接。如果是，则当即返回该边信息。注意，最终需要返回空集合，作为默认情况
int n = 1003;
vector<int> father1 = vector<int>(n, 0);  // 必须如此写
void init1() {
  for (int i = 0; i < n; i++)
    father1[i] = i;
}
int find1(int u) {
  return u == father1[u] ? u : father1[u] = find1(father1[u]);
}
// 将v->u 这条边加入并查集
void join1(int u, int v) {
  u = find1(u);
  v = find1(v);
  if (u == v)
    return;
  father1[v] = u;
}
bool isSame1(int u, int v) {
  u = find1(u);
  v = find1(v);
  return u == v;
}

vector<int> findRedundantConnection1(vector<vector<int>>& edges) {
  init1();
  for (int i = 0; i < edges.size(); i++) {
    if (isSame1(edges[i][0], edges[i][1]))
      return edges[i];
    join1(edges[i][0], edges[i][1]);
  }
  return {};
}

int main() {
  vector<vector<int>> edges1 = {{1, 2}, {1, 3}, {2, 3}};
  vector<vector<int>> edges2 = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
  printVector(findRedundantConnection(edges1));
  printVector(findRedundantConnection(edges2));
  printVector(findRedundantConnection1(edges1));
  printVector(findRedundantConnection1(edges2));
  return 0;
}