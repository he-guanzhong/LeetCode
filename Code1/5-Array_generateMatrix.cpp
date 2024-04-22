#include "head.h"
/* 59. 螺旋矩阵 II
给定一个正整数 n，生成一个包含 1 到 n^2
所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。

示例:
输入: 3 输出: [ [ 1, 2, 3 ], [ 8, 9, 4 ], [ 7, 6, 5 ] ] */

// 螺旋矩阵打印，先创建计数器cnt=1，并定义上下左右四个变量left/right/up/down
// 循环条件为left<=right和up<=down，因为相等时也是可以赋值的。
// 按照顺时针顺序依次遍历，更新完上边后，对于实时判断是否大于下边，可有可无。有了可少进一轮循环。没有则不影响最终结果
vector<vector<int>> generateMatrix(int n) {
  int left = 0, top = 0, right = n - 1, bottom = n - 1;
  int i = 0;
  vector<vector<int>> result(n, vector<int>(n, 0));
  while (left <= right && top <= bottom) {
    for (int j = left; j <= right; j++)
      result[top][j] = ++i;
    top++;
    if (top > bottom)
      break;
    for (int j = top; j <= bottom; j++)
      result[j][right] = ++i;
    right--;
    if (right < left)
      break;
    for (int j = right; j >= left; j--)
      result[bottom][j] = ++i;
    bottom--;
    if (bottom < top)
      break;
    for (int j = bottom; j >= top; j--)
      result[j][left] = ++i;
    left++;
    if (left > right)
      break;
  }
  return result;
}

// 推荐解法，左闭右开
vector<vector<int>> generateMatrix1(int n) {
  vector<vector<int>> res(n, vector<int>(n, 0));
  int startX = 0, startY = 0;
  int cnt = 1;
  int loop = n / 2;  // 总计要多少圈
  int mid = n / 2;   // 奇数边长情况下的中间值
  int offset = 1;    // 右开区间的偏移量
  int i, j;          // 实际要移动的点
  while (loop--) {
    i = startX;
    j = startY;
    for (; j < n - offset; j++)
      res[i][j] = cnt++;
    for (; i < n - offset; i++)
      res[i][j] = cnt++;
    for (; j > startY; j--)
      res[i][j] = cnt++;
    for (; i > startX; i--)
      res[i][j] = cnt++;
    startX++;  // 第二圈起始位置
    startY++;
    offset++;  // 下一回环需要叠加
  }
  if (n % 2)
    res[mid][mid] = n * n;  // 奇数位中央点特殊处理
  return res;
}

// 朴素解法，左闭右闭
vector<vector<int>> generateMatrix2(int n) {
  vector<vector<int>> res(n, vector<int>(n, 0));
  int left = 0, right = res[0].size() - 1, up = 0, down = res.size() - 1;
  int cnt = 1;
  while (left <= right && up <= down) {
    for (int i = left; i <= right; i++)
      res[up][i] = cnt++;
    up++;
    for (int i = up; i <= down; i++)
      res[i][right] = cnt++;
    right--;
    for (int i = right; i >= left; i--)
      res[down][i] = cnt++;
    down--;
    for (int i = down; i >= up; i--)
      res[i][left] = cnt++;
    left++;
  }
  return res;
}

int main() {
  int n = 5;
  printMat(generateMatrix(n));
  printMat(generateMatrix1(n));
  return 0;
}