#include "head.h"
/*  dijkstra（堆优化版）精讲
题目描述：
  小明是一位科学家，他需要参加一场重要的国际科学大会，以展示自己的最新研究成果。
  小明的起点是第一个车站，终点是最后一个车站。然而，途中的各个车站之间的道路状况、交通拥堵程度以及可能的自然因素（如天气变化）等不同，
  这些因素都会影响每条路径的通行时间。
  小明希望能选择一条花费时间最少的路线，以确保他能够尽快到达目的地。
输入描述：
  第一行包含两个正整数，第一个正整数 N 表示一共有 N 个公共汽车站，第二个正整数
  M表示有 M 条公路。 接下来为 M 行，每行包括三个整数，S、E 和 V，代表了从 S
  车站可以单向直达 E 车站，并且需要花费 V 单位的时间。
输出描述：
  输出一个整数，代表小明从起点到终点所花费的最小时间。
输入示例：
  7 9
  1 2 1
  1 3 4
  2 3 2
  2 4 5
  3 4 2
  4 5 3
  2 6 4
  5 7 4
  6 7 9
输出示例：
  12。*/
struct Edge {
  int to, val;
  Edge(int t, int v) : to(t), val(v) {}
};

int dijkstra(vector<list<Edge>>& edges, int n) {
  vector<int> minDist(n + 1, INT_MAX);
  vector<bool> visited(n + 1, 0);
  minDist[1] = 0;
  auto cmp = [](pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
  };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> que(
      cmp);
  que.push({1, 0});
  while (que.size()) {
    pair<int, int> cur = que.top();
    visited[cur.first] = true;
    que.pop();
    for (const Edge& e : edges[cur.first]) {
      if (!visited[e.to] && minDist[cur.first] + e.val < minDist[e.to]) {
        minDist[e.to] = minDist[cur.first] + e.val;
        que.push({e.to, minDist[e.to]});
      }
    }
  }
  return minDist[n] == INT_MAX ? -1 : minDist[n];
}

// 边数较少，使用邻接表的形式存储。小顶堆维护当前帧可到达的所有结点，及其距源点的代价
// 时间复杂度ElogE，E为边数，其和顶点数无关，因为每个边都处理了一次，为E，处理的过程时进入或弹出优先队列，为logE。空间复杂度V+E
// Edge记录每一条边的代价
class myComparison {
 public:
  bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return lhs.second > rhs.second;
  };
};
int dijkstra1(vector<list<Edge>>& edges, int n) {
  vector<int> minDist(n + 1, INT_MAX);
  vector<bool> visited(n + 1, false);
  // 小顶堆，维护待处理的，离原点近的结点。其为<结点，结点至源点的代价>
  auto cmp = [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return lhs.second > rhs.second;
  };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
  // 首个元素从1开始
  minDist[1] = 0;
  pq.push({1, 0});
  while (!pq.empty()) {
    // 1.找到当前距离源点代价最低的结点
    pair<int, int> cur = pq.top();
    pq.pop();
    // 有时1->3, 2->3均有代价，都在pq中，但是到3时，已经被处理过了
    if (visited[cur.first])
      continue;

    // 2.将其标记为已访问
    visited[cur.first] = true;
    // 3.更新剩余潜在可连接的结点，其距离源点代价
    for (Edge edge : edges[cur.first]) {
      if (!visited[edge.to] &&
          minDist[cur.first] + edge.val < minDist[edge.to]) {
        minDist[edge.to] = minDist[cur.first] + edge.val;
        pq.push({edge.to, minDist[edge.to]});
      }
    }
  }
  if (minDist[n] == INT_MAX)
    return -1;
  else
    return minDist[n];
}

int main() {
  int N = 7, M = 9;
  vector<list<Edge>> edges(N + 1);
  edges[1].push_back(Edge(2, 1));
  edges[1].push_back(Edge(3, 4));
  edges[2].push_back(Edge(3, 2));
  edges[2].push_back(Edge(4, 5));
  edges[3].push_back(Edge(4, 2));
  edges[4].push_back(Edge(5, 3));
  edges[2].push_back(Edge(6, 4));
  edges[5].push_back(Edge(7, 4));
  edges[6].push_back(Edge(7, 9));

  cout << dijkstra(edges, N) << endl;
  cout << dijkstra1(edges, N) << endl;

  return 0;
}