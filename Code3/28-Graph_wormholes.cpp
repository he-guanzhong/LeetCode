#include "head.h"
/*  bellman_ford之判断负权回路
题目描述：
  某国为促进城市间经济交流，决定对货物运输提供补贴。共有 n 个编号为 1 到 n
  的城市，通过道路网络连接，网络中的道路仅允许从某个城市单向通行到另一个城市，不能反向通行。
  网络中的道路都有各自的运输成本和政府补贴，道路的权值计算方式为：运输成本 -
  政府补贴。权值为正表示扣除了政府补贴后运输货物仍需支付的费用；
  权值为负则表示政府的补贴超过了支出的运输成本，实际表现为运输过程中还能赚取一定的收益。
  然而，在评估从城市 1 到城市 n
  的所有可能路径中综合政府补贴后的最低运输成本时，存在一种情况：图中可能出现负权回路。
  负权回路是指一系列道路的总权值为负，这样的回路使得通过反复经过回路中的道路，理论上可以无限地减少总成本或无限地增加总收益。
  为了避免货物运输商采用负权回路这种情况无限的赚取政府补贴，算法还需检测这种特殊情况。
  请找出从城市 1 到城市 n
  的所有可能路径中，综合政府补贴后的最低运输成本。同时能够检测并适当处理负权回路的存在。
  城市 1 到城市 n 之间可能会出现没有路径的情况
输入描述：
  第一行包含两个正整数，第一个正整数 n 表示该国一共有 n 个城市，第二个整数 m
  表示这些城市中共有 m 条道路。
  接下来为 m 行，每行包括三个整数，s、t 和 v，表示 s 号城市运输货物到达 t
  号城市，道路权值为 v。
输出描述：
  如果没有发现负权回路，则输出一个整数，表示从城市 1 到城市 n
  的最低运输成本（包括政府补贴）。
  如果该整数是负数，则表示实现了盈利。如果发现了负权回路的存在，则输出
  "circle"。如果从城市 1 无法到达城市 n，则输出 "unconnected"。
输入示例：
  4 4
  1 2 -1
  2 3 1
  3 1 -1
  3 4 1
输出示例：
  circle  */

// 原理是松弛n次，即多松弛一次，观察是minDist否有变化
int wormholes(const vector<vector<int>>& grid, int n) {
  vector<int> minDist(n + 1, INT_MAX);
  minDist[1] = 0;
  bool flag = false;
  for (int i = 1; i <= n; i++) {
    for (const vector<int>& edge : grid) {
      int from = edge[0];
      int to = edge[1];
      int price = edge[2];
      if (i < n && minDist[from] != INT_MAX &&
          minDist[from] + price < minDist[to]) {
        minDist[to] = minDist[from] + price;
      } else if (i == n && minDist[from] != INT_MAX &&
                 minDist[from] + price < minDist[to]) {
        flag = true;  // n次松弛时，还有边的代价在更新，说明有负权回路
      }
    }
  }
  return flag ? -2 : minDist[n];
}

// SPFA算法也可以判断是否负权回路，某个结点如果入度大于n-1，则说明存在
struct Edge {
  int to, val;
  Edge(int t, int v) : to(t), val(v) {}
};
int SPFA(vector<list<Edge>>& edges, int n) {
  vector<int> minDist(n + 1, INT_MAX);
  minDist[1] = 0;
  queue<int> que;
  que.push(1);
  vector<int> inDegree(n + 1, 0);  // 统计每点入度
  int flag = false;
  while (que.size()) {
    int cur = que.front();
    que.pop();
    for (Edge edge : edges[cur]) {
      if (minDist[edge.to] > minDist[cur] + edge.val) {
        minDist[edge.to] = minDist[cur] + edge.val;
        que.push(edge.to);
        if (++inDegree[edge.to] >= n) {
          flag = true;
          return -2;  // 直接返回，或者清空que在退出
        }
      }
    }
  }
  return minDist[n];
}

int main() {
  int N = 4, M = 4;
  vector<vector<int>> grid(N + 1, vector<int>(3, 0));
  grid[1] = {1, 2, -1};
  grid[2] = {2, 3, 1};
  grid[3] = {3, 1, -1};
  grid[4] = {3, 4, 1};
  int ans = wormholes(grid, N);
  vector<list<Edge>> edges(N + 1);
  edges[1].push_back(Edge(2, -1));
  edges[2].push_back(Edge(3, 1));
  edges[3].push_back(Edge(1, -1));
  edges[3].push_back(Edge(4, 1));
  ans = SPFA(edges, N);

  if (ans == INT_MAX)
    cout << "unconnected" << endl;
  else if (ans == -2)
    cout << "circle" << endl;
  else
    cout << ans << endl;
  return 0;
}