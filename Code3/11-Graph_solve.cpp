#include "head.h"
/* 130. 被围绕的区域
给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' ，找到所有被 'X'
围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。
示例 1：
输入：board =
[["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
输出：[["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
解释：被围绕的区间不会存在于边界上，换句话说，任何边界上的 'O' 都不会被填充为
'X'。 任何不在边界上，或不与边界上的 'O' 相连的 'O' 最终都会被填充为
'X'。如果两个元素在水平或垂直方向相邻，则称它们是“相连”的。
示例 2：
输入：board = [["X"]]
输出：[["X"]] */

// 分两步，一、四周边界遍历，将O特殊标记为A；二、全图遍历，先中间O改为X，再A改为O，次序不得颠倒
// dfs遍历过程中，注意跳过X和已经标记过的A。
void dfs(vector<vector<char>>& board, int x, int y) {
  board[x][y] = 'Y';
  int dir[] = {1, 0, -1, 0, 1};
  for (int i = 0; i < 4; i++) {
    int nextX = x + dir[i];
    int nextY = y + dir[i + 1];
    if (nextX < 0 || nextX >= board.size() || nextY < 0 ||
        nextY >= board[0].size() || board[nextX][nextY] == 'X' ||
        board[nextX][nextY] == 'Y')
      continue;
    dfs(board, nextX, nextY);
  }
}
void solve(vector<vector<char>>& board) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      if (board[i][j] == 'O' && (i == 0 || i == board.size() - 1 || j == 0 ||
                                 j == board[0].size() - 1))
        dfs(board, i, j);
    }
  }
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      if (board[i][j] == 'O')
        board[i][j] = 'X';
      if (board[i][j] == 'Y')
        board[i][j] = 'O';
    }
  }
}

// 保留只有四周连接的O，分两步：一、使用dfs将四周连接O特殊标记（例如A），
// 二、遍历全图，将中央O改为X，四周A改为O，注意次序不得颠倒。
int dir[4][2] = {1, 0, -1, 0, 0, 1, 0, -1};
void dfs1(vector<vector<char>>& board, int x, int y) {
  board[x][y] = 'A';
  for (int i = 0; i < 4; i++) {
    int nextX = x + dir[i][0];
    int nextY = y + dir[i][1];
    if (nextX < 0 || nextX >= board.size() || nextY < 0 ||
        nextY >= board[0].size())
      continue;
    if (board[nextX][nextY] == 'X' || board[nextX][nextY] == 'A')
      continue;
    dfs1(board, nextX, nextY);
  }
}
void solve1(vector<vector<char>>& board) {
  int m = board.size(), n = board[0].size();
  for (int i = 0; i < m; i++) {
    if (board[i][0] == 'O')
      dfs1(board, i, 0);
    if (board[i][n - 1] == 'O')
      dfs1(board, i, n - 1);
  }
  for (int j = 0; j < n; j++) {
    if (board[0][j] == 'O')
      dfs1(board, 0, j);
    if (board[m - 1][j] == 'O')
      dfs1(board, m - 1, j);
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == 'O')
        board[i][j] = 'X';
      if (board[i][j] == 'A')
        board[i][j] = 'O';
    }
  }
}

int main() {
  vector<vector<char>> board1 = {{'X', 'X', 'X', 'X'},
                                 {'X', 'O', 'O', 'X'},
                                 {'X', 'X', 'O', 'X'},
                                 {'X', 'O', 'X', 'X'}};
  vector<vector<char>> board2 = {{'X'}};
  vector<vector<char>> board3 = {
      {'O', 'O', 'O'}, {'O', 'O', 'O'}, {'O', 'O', 'O'}};
  vector<vector<char>> board4 = board1;
  vector<vector<char>> board5 = board2;
  vector<vector<char>> board6 = board3;
  solve(board1);
  solve(board2);
  solve(board3);
  printMat(board1);
  printMat(board2);
  printMat(board3);
  solve(board4);
  solve(board5);
  solve(board6);
  printMat(board4);
  printMat(board5);
  printMat(board6);
  return 0;
}