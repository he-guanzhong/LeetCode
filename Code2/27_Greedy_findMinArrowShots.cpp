#include "head.h"
/* 452. 用最少数量的箭引爆气球
有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 points
，其中points{i} = {xstart, xend} 表示水平直径在 xstart 和
xend之间的气球。你不知道气球的确切 y 坐标。
一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。在坐标 x
处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend， 且满足  xstart
≤ x ≤ xend，则该气球会被 引爆 。可以射出的弓箭的数量 没有限制 。
弓箭一旦被射出之后，可以无限地前进。
给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。
示例 1：
  输入：points = {{10,16},{2,8},{1,6},{7,12}}
  出：2
  解释：气球可以用2支箭来爆破:
    -在x = 6处射出箭，击破气球{2,8}和{1,6}。
    -在x = 11处发射箭，击破气球{10,16}和{7,12}。
示例 2：
  输入：points = {{1,2},{3,4},{5,6},{7,8}}
  输出：4
  解释：每个气球需要射出一支箭，总共需要4支箭。
示例 3：
  输入：points = {{1,2},{2,3},{3,4},{4,5}}
  输出：2
  解释：气球可以用2支箭来爆破:
    - 在x = 2处发射箭，击破气球{1,2}和{2,3}。
    - 在x = 4处射出箭，击破气球{3,4}和{4,5}。
    -231 <= xstart < xend <= 231 - 1*/

int findMinArrowShots(vector<vector<int>>& points) {
  sort(points.begin(), points.end(),
       [](vector<int> a, vector<int> b) { return a[0] < b[0]; });
  int ans = 1;
  if (points.size() < 2)
    return ans;
  for (int i = 1; i < points.size(); i++) {
    if (points[i][0] > points[i - 1][1]) {
      ans++;
    } else {
      points[i][1] = min(points[i - 1][1], points[i][1]);
    }
  }
  return ans;
}

// 先按照起点从小到大排序，从左到右遍历两两比较，若i起点大于i-1终点，更新结果。若i与i-1有重合，更新缩小i的终点。
// 先按照起始点，从小到大排序，然后从左向右遍历。凡有重叠气球，必只能覆盖较小的那个范围，如超出最小有边界，则势必还需要一支箭
int findMinArrowShots1(vector<vector<int>>& points) {
  sort(points.begin(), points.end(),
       [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });
  if (points.empty())  // 要比较相邻元素，必须先判空
    return 0;
  int result = 1;
  for (int i = 1; i < points.size(); i++) {
    if (points[i][0] > points[i - 1][1])  // i和i-1不挨着，不能>=
      result++;
    else  // i和i-1重叠，则取重叠气球的最小边界为准
      points[i][1] = min(points[i - 1][1], points[i][1]);
  }
  return result;
}

int main() {
  vector<vector<int>> points1 = {{10, 16}, {2, 8}, {1, 6}, {7, 12}};
  vector<vector<int>> points2 = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
  vector<vector<int>> points3 = {{1, 2}, {2, 3}, {3, 4}, {4, 5}};
  vector<vector<int>> points4 = {{-2147483648, 2147483647}};
  vector<vector<int>> points5 = {{3, 9}, {7, 12}, {3, 8}, {6, 8}, {9, 10},
                                 {2, 9}, {0, 9},  {3, 9}, {0, 6}, {2, 8}};
  cout << findMinArrowShots(points1) << " " << findMinArrowShots(points2) << " "
       << findMinArrowShots(points3) << " " << findMinArrowShots(points4) << " "
       << findMinArrowShots(points5) << endl;
  cout << findMinArrowShots1(points1) << " " << findMinArrowShots1(points2)
       << " " << findMinArrowShots1(points3) << " "
       << findMinArrowShots1(points4) << " " << findMinArrowShots1(points5)
       << endl;
  return 0;
}