#include "head.h"
/* 42. 接雨水
给定 n 个非负整数表示每个宽度为 1
的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
示例 1：
输入：height = [0,1,0,2,1,0,1,3,2,1,2,1]
输出：6
解释：上面是由数组 [0,1,0,2,1,0,1,3,2,1,2,1] 表示的高度图，在这种情况下，可以接
6 个单位的雨水（蓝色部分表示雨水）。 示例 2：
输入：height = [4,2,0,3,2,5]
输出：9  */

// 双指针求列雨水。记录每一列的最大左柱高、最大右柱高，对每一列雨水高度求和。注意只有两柱不能接雨水。
// 单调栈求行雨水。从栈底到栈头从大到小排列。遇下一个更大的元素，根据左柱、底部、右柱三个信息计算。top为雨水底，弹出后若栈仍不空，才有左柱可以计算
int trap(vector<int>& height) {
  if (height.size() <= 2)
    return 0;
  int result = 0;
  vector<int> maxLeft(height.size(), 0);
  vector<int> maxRight(height.size(), 0);
  maxLeft[0] = height[0];
  maxRight[height.size() - 1] = height[height.size() - 1];
  for (int i = 1; i < height.size(); i++)
    maxLeft[i] = max(maxLeft[i - 1], height[i]);
  for (int i = height.size() - 2; i >= 0; i--)
    maxRight[i] = max(maxRight[i + 1], height[i]);
  for (int i = 1; i < height.size() - 1; i++) {
    result += (min(maxLeft[i], maxRight[i]) - height[i]);
  }
  return result;
}

// 单调栈，从栈底到栈顶，按照从大到小排序，可以求下一个比本元素更大的位置。stack中记录下标即可。若新元素比栈顶元素小，直接压入。
// 新元素等于栈顶元素，则将老元素弹出，再压入新元素，如此是为了保证接雨水的左柱实时更新
// 新元素大于栈顶元素，则记录此时st.top()为坑底mid，弹出后，新的st.top()即为左柱，i为右柱，则接雨水的高为min(height[i],height[st.top()])-height[mid]
// 接雨水的宽为左右柱下标之差，减一，i-st.top()-1
int trap1(vector<int>& height) {
  stack<int> st;
  st.push(0);
  int result = 0;
  for (int i = 1; i < height.size(); i++) {
    if (height[i] < height[st.top()])
      st.push(i);
    else if (height[i] == height[st.top()]) {
      st.pop();
      st.push(i);
    } else {
      while (!st.empty() && height[i] > height[st.top()]) {
        int mid = st.top();
        st.pop();
        if (!st.empty()) {
          int h = min(height[i], height[st.top()]) - height[mid];
          int w = i - st.top() - 1;
          result += h * w;
        }
      }
      st.push(i);
    }
  }
  return result;
}
// 精简单调栈，如果新元素等于栈顶元素，实际也可以不弹出老的再压入新，如此，会新增一道计算雨水高度0的工序
int trap2(vector<int>& height) {
  stack<int> st;
  st.push(0);
  int result = 0;
  for (int i = 1; i < height.size(); i++) {
    while (!st.empty() && height[i] > height[st.top()]) {
      int mid = st.top();
      st.pop();
      if (!st.empty()) {
        int h = min(height[i], height[st.top()]) - height[mid];
        int w = i - st.top() - 1;
        result += h * w;
      }
    }
    st.push(i);
  }
  return result;
}

// 暴力解法。双指针，求每一列的雨水高度，总和即为所有雨水和。第一列和最后一列不能接雨水，对于每一列，分别记录其左侧、最右侧最大柱高
// 左右最大柱高的最低值，就是雨水面，本列高度就是雨水底，求差。如果差为正，即可接雨水，累计求和。时间复杂度O(n^2)，超时。不可使用。
int trap3(vector<int>& height) {
  int result = 0;
  for (int i = 0; i < height.size(); i++) {
    if (i == 0 || i == height.size() - 1)
      continue;
    int lHeight = height[i], rHeight = height[i];
    for (int l = i - 1; l >= 0; l--) {
      if (height[l] > lHeight)
        lHeight = height[l];
    }
    for (int r = i + 1; r < height.size(); r++)
      rHeight = max(rHeight, height[r]);
    int h = min(lHeight, rHeight) - height[i];
    if (h > 0)
      result += h;
  }
  return result;
}

// 优化的双指针，使用额外数组maxLeft和maxRight记录每个位置最左侧和最右侧柱子的最大值。注意左侧右侧，第一个起始元素要特殊初始化
// 时间复杂度O(n)
int trap4(vector<int>& height) {
  if (height.size() <= 2)  // 小于等于2个元素，必不可能接雨水
    return 0;
  int size = height.size();
  int result = 0;
  vector<int> leftMax(size, 0);
  vector<int> rightMax(size, 0);
  leftMax[0] = height[0];
  rightMax[size - 1] = height[size - 1];
  for (int i = 1; i < size; i++)
    leftMax[i] = max(leftMax[i - 1], height[i]);
  for (int i = size - 2; i >= 0; i--)
    rightMax[i] = max(rightMax[i + 1], height[i]);
  for (int i = 1; i < size; i++) {
    int h = min(leftMax[i], rightMax[i]) - height[i];
    if (h > 0)
      result += h;
  }
  return result;
}

int main() {
  vector<int> num1 = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1},
              num2 = {4, 2, 0, 3, 2, 5}, num3 = {2, 4}, num4 = {1, 2, 3, 4};
  cout << trap(num1) << " " << trap(num2) << endl;
  cout << trap2(num1) << " " << trap2(num2) << endl;
  return 0;
}