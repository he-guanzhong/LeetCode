#include "head.h"
/* 74. 搜索二维矩阵
给你一个满足下述两条属性的 m x n 整数矩阵：
    每行中的整数从左到右按非严格递增顺序排列。
    每行的第一个整数大于前一行的最后一个整数。
给你一个整数 target ，如果 target 在矩阵中，返回 true ；否则，返回 false 。
示例 1：
  输入：matrix = [[1,3,5,7],
                  [10,11,16,20],
                  [23,30,34,60]], target = 3
  输出：true
示例 2：
  输入：matrix = [[1,3,5,7],[10,11,16,20],[23,30,34,60]], target = 13
  输出：false */

bool searchMatrix(vector<vector<int>>& matrix, int target) {
  int m = matrix.size(), n = matrix[0].size();
  int i = 0, j = n - 1;
  while (i < m && j >= 0) {
    if (matrix[i][j] > target)
      j--;
    else if (matrix[i][j] < target)
      i++;
    else
      return true;
  }
  return false;
}

// 注意和题目
// 搜索二维矩阵II的区别。一次二分查找，将二维矩阵拼接为一维数组。时间复杂度O(logmn)
bool searchMatrix1(vector<vector<int>>& matrix, int target) {
  int m = matrix.size(), n = matrix[0].size();
  int left = 0, right = m * n - 1;
  while (left <= right) {
    int mid = left + ((right - left) >> 1);
    int num = matrix[mid / n][mid % n];
    if (num < target)
      left = mid + 1;
    else if (num > target)
      right = mid - 1;
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