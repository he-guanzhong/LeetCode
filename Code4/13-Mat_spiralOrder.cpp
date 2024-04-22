#include "head.h"
/* 54. 螺旋矩阵
给你一个 m 行 n 列的矩阵 matrix ，请按照 顺时针螺旋顺序 ，返回矩阵中的所有元素。
示例 1：
输入：matrix = [[1,2,3],[4,5,6],[7,8,9]]
输出：[1,2,3,6,9,8,7,4,5]
示例 2：
输入：matrix = [[1,2,3,4],[5,6,7,8],[9,10,11,12]]
输出：[1,2,3,4,8,12,11,10,9,5,6,7]
*/

vector<int> spiralOrder(vector<vector<int>>& matrix) {
  vector<int> ans;
  int m = matrix.size(), n = matrix[0].size();
  int left = 0, right = n - 1, up = 0, down = m - 1;
  while (left <= right && up <= down) {
    for (int i = left; i <= right; i++)
      ans.push_back(matrix[up][i]);
    up++;
    if (up > down)
      break;
    for (int i = up; i <= down; i++)
      ans.push_back(matrix[i][right]);
    right--;
    if (right < left)
      break;
    for (int i = right; i >= left; i--)
      ans.push_back(matrix[down][i]);
    down--;
    if (down < up)
      break;
    for (int i = down; i >= up; i--)
      ans.push_back(matrix[i][left]);
    left++;
    if (left > right)
      break;
  }
  return ans;
}

// 设置上下左右四个边界，不断缩进遍历。注意，每次移动标志位，要立刻判断是否超界并break。使用++i>j，先移动，在判断。
vector<int> spiralOrder1(vector<vector<int>>& matrix) {
  int left = 0, right = matrix[0].size() - 1, top = 0,
      bottom = matrix.size() - 1;
  vector<int> ans;
  while (left <= right && top <= bottom) {
    for (int i = left; i <= right; i++)
      ans.push_back(matrix[top][i]);
    if (++top > bottom)
      break;
    for (int i = top; i <= bottom; i++)
      ans.push_back(matrix[i][right]);
    if (--right < left)
      break;
    for (int i = right; i >= left; i--)
      ans.push_back(matrix[bottom][i]);
    if (--bottom < top)
      break;
    for (int i = bottom; i >= top; i--)
      ans.push_back(matrix[i][left]);
    if (++left > right)
      break;
  }
  return ans;
}

int main() {
  vector<vector<int>> matrix1 = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  vector<vector<int>> matrix2 = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
  printVector(spiralOrder(matrix1));
  printVector(spiralOrder(matrix2));
  printVector(spiralOrder1(matrix1));
  printVector(spiralOrder1(matrix2));
  return 0;
}