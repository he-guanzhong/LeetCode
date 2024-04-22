#include "head.h"
/* 74. 搜索二维矩阵
给你一个满足下述两条属性的 m x n 整数矩阵：
    每行中的整数从左到右按非严格递增顺序排列。
    每行的第一个整数大于前一行的最后一个整数。

给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。
示例 1：
输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 3
输出：true
示例 2：
输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
输出：false */

bool searchMatrix(vector<vector<int>>& matrix, int target) {
  int m = matrix.size(), n = matrix[0].size();
  int i = m - 1, j = 0;
  while (i >= 0 && j < n) {
    if (target < matrix[i][j])
      i--;
    else if (target > matrix[i][j])
      j++;
    else
      return true;
  }
  return false;
}

// 可选从右上角，或坐下角开始搜索。时间复杂度O(m+n)
bool searchMatrix1(vector<vector<int>>& matrix, int target) {
  int i = 0, j = matrix[0].size() - 1;
  while (i < matrix.size() && j >= 0) {
    if (target < matrix[i][j])
      j--;
    else if (target > matrix[i][j])
      i++;
    else
      return true;
  }
  return false;
}

int main() {
  vector<vector<int>> matrix = {
      {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  cout << searchMatrix(matrix, 3) << " " << searchMatrix(matrix, 13) << " "
       << searchMatrix(matrix, 7) << endl;
  cout << searchMatrix1(matrix, 3) << " " << searchMatrix1(matrix, 13) << " "
       << searchMatrix1(matrix, 7) << endl;
  return 0;
}