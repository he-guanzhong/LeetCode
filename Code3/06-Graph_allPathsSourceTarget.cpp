#include "head.h"
/* 797. 所有可能的路径
给你一个有 n 个节点的 有向无环图（DAG），请你找出所有从节点 0 到节点 n-1
的路径并输出（不要求按特定顺序） graph[i] 是一个从节点 i
可以访问的所有节点的列表（即从节点 i 到节点 graph[i][j]存在一条有向边）。
示例 1： 输入：graph = [[1,2],[3],[3],[]]
输出：[[0,1,3],[0,2,3]]
解释：有两条路径 0
-> 1 -> 3 和 0 -> 2 -> 3
示例 2：
输入：graph = [[4,3,1],[3,2,4],[3],[4],[]]
输出：[[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]] */

// 先压入0节点，传参为刚刚压入的节点编号，返回条件是其编号等于最后一个下标。for循环内遍历当前下标可以到达的节点。压入、判断、弹出
void dfs(vector<vector<int>>& graph,
         int index,
         vector<int>& path,
         vector<vector<int>>& result) {
  if (index == graph.size() - 1) {
    result.push_back(path);
    return;
  }
  for (int i = 0; i < graph[index].size(); i++) {
    path.push_back(graph[index][i]);
    dfs(graph, graph[index][i], path, result);
    path.pop_back();
  }
}

vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph) {
  vector<vector<int>> result;
  vector<int> path;
  path.push_back(0);
  dfs(graph, 0, path, result);
  return result;
}

// 假定当前已遍历节点为x，退出条件即为遍历到的节点，已到达图的最末尾节点graph.size()-1，则将path压入result返回，因为有向无环图，必可以到终点
// 深度优先搜索，对于该节点x，将其链接的下一层节点graph[x][i]，先压入path，然后进入递归，回溯时要pop弹出本层曾经压入的节点。
// 由于x定义为，已遍历的节点，故在函数一开始，就将起始点0压入。
vector<vector<int>> result1;
vector<int> path1;
void dfs1(vector<vector<int>>& graph, int x) {
  if (x == graph.size() - 1) {
    result1.push_back(path1);
    return;
  }
  for (int i = 0; i < graph[x].size(); i++) {
    path1.push_back(graph[x][i]);
    dfs1(graph, graph[x][i]);
    path1.pop_back();
  }
}
vector<vector<int>> allPathsSourceTarget1(vector<vector<int>>& graph) {
  result1.clear();
  path1.clear();
  path1.push_back(0);
  dfs1(graph, 0);
  return result1;
}

int main() {
  vector<vector<int>> graph1 = {{1, 2}, {3}, {4}, {}};
  vector<vector<int>> graph2 = {{4, 3, 1}, {3, 2, 4}, {3}, {4}, {}};
  printMat(allPathsSourceTarget(graph1));
  printMat(allPathsSourceTarget(graph2));
  printMat(allPathsSourceTarget1(graph1));
  printMat(allPathsSourceTarget1(graph2));
  return 0;
}