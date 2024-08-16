#include "head.h"
/* 240. 搜索二维矩阵 II
编写一个高效的算法来搜索 m x n 矩阵 matrix 中的一个目标值 target
。该矩阵具有以下特性： 每行的元素从左到右升序排列。 每列的元素从上到下升序排列。
示例 1：
  输入：matrix =
    [[1,4,7,11,15],
    [2,5,8,12,19],
    [3,6,9,16,22],
    [10,13,14,17,24],
    [18,21,23,26,30]],
        target = 5
  输出：true
示例 2：
  输入：matrix =
    [[1,4,7,11,15],[2,5,8,12,19],[3,6,9,16,22],[10,13,14,17,24],[18,21,23,26,30]],
        target = 20
  输出：false */

bool searchMatrix(vector<vector<int>>& matrix, int target) {
  int i = 0, j = matrix[0].size() - 1;
  while (i < matrix.size() && j >= 0) {
    if (matrix[i][j] < target)
      i++;
    else if (matrix[i][j] > target)
      j--;
    else
      return true;
  }
  return false;
}

// 首选Z形查找。矩阵大小m*n，从右上角[0,n-1]开始，若matrix[i][j]小，则向左j--，若matrix[i][j]大，则向下i++。最终找不到即返回假。
// 推荐从左下角往上找，不推荐右上角，因为可能matrix为空，就没有第一行，故不能直接访问matrix[0]。因为时间复杂度O(m+n)
bool searchMatrix1(vector<vector<int>>& matrix, int target) {
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

// 二分查找，lower_bound函数，对每一行二分查找。时间复杂度mlog(n)。
bool searchMatrix2(vector<vector<int>>& matrix, int target) {
  for (const auto& row : matrix) {
    auto it = lower_bound(row.begin(), row.end(), target);
    if (it != row.end() && *it == target)
      return true;
  }
  return false;
}

int main() {
  vector<vector<int>> matrix1 = {{1, 4, 7, 11, 15},
                                 {2, 5, 8, 12, 19},
                                 {3, 6, 9, 16, 22},
                                 {10, 13, 14, 17, 24},
                                 {18, 21, 23, 26, 30}};
  vector<vector<int>> matrix2 = matrix1;
  cout << searchMatrix(matrix1, 5) << " " << searchMatrix(matrix2, 20) << endl;
  cout << searchMatrix1(matrix1, 5) << " " << searchMatrix1(matrix2, 20)
       << endl;
  return 0;
}