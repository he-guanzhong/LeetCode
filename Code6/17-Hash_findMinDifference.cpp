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

int getMinute(const string& s) {
  return (s[0] - '0') * 600 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + s[4] -
         '0';
}
int findMinDifference(vector<string>& timePoints) {
  if (timePoints.size() > 24 * 60)
    return 0;
  vector<int> dp(timePoints.size(), 0);
  for (int i = 0; i < timePoints.size(); i++) {
    dp[i] = getMinute(timePoints[i]);
  }
  sort(dp.begin(), dp.end());
  dp.push_back(dp.front() + 24 * 60);
  int ans = INT_MAX;
  for (int i = 1; i < dp.size(); i++) {
    int diff = dp[i] - dp[i - 1];
    ans = min(ans, diff);
  }
  return ans;
}

// 时间字符串转整数函数，可以直接char处理，不必stoi。比较每两个时间之间最小值，则问题转化为，排序后数组，两两相邻数组差最小值
// 字符串可以直接排序，不必转化为整数。注意24小时是24*60=1440分钟，故两两时间差，还要包括最小时间（首）+1440，与最大时间（尾）之差
// 时间转换函数，首位是10小时位，即600分钟，第二位是小时，60分钟，第三位是10分钟位，故10分钟
// 鸽笼原理。如果数组内元素超过1440个，则必有两个时间重复，此时最小时间差为0，可节省时间复杂度
int getMinute1(const string& s) {
  return (s[0] - '0') * 600 + (s[1] - '0') * 60 + (s[3] - '0') * 10 + s[4] -
         '0';
}
int findMinDifference1(vector<string>& timePoints) {
  int n = timePoints.size();
  if (n > 1440)
    return 0;
  sort(timePoints.begin(), timePoints.end());
  int firstMinute = getMinute1(timePoints[0]);
  int preMinute = firstMinute;
  int ans = INT_MAX;
  for (int i = 1; i < timePoints.size(); i++) {
    int curMinute = getMinute1(timePoints[i]);
    ans = min(ans, curMinute - preMinute);
    preMinute = curMinute;
  }
  ans = min(ans, firstMinute + 1440 - preMinute);
  return ans;
}

int main() {
  vector<string> str1 = {"23:59", "00:00"}, str2 = {"00:00", "23:59", "00:00"};
  cout << findMinDifference(str1) << " " << findMinDifference(str2) << endl;
  cout << findMinDifference1(str1) << " " << findMinDifference1(str2) << endl;
  return 0;
}