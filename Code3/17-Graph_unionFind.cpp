#include "head.h"
// 并查集
// 作用：1. 将两个元素放在同一集合之内。2. 查询两个元素是否在同一集合。

const int n = 1000;
int father[n];
void init() {
  for (int i = 0; i < n; i++)
    father[i] = i;
}
int find(int u) {
  return u == father[u] ? u : father[u] = find(father[u]);
}
bool isSame(int u, int v) {
  return find(u) == find(v);
}
void join(int u, int v) {
  u = find(u);
  v = find(v);
  if (u == v)
    return;
  father[u] = v;
}

// 总计四个函数。初始化。寻根（路径压缩）。是否同一集合。v->u加入集合
int n1 = 1000;  // 结点数量
vector<int> father1(n1, 0);

// 初始化，所有元素一开始要指向自己
void init1() {
  for (int i = 0; i < n1; i++)
    father1[i] = i;
}
// 寻根。如果找到自己，就结束。如果没找到，就递归
int find1(int u) {
  if (father1[u] == u)
    return u;
  else
    return find1(father1[u]);
}

// 路径压缩。将所有孙节点都变为子节点。递归得到根节点后，每一层回溯时，将father1[u]=root
int find2(int u) {
  if (father1[u] == u)
    return u;
  else
    return father1[u] = find2(father1[u]);
}
// 路径压缩，简写
int find3(int u) {
  return (father1[u] == u) ? u : father1[u] = find3(father1[u]);
}

// 判断两个元素是否在同一集合里
bool isSame1(int u, int v) {
  u = find1(u);
  v = find1(v);
  return u == v;
}

// 沿v->u 将u加入并查集。
void join1(int u, int v) {
  u = find1(u);
  v = find1(v);
  if (u == v)
    return;
  father1[v] = u;
}

// join函数不能使用isSame简写,因为这是将原始的v->u，
void join_wrong1(int u, int v) {
  if (isSame(u, v))
    return;
  father1[v] = u;
}
// join函数还可以按秩排序，将秩小的u，指向秩大的v。否则二者相反
// 如果二者秩相等
// 查询的时间复杂度O(n1)=logn,随着数据量越来越大，越趋近于O(n1)=1。因为最一开始时logN，经历过一次路径压缩后，得到1
vector<int> ranking(n1, 1);
void join_rank1(int u, int v) {
  u = find1(u);
  v = find1(v);
  if (u == v)
    return;
  if (ranking[u] <= ranking[v])
    father1[u] = v;
  else
    father1[v] = u;
  if (ranking[u] == ranking[v] && u != v)
    ranking[v]++;
}

int main() {
  init();
  join(1, 8);
  join(3, 8);
  join(1, 7);
  join(8, 5);
  join(2, 9);
  join(6, 2);
  init1();
  join1(1, 8);
  join1(3, 8);
  join1(1, 7);
  join1(8, 5);
  join1(2, 9);
  join1(6, 2);
  cout << isSame(8, 7) << " " << isSame(7, 2) << endl;
  cout << isSame1(8, 7) << " " << isSame1(7, 2) << endl;
  return 0;
}