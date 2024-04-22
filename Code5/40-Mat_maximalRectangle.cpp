#include "head.h"
/* 85. 最大矩形
给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，找出只包含 1
的最大矩形，并返回其面积。
示例 1：
输入：matrix =
[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
输出：6
解释：最大矩形如上图所示。
示例 2：
输入：matrix = [["0"]]
输出：0
示例 3：
输入：matrix = [["1"]]
输出：1 */

// 本题核心考察单调栈
int maximalRectangle(vector<vector<char>>& matrix) {}

// 暴力解法，left保存每一行、每一列连续1的个数，若该位为1，则在其左连续1的数量上，再加一。
// 二次遍历，对等于1的每位，设置宽度width即为连续1个数，高度k可以从i-1行向上拓展。不断更新最窄宽度，乘以高度即为面积
// 在该位最大面积基础上，外壳再套一层返回值最大面积。时间复杂度O(n)=n*n*m
int maximalRectangle1(vector<vector<char>>& matrix) {
  int m = matrix.size();
  if (m == 0)
    return 0;
  int n = matrix[0].size();
  vector<vector<int>> left(m, vector<int>(n, 0));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] == '1')
        left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;  // 注意括号
    }
  }
  int ret = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] == '0')
        continue;
      int width = left[i][j];
      int area = width;
      for (int k = i - 1; k >= 0; k--) {
        width = min(width, left[k][j]);
        area = max(area, (i - k + 1) * width);
      }
      ret = max(ret, area);
    }
  }
  return ret;
}

int main() {
  vector<vector<char>> matrix1 = {{'1', '0', '1', '0', '0'},
                                  {'1', '0', '1', '1', '1'},
                                  {'1', '1', '1', '1', '1'},
                                  {'1', '0', '0', '1', '0'}};
  vector<vector<char>> matrix2 = {{'0'}};
  vector<vector<char>> matrix3 = {{'1'}};

  cout << maximalRectangle(matrix1) << " " << maximalRectangle(matrix2) << " "
       << maximalRectangle(matrix3) << endl;
  return 0;
}