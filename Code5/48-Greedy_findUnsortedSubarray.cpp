#include "head.h"
/* 581. 最短无序连续子数组
给你一个整数数组 nums ，你需要找出一个 连续子数组
，如果对这个子数组进行升序排序，那么整个数组都会变为升序排序。
请你找出符合题意的 最短 子数组，并输出它的长度。
示例 1：
输入：nums = [2,6,4,8,10,9,15]
输出：5
解释：你只需要对 [6, 4, 8, 10, 9] 进行升序排序，那么整个表都会变为升序排序。
示例 2：
输入：nums = [1,2,3,4]
输出：0
示例 3：
输入：nums = [1]
输出：0
进阶：你可以设计一个时间复杂度为 O(n) 的解决方案吗？ */

int findUnsortedSubarray(vector<int>& nums) {
  int minV = INT_MAX, maxV = INT_MIN;
  int n = nums.size();
  int left = n - 1, right = 0;
  for (int i = 0; i < n; i++) {
    if (nums[i] >= maxV)
      maxV = nums[i];
    else
      right = i;
    if (nums[n - 1 - i] <= minV)
      minV = nums[n - 1 - i];
    else
      left = n - 1 - i;
  }
  return right > left ? right - left + 1 : 0;
}

// 方法一，排序。注意C++11新函数is_sorted()，其默认是less<>即e1<e2从小到大排列，此时greater<>是e1>e2从大到小排列
// 数组可以分为A(有序)-B(无序)-C(有序)三个部分。故整体排序后数组和原数组对比，确定B(无序)中的[i,j]区间
int findUnsortedSubarray1(vector<int>& nums) {
  if (is_sorted(nums.begin(), nums.end()))
    return 0;
  vector<int> numsSorted = nums;
  sort(numsSorted.begin(), numsSorted.end());
  int i = 0, j = nums.size() - 1;
  while (i < nums.size() && nums[i] == numsSorted[i])
    i++;
  while (j >= 0 && nums[j] == numsSorted[j])
    j--;
  return max(0, (j - i + 1));
}

// 一次遍历。初始化左、右下标为-1，临时最大值、最小值分别为INT最小值、最大值。使用i从左向右遍历，则n-1-i即为从右向左遍历的下标
// 从左向右看，数应越来越大（大于等于），不断更新临时最大值。若发现某元素小于临时最大值，说明此处为B（无序）右界i
// 从右向左看，数应越来越小（小于等于），不断更新临时最小值。若发现某元素大于临时最小值，说明此处为B（无序）左界n-i-1
// 若为以排序数列，则right未变化过，恒等于-1，则返回长度0，否则返回长度right-left+1
int findUnsortedSubarray2(vector<int>& nums) {
  int left = -1, right = -1;
  int n = nums.size();
  int maxNum = INT_MIN, minNum = INT_MAX;
  for (int i = 0; i < n; i++) {
    if (nums[i] >= maxNum)
      maxNum = nums[i];
    else
      right = i;
    if (nums[n - 1 - i] <= minNum)
      minNum = nums[n - 1 - i];
    else
      left = n - 1 - i;
  }
  return right == -1 ? 0 : right - left + 1;
}

int main() {
  vector<int> nums1 = {2, 6, 4, 8, 10, 9, 15}, nums2 = {1, 2, 3, 4},
              nums3 = {1}, nums4 = {1, 2, 3, 3, 3}, nums5 = {2, 1};
  cout << findUnsortedSubarray(nums1) << " " << findUnsortedSubarray(nums2)
       << " " << findUnsortedSubarray(nums3) << " "
       << findUnsortedSubarray(nums4) << " " << findUnsortedSubarray(nums5)
       << endl;
  cout << findUnsortedSubarray1(nums1) << " " << findUnsortedSubarray1(nums2)
       << " " << findUnsortedSubarray1(nums3) << " "
       << findUnsortedSubarray1(nums4) << " " << findUnsortedSubarray1(nums5)
       << endl;
  return 0;
}