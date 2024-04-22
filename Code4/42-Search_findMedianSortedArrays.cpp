#include "head.h"
/* 4. 寻找两个正序数组的中位数
给定两个大小分别为 m 和 n 的正序（从小到大）数组 nums1 和
nums2。请你找出并返回这两个正序数组的 中位数 。
算法的时间复杂度应该为 O(log (m+n)) 。
示例 1：
输入：nums1 = [1,3], nums2 = [2]
输出：2.00000
解释：合并数组 = [1,2,3] ，中位数 2
示例 2：
输入：nums1 = [1,2], nums2 = [3,4]
输出：2.50000
解释：合并数组 = [1,2,3,4] ，中位数 (2 + 3) / 2 = 2.5 */

int getKmin(vector<int>& nums1,
            vector<int>& nums2,
            int l1,
            int r1,
            int l2,
            int r2,
            int k) {
  int len1 = r1 - l1 + 1, len2 = r2 - l2 + 1;
  if (len1 > len2)
    return getKmin(nums2, nums1, l2, r2, l1, r1, k);
  if (len1 == 0)
    return nums2[l2 + k - 1];
  if (k == 1)
    return min(nums1[l1], nums2[l2]);
  int i = l1 + min(k / 2, len1) - 1, j = l2 + min(k / 2, len2) - 1;
  if (nums1[i] < nums2[j])
    return getKmin(nums1, nums2, i + 1, r1, l2, r2, k - (i - l1 + 1));
  else
    return getKmin(nums1, nums2, l1, r1, j + 1, r2, k - (j - l2 + 1));
}
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
  int len1 = nums1.size(), len2 = nums2.size();
  return (getKmin(nums1, nums2, 0, len1 - 1, 0, len2 - 1,
                  (len1 + len2 + 1) / 2) +
          getKmin(nums1, nums2, 0, len1 - 1, 0, len2 - 1,
                  (len1 + len2) / 2 + 1)) /
         2.0;
}

// 简易思路是两个数组合并，根据长度为奇数、偶数返回中位数，时间复杂度和空间复杂度均为O(m+n)
// 问题转化为求第k个最小元素。主函数可以求两个第k值，即（总长度+1）/2，和（总长度）+2/2，取中二者平均值
// 辅助函数为求第k个最小元素，传入参数为两数组，各个起始、终止点，当前剩余k。首先求两数组长度，利用递归参数交换，保证len1<len2
// 如果len1已经为0，返回len2有效区间的第k小的元素。如果k==1，即求len1和len2两个有效区间首元素最小值
// 以长度k/2为截断点，注意排除其长度可能已经超过Len1或len2的意外。两截断点值nums1[i]和nums2[j]更小的一个，前方舍弃，start从i+1，k长度亦更新
int getKthElem1(vector<int>& nums1,
                int start1,
                int end1,
                vector<int>& nums2,
                int start2,
                int end2,
                int k) {
  int len1 = end1 - start1 + 1, len2 = end2 - start2 + 1;
  if (len1 > len2)  // 保证len1短于len2
    return getKthElem1(nums2, start2, end2, nums1, start1, end1, k);
  if (len1 == 0)  // 如果len1过短，返回len2第k小的元素
    return nums2[start2 + k - 1];
  else if (k == 1)  // 需要返回第一小的元素，看l1和l2的当前区间首元素，更小之
    return min(nums1[start1], nums2[start2]);
  int i = start1 + min(len1, k / 2) - 1;
  int j = start2 + min(len2, k / 2) - 1;
  // 取更小一段，start更新为截至点+1，k要减去本次截断长度
  if (nums1[i] < nums2[j])
    return getKthElem1(nums1, i + 1, end1, nums2, start2, end2,
                       k - (i - start1 + 1));
  else
    return getKthElem1(nums1, start1, end1, nums2, j + 1, end2,
                       k - (j - start2 + 1));
}
// 无论奇偶，求第k个元素，可以是（总长度+1）/2，和（总长度）+2/2二者平均值代替
double findMedianSortedArrays1(vector<int>& nums1, vector<int>& nums2) {
  int m = nums1.size(), n = nums2.size();
  int left = (m + n + 1) / 2, right = (m + n + 2) / 2;
  return (getKthElem1(nums1, 0, m - 1, nums2, 0, n - 1, left) +
          getKthElem1(nums1, 0, m - 1, nums2, 0, n - 1, right)) /
         2.0;
}

int main() {
  vector<int> nums1 = {1, 3}, nums2 = {2}, nums3 = {1, 2}, nums4 = {3, 4};
  cout << findMedianSortedArrays(nums1, nums2) << " "
       << findMedianSortedArrays(nums3, nums4) << " " << endl;
  cout << findMedianSortedArrays1(nums1, nums2) << " "
       << findMedianSortedArrays1(nums3, nums4) << " " << endl;
  return 0;
}