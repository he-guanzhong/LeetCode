#include "head.h"
/* 841. 钥匙和房间
有 n 个房间，房间按从 0 到 n - 1 编号。最初，除 0
号房间外的其余所有房间都被锁住。你的目标是进入所有的房间。然而，你不能在没有获得钥匙的时候进入锁住的房间。
当你进入一个房间，你可能会在里面找到一套不同的钥匙，每把钥匙上都有对应的房间号，即表示钥匙可以打开的房间。你可以拿上所有钥匙去解锁其他房间。
给你一个数组 rooms 其中 rooms[i] 是你进入 i 号房间可以获得的钥匙集合。如果能进入
所有 房间返回 true，否则返回 false。
示例 1：
  输入：rooms = [[1],[2],[3],[]]
  输出：true
  解释：
    我们从 0 号房间开始，拿到钥匙 1。
    之后我们去 1 号房间，拿到钥匙 2。
    然后我们去 2 号房间，拿到钥匙 3。
    最后我们去了 3 号房间。
    由于我们能够进入每个房间，我们返回 true。
示例 2：
  输入：rooms = [[1,3],[3,0,1],[2],[0]]
  输出：false
  解释：我们不能进入 2 号房间。 */

void dfs(vector<vector<int>>& rooms, int cur, vector<bool>& visited) {
  visited[cur] = true;
  for (int i = 0; i < rooms[cur].size(); i++) {
    if (!visited[rooms[cur][i]])
      dfs(rooms, rooms[cur][i], visited);
  }
}
bool canVisitAllRooms(vector<vector<int>>& rooms) {
  vector<bool> visited(rooms.size(), false);
  dfs(rooms, 0, visited);
  for (const bool& i : visited) {
    if (!i)
      return false;
  }
  return true;
}

// 深度优先搜索，设立visited数组记录是否访问过。传参为当前房间，结点在本层处理。访问过即直接返回。没访问过就标记访问，并执行下一层
// 深度优先搜索。方式一，在递归中处理，标记当前结点
void dfs2(vector<vector<int>>& rooms, int key, vector<bool>& visited) {
  if (visited[key] == true)
    return;
  visited[key] = true;
  for (int i : rooms[key])
    dfs2(rooms, i, visited);
}
bool canVisitAllRooms2(vector<vector<int>>& rooms) {
  vector<bool> visited(rooms.size(), false);
  dfs2(rooms, 0, visited);
  for (bool i : visited) {
    if (i == false)
      return false;
  }
  return true;
}

// 深度优先搜索，在循环内部即判断，不满足不进入下一层。该方法要求，必须在函数本体内
void dfs1(vector<vector<int>>& rooms, int key, vector<bool>& visited) {
  for (int i : rooms[key]) {
    if (visited[i] == false) {
      visited[i] = true;
      dfs1(rooms, i, visited);
    }
  }
}
bool canVisitAllRooms1(vector<vector<int>>& rooms) {
  vector<bool> visited(rooms.size(), false);
  visited[0] = true;  // 必须先将0结点设为访问过
  dfs1(rooms, 0, visited);
  for (bool i : visited) {
    if (i == false)
      return false;
  }
  return true;
}

// 自制，广度优先搜索方法
bool canVisitAllRooms3(vector<vector<int>>& rooms) {
  int m = rooms.size();
  vector<bool> visited(m, false);
  visited[0] = true;
  queue<int> que;
  que.push(0);
  while (!que.empty()) {
    int key = que.front();
    que.pop();
    for (int i = 0; i < rooms[key].size(); i++) {
      if (visited[rooms[key][i]] == false) {
        que.push(rooms[key][i]);
        visited[rooms[key][i]] = true;
      }
    }
  }
  for (int i = 0; i < m; i++) {
    if (visited[i] == false)
      return false;
  }
  return true;
}

int main() {
  vector<vector<int>> rooms1 = {{1}, {2}, {3}, {0}};
  vector<vector<int>> rooms2 = {{1, 3}, {3, 0, 1}, {2}, {0}};
  cout << canVisitAllRooms(rooms1) << " " << canVisitAllRooms(rooms2) << endl;
  cout << canVisitAllRooms1(rooms1) << " " << canVisitAllRooms1(rooms2) << endl;

  return 0;
}