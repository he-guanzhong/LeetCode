#include "head.h"
/* 73. 矩阵置零
给定一个 m x n 的矩阵，如果一个元素为 0 ，则将其所在行和列的所有元素都设为 0
。请使用 原地 算法。
示例 1：
输入：matrix = [[1,1,1],[1,0,1],[1,1,1]]
输出：[[1,0,1],[0,0,0],[1,0,1]]
示例 2：
输入：matrix = [[0,1,2,0],[3,4,5,2],[1,3,1,5]]
输出：[[0,0,0,0],[0,4,5,0],[0,3,1,0]]
*/

// 核心是以第一行、第一列标记需要置0的坐标。如此首行、首列原始含0信息会被破坏，故要额外记录首行、首列含0信息，并事后统一赋0
// 实际可以单独孤立首列，首行若存在原始0，则第一遍将首行全部赋值为0，进而影响全矩阵为0，故需从下至上遍历，使原始0最后处理
void setZeroes(vector<vector<int>>& matrix) {
  bool rowFlg = false, colFlg = false;
  int m = matrix.size(), n = matrix[0].size();
  for (int i = 0; i < m; i++) {
    if (matrix[i][0] == 0)
      colFlg = true;
    for (int j = 1; j < n; j++) {
      if (matrix[i][j] == 0) {
        matrix[0][j] = 0;
        matrix[i][0] = 0;
      }
    }
  }
  for (int i = m - 1; i >= 0; i--) {
    for (int j = 1; j < n; j++) {
      if (matrix[i][0] == 0 || matrix[0][j] == 0)
        matrix[i][j] = 0;
    }
    if (colFlg)
      matrix[i][0] = 0;
  }
}

// 只用一个标记变量，记录首列是否有0状态。一次遍历首列，先判断首列是否含0，再根据该行（除第一列外）是否有0，对首行元素置0。
// 二次从下至上，遍历除首列外其余元素，若首行、首列中含0，则置0。其后，看首列原始含0状态，对首列置0。不得从上至下，否则全矩阵置0
void setZeroes1(vector<vector<int>>& matrix) {
  int m = matrix.size(), n = matrix[0].size();
  bool colFlg = false;
  for (int i = 0; i < m; i++) {
    if (matrix[i][0] == 0)
      colFlg = true;
    for (int j = 1; j < n; j++) {
      if (matrix[i][j] == 0)
        matrix[i][0] = matrix[0][j] = 0;
    }
  }
  for (int i = m - 1; i >= 0; i--) {
    for (int j = 1; j < n; j++) {
      if (matrix[i][0] == 0 || matrix[0][j] == 0)
        matrix[i][j] = 0;
    }
    if (colFlg)
      matrix[i][0] = 0;
  }
}
// 特殊标记首行、首列元素是否有0状态，除首行、首列外其余元素均被首行、列标记决定。对除首行、首列外其余元素检测是否有0，如有，则在首行、首列中标记。
// 根据首行、首列0状态，对除首行、首列外元素，统一置0。最后，如首行、首列原始有0，在统一对其置0。不得先对首行、首列取0，否则全矩阵都为0。
// 时间复杂度O(mn)，空间复杂度O(2)，因为只申请了两个常数
void setZeroes2(vector<vector<int>>& matrix) {
  int m = matrix.size(), n = matrix[0].size();
  bool rowFlg = false, colFlg = false;
  for (int i = 0; i < m; i++) {
    if (matrix[i][0] == 0)
      colFlg = true;
  }
  for (int j = 0; j < n; j++) {
    if (matrix[0][j] == 0)
      rowFlg = true;
  }
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      if (matrix[i][j] == 0) {
        matrix[0][j] = 0;
        matrix[i][0] = 0;
      }
    }
  }
  for (int i = 1; i < m; i++) {
    for (int j = 1; j < n; j++) {
      if (matrix[i][0] == 0 || matrix[0][j] == 0)
        matrix[i][j] = 0;
    }
  }
  if (colFlg) {
    for (int i = 0; i < m; i++)
      matrix[i][0] = 0;
  }
  if (rowFlg) {
    for (int j = 0; j < n; j++)
      matrix[0][j] = 0;
  }
}

// 方法一，标记数组。对出现过0的位置标记为true。二次遍历中对标记位置零。时间复杂度O(mn)，空间复杂度O(m+n)
void setZeroes3(vector<vector<int>>& matrix) {
  vector<pair<int, int>> mark;
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[0].size(); j++) {
      if (matrix[i][j] == 0)
        mark.push_back({i, j});
    }
  }
  for (int k = 0; k < mark.size(); k++) {
    int x = mark[k].first;
    int y = mark[k].second;
    for (int i = 0; i < matrix.size(); i++)
      matrix[i][y] = 0;
    for (int j = 0; j < matrix[0].size(); j++)
      matrix[x][j] = 0;
  }
}

int main() {
  vector<vector<int>> matrix1 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  vector<vector<int>> matrix2 = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
  setZeroes(matrix1);
  setZeroes(matrix2);
  printMat(matrix1);
  printMat(matrix2);
  matrix1 = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};
  matrix2 = {{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}};
  setZeroes1(matrix1);
  setZeroes1(matrix2);
  printMat(matrix1);
  printMat(matrix2);
  return 0;
}