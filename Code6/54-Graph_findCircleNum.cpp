#include "head.h"

/* 547. 省份数量
有 n 个城市，其中一些彼此相连，另一些没有相连。如果城市 a 与城市 b
直接相连，且城市 b 与城市 c 直接相连，那么城市 a 与城市 c 间接相连。
省份 是一组直接或间接相连的城市，组内不含其他没有相连的城市。
给你一个 n x n 的矩阵 isConnected ，其中 isConnected[i][j] = 1 表示第 i
个城市和第 j 个城市直接相连，而 isConnected[i][j] = 0 表示二者不直接相连。
返回矩阵中 省份 的数量。
示例 1：
  输入：isConnected = [[1,1,0],[1,1,0],[0,0,1]]
  输出：2
示例 2：
  输入：isConnected = [[1,0,0],[0,1,0],[0,0,1]]
  输出：3
提示：
  1 <= n <= 200
  n == isConnected.length
  n == isConnected[i].length
  isConnected[i][j] 为 1 或 0
  isConnected[i][i] == 1
  isConnected[i][j] == isConnected[j][i] */

int find(int u, vector<int>& father) {
  return father[u] == u ? u : father[u] = find(father[u], father);
}
void join(int u, int v, vector<int>& father) {
  u = find(u, father);
  v = find(v, father);
  if (u == v)
    return;
  father[u] = v;
}
int findCircleNum(vector<vector<int>>& isConnected) {
  int n = isConnected.size();
  vector<int> father(n, 0);
  iota(father.begin(), father.end(), 0);
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++)
      if (isConnected[i][j])
        join(i, j, father);
  }
  int ans = 0;
  for (int i = 0; i < n; i++)
    ans += father[i] == i;
  return ans;
}

// 并查集典型题。给出邻接矩阵，求联通分量数。联通分量的根节点特征是，其父节点即为自身
// 题目备注中，已说明isConnected[i][i]==1，故所有城市必完全存在，init()函数无需特殊处理
// [i][j]和[j][i]完全相等，故遍历矩阵只需要从右上角，或左下角开始，无需遍历全矩阵
// join函数自带区分u,v是否一个集合，故无需专门的isSame()函数
vector<int> father1;
void init1() {
  father1.resize(201);
  iota(father1.begin(), father1.end(), 0);
}
int find1(int u) {
  return father1[u] == u ? u : father1[u] = find1(father1[u]);
}
bool isSame1(int u, int v) {
  return find1(u) == find1(v);
}
void join1(int u, int v) {
  u = find1(u);
  v = find1(v);
  if (u == v)
    return;
  father1[v] = u;
}
int findCircleNum1(vector<vector<int>>& isConnected) {
  int n = isConnected.size();
  init1();
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (isConnected[i][j] == 1)
        join1(i, j);
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++)
    ans += (father1[i] == i);
  return ans;
}

int main() {
  vector<vector<int>> isConnected1 = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}},
                      isConnected2 = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};
  cout << findCircleNum(isConnected1) << " " << findCircleNum(isConnected2)
       << endl;
  cout << findCircleNum1(isConnected1) << " " << findCircleNum1(isConnected2)
       << endl;
  return 0;
}