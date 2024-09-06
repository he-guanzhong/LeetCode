#include "head.h"
/* LCR 186. 文物朝代判断
展览馆展出来自 13 个朝代的文物，每排展柜展出 5
个文物。某排文物的摆放情况记录于数组 places，其中 places[i] 表示处于第 i
位文物的所属朝代编号。其中，编号为 0
的朝代表示未知朝代。请判断并返回这排文物的所属朝代编号是否连续（如遇未知朝代可算作连续情况）。
示例 1：
  输入: places = [0, 6, 9, 0, 7]
  输出: True
示例 2：
  输入: places = [7, 8, 9, 10, 11]
  输出: True
提示：
    places.length = 5
    0 <= places[i] <= 13 */

bool checkDynasty(vector<int>& places) {
  if (places.size() < 2)
    return true;
  int minVal = 14, maxVal = 0;
  bool arr[14] = {0};
  for (int i = 0; i < places.size(); i++) {
    if (places[i] != 0) {
      if (arr[places[i]])
        return false;
      arr[places[i]] = true;
      maxVal = fmax(places[i], maxVal);
      minVal = fmin(places[i], minVal);
    }
  }
  return maxVal - minVal < 5;
}

// 判断连续，关键是最大、最小值m-n<5，且无重复。
// 方法一，集合判断是否重复，最大值初始化为0，最小值初始化为14，不能颠倒。遍历place，遇0直接跳过。重复了直接返回假，更新最大最小值，相差>=5直接返回假。
// 时间复杂度和空间复杂度O(1)，因为题目指定了places大小为5
bool checkDynasty1(vector<int>& places) {
  unordered_set<int> uset;
  int maxVal = 0, minVal = 14;
  for (int place : places) {
    if (place == 0)
      continue;
    if (uset.find(place) != uset.end())
      return false;
    uset.insert(place);
    minVal = min(place, minVal);
    maxVal = max(place, maxVal);
  }
  return maxVal - minVal < 5;
}

// 方法二，排序+遍历。对比相邻结果[i,i+1]确定是否重复。unknown标志位确定第一个非0元素位置。最终判断最后一位places[n-1]和place[unknown]之差是否小于5
bool checkDynasty2(vector<int>& places) {
  sort(places.begin(), places.end());
  int unknown = 0;
  for (int i = 0; i < places.size() - 1; i++) {
    if (places[i] == 0)
      unknown++;
    else if (places[i] == places[i + 1])
      return false;
  }
  return places[places.size() - 1] - places[unknown] < 5;
}

int main() {
  vector<int> places1 = {0, 6, 9, 0, 7}, places2 = {7, 8, 9, 10, 11},
              places3 = {13, 13, 9, 12, 10};
  cout << checkDynasty(places1) << " " << checkDynasty(places2) << " "
       << checkDynasty(places3) << endl;
  cout << checkDynasty1(places1) << " " << checkDynasty1(places2) << " "
       << checkDynasty1(places3) << endl;

  return 0;
}