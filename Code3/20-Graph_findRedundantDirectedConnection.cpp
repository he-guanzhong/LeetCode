#include "head.h"
/* 685. 冗余连接 II
在本问题中，有根树指满足以下条件的 有向
图。该树只有一个根节点，所有其他节点都是该根节点的后继。该树除了根节点之外的每一个节点都有且只有一个父节点，而根节点没有父节点。
输入一个有向图，该图由一个有着 n1 个节点（节点值不重复，从 1 到
n）的树及一条附加的有向边构成。附加的边包含在 1 到 n1
中的两个不同顶点间，这条附加的边不属于树中已存在的边。
结果图是一个以边组成的二维数组 edges 。 每个元素是一对 [ui, vi]，用以表示 有向
图中连接顶点 ui 和顶点 vi 的边，其中 ui 是 vi 的一个父节点。
返回一条能删除的边，使得剩下的图是有 n1
个节点的有根树。若有多个答案，返回最后出现在给定二维数组的答案。
示例 1：
  输入：edges = [[1,2],[1,3],[2,3]]
  输出：[2,3]
示例 2：
  输入：edges = [[1,2],[2,3],[3,4],[4,1],[1,5]]
  输出：[4,1]
提示：
    n == edges.length
    3 <= n <= 1000 */

static const int N = 1003;
int father[N];
void init() {
  for (int i = 0; i < N; i++)
    father[i] = i;
}
int find(int u) {
  return father[u] == u ? u : father[u] = find(father[u]);
}
bool isSame(int u, int v) {
  return find(u) == find(v);
}
void join(int u, int v) {
  u = find(u);
  v = find(v);
  if (u == v)
    return;
  father[v] = u;
}
vector<int> loop(vector<vector<int>>& edges) {
  init();
  for (const auto& edge : edges) {
    if (isSame(edge[0], edge[1]))
      return edge;
    join(edge[0], edge[1]);
  }
  return {};
}
bool isTreeAfterRemove(vector<vector<int>>& edges, int removeIndex) {
  init();
  for (int i = 0; i < edges.size(); i++) {
    if (i == removeIndex)
      continue;
    if (isSame(edges[i][0], edges[i][1]))
      return false;
    join(edges[i][0], edges[i][1]);
  }
  return true;
}
vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
  vector<int> inDeg(N, 0);
  for (const auto& edge : edges) {
    inDeg[edge[1]]++;
  }
  vector<int> inDeg2Index;
  for (int i = 0; i < edges.size(); i++) {
    if (inDeg[edges[i][1]] == 2)
      inDeg2Index.push_back(i);
  }
  if (inDeg2Index.empty()) {
    return loop(edges);
  }
  if (isTreeAfterRemove(edges, inDeg2Index[1]))
    return edges[inDeg2Index[1]];
  else
    return edges[inDeg2Index[0]];
}

// 注意u->v中，u是父节点，v为子节点。因此v的入度即为其父结点数。题目说明，每个结点只有一个父节点。故所有结点的入度均为1，除了根节点入度为0
// 异常分三种情况。2入度的要看删除那条边成树。入度为0，必成环要删除成环边。故首先统计入度。倒序遍历所有边，记录其入度为2结，在edges中的下标，入vec
// 若vec内不为空，其大小size必为2。则用一个函数看删除vec[0]或vec[1]（遇到这条边下标直接跳过即可）哪个可以成树，返回该下标对应边。
// 若vec为空，则用一个函数，直接删除成环边。

// 对于有向图，想改树，必先遍历所有边的第二个数值，统计每个结点的入度。
// 遍历所有边，找到入度为2的结点。记录边下标。此过程必反向遍历，因为最后要删除的边，如此可在vec的头两位记录与之相连边号
// 如果存在入度为2的结点，判断其第一边，或第二边，删除后可成树与否。如是，返回该边
// 如果不存在入度2的结点。则必存在环，遍历整个边集，找到需要删除的边
// 特别注意，并查集初始化时，由于边数可能大于结点数，必须多初始化一部分
static const int M = 1003;                // 总结点数
int n1;                                   // 注意，边数不等于节点数
vector<int> father1 = vector<int>(M, 0);  // 必须如此写
void init1() {
  for (int i = 0; i < n1; i++)
    father1[i] = i;
}
int find1(int u) {
  return u == father1[u] ? u : father1[u] = find1(father1[u]);
}
// v->u，子节点指向父节点
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
bool isTreeAfterRemoveEdge1(vector<vector<int>>& edges, int deleteEdge) {
  init1();
  for (int i = 0; i < edges.size(); i++) {
    if (i == deleteEdge)
      continue;
    if (isSame1(edges[i][0], edges[i][1]))
      return false;
    join1(edges[i][0], edges[i][1]);
  }
  return true;
}
vector<int> getRemoveEdge1(vector<vector<int>>& edges) {
  init1();
  for (int i = 0; i < edges.size(); i++) {
    if (isSame1(edges[i][0], edges[i][1]))
      return edges[i];
    join1(edges[i][0], edges[i][1]);
  }
  return {};
}
vector<int> findRedundantDirectedConnection1(vector<vector<int>>& edges) {
  n1 = edges.size();
  vector<int> inDegree(M, 0);
  for (int i = 0; i < edges.size(); i++)
    inDegree[edges[i][1]]++;

  vector<int> vec;  // 保存入度为2的结点，保存边的下标
  for (int i = edges.size() - 1; i >= 0; i--) {
    if (inDegree[edges[i][1]] == 2)
      vec.push_back(i);
  }
  if (vec.size() > 0) {  // 有入度为2的结点
    if (isTreeAfterRemoveEdge1(edges, vec[0]))
      return edges[vec[0]];
    else
      return edges[vec[1]];
  }
  return getRemoveEdge1(edges);
}

int main() {
  vector<vector<int>> edges1 = {{1, 2}, {1, 3}, {2, 3}};
  vector<vector<int>> edges2 = {{1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 5}};
  printVector(findRedundantDirectedConnection(edges1));
  printVector(findRedundantDirectedConnection(edges2));
  printVector(findRedundantDirectedConnection1(edges1));
  printVector(findRedundantDirectedConnection1(edges2));
  return 0;
}