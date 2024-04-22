#include "head.h"
/* 435. 无重叠区间
给定一个区间的集合，找到需要移除区间的最小数量，使剩余区间互不重叠。
注意: 可以认为区间的终点总是大于它的起点。 区间 {1,2} 和 {2,3}
的边界相互“接触”，但没有相互重叠。
示例 1:
    输入: { {1,2}, {2,3}, {3,4}, {1,3} }
    输出: 1
    解释: 移除 {1,3} 后，剩下的区间没有重叠。
示例 2:
    输入: { {1,2}, {1,2}, {1,2} }
    输出: 2
    解释: 你需要移除两个 {1,2} 来使剩下的区间没有重叠。
示例 3:
    输入: { {1,2}, {2,3} }
    输出: 0
    解释: 你不需要移除任何区间，因为它们已经是无重叠的了。 */

// 起点从小到大排序，相邻两两比较，若i起点在i-1范围内，重复区间加一，更新i终点为i和i-1最小值
int eraseOverlapIntervals(vector<vector<int>> &intervals) {
  sort(intervals.begin(), intervals.end(),
       [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; });
  int result = 0;
  int end = intervals[0][1];
  for (int i = 1; i < intervals.size(); i++) {
    if (end <= intervals[i][0]) {
      end = intervals[i][1];
    } else {
      result++;
      end = min(intervals[i][1], end);
    }
  }
  return result;
}

// 按最右边界，从小到大排序。然后从左向右遍历，记录每个右边界的最左停止线，一旦发现新区间左起点与之前停止线不相交，则非交叉区间数加一
// 总数量减去非交叉区间数，得到交叉区间数
int eraseOverlapIntervals1(vector<vector<int>> &intervals) {
  sort(intervals.begin(), intervals.end(),
       [](vector<int> &a, vector<int> &b) { return a[1] < b[1]; });
  int count = 1; // 记录非交叉区间数
  int end = intervals[0][1];
  for (int i = 1; i < intervals.size(); i++) {
    if (intervals[i][0] >= end) {
      end = intervals[i][1];
      count++;
    }
  }
  return intervals.size() - count;
}
// 若按左边界排序，从左向右遍历，记录的是重叠区间数
int eraseOverlapIntervals2(vector<vector<int>> &intervals) {
  sort(intervals.begin(), intervals.end(),
       [](vector<int> &a, vector<int> &b) { return a[0] < b[0]; });
  int count = 0; // 重叠区间从0开始
  int end = intervals[0][1];
  for (int i = 1; i < intervals.size(); i++) {
    if (intervals[i][0] < intervals[i - 1][1]) { // 有重叠
      count++;
      intervals[i][1] = min(intervals[i][1], intervals[i - 1][1]);
    }
  }
  return count;
}

int main() {
  vector<vector<int>> points1 = {{1, 2}, {2, 3}, {3, 4}, {1, 3}};
  vector<vector<int>> points2 = {{1, 2}, {1, 2}, {1, 2}};
  vector<vector<int>> points3 = {{1, 2}, {2, 3}};

  cout << eraseOverlapIntervals(points1) << " "
       << eraseOverlapIntervals(points2) << " "
       << eraseOverlapIntervals(points3) << " " << endl;
  cout << eraseOverlapIntervals1(points1) << " "
       << eraseOverlapIntervals1(points2) << " "
       << eraseOverlapIntervals1(points3) << " " << endl;
  return 0;
}