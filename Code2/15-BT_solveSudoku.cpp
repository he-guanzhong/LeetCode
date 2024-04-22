#include "head.h"
/* 37. 解数独
编写一个程序，通过填充空格来解决数独问题。
数独的解法需 遵循如下规则：
    数字 1-9 在每一行只能出现一次。
    数字 1-9 在每一列只能出现一次。
    数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。（请参考示例图）
数独部分空格内已填入了数字，空白格用 '.' 表示。
{
  {'5', '3', '4', '6', '7', '8', '9', '1', '2'},
      {'6', '7', '2', '1', '9', '5', '3', '4', '8'},
      {'1', '9', '8', '3', '4', '2', '5', '6', '7'},
      {'8', '5', '9', '7', '6', '1', '4', '2', '3'},
      {'4', '2', '6', '8', '5', '3', '7', '9', '1'},
      {'7', '1', '3', '9', '2', '4', '8', '5', '6'},
      {'9', '6', '1', '5', '3', '7', '2', '8', '4'},
      {'2', '8', '7', '4', '1', '9', '6', '3', '5'}, {
    '3', '4', '5', '2', '8', '6', '1', '7', '9'
  } */

// 要填入的数字类型是char，不是int。只有一种解，树枝遍历，回溯函数带返回值。对矩阵每一个为'.'的位置，[row,col],依次填入'1'到'9'。
// 只要数据合规valid即填入，并进入下一轮递归，一旦到达终点true，则一路返回true。
// 终止条件为，9个数字都试过了，仍不满足，返回false。如此即可回溯'.'赋值，并在横向遍历中，重新对此位置赋值。
// 程序最终终止于，遍历了所有结点，所有空都被填满，即没有'.'。此时返回true。如此即可
bool isValid(int row, int col, char num, vector<vector<char>>& board) {
  for (int i = 0; i < 9; i++) {
    if (board[row][i] == num)
      return false;
    if (board[i][col] == num)
      return false;
  }
  for (int i = row / 3 * 3; i < row / 3 * 3 + 3; i++) {
    for (int j = col / 3 * 3; j < col / 3 * 3 + 3; j++) {
      if (board[i][j] == num)
        return false;
    }
  }
  return true;
}
bool backtracking(vector<vector<char>>& board) {
  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (board[row][col] == '.') {
        for (char i = '1'; i <= '9'; i++) {
          if (isValid(row, col, i, board)) {
            board[row][col] = i;
            if (backtracking(board))
              return true;
            board[row][col] = '.';
          }
        }
        return false;
      }
    }
  }
  return true;
}
void solveSudoku(vector<vector<char>>& board) {
  backtracking(board);
}

// 二维数组的回溯，对每一个有左右坐标的空，分别进行‘1’-‘9’的判断，如果可行，即填入。如9个数字都不行，则返回false
// 最终无false返回，说明可行有解，返回true。故一路true返回原点
// 判断条件为输入行数、列数、值、矩阵。同行、同列出现相等值不行。对找到3*3矩阵起点内二维搜索找到等值不行
// 时间复杂度O=9^m，m为‘.'的数目。空间复杂度n^2
bool isValid1(int row, int col, char val, vector<vector<char>>& board) {
  for (int i = 0; i < 9; i++) {
    if (board[i][col] == val)
      return false;
  }
  for (int i = 0; i < 9; i++) {
    if (board[row][i] == val)
      return false;
  }
  int startRow = row / 3 * 3;
  int startCol = col / 3 * 3;
  for (int i = startRow; i < startRow + 3; i++) {
    for (int j = startCol; j < startCol + 3; j++) {
      if (board[i][j] == val)
        return false;
    }
  }
  return true;
}
bool backtracking1(vector<vector<char>>& board) {
  for (int row = 0; row < board.size(); row++) {
    for (int col = 0; col < board[0].size(); col++) {
      if (board[row][col] == '.') {
        for (char k = '1'; k <= '9'; k++) {
          if (isValid1(row, col, k, board)) {
            board[row][col] = k;
            if (backtracking1(board))
              return true;
            board[row][col] = '.';
          }
        }
        return false;  // 9个数字都不符合
      }
    }
  }
  return true;
}

void solveSudoku1(vector<vector<char>>& board) {
  backtracking1(board);
}

int main() {
  vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  vector<vector<char>> board1 = board;
  solveSudoku(board);
  printMat(board);
  solveSudoku(board1);
  printMat(board1);
  /*   vector<vector<int>> test = {{1, 2, 3}, {4, 5, 6}};
    printMat(test); */
  return 0;
}
