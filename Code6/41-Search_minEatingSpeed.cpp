#include "head.h"
/* 875. 爱吃香蕉的珂珂
珂珂喜欢吃香蕉。这里有 n 堆香蕉，第 i 堆中有 piles[i]
根香蕉。警卫已经离开了，将在 h 小时后回来。
珂珂可以决定她吃香蕉的速度 k
（单位：根/小时）。每个小时，她将会选择一堆香蕉，从中吃掉 k 根。如果这堆香蕉少于
k 根，她将吃掉这堆的所有香蕉，然后这一小时内不会再吃更多的香蕉。
珂珂喜欢慢慢吃，但仍然想在警卫回来前吃掉所有的香蕉。
返回她可以在 h 小时内吃掉所有香蕉的最小速度 k（k 为整数）。
示例 1：
  输入：piles = [3,6,7,11], h = 8
  输出：4
示例 2：
  输入：piles = [30,11,23,4,20], h = 5
  输出：30
示例 3：
  输入：piles = [30,11,23,4,20], h = 6
  输出：23
提示：
  1 <= piles.length <= 104
  piles.length <= h <= 109
  1 <= piles[i] <= 109 */

int minEatingSpeed(vector<int>& piles, int h) {
  long long l = 1, r = accumulate(piles.begin(), piles.end(), 0ll);
  while (l <= r) {
    long m = l + ((r - l) >> 1);
    int hour = 0;
    for (const int& i : piles) {
      hour += (i - 1) / m + 1;
    }
    if (hour > h)
      l = m + 1;
    else
      r = m - 1;
  }
  return l;
}

// 自变量是吃香蕉速度x，最慢为1，如此时间最长，为总香蕉数量。最快为最大的那一堆香蕉数量，如此时间最短，为堆数
// 二分法，对每一种速度x，遍历每一堆求总时间cnt，注意数量范围[1,m]之内的堆，对应速度m，结果应该等于1，则特殊向上取整处理。
// 时间过长cnt>h，应加快速度，left右移。反之cnt<h，可以减缓速度，right左移。
// 注意时间相等时，可以尝试再慢一些，而不是直接返回答案。故cnt<=h是right左移的条件，最终返回的是左指针
// 时间复杂度O(NlogN)。
int minEatingSpeed1(vector<int>& piles, int h) {
  int maxVal = *max_element(piles.begin(), piles.end());
  int left = 1, right = maxVal;
  while (left <= right) {
    int mid = left + ((right - left) >> 1);
    int cnt = 0;
    for (const int& i : piles) {
      cnt += (i - 1) / mid + 1;
    }
    if (cnt > h) {
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }
  return left;
}

int main() {
  vector<int> vec1 = {3, 6, 7, 11}, vec2 = {30, 11, 23, 4, 20},
              vec3 = {30, 11, 23, 4, 20}, vec4 = {1, 1, 1, 999999999},
              vec5 = {332484035, 524908576, 855865114, 632922376, 222257295,
                      690155293, 112677673, 679580077, 337406589, 290818316,
                      877337160, 901728858, 679284947, 688210097, 692137887,
                      718203285, 629455728, 941802184};
  cout << minEatingSpeed(vec1, 8) << " " << minEatingSpeed(vec2, 5) << " "
       << minEatingSpeed(vec3, 6) << " " << minEatingSpeed(vec4, 10) << " "
       << minEatingSpeed(vec5, 823855818) << endl;
  cout << minEatingSpeed1(vec1, 8) << " " << minEatingSpeed1(vec2, 5) << " "
       << minEatingSpeed1(vec3, 6) << " " << minEatingSpeed1(vec4, 10) << " "
       << minEatingSpeed1(vec5, 823855818) << endl;
  return 0;
}