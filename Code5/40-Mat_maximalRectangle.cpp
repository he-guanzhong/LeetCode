#include "head.h"
/* 85. 最大矩形
给定一个仅包含 0 和 1 、大小为 rows x cols 的二维二进制矩阵，找出只包含 1
的最大矩形，并返回其面积。
示例 1：
  输入：matrix =
    [["1","0","1","0","0"],
    ["1","0","1","1","1"],
    ["1","1","1","1","1"],
    ["1","0","0","1","0"]]
  输出：6
  解释：最大矩形如上图所示。
示例 2：
  输入：matrix = [["0"]]
  输出：0
示例 3：
  输入：matrix = [["1"]]
  输出：1 */

// 本题核心考察单调栈。把每一行都当做最大直方图面积来计算
// 辅助函数，求直方图的最大面积。单调栈，保存下标。当不能修改原数组，收尾各插入高度为0辅助柱时，需额外特殊处理。
// 首下标压入-1，并且保证栈顶元素不能为-1，如此保证栈不为空。假定最后一柱高度是0，清空栈内所有元素，直至-1
// 主函数，辅助数组heights记录每一行其上，连续1的个数，作为高度。遇到1可累计高度，遇到0则高度清零
int getMaxArea(const vector<int>& heights) {
  stack<int> st;
  st.push(-1);
  int area = 0;
  for (int i = 0; i < heights.size(); i++) {
    while (st.top() != -1 && heights[i] <= heights[st.top()]) {
      int h = heights[st.top()];
      st.pop();
      int w = i - st.top() - 1;
      area = max(area, h * w);
    }
    st.push(i);
  }
  while (st.top() != -1) {
    int h = heights[st.top()];
    st.pop();
    int w = heights.size() - st.top() - 1;
    area = max(area, h * w);
  }
  return area;
}
int maximalRectangle(vector<vector<char>>& matrix) {
  int m = matrix.size();
  if (m == 0)
    return 0;
  int n = matrix[0].size();
  vector<int> heights(n, 0);  // 该行直方图，纵向高度是竖向连续1的数量
  int ans = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      heights[j] = matrix[i][j] == '1' ? heights[j] + 1 : 0;
    }
    ans = max(ans, getMaxArea(heights));
  }
  return ans;
}

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