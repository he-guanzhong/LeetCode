#include "head.h"
/*  拓扑排序精讲     210. 课程表 II
题目描述：
某个大型软件项目的构建系统拥有 N 个文件，文件编号从 0 到 N -
1，在这些文件中，某些文件依赖于其他文件的内容，这意味着如果文件 A 依赖于文件
B，则必须在处理文件 A 之前处理文件 B （0 <= A, B <= N -
1）。请编写一个算法，用于确定文件处理的顺序。
输入描述：
  第一行输入两个正整数 M, N。表示 N 个文件之间拥有 M 条依赖关系。
  后续 M 行，每行两个正整数 S 和 T，表示 T 文件依赖于 S 文件。
输出描述：
  输出共一行，如果能处理成功，则输出文件顺序，用空格隔开。
  如果不能成功处理（相互依赖），则输出 -1。
输入示例：
  5 4
  0 1
  0 2
  1 3
  2 4
输出示例：
  0 1 2 3 4
  文件依赖关系如下：0->1->3, 0->2->4
  所以，文件处理的顺序除了示例中的顺序，还存在
  0 2 4 1 3
  0 2 1 3 4
  等等合法的顺序。*/

vector<int> toposort(vector<vector<int>>& source, int n) {
  vector<int> ans;
  vector<int> inDeg(n, 0);
  vector<vector<int>> grid(n);
  for (vector<int>& s : source) {
    inDeg[s[1]]++;
    grid[s[0]].push_back(s[1]);
  }
  queue<int> que;
  for (int i = 0; i < n; i++) {
    if (inDeg[i] == 0)
      que.push(i);
  }
  while (que.size()) {
    int cur = que.front();
    que.pop();
    ans.push_back(cur);
    for (int& next : grid[cur]) {
      if (--inDeg[next] == 0)
        que.push(next);
    }
  }
  if (ans.size() != n)
    ans = {-1};
  return ans;
}

vector<int> toposort1(vector<vector<int>>& source, int n) {
  vector<int> ans;                       // 保存结果
  vector<int> inDegree(n, 0);            // 统计入度
  unordered_map<int, vector<int>> umap;  // 指向关系
  for (auto edge : source) {
    inDegree[edge[1]]++;               // t入度加一
    umap[edge[0]].push_back(edge[1]);  // s指向t
  }
  queue<int> que;  // 入度为0的结点进入队列
  for (int i = 0; i < n; i++) {
    if (inDegree[i] == 0)
      que.push(i);
  }
  // 对每个入度为0的结点分别处理
  while (que.size()) {
    int cur = que.front();
    que.pop();
    ans.push_back(cur);            // 当前入度为0的结点压入结果
    vector<int> dest = umap[cur];  // 当前结点是否有后继结点？
    for (int i = 0; i < dest.size(); i++) {
      inDegree[dest[i]]--;         // 后继节点入度减一
      if (inDegree[dest[i]] == 0)  // 入度为0就压入待处理队列
        que.push(dest[i]);
    }
  }
  // 结果中节点数小于总节点数，有环
  if (ans.size() != n)
    return {-1};
  return ans;
}

int main() {
  int N = 5, M = 4;
  vector<vector<int>> source = {{0, 1}, {0, 2}, {1, 3}, {2, 4}};
  printVector(toposort(source, N));
  printVector(toposort1(source, N));

  return 0;
}