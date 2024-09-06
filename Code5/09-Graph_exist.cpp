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
  输出：false
提示：
    m == board.length
    n = board[i].length
    1 <= m, n <= 6
    1 <= word.length <= 15
    board 和 word 仅由大小写英文字母组成
进阶：你可以使用搜索剪枝的技术来优化解决方案，使其在 board
更大的情况下可以更快解决问题？*/

bool dfs(vector<vector<char>>& board,
         string word,
         vector<vector<bool>>& visited,
         int x,
         int y,
         int index) {
  if (index == word.size())
    return true;
  visited[x][y] = true;
  int dir[] = {1, 0, -1, 0, 1};
  for (int k = 0; k < 4; k++) {
    int nextx = x + dir[k];
    int nexty = y + dir[k + 1];
    if (nextx < 0 || nextx >= board.size() || nexty < 0 ||
        nexty >= board[0].size() || visited[nextx][nexty] ||
        board[nextx][nexty] != word[index])
      continue;
    if (dfs(board, word, visited, nextx, nexty, index + 1))
      return true;
  }
  visited[x][y] = false;
  return false;
}

bool exist(vector<vector<char>>& board, string word) {
  vector<vector<bool>> visited(board.size(), vector<bool>(board[0].size(), 0));
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      if (board[i][j] == word[0] && dfs(board, word, visited, i, j, 1))
        return true;
    }
  }
  return false;
}

bool dfs1(vector<vector<char>>& board,
          string word,
          int x,
          int y,
          int k,
          vector<vector<bool>>& visited) {
  if (k == word.size() - 1)
    return true;
  visited[x][y] = true;
  k++;
  int dir[] = {1, 0, -1, 0, 1};
  for (int i = 0; i < 4; i++) {
    int newX = x + dir[i];
    int newY = y + dir[i + 1];
    if (newX < 0 || newX >= board.size() || newY < 0 ||
        newY >= board[0].size() || visited[newX][newY] ||
        word[k] != board[newX][newY])
      continue;
    if (dfs1(board, word, newX, newY, k, visited))
      return true;
  }
  visited[x][y] = false;
  return false;
}
bool exist1(vector<vector<char>>& board, string word) {
  int m = board.size(), n = board[0].size();
  vector<vector<bool>> visited(m, vector<bool>(n, false));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == word[0] && dfs1(board, word, i, j, 0, visited))
        return true;
    }
  }
  return false;
}

int main() {
  vector<vector<char>> board1 = {
      {'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}};
  vector<vector<char>> board2 = {
      {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
      {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'},
      {'A', 'A', 'A', 'A', 'A', 'A'}, {'A', 'A', 'A', 'A', 'A', 'A'}};
  string word1 = "ABCCED", word2 = "SEE", word3 = "ABCB",
         word4 = "AAAAAAAAAAAAAAB";
  cout << exist(board1, word1) << " " << exist(board1, word2) << " "
       << exist(board1, word3) << " " << exist(board2, word4) << endl;
  cout << exist1(board1, word1) << " " << exist1(board1, word2) << " "
       << exist1(board1, word3) << " " << exist1(board2, word4) << endl;
  return 0;
}