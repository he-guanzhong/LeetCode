#include "head.h"
/* 207. 课程表
你这个学期必须选修 numCourses 门课程，记为 0 到 numCourses - 1 。
在选修某些课程之前需要一些先修课程。 先修课程按数组 prerequisites 给出，其中
prerequisites[i] = [ai, bi] ，表示如果要学习课程 ai 则 必须 先学习课程  bi 。
    例如，先修课程对 [0, 1] 表示：想要学习课程 0 ，你需要先完成课程 1 。
请你判断是否可能完成所有课程的学习？如果可以，返回 true ；否则，返回 false 。
示例 1：
输入：numCourses = 2, prerequisites = [[1,0]]
输出：true
解释：总共有 2 门课程。学习课程 1 之前，你需要完成课程 0 。这是可能的。
示例 2：
输入：numCourses = 2, prerequisites = [[1,0],[0,1]]
输出：false
解释：总共有 2 门课程。学习课程 1
之前，你需要先完成​课程 0 ；并且学习课程 0
之前，你还应先完成课程 1 。这是不可能的。*/

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
  unordered_map<int, vector<int>> umap;
  vector<int> inDeg(numCourses, 0);
  for (vector<int>& direct : prerequisites) {
    umap[direct[1]].push_back(direct[0]);
    inDeg[direct[0]]++;
  }
  queue<int> que;
  for (int i = 0; i < numCourses; i++) {
    if (inDeg[i] == 0)
      que.push(i);
  }
  int visited = 0;
  while (!que.empty()) {
    int i = que.front();
    que.pop();
    visited++;
    for (int j : umap[i]) {
      inDeg[j]--;
      if (inDeg[j] == 0)
        que.push(j);
    }
  }

  return visited == numCourses;
}

// dfs1搜索，拓扑排序。额外需要三个变量，edges记录统计过的，每个起点分别能到达什么终点。visited记录结点访问状态，0-未访问，1-搜索中，2-已搜索
// valid记录过程结果。首先一次遍历统计edges，注意标志位为B。其次对每个没有访问过的结点dfs1。
// dfs1对当前结点u先记录其搜索中。对其指向每一个v，若1-搜索中，则成环，不存在拓扑排序。若0-未搜索，进入下一层迭代。
// 回溯时valid为假可直接返回。为真则要记录u为2-已搜索。时间复杂度和空间复杂度均为O(m+n)
void dfs1(vector<vector<int>>& edges,
          vector<int>& visited,
          bool& valid,
          int u) {
  visited[u] = 1;
  for (int v : edges[u]) {
    if (visited[v] == 1) {
      valid = false;
      return;
    } else if (visited[v] == 0) {
      dfs1(edges, visited, valid, v);
      if (!valid)
        return;
    }
  }
  visited[u] = 2;
}
bool canFinish1(int numCourses, vector<vector<int>>& prerequisites) {
  vector<vector<int>> edges(numCourses);
  vector<int> visited(numCourses, 0);
  bool valid = true;
  for (const auto& info : prerequisites) {
    edges[info[1]].push_back(info[0]);  // 对每一个起点B，能到达的A压入vector
  }
  for (int i = 0; i < numCourses && valid; i++) {  // 注意valid条件
    if (!visited[i])                               // 没有访问过的结点
      dfs1(edges, visited, valid, i);
  }
  return valid;
}

// bfs，拓扑排序。统计每个结点指向edges，和每个节点入度indeg。对入度为0结点压入队列。队列弹出u时，减少其指向的v入度，入度为0的再压入
// 入度有两个作用，第一，选入度为0的作为que起始点，第二，只有经过删减入度后，其值为0的，才能作为新节点压入。
// 如此返回弹出元素个数visited，若其等于numCourse则所有均被反馈。时间复杂度和空间复杂度均为O(m+n)
bool canFinish2(int numCourses, vector<vector<int>>& prerequisites) {
  vector<vector<int>> edges(numCourses);
  vector<int> indeg(numCourses, 0);
  int visit = 0;
  for (const auto& info : prerequisites) {
    edges[info[1]].push_back(info[0]);  // 对每一个起点B，能到达的A压入vector
    indeg[info[0]]++;
  }
  queue<int> que;
  for (int i = 0; i < numCourses; i++) {  // 注意valid条件
    if (indeg[i] == 0)                    // 没有访问过的结点
      que.push(i);
  }
  while (!que.empty()) {
    visit++;
    int u = que.front();
    que.pop();
    for (int v : edges[u]) {
      indeg[v]--;
      if (indeg[v] == 0)
        que.push(v);
    }
  }
  return visit == numCourses;
}
int main() {
  int numCourses1 = 2;
  vector<vector<int>> prerequisites1 = {{1, 0}};
  int numCourses2 = 2;
  vector<vector<int>> prerequisites2 = {{1, 0}, {0, 1}};
  vector<vector<int>> prerequisites3 = {{1, 0}, {1, 2}, {0, 1}};

  cout << canFinish(2, prerequisites1) << " " << canFinish(2, prerequisites2)
       << " " << canFinish(3, prerequisites3) << endl;
  cout << canFinish1(2, prerequisites1) << " " << canFinish1(2, prerequisites2)
       << " " << canFinish1(3, prerequisites3) << endl;
  return 0;
}