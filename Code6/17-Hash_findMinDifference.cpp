#include "head.h"

/* 539. 最小时间差
给定一个 24 小时制（小时:分钟
"HH:MM"）的时间列表，找出列表中任意两个时间的最小时间差并以分钟数表示。
示例 1：
  输入：timePoints = ["23:59","00:00"]
  输出：1
示例 2：
  输入：timePoints = ["00:00","23:59","00:00"]
  输出：0
提示：
    2 <= timePoints.length <= 2 * 104
    timePoints[i] 格式为 "HH:MM" */

int findMinDifference(vector<string>& timePoints) {
  vector<int> tmp(timePoints.size(), 0);
  for (int i = 0; i < timePoints.size(); i++) {
    string str = timePoints[i];
    tmp[i] = stoi(str.substr(0, 2)) * 60 + stoi(str.substr(3));
  }
  sort(tmp.begin(), tmp.end());
  tmp.push_back(tmp.front() + 24 * 60);
  int ans = INT_MAX;
  for (int i = 1; i < tmp.size(); i++) {
    ans = min(ans, tmp[i] - tmp[i - 1]);
  }
  return ans;
}

int main() {
  vector<string> str1 = {"23:59", "00:00"}, str2 = {"00:00", "23:59", "00:00"};
  cout << findMinDifference(str1) << " " << findMinDifference(str2) << endl;
  return 0;
}