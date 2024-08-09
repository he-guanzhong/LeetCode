#include "head.h"
/* 1356. 根据数字二进制下 1 的数目排序
给你一个整数数组 arr 。请你将数组中的元素按照其二进制表示中数字 1
的数目升序排序。
如果存在多个数字二进制中 1 的数目相同，则必须将它们按照数值大小升序排列。
请你返回排序后的数组。
示例 1：
  输入：arr = [0,1,2,3,4,5,6,7,8]
  输出：[0,1,2,4,8,3,5,6,7]
  解释：[0] 是唯一一个有 0 个 1 的数。
    [1,2,4,8] 都有 1 个 1 。
    [3,5,6] 有 2 个 1 。
    [7] 有 3 个 1 。
    按照 1 的个数排序得到的结果数组为 [0,1,2,4,8,3,5,6,7]
示例 2：
  输入：arr = [1024,512,256,128,64,32,16,8,4,2,1]
  输出：[1,2,4,8,16,32,64,128,256,512,1024]
  解释：数组中所有整数二进制下都只有 1 个 1 ，所以你需要按照数值大小将它们排序。
示例 3：
  输入：arr = [10000,10000]
  输出：[10000,10000]
示例 4：
  输入：arr = [2,3,5,7,11,13,17,19]
  输出：[2,3,5,17,7,11,13,19]
示例 5：
  输入：arr = [10,100,1000,10000]
  输出：[10,100,10000,1000] */

vector<int> sortByBits(vector<int>& arr) {
  vector<pair<int, int>> tmp(arr.size());
  for (int i = 0; i < arr.size(); i++) {
    tmp[i].first = arr[i];
    int n = arr[i];
    int cnt = 0;
    while (n) {
      n &= (n - 1);
      cnt++;
    }
    tmp[i].second = cnt;
  }
  sort(tmp.begin(), tmp.end(), [](pair<int, int> a, pair<int, int> b) {
    if (a.second != b.second)
      return a.second < b.second;
    else
      return a.first < b.first;
  });
  vector<int> ans(arr.size());
  for (int i = 0; i < arr.size(); i++)
    ans[i] = tmp[i].first;
  return ans;
}

// 独立函数计算bitCount
static int bitCount1(int n) {
  int cnt = 0;
  while (n) {
    n &= n - 1;  // 加减法4级，复合赋值14级
    cnt++;
  }
  return cnt;
}
static bool cmp1(int a, int b) {
  int bitA = bitCount1(a), bitB = bitCount1(b);
  if (bitA == bitB)
    return a < b;
  else
    return bitA < bitB;
}
vector<int> sortByBits1(vector<int>& arr) {
  sort(arr.begin(), arr.end(), cmp1);
  return arr;
}

int main() {
  vector<int> arr1 = {0, 1, 2, 3, 4, 5, 6, 7, 8},
              arr2 = {1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1},
              arr3 = {10000, 10000}, arr4 = {2, 3, 5, 7, 11, 13, 17, 19},
              arr5 = {10, 100, 1000, 10000};
  printVector(sortByBits(arr1));
  printVector(sortByBits(arr2));
  printVector(sortByBits(arr3));
  printVector(sortByBits(arr4));
  printVector(sortByBits(arr5));
  printVector(sortByBits1(arr1));
  printVector(sortByBits1(arr2));
  printVector(sortByBits1(arr3));
  printVector(sortByBits1(arr4));
  printVector(sortByBits1(arr5));
  return 0;
}