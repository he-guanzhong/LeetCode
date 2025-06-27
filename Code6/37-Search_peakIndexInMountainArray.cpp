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

// 二分法。中点的特性是，arr[i]>arr[i+1]，若满足则一定在左面，若不满足，一定在右面。
// 由于比较的是i和i+1，最终一步left==right时，其必定处于某一序列a<b>c的a位，不满足条件，left标志位右移，此即为答案
int peakIndexInMountainArray(vector<int>& arr) {
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

int main() {
  vector<int> arr1({0, 1, 0}), arr2({0, 2, 1, 0}), arr3({0, 10, 5, 2});
  cout << peakIndexInMountainArray(arr1) << " "
       << peakIndexInMountainArray(arr2) << " "
       << peakIndexInMountainArray(arr3) << endl;

  return 0;
}