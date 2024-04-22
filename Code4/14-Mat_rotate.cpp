#include "head.h"
/* 48. 旋转图像
给定一个 n × n 的二维矩阵 matrix 表示一个图像。请你将图像顺时针旋转 90 度。
你必须在 原地 旋转图像，这意味着你需要直接修改输入的二维矩阵。请不要
使用另一个矩阵来旋转图像。
示例 1：
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[[7,4,1],[8,5,2],[9,6,3]]
示例 2：
输入：matrix = [[5,1,9,11],[2,4,8,10],[13,3,6,7],[15,14,12,16]]
输出：[[15,13,2,5],[14,3,4,1],[12,6,8,9],[16,7,10,11]] */

void rotate(vector<vector<int>>& matrix) {
  int n = matrix.size();
  for (int i = 0; i < n / 2; i++) {
    for (int j = 0; j < n; j++)
      swap(matrix[i][j], matrix[n - 1 - i][j]);
  }
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++)
      swap(matrix[i][j], matrix[j][i]);
  }
}

// 两次翻转法。顺时针旋转90，[i,j]转化为[j,n-1-i]，即原列数直接变行数，n-1减去原行数为新列数。故先上下水平反转。变为[n-1-i,j]
// 第二次沿左上右下对角线反转，变为[j,n-1-i]，j范围[0,i]，反转半边即可。C语言swap要使用指针和取址符号。
void rotate1(vector<vector<int>>& matrix) {
  int n = matrix.size();
  for (int i = 0; i < n / 2; i++) {
    for (int j = 0; j < n; j++)
      swap(matrix[i][j], matrix[n - 1 - i][j]);
  }
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++)
      swap(matrix[i][j], matrix[j][i]);
  }
}

int main() {
  vector<vector<int>> matrix1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  vector<vector<int>> matrix2 = {
      {5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
  rotate(matrix1);
  rotate(matrix2);
  printMat(matrix1);
  printMat(matrix2);
  matrix1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  matrix2 = {{5, 1, 9, 11}, {2, 4, 8, 10}, {13, 3, 6, 7}, {15, 14, 12, 16}};
  rotate1(matrix1);
  rotate1(matrix2);
  printMat(matrix1);
  printMat(matrix2);
  return 0;
}