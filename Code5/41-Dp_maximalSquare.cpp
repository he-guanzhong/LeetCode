#include "head.h"
/* 221. 最大正方形
在一个由 '0' 和 '1' 组成的二维矩阵内，找到只包含 '1'
的最大正方形，并返回其面积。
示例 1：
  输入：matrix =
    [["1","0","1","0","0"],
    ["1","0","1","1","1"],
    ["1","1","1","1","1"],
    ["1","0","0","1","0"]]
  输出：4
示例 2：
  输入：matrix = [["0","1"],["1","0"]]
  输出：1
示例 3：
  输入：matrix = [["0"]]
  输出：0 */

int maximalSquare(vector<vector<char>>& matrix) {
  int m = matrix.size(), n = matrix[0].size();
  int ans = 0, pre = 0;
  vector<int> dp(n + 1);
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      pre = dp[j - 1];
      if (matrix[i - 1][j - 1] == '1') {
        dp[j] = min({dp[j], dp[j - 1], pre}) + 1;
        ans = max(ans, dp[j]);
      } else {
        dp[j] = 0;
      }
    }
  }
  return ans * ans;
}

// 动态规划，核心dp[i][j]表示以[i.j]为下标最大正方形的边长。可以设置[m+1,n+1]矩阵，规避第一行和第一列特殊初始化的影响。
// dp[i][j]边长，取决于其左、上、左上共三个方向上的边张最短值+1，三者任一为短，均不能构成正方形。最终，边长的二次方即为答案所求面积
int maximalSquare1(vector<vector<char>>& matrix) {
  int m = matrix.size();
  if (m == 0)
    return 0;
  int n = matrix[0].size();
  int ans = 0;
  vector<vector<int>> dp(m, vector<int>(n, 0));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (matrix[i][j] == '0') {
        continue;
      }
      if (i == 0 || j == 0)
        dp[i][j] = 1;
      else
        dp[i][j] = min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]}) + 1;
      ans = max(ans, dp[i][j]);
    }
  }
  return ans * ans;
}

int main() {
  vector<vector<char>> matrix1 = {{'1', '0', '1', '0', '0'},
                                  {'1', '0', '1', '1', '1'},
                                  {'1', '1', '1', '1', '1'},
                                  {'1', '0', '0', '1', '0'}};
  vector<vector<char>> matrix2 = {{'1', '0'}, {'0', '1'}};
  vector<vector<char>> matrix3 = {{'0'}};

  cout << maximalSquare(matrix1) << " " << maximalSquare(matrix2) << " "
       << maximalSquare(matrix3) << endl;
  cout << maximalSquare1(matrix1) << " " << maximalSquare1(matrix2) << " "
       << maximalSquare1(matrix3) << endl;
  return 0;
}