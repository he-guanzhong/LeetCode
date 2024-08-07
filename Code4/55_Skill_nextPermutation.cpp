#include "head.h"
/* 31. 下一个排列
整数数组的一个 排列  就是将其所有成员以序列或线性顺序排列。
    例如，arr = [1,2,3] ，以下这些都可以视作 arr
的排列：[1,2,3]、[1,3,2]、[3,1,2]、[2,3,1] 。
整数数组的 下一个排列
是指其整数的下一个字典序更大的排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，那么数组的
下一个排列
就是在这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列（即，其元素按升序排列）。
    例如，arr = [1,2,3] 的下一个排列是 [1,3,2] 。
    类似地，arr = [2,3,1] 的下一个排列是 [3,1,2] 。
    而 arr = [3,2,1] 的下一个排列是 [1,2,3] ，因为 [3,2,1]
不存在一个字典序更大的排列。
给你一个整数数组 nums ，找出 nums 的下一个排列。
必须 原地 修改，只允许使用额外常数空间。
示例 1：
  输入：nums = [1,2,3]
  输出：[1,3,2]
示例 2：
  输入：nums = [3,2,1]
  输出：[1,2,3]
示例 3：
  输入：nums = [1,1,5]
  输出：[1,5,1] */

void nextPermutation(vector<int>& nums) {
  for (int i = nums.size() - 1; i >= 0; i--) {
    for (int j = nums.size() - 1; j > i; j--) {
      if (nums[j] > nums[i]) {
        swap(nums[i], nums[j]);
        reverse(nums.begin() + i + 1, nums.end());
        return;
      }
    }
  }
  reverse(nums.begin(), nums.end());
}

// 不要使用回溯全排列。实质是找组成整数紧接着更大的一个。第一步，从后向前，找第一个有序数对a[i]<a[i+1]。具体操作是先初始化i=n-2，如果a[i]>=a[i+1]就不断前移
// 找[i+1,n)区间内（必为降序），第一次出现a[j]>a[i]的位置，交换i和j。对[i+1,n)区间重新按从小到大排序。注意，如果i==-1说明一直没有找到，说明为全降序，直接反转序列
// 时间复杂度O(n)，因为至多扫描两遍序列，一遍反转，且原地修改。空间复杂度O(1)，此函数为C++标准库函数next_permutation
void nextPermutation1(vector<int>& nums) {
  int i = nums.size() - 2;
  while (i >= 0 && nums[i] >= nums[i + 1])
    i--;
  if (i >= 0) {
    int j = nums.size() - 1;
    while (j >= 0 && nums[j] <= nums[i])
      j--;
    swap(nums[i], nums[j]);
  }
  reverse(nums.begin() + i + 1, nums.end());
}

// 数组是中间高两边低的尖峰型，核心是找到第一个左侧nums[i]小于右侧nums[j]的对，二者置换，然后对置换后[i+1,n]区间反转重排
void nextPermutation2(vector<int>& nums) {
  for (int i = nums.size() - 1; i >= 0; i--) {
    for (int j = nums.size() - 1; j > i; j--) {
      if (nums[j] > nums[i]) {
        swap(nums[i], nums[j]);
        reverse(nums.begin() + i + 1, nums.end());
        return;
      }
    }
  }
  reverse(nums.begin(), nums.end());
}

void nextPermutation3(vector<int>& nums) {
  next_permutation(nums.begin(), nums.end());
}

int main() {
  vector<int> nums1 = {1, 2, 3}, nums2 = {3, 2, 1}, nums3 = {1, 1, 5},
              nums4 = {1, 5, 1};
  nextPermutation(nums1);
  nextPermutation(nums2);
  nextPermutation(nums3);
  nextPermutation(nums4);
  printVector(nums1);
  printVector(nums2);
  printVector(nums3);
  printVector(nums4);
  nums1 = {1, 2, 3}, nums2 = {3, 2, 1}, nums3 = {1, 1, 5}, nums4 = {1, 5, 1};
  nextPermutation1(nums1);
  nextPermutation1(nums2);
  nextPermutation1(nums3);
  nextPermutation1(nums4);
  printVector(nums1);
  printVector(nums2);
  printVector(nums3);
  printVector(nums4);
  return 0;
}
