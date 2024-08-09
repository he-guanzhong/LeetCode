#include "head.h"
/* 11. 盛最多水的容器
给定一个长度为 n 的整数数组 height 。有 n 条垂线，第 i 条线的两个端点是 (i, 0)
和 (i, height[i]) 。
找出其中的两条线，使得它们与 x 轴共同构成的容器可以容纳最多的水。
返回容器可以储存的最大水量。
说明：你不能倾斜容器。
示例 1：
  输入：[1,8,6,2,5,4,8,3,7]
  输出：49
  解释：图中垂直线代表输入数组
    [1,8,6,2,5,4,8,3,7]。在此情况下，容器能够容纳水（表示为蓝色部分）的最大值为49。
示例 2：
  输入：height = [1,1]
  输出：1 */

int maxArea(vector<int>& height) {
  int n = height.size();
  int left = 0, right = n - 1;
  int ans = 0;
  while (left < right) {
    int area = (right - left) * min(height[left], height[right]);
    ans = max(ans, area);
    if (height[left] < height[right])
      left++;
    else
      right--;
  }
  return ans;
}

// 本题求的是双柱所围矩形面积，与中心柱的高低无关，应用双指针。注意和接雨水的双指针法区分，接雨水求的是每一柱之上“雨水”的面积和。
// 双指针初始化为左右边界，不断向中央收紧，每次只能移动较短的一边，如此才能让容器有机会最大。
// 注意一定要先计算，再移动板。
int maxArea1(vector<int>& height) {
  int left = 0, right = height.size() - 1;
  int result = 0;
  while (left < right) {
    result = max(result, min(height[right], height[left]) * (right - left));
    if (height[left] < height[right])
      left++;
    else
      right--;
  }
  return result;
}

int main() {
  vector<int> temp1 = {1, 8, 6, 2, 5, 4, 8, 3, 7}, temp2 = {1, 1}, temp3 = {};
  cout << maxArea(temp1) << " " << maxArea(temp2) << " " << maxArea(temp3)
       << " " << endl;
  cout << maxArea1(temp1) << " " << maxArea1(temp2) << " " << maxArea1(temp3)
       << " " << endl;
  return 0;
}