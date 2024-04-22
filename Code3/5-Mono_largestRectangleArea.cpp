#include "head.h"
/* 84. 柱状图中最大的矩形
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为1。
求在该柱状图中，能够勾勒出来的矩形的最大面积。
示例 1:
输入：heights = [2,1,5,6,2,3]
输出：10
解释：最大的矩形为图中红色区域，面积为 10
示例 2：
输入： heights = [2,4]
输出： 4 */

// 单调栈，本质是算左、右柱（不含）相夹的各中柱面积，因此，队首、队尾人工加入两个0，以计算全部柱面积。
// 栈底到栈顶从小到大排列，故一旦发现更小的，即弹出
int largestRectangleArea(vector<int>& heights) {
  heights.insert(heights.begin(), 0);
  heights.push_back(0);
  stack<int> st;
  st.push(0);
  int result = 0;
  for (int i = 1; i < heights.size(); i++) {
    while (!st.empty() && heights[i] < heights[st.top()]) {
      int mid = st.top();
      st.pop();
      if (!st.empty()) {
        result = max(result, heights[mid] * (i - st.top() - 1));
      }
    }
    st.push(i);
  }
  return result;
}

// 单调栈，求的是该元素柱，向左侧和右侧第一个小于该元素的位置，故应该从栈底到栈头，按照从小到大的顺序排列
// 注意开头要插入一个0，否则对于递减序列，每次都弹出栈，栈空则不计算面积。
// 结尾要插入一个0，否则对于递增序列，全部压入了之后，没有一次栈弹出，没有结果。
int largestRectangleArea1(vector<int>& heights) {
  heights.insert(heights.begin(), 0);
  heights.push_back(0);
  stack<int> st;
  st.push(0);
  int result = 0;
  for (int i = 1; i < heights.size(); i++) {
    if (heights[i] > heights[st.top()])
      st.push(i);
    else if (heights[i] == heights[st.top()]) {
      st.pop();
      st.push(i);
    } else {
      while (!st.empty() && heights[i] < heights[st.top()]) {
        int mid = st.top();
        st.pop();
        if (!st.empty()) {
          int h = heights[mid];
          int w = i - st.top() - 1;
          result = max(result, h * w);
        }
      }
      st.push(i);
    }
  }
  return result;
}

// 双指针法。找该为支点左侧、右侧第一个小于该元素的点，注意保存的是左侧第一个小柱的下标，不是小柱的高度。
// 下标初始化，一定是左小元素为-1，右小元素为size，因为可以跳出while
// 不能使用t--和t++，否则超时。一旦发现要跳跃，直接minLeftIndex[t]=t
int largestRectangleArea2(vector<int>& heights) {
  int result = 0;
  int size = heights.size();
  vector<int> minLeftIndex(size, 0), minRightIndex(size, 0);
  minLeftIndex[0] = -1;  // 初始化注意和while条件匹配
  minRightIndex[size - 1] = size;
  for (int i = 1; i < size; i++) {
    int t = i - 1;
    while (t >= 0 && heights[t] >= heights[i])
      // 这里不能使用t--，否则超时
      t = minLeftIndex[t];
    minLeftIndex[i] = t;
  }
  for (int i = size - 2; i >= 0; i--) {
    int t = i + 1;
    while (t < size && heights[t] >= heights[i])
      // 此处不要使用 t++，否则超时
      t = minRightIndex[t];
    minRightIndex[i] = t;
  }
  for (int i = 0; i < size; i++) {
    int h = heights[i];
    int w = minRightIndex[i] - minLeftIndex[i] - 1;
    result = max(result, h * w);
  }
  return result;
}

int main() {
  vector<int> num1 = {2, 1, 5, 6, 2, 3}, num2 = {2, 4}, num3 = {2, 4, 6, 8},
              num4 = {8, 6, 4, 2};
  cout << largestRectangleArea(num1) << " " << largestRectangleArea(num2) << " "
       << largestRectangleArea(num3) << " " << largestRectangleArea(num4)
       << endl;
  cout << largestRectangleArea1(num1) << " " << largestRectangleArea1(num2)
       << " " << largestRectangleArea1(num3) << " "
       << largestRectangleArea1(num4) << endl;
  return 0;
}