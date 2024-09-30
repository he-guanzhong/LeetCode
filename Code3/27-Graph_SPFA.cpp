#include "head.h"
/*  Bellman_ford 队列优化算法（又名SPFA）
题目描述：
  某国为促进城市间经济交流，决定对货物运输提供补贴。共有 n 个编号为 1 到 n
  的城市，通过道路网络连接，网络中的道路仅允许从某个城市单向通行到另一个城市，不能反向通行。
  网络中的道路都有各自的运输成本和政府补贴，道路的权值计算方式为：运输成本-政府补贴。
  权值为正表示扣除了政府补贴后运输货物仍需支付的费用；权值为负则表示政府的补贴超过了支出的运输成本，实际表现为运输过程中还能赚取一定的收益。
  请找出从城市 1 到城市 n 的所有可能路径中，综合政府补贴后的最低运输成本。
  如果最低运输成本是一个负数，它表示在遵循最优路径的情况下，运输过程中反而能够实现盈利。
  城市 1 到城市 n
  之间可能会出现没有路径的情况，同时保证道路网络中不存在任何负权回路。
    负权回路是指一系列道路的总权值为负，这样的回路使得通过反复经过回路中的道路，理论上可以无限地减少总成本或无限地增加总收益。
输入描述：
  第一行包含两个正整数，第一个正整数 n 表示该国一共有 n 个城市，第二个整数 m
  表示这些城市中共有 m 条道路。
  接下来为 m 行，每行包括三个整数，s、t 和 v，表示 s 号城市运输货物到达 t
  号城市，道路权值为 v（单向图）。
输出描述：
  如果能够从城市 1 到连通到城市 n，
  请输出一个整数，表示运输成本。如果该整数是负数，则表示实现了盈利。如果从城市 1
  没有路径可达城市 n，请输出 "unconnected"。
输入示例：
  6 7
  5 6 -2
  1 2 1
  5 3 1
  2 5 2
  2 4 -3
  4 6 4
  1 3 5
输出示例：
  12。*/

struct Edge {
  int to, val;
  Edge(int t, int v) : to(t), val(v) {}
};

int SPFA(vector<list<Edge>>& edges, int n) {
  vector<int> minDist(n + 1, INT_MAX);
  minDist[1] = 0;
  queue<int> que;
  que.push(1);
  while (que.size()) {
    int cur = que.front();
    que.pop();
    for (const Edge& e : edges[cur]) {
      if (minDist[cur] + e.val < minDist[e.to]) {
        minDist[e.to] = minDist[cur] + e.val;
        que.push(e.to);
      }
    }
  }
  return minDist[n] == INT_MAX ? -1 : minDist[n];
}

// SPFA: shortest path faster algorithm
// 时间复杂度，图越稠密，为双向且每两个结点相连，接近Bellman_ford的V*E。越稀疏，甚至为单链，时间复杂度为N，整体看是K*N
int SPFA1(vector<list<Edge>>& grid, int n) {
  // 起点从1开始，其距源点代价为0，并压入队列
  vector<int> minDist(n + 1, INT_MAX);
  minDist[1] = 0;
  queue<int> que;
  que.push(1);
  while (que.size()) {
    int cur = que.front();
    que.pop();
    // 遍历该结点链接的每一条边，更新代价，并压入队列
    for (Edge edge : grid[cur]) {
      if (minDist[cur] + edge.val < minDist[edge.to]) {
        minDist[edge.to] = minDist[cur] + edge.val;
        que.push(edge.to);
      }
    }
  }
  return minDist[n];
}

int main() {
  int N = 6, M = 7;
  vector<list<Edge>> grid(N + 1);
  grid[5].push_back(Edge(6, -2));
  grid[1].push_back(Edge(2, 1));
  grid[5].push_back(Edge(3, 1));
  grid[2].push_back(Edge(5, 2));
  grid[2].push_back(Edge(4, -3));
  grid[4].push_back(Edge(6, 4));
  grid[1].push_back(Edge(3, 5));
  int ans = SPFA(grid, N);
  cout << (ans == INT_MAX ? string("unconnected") : to_string(ans)) << endl;
  ans = SPFA1(grid, N);
  cout << (ans == INT_MAX ? string("unconnected") : to_string(ans)) << endl;
  return 0;
}