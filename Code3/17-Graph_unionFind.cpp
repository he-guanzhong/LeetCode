#include "head.h"
// 查并集
// 作用：1. 将两个元素放在同一集合之内。2. 查询两个元素是否在同一集合。

// 初始化。寻根（路径压缩）。是否同一集合。v->u加入集合
int m = 100;
vector<int> pere(m, 0);
void init() {
  for (int i = 0; i < m; i++)
    pere[i] = i;
}
int find(int u) {
  if (pere[u] == u)
    return u;
  else
    return pere[u] = find(pere[u]);
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
  pere[v] = u;
}

int n = 1000;  // 结点数量
vector<int> father(n, 0);

// 初始化，所有元素一开始要指向自己
void init1() {
  for (int i = 0; i < n; i++)
    father[i] = i;
}
// 寻根。如果找到自己，就结束。如果没找到，就递归
int find1(int u) {
  if (father[u] == u)
    return u;
  else
    return find1(father[u]);
}

// 路径压缩。将所有孙节点都变为子节点。递归得到根节点后，每一层回溯时，将father[u]=root
int find2(int u) {
  if (father[u] == u)
    return u;
  else
    return father[u] = find2(father[u]);
}
// 路径压缩，简写
int find3(int u) {
  return (father[u] == u) ? u : father[u] = find3(father[u]);
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
  father[v] = u;
}

// join函数不能使用isSame简写,因为这是将原始的v->u，
void join_wrong1(int u, int v) {
  if (isSame(u, v))
    return;
  father[v] = u;
}
// join函数还可以按秩排序，将秩小的u，指向秩大的v。否则二者相反
// 如果二者秩相等
// 查询的时间复杂度O(n)=logn,随着数据量越来越大，越趋近于O(n)=1。因为最一开始时logN，经历过一次路径压缩后，得到1
vector<int> ranking(n, 1);
void join_rank1(int u, int v) {
  u = find1(u);
  v = find1(v);
  if (u == v)
    return;
  if (ranking[u] <= ranking[v])
    father[u] = v;
  else
    father[v] = u;
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
}