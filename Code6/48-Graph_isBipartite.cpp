#include "head.h"

/* 785. 判断二分图
存在一个 无向图 ，图中有 n 个节点。其中每个节点都有一个介于 0 到 n - 1
之间的唯一编号。给你一个二维数组 graph ，其中 graph{u] 是一个节点数组，由节点 u
的邻接节点组成。形式上，对于 graph[u] 中的每个 v ，都存在一条位于节点 u 和节点 v
之间的无向边。该无向图同时具有以下属性： 不存在自环（graph[u] 不包含 u）。
不存在平行边（graph[u] 不包含重复值）。
如果 v 在 graph[u] 内，那么 u 也应该在 graph[v] 内（该图是无向图）
这个图可能不是连通图，也就是说两个节点 u 和 v 之间可能不存在一条连通彼此的路径。
二分图 定义：如果能将一个图的节点集合分割成两个独立的子集 A 和 B
，并使图中的每一条边的两个节点一个来自 A 集合，一个来自 B 集合，就将这个图称为
二分图 。
如果图是二分图，返回 true ；否则，返回 false 。
示例 1：
  输入：graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
  输出：false
  解释：不能将节点分割成两个独立的子集，以使每条边都连通一个子集中的一个节点与另一个子集中的一个节点。
示例 2：
  输入：graph = [[1,3],[0,2],[1,3],[0,2]]
  输出：true
  解释：可以将节点分成两组: {0, 2} 和 {1, 3} 。
提示：
  graph.length == n
  1 <= n <= 100
  0 <= graph[u].length < n
  0 <= graph[u][i] <= n - 1
  graph[u] 不会包含 u
  graph[u] 的所有值 互不相同
  如果 graph[u] 包含 v，那么 graph[v] 也会包含 u */

bool dfs(vector<vector<int>>& graph, int x, vector<int>& colors) {
  int color = colors[x];
  int nextColor = color == 1 ? 2 : 1;
  for (int i = 0; i < graph[x].size(); i++) {
    int node = graph[x][i];
    if (colors[node] == color)
      return false;
    if (colors[node] == 0) {
      colors[node] = nextColor;
      if (dfs(graph, node, colors) == false)
        return false;
    }
  }
  return true;
}

bool isBipartite(vector<vector<int>>& graph) {
  vector<int> colors(graph.size(), 0);
  for (int i = 0; i < graph.size(); i++) {
    if (colors[i] == 0) {
      colors[i] = 1;
      if (dfs(graph, i, colors) == false)
        return false;
    }
  }
  return true;
}

// 从一个节点出发，每轮交替对该轮空白结点，染红/黑二者之一。若遇到与本轮同色结点，说明不符合要求，返回假
// 注意，结点不一定全部是联通的，要保证每个回环均满足要求，
// 所以主函数中，一定要遍历所有结点一次，注意可能此时结点已被染色过，所以只深度搜索未染色的结点
// visited和color入参可以二合一。
bool dfs1(int index,
          vector<vector<int>>& graph,
          vector<int>& visited,
          int color) {
  visited[index] = color;
  int nextColor = color == 1 ? 2 : 1;
  vector<int>& next = graph[index];
  for (int i = 0; i < next.size(); i++) {
    if (visited[next[i]] == 0 &&
        dfs1(next[i], graph, visited, nextColor) == false)
      return false;
    if (visited[next[i]] == visited[index])
      return false;
  }
  return true;
}
bool isBipartite1(vector<vector<int>>& graph) {
  vector<int> visited(graph.size(), 0);
  for (int i = 0; i < graph.size(); i++) {
    if (visited[i] == 0 && dfs1(i, graph, visited, 1) == false)
      return false;
  }
  return true;
}

// 广度优先搜索BFS，默认每个图起始节点颜色为1。向外拓展结点时，可以不通过层数的方式记录新颜色nextColor。
// 因为每个子节点颜色nextColor，都取决于母结点颜色visit[cur]
bool bfs1(int index, vector<vector<int>>& graph, vector<int>& visited) {
  visited[index] = 1;  // default color
  queue<int> que;
  que.push(index);
  while (!que.empty()) {
    int cur = que.front();
    que.pop();
    int nextColor = visited[cur] == 1 ? 2 : 1;
    for (int i = 0; i < graph[cur].size(); i++) {
      int next = graph[cur][i];
      if (visited[next] == visited[cur])
        return false;
      if (visited[next] == 0) {
        visited[next] = nextColor;
        que.push(next);
      }
    }
  }
  return true;
}
bool isBipartite2(vector<vector<int>>& graph) {
  int n = graph.size();
  vector<int> visited(n, 0);
  for (int i = 0; i < n; i++) {
    if (visited[i] == 0 && bfs1(i, graph, visited) == false)
      return false;
  }
  return true;
}

int main() {
  vector<vector<int>> graph1 = {{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}},
                      graph2 = {{1, 3}, {0, 2}, {1, 3}, {0, 2}},
                      graph3 = {{4}, {}, {4}, {4}, {0, 2, 3}},
                      graph4 = {{},
                                {2, 4, 6},
                                {1, 4, 8, 9},
                                {7, 8},
                                {1, 2, 8, 9},
                                {6, 9},
                                {1, 5, 7, 8, 9},
                                {3, 6, 9},
                                {2, 3, 4, 6, 9},
                                {2, 4, 5, 6, 7, 8}};
  cout << isBipartite(graph1) << " " << isBipartite(graph2) << " "
       << isBipartite(graph3) << " " << isBipartite(graph4) << endl;
  cout << isBipartite1(graph1) << " " << isBipartite1(graph2) << " "
       << isBipartite1(graph3) << " " << isBipartite1(graph4) << endl;

  return 0;
}