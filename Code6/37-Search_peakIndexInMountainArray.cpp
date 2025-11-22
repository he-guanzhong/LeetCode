#include "head.h"
/* 852. 山脉数组的峰顶索引
给定一个长度为 n 的整数 山脉 数组 arr ，其中的值递增到一个 峰值元素 然后递减。
返回峰值元素的下标。
你必须设计并实现时间复杂度为 O(log(n)) 的解决方案。
示例 1：
  输入：arr = [0,1,0]
  输出：1
示例 2：
  输入：arr = [0,2,1,0]
  输出：1
示例 3：
  输入：arr = [0,10,5,2]
  输出：1
提示：
  3 <= arr.length <= 105
  0 <= arr[i] <= 106
  题目数据 保证 arr 是一个山脉数组 */

int peakIndexInMountainArray(vector<int>& arr) {
  int l = 1, r = arr.size() - 2;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    if (arr[m - 1] < arr[m] && arr[m] > arr[m + 1])
      return m;
    else if (arr[m - 1] < arr[m] && arr[m] < arr[m + 1])
      l = m + 1;
    else
      r = m - 1;
  }
  return 0;
}

// 二分法。中点的特性是，arr[i]>arr[i+1]，若满足则一定在左面，若不满足，一定在右面。
// 由于比较的是i和i+1，最终一步left==right时，有可能处于某一序列a<b>c中
// 假定m落在a位，a<b不满足条件，left标志位右移至b，为答案
// 也有可能m处于b位，b>c满足条件，right标志位左移至a，b不动。left为答案。
// 因此，left标志代表第一次满足arr[i]>arr[i+1]，即山峰下降的起点
int peakIndexInMountainArray1(vector<int>& arr) {
  int left = 0, right = arr.size() - 2;
  while (left <= right) {
    int m = left + ((right - left) >> 1);
    if (arr[m] > arr[m + 1]) {
      right = m - 1;
    } else {
      left = m + 1;
    }
  }
  return left;
}

// 也可以认为中点的特性是arr[m-1]<arr[m]，只要满足，说明中点在更右侧，左边界右移
// 因此，left含义是第一个不满足升序的位置。最终循环退出时必为right<left，则right为最后一个满足升序的位置，为答案
int peakIndexInMountainArray2(vector<int>& arr) {
  int left = 1, right = arr.size() - 1;
  while (left <= right) {
    int m = left + ((right - left) >> 1);
    if (arr[m] > arr[m - 1])
      left = m + 1;
    else
      right = m - 1;
  }
  return right;
}

int main() {
  vector<int> arr1({0, 1, 0}), arr2({0, 2, 1, 0}), arr3({0, 10, 5, 2}),
      arr4({3, 5, 3, 2, 0});
  cout << peakIndexInMountainArray(arr1) << " "
       << peakIndexInMountainArray(arr2) << " "
       << peakIndexInMountainArray(arr3) << " "
       << peakIndexInMountainArray(arr4) << endl;
  cout << peakIndexInMountainArray1(arr1) << " "
       << peakIndexInMountainArray1(arr2) << " "
       << peakIndexInMountainArray1(arr3) << " "
       << peakIndexInMountainArray1(arr4) << endl;
  return 0;
}