#include "head.h"
/*  bellman_ford之单源有限最短路
题目描述：
  某国为促进城市间经济交流，决定对货物运输提供补贴。共有 n 个编号为 1 到 n
  的城市，通过道路网络连接，网络中的道路仅允许从某个城市单向通行到另一个城市，不能反向通行。
  网络中的道路都有各自的运输成本和政府补贴，道路的权值计算方式为：运输成本-政府补贴。
  权值为正表示扣除了政府补贴后运输货物仍需支付的费用；
  权值为负则表示政府的补贴超过了支出的运输成本，实际表现为运输过程中还能赚取一定的收益。
  请计算在最多经过 k 个城市的条件下，从城市 src 到城市 dst 的最低运输成本。
输入描述：
  第一行包含两个正整数，第一个正整数 n 表示该国一共有 n 个城市，第二个整数 m
  表示这些城市中共有 m 条道路。
  接下来为 m 行，每行包括三个整数，s、t 和 v，表示 s 号城市运输货物到达 t
  号城市，道路权值为 v。
  最后一行包含三个正整数，src、dst、和 k，src 和 dst 为城市编号，从 src 到 dst
  经过的城市数量限制。
输出描述：
  输出一个整数，表示从城市src到城市dst的最低运输成本，如果无法在给定经过城市数量限制下找到从
  src 到 dst 的路径，则输出 "unreachable"，表示不存在符合条件的运输方案。
输入示例：
  6 7
  1 2 1
  2 4 -3
  2 5 2
  1 3 5
  3 5 1
  4 6 4
  5 6 -2
  2 6 1
输出示例：
  0  */

string finiteShortestV(vector<vector<int>>& grid,
                       int n,
                       int src,
                       int dst,
                       int k) {
  vector<int> minDist(n + 1, INT_MAX);
  vector<int> last(n + 1, INT_MAX);
  minDist[src] = last[src] = 0;
  for (int i = 0; i <= k; i++) {
    for (int j = 0; j < grid.size(); j++) {
      int from = grid[j][0], to = grid[j][1], val = grid[j][2];
      if (last[from] != INT_MAX && last[from] + val < minDist[to])
        minDist[to] = last[from] + val;
    }
    last = minDist;
  }
  return minDist[dst] == INT_MAX ? "unreachable" : to_string(minDist[dst]);
}

// 经过k个结点，及最多通过k+1条边。即多松弛k+1次。由于有负权回路，且给出的边顺序不定，故要保存上一周期的minDist，作为本周期计算依据
// 判断是否有负权回路，仅看minDist[dst]是否变化，而不关心其数值是否正确。但本题关心
string finiteShortestV1(const vector<vector<int>>& grid,
                        int n,
                        int src,
                        int dst,
                        int k) {
  vector<int> minDist(n + 1, INT_MAX);
  vector<int> last_minDist(n + 1, INT_MAX);
  minDist[src] = 0;
  for (int i = 1; i <= k + 1; i++) {
    last_minDist = minDist;
    for (const vector<int>& edge : grid) {
      int from = edge[0];
      int to = edge[1];
      int price = edge[2];
      if (last_minDist[from] != INT_MAX &&
          minDist[to] > last_minDist[from] + price) {
        minDist[to] = last_minDist[from] + price;  // 更新本周期松弛结果
      }
    }
  }
  return minDist[dst] == INT_MAX ? "unreachable" : to_string(minDist[dst]);
}

// SPFA算法，使用queSize控制松弛次数。入队出队有消耗，避免同一结点重复压入使用visited数组。但对稠密图，还是不如普通算法
struct Edge {
  int to, val;
  Edge(int t, int v) : to(t), val(v) {}
};

string finiteShortestE(vector<list<Edge>>& edges,
                       int n,
                       int src,
                       int dst,
                       int k) {
  vector<int> minDist(n + 1, INT_MAX);
  minDist[src] = 0;
  queue<int> que;
  que.push(src);
  k++;
  while (que.size() && k--) {
    int size = que.size();
    vector<bool> visited(n + 1);
    vector<int> last = minDist;
    while (size--) {
      int cur = que.front();
      que.pop();
      for (const auto& e : edges[cur]) {
        if (last[cur] != INT_MAX && last[cur] + e.val < minDist[e.to]) {
          minDist[e.to] = last[cur] + e.val;
          if (visited[e.to])
            continue;
          que.push(e.to);
          visited[e.to] = true;
        }
      }
    }
  }
  return minDist[dst] == INT_MAX ? "unreachable" : to_string(minDist[dst]);
}
string finiteShortestE1(vector<list<Edge>>& edges,
                        int n,
                        int src,
                        int dst,
                        int k) {
  vector<int> minDist(n + 1, INT_MAX);
  vector<int> last_minDist(n + 1, INT_MAX);
  minDist[src] = 0;
  queue<int> que;
  que.push(src);
  k++;
  while (que.size() && k--) {
    last_minDist = minDist;
    vector<bool> visited(n + 1, false);
    int queSize = que.size();
    while (queSize--) {  // 该轮松弛
      int cur = que.front();
      que.pop();
      for (Edge edge : edges[cur]) {
        if (minDist[edge.to] > last_minDist[cur] + edge.val) {
          minDist[edge.to] = last_minDist[cur] + edge.val;
          if (visited[edge.to])  // 本轮压入过一次就不再压入
            continue;
          que.push(edge.to);
          visited[edge.to] = true;
        }
      }
    }
  }
  return minDist[dst] == INT_MAX ? "unreachable" : to_string(minDist[dst]);
}

int main() {
  int N = 6, M = 7;
  int src = 2, dst = 6, k = 1;
  int ans;
  vector<vector<int>> grid(M + 1, vector<int>(3, 0));
  grid[1] = {1, 2, 1};
  grid[2] = {2, 4, -3};
  grid[3] = {2, 5, 2};
  grid[4] = {1, 3, 5};
  grid[5] = {3, 5, 1};
  grid[6] = {4, 6, 4};
  grid[7] = {5, 6, -2};
  cout << finiteShortestV(grid, N, src, dst, k) << endl;
  cout << finiteShortestV1(grid, N, src, dst, k) << endl;

  vector<list<Edge>> edges(N + 1);
  edges[1].push_back(Edge(2, 1));
  edges[2].push_back(Edge(4, -3));
  edges[2].push_back(Edge(5, 2));
  edges[1].push_back(Edge(3, 5));
  edges[3].push_back(Edge(5, 1));
  edges[4].push_back(Edge(6, 4));
  edges[5].push_back(Edge(6, -2));
  cout << finiteShortestE(edges, N, src, dst, k) << endl;
  cout << finiteShortestE1(edges, N, src, dst, k) << endl;

  return 0;
}