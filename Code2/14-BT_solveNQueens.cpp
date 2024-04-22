#include <map>
#include "head.h"
/* 51. N 皇后
按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
n 皇后问题 研究的是如何将 n 个皇后放置在 n×n
的棋盘上，并且使皇后彼此之间不能相互攻击。
给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，该方案中 'Q' 和 '.'
分别代表了皇后和空位。
输入：n = 4
输出：[[".Q..","...Q","Q...","..Q."],["..Q.","Q...","...Q",".Q.."]]
解释：如上图所示，4 皇后问题存在两个不同的解法。 */

// 棋盘必须全部初始化为'.'。回溯函数传入深度，即行数row。退出条件为行数等于n。横向遍历列数col。如果该位置valid有效才进入下一层循环
// 有效valid函数，三个判断。1、固定列数，判断以上每一行是否有Q。2、从该起点同一层for，必须同步，沿左上方向寻找Q。3、右上方向寻找Q
// 注意：不必判断固定行数，每一列的值，因为该行其余元素必为'.'。
bool isValid(int n, int pos, int depth, vector<string>& path) {
  for (int i = 0; i < depth; i++) {
    if (path[i][pos] == 'Q')
      return false;
  }
  for (int i = depth, j = pos; i >= 0 && j >= 0; i--, j--) {
    if (path[i][j] == 'Q')
      return false;
  }
  for (int i = depth, j = pos; i >= 0 && j < n; i--, j++) {
    if (path[i][j] == 'Q')
      return false;
  }
  return true;
}
void backtracking(int n,
                  int depth,
                  vector<string>& path,
                  vector<vector<string>>& result) {
  if (depth == n) {
    result.push_back(path);
    return;
  }
  for (int i = 0; i < n; i++) {
    if (isValid(n, i, depth, path)) {
      path[depth][i] = 'Q';
      backtracking(n, depth + 1, path, result);
      path[depth][i] = '.';
    }
  }
}
vector<vector<string>> solveNQueens(int n) {
  vector<vector<string>> result;
  vector<string> path(n, string(n, '.'));
  backtracking(n, 0, path, result);
  return result;
}

// 递归广度是棋盘宽度，递归深度是棋盘高度，故外置result，单个成功路径可初始化为n*n全为'.'的棋盘，作为参数传入
// 由上至下深度搜索，退出条件为行深度row==n，故需额外记录并传入参数row。不能使用size，因为初始化时已经相等
// 广度搜索方向为col，只要可以满足Q放置棋盘方案可行，即赋值。然后递归下一层row+1，回溯时该棋盘位置恢复'.'
// 判断某位置是否可以放置Q：1.同列内不同行数位置未出现过Q；2.左上方45度所有位置未出现过Q；3.右上方135度位置未出现过Q
// 同层不必判断是否存在Q，因为递归时每层只会赋值一个Q。时间复杂度n!，空间复杂度n

vector<vector<string>> result1;
bool isValid1(int row, int col, vector<string>& chessboard, int n) {
  for (int i = 0; i < row; i++) {
    if (chessboard[i][col] == 'Q')
      return false;
  }
  for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
    if (chessboard[i][j] == 'Q')
      return false;
  }
  for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) {
    if (chessboard[i][j] == 'Q')
      return false;
  }
  return true;
}
void backtracking1(int n, int row, vector<string>& chessboard) {
  if (row == n) {  // 深度行数达到n
    result1.push_back(chessboard);
    return;
  }
  for (int col = 0; col < n; col++) {
    if (isValid1(row, col, chessboard, n)) {
      chessboard[row][col] = 'Q';
      backtracking1(n, row + 1, chessboard);
      chessboard[row][col] = '.';
    }
  }
}
vector<vector<string>> solveNQueens1(int n) {
  result1.clear();
  vector<string> chessboard(n, string(n, '.'));  // 初始化结果容器
  backtracking1(n, 0, chessboard);
  return result1;
}

int main() {
  printMat(solveNQueens(4));
  printMat(solveNQueens(3));
  printMat(solveNQueens(1));
  printMat(solveNQueens1(4));
  printMat(solveNQueens1(3));
  printMat(solveNQueens1(1));
  return 0;
}