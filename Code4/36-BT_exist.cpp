#include "head.h"
/* 79. 单词搜索
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word
存在于网格中，返回 true ；否则，返回 false 。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
示例 1：
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
"ABCCED" 输出：true
示例 2：
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
"SEE" 输出：true
示例 3：
输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word =
"ABCB" 输出：false */

bool dfs(vector<vector<char>>& board,
         string word,
         int x,
         int y,
         int z,
         vector<vector<bool>>& visited) {
  if (board[x][y] != word[z])
    return false;
  if (z == word.size() - 1)
    return true;
  int m = board.size(), n = board[0].size();
  visited[x][y] = true;
  int dir[] = {1, 0, -1, 0, 1};
  for (int i = 0; i < 4; i++) {
    int newX = x + dir[i];
    int newY = y + dir[i + 1];
    if (newX < 0 || newX >= m || newY < 0 || newY >= n || visited[newX][newY] ||
        board[newX][newY] != word[z + 1])
      continue;
    if (dfs(board, word, newX, newY, z + 1, visited))
      return true;
  }
  visited[x][y] = false;
  return false;
}
bool exist(vector<vector<char>>& board, string word) {
  vector<vector<bool>> visited(board.size(),
                               vector<bool>(board[0].size(), false));
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      if (dfs(board, word, i, j, 0, visited))
        return true;
    }
  }
  return false;
}

// 设置visited数组，记录结点访问过的情况。主函数中对任何结点都压入。dfs1中做不等的判断。退出条件是index，即word当前位置等于size-1。
// dfs1函数内，首、尾对visited赋值。排除四个方向及访问过的情况。依然直接压入结点。
// 由于只找到一条满足的路径即可。故dfs1函数返回值bool，只要为true，可一路返回最上一层
bool dfs1(vector<vector<char>>& board,
          string word,
          vector<vector<bool>>& visited,
          int x,
          int y,
          int index) {
  if (board[x][y] != word[index])
    return false;
  if (index == word.size() - 1)
    return true;
  visited[x][y] = true;
  int dir[] = {1, 0, -1, 0, 1};
  for (int i = 0; i < 4; i++) {
    int newX = x + dir[i];
    int newY = y + dir[i + 1];
    if (newX < 0 || newX >= board.size() || newY < 0 ||
        newY >= board[0].size() || visited[newX][newY] == true)
      continue;
    if (dfs1(board, word, visited, newX, newY, index + 1))
      return true;
  }
  visited[x][y] = false;
  return false;
}
bool exist1(vector<vector<char>>& board, string word) {
  vector<vector<bool>> visited(board.size(),
                               vector<bool>(board[0].size(), false));
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      if (dfs1(board, word, visited, i, j, 0))
        return true;
    }
  }
  return false;
}

int main() {
  vector<vector<char>> board1 = {
      {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  vector<vector<char>> board2 = {{'a'}};
  string word1 = "ABCCED", word2 = "SEE", word3 = "ABCB", word4 = "a";
  cout << exist(board1, word1) << " " << exist(board1, word2) << " "
       << exist(board1, word3) << " " << exist(board2, word4) << endl;
  cout << exist1(board1, word1) << " " << exist1(board1, word2) << " "
       << exist1(board1, word3) << " " << exist1(board2, word4) << endl;
  return 0;
}