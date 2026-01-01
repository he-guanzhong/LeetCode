#include "head.h"
/* 454. 四数相加 II
给你四个整数数组 nums1、nums2、nums3 和 nums4 ，数组长度都是 n
，请你计算有多少个元组 (i, j, k, l) 能满足： 0 <= i, j, k, l < n nums1[i] +
nums2[j] + nums3[k] + nums4[l] == 0
为了使问题简单化，所有的 A, B, C, D
具有相同的长度 N，且 0 ≤ N ≤ 500 。所有整数的范围在 -2^28 到 2^28 - 1
之间，最终结果不会超过 2^31 - 1 。
例如:
  输入: A = [ 1, 2] B = [-2,-1] C = [-1, 2] D = [ 0, 2]
  输出:2
  解释:两个元组如下:
    (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
    (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0 */

int fourSumCount(vector<int>& nums1,
                 vector<int>& nums2,
                 vector<int>& nums3,
                 vector<int>& nums4) {
  unordered_map<int, int> umap;
  for (int i = 0; i < nums1.size(); i++) {
    for (int j = 0; j < nums2.size(); j++) {
      umap[nums1[i] + nums2[j]]++;
    }
  }
  int ans = 0;
  for (int i = 0; i < nums3.size(); i++) {
    for (int j = 0; j < nums4.size(); j++) {
      if (umap.find(-nums3[i] - nums4[j]) != umap.end())
        ans += umap[-nums3[i] - nums4[j]];
    }
  }
  return ans;
}

// 四个独立数组，总和是0的可能数，分两个组计算大小，第一组AB时，unordered_map记录总和，和该和出现的次数
// 遍历第二组时，如果CD总和的负数，在哈希表出现过。设立计数cnt，加上该和在第一组出现的次数
// 注意，哈希表的第二个值，不是记录坐标，而是记录次数，因为同样总和是2，第一组可能有很多种排列组合
int fourSumCount1(vector<int>& A,
                  vector<int>& B,
                  vector<int>& C,
                  vector<int>& D) {
  unordered_map<int, int> umap;  // key 存放a+b，value存放次数
  for (int a : A) {
    for (int b : B) {
      umap[a + b]++;
    }
  }
  int count = 0;  // a+b+c+d总次数
  for (int c : C) {
    for (int d : D) {
      if (umap.find(0 - c - d) != umap.end())  // 一旦相等，提取存放次数
        count += umap[0 - c - d];
    }
  }
  return count;
}

int main() {
  vector<int> A1 = {1, 2}, B1 = {-2, -1}, C1 = {-1, 2}, D1 = {0, 2};
  vector<int> A2 = {-1, -1}, B2 = {-1, 1}, C2 = {-1, 1}, D2 = {1, -1};
  cout << fourSumCount(A1, B1, C1, D1) << " " << fourSumCount(A2, B2, C2, D2)
       << endl;
  cout << fourSumCount1(A1, B1, C1, D1) << " " << fourSumCount1(A2, B2, C2, D2)
       << endl;
  return 0;
}