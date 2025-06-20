#include "head.h"
/* 304. 二维区域和检索 - 矩阵不可变
给定一个二维矩阵 matrix，以下类型的多个请求：
计算其子矩形范围内元素的总和，该子矩阵的 左上角 为 (row1, col1) ，右下角 为
(row2, col2) 。 实现 NumMatrix 类：
NumMatrix(int[][] matrix) 给定整数矩阵 matrix 进行初始化
int sumRegion(int row1, int col1, int row2, int col2) 返回 左上角 (row1, col1)
、右下角 (row2, col2) 所描述的子矩阵的元素 总和 。
示例 1：
  输入:
    ["NumMatrix","sumRegion","sumRegion","sumRegion"]
    [[[[3,0,1,4,2],
    [5,6,3,2,1],
    [1,2,0,1,5],
    [4,1,0,1,7],
    [1,0,3,0,5]]],
    [2,1,4,3],[1,1,2,2],[1,2,2,4]]
  输出:
    [null, 8, 11, 12]
解释:
  NumMatrix numMatrix = new
  NumMatrix([[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]);
  numMatrix.sumRegion(2, 1, 4, 3); // return 8 (红色矩形框的元素总和)
  numMatrix.sumRegion(1, 1, 2, 2); // return 11 (绿色矩形框的元素总和)
  numMatrix.sumRegion(1, 2, 2, 4); // return 12 (蓝色矩形框的元素总和)
提示：
  m == matrix.length
  n == matrix[i].length
  1 <= m, n <= 200
  -105 <= matrix[i][j] <= 105
  0 <= row1 <= row2 < m
  0 <= col1 <= col2 < n
  最多调用 104 次 sumRegion 方法 */

class NumMatrix {
 public:
  NumMatrix(vector<vector<int>>& matrix) {
    sum = vector<vector<int>>(matrix.size() + 1,
                              vector<int>(matrix[0].size() + 1, 0));
    for (int i = 0; i < matrix.size(); i++) {
      for (int j = 0; j < matrix[0].size(); j++) {
        sum[i + 1][j + 1] =
            sum[i][j + 1] + sum[i + 1][j] - sum[i][j] + matrix[i][j];
      }
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    return sum[row2 + 1][col2 + 1] - sum[row2 + 1][col1] - sum[row1][col2 + 1] +
           sum[row1][col1];
  }
  vector<vector<int>> sum;
};

// 二维数组前缀和，求前缀和矩阵式，已经使用了公式
class NumMatrix1 {
 public:
  NumMatrix1(vector<vector<int>>& matrix) {
    int m = matrix.size();
    if (m == 0)
      return;
    int n = matrix[0].size();
    sum.resize(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
      for (int j = 1; j <= n; j++) {
        sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] +
                    matrix[i - 1][j - 1];
      }
    }
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    return sum[row2 + 1][col2 + 1] + sum[row1][col1] - sum[row1][col2 + 1] -
           sum[row2 + 1][col1];
  }

 public:
  vector<vector<int>> sum;
};

int main() {
  vector<vector<int>> matrix = {{3, 0, 1, 4, 2},
                                {5, 6, 3, 2, 1},
                                {1, 2, 0, 1, 5},
                                {4, 1, 0, 1, 7},
                                {1, 0, 3, 0, 5}};
  NumMatrix numMat(matrix);
  cout << numMat.sumRegion(2, 1, 4, 3) << " " << numMat.sumRegion(1, 1, 2, 2)
       << " " << numMat.sumRegion(1, 2, 2, 4) << endl;
  NumMatrix1 numMat1(matrix);
  cout << numMat1.sumRegion(2, 1, 4, 3) << " " << numMat1.sumRegion(1, 1, 2, 2)
       << " " << numMat1.sumRegion(1, 2, 2, 4) << endl;
  return 0;
}