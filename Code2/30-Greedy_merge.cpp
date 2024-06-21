#include "head.h"
/* 56. 合并区间
以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [starti,
endi] 。请你合并所有重叠的区间，并返回
一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
示例 1：
  输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
  输出：[[1,6],[8,10],[15,18]]
  解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].
示例 2：
  输入：intervals = [[1,4],[4,5]]
  输出：[[1,5]]
  解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。 */

vector<vector<int>> merge(vector<vector<int>>& intervals) {
  sort(intervals.begin(), intervals.end(),
       [](vector<int> a, vector<int> b) { return a[0] < b[0]; });
  vector<vector<int>> ans;
  ans.push_back(intervals[0]);
  for (int i = 1; i < intervals.size(); i++) {
    if (intervals[i][0] > ans.back()[1]) {
      ans.push_back(intervals[i]);
    } else {
      ans.back()[1] = max(intervals[i][1], ans.back()[1]);
    }
  }
  return ans;
}

// 左边界从小到大排序，单独结果容器，首元素压入，比较剩余元素左边界有重合，更新结果末尾元素右边界，左边界不重合，压入结果容器。
// 找重叠区间，还是先按照左边界，从小到大排序。单独设立结果容器。将首个区间压入容器，直接在容器中修改区间的右边界
// 若下一区间左边界小于结果容器右边界，有重合。更新容器内右边界。若下一区间无重合，则将区间压入容器
// 时间复杂度O(nlogn), 空间复杂度O(logn)，排序需要的空间开销
vector<vector<int>> merge1(vector<vector<int>>& intervals) {
  vector<vector<int>> result;
  if (intervals.empty())
    return result;
  sort(intervals.begin(), intervals.end(),
       [](const vector<int>& a, const vector<int>& b) { return a[0] < b[0]; });
  result.push_back(intervals[0]);
  for (int i = 0; i < intervals.size(); i++) {
    if (intervals[i][0] <= result.back()[1])
      result.back()[1] = max(result.back()[1], intervals[i][1]);
    else
      result.push_back(intervals[i]);
  }
  return result;
}

int main() {
  vector<vector<int>> points1 = {{1, 3}, {2, 6}, {8, 10}, {15, 18}};
  vector<vector<int>> points2 = {{1, 4}, {4, 5}};
  vector<vector<int>> points3 = {{2, 3}, {4, 5}, {6, 7}, {8, 9}, {1, 10}};
  printMat(merge(points1));
  printMat(merge(points2));
  printMat(merge(points3));
  printMat(merge1(points1));
  printMat(merge1(points2));
  printMat(merge1(points3));
  return 0;
}