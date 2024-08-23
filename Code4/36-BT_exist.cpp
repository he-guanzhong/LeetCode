#include "head.h"
/* 79. 单词搜索
给定一个 m x n 二维字符网格 board 和一个字符串单词 word 。如果 word
存在于网格中，返回 true ；否则，返回 false 。
单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母不允许被重复使用。
示例 1：
  输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]],
        word = "ABCCED"
  输出：true
示例 2：
  输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]],
  word = "SEE"
  输出：true
示例 3：
  输入：board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]],
  word = "ABCB"
  输出：false */

bool dfs(vector<vector<char>>& board,
         string word,
         int x,
         int y,
         int index,
         vector<vector<bool>>& visited) {
  if (board[x][y] != word[index])
    return false;
  if (index >= word.size() - 1)
    return true;
  visited[x][y] = true;

  index++;
  int dir[] = {1, 0, -1, 0, 1};
  for (int k = 0; k < 4; k++) {
    int nextx = x + dir[k];
    int nexty = y + dir[k + 1];
    if (nextx < 0 || nextx >= board.size() || nexty < 0 ||
        nexty >= board[0].size() || visited[nextx][nexty] ||
        board[nextx][nexty] != word[index])
      continue;
    if (dfs(board, word, nextx, nexty, index, visited))
      return true;
  }
  index--;
  visited[x][y] = false;
  return false;
}
bool exist(vector<vector<char>>& board, string word) {
  int index = 0;
  vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), 0));
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      if (dfs(board, word, i, j, index, visited))
        return true;
    }
  }
  return false;
}

// 设置visited数组，记录结点访问过的情况。为了使主函数更简洁，故对任何结点都压入。
// 相应地，dfs1起始就要先做双方字符是否相等的判断。只有相等，才进入最终退出条件。
// 最终退出条件是，index表示word当前处理位，由于上一行已确保其相等于棋盘某值，故只要其等于size-1，可直接返回真。
// dfs1主体函数内，首、尾对visited赋值。排除四个方向及访问过的情况。依然直接压入结点。
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