#include "head.h"
/* 118. 杨辉三角
给定一个非负整数 numRows，生成「杨辉三角」的前 numRows 行。
在「杨辉三角」中，每个数是它左上方和右上方的数的和。
示例 1:
  输入: numRows = 5
  输出: [[1],[1,1],[1,2,1],[1,3,3,1],[1,4,6,4,1]]
示例 2:
  输入: numRows = 1
  输出: [[1]] */

vector<vector<int>> generate(int numRows) {
  vector<vector<int>> ans(numRows);
  for (int i = 0; i < numRows; i++) {
    ans[i] = vector<int>(i + 1, 1);
    for (int j = 1; j < i; j++) {
      ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
    }
  }
  return ans;
}

// 杨辉三角性质，第i行（从0开始）有i+1个元素。每行首尾元素[0][i]均为1，每行第j个元素，等于上一行j-1元素和j元素之和。
// 直接在二维数组上操作。但必须初始化行数。
vector<vector<int>> generate1(int numRows) {
  vector<vector<int>> dp(numRows);
  for (int i = 0; i < numRows; i++) {
    dp[i].resize(i + 1);
    dp[i][0] = dp[i][i] = 1;
    for (int j = 1; j < i; j++)
      dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
  }
  return dp;
}
int main() {
  printMat(generate(5));
  printMat(generate(1));
  printMat(generate1(5));
  printMat(generate1(1));
  return 0;
}