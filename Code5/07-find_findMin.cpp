#include "head.h"
/* 154. 寻找旋转排序数组中的最小值 II
已知一个长度为 n 的数组，预先按照升序排列，经由 1 到 n 次 旋转
后，得到输入数组。例如，原数组 nums = [0,1,4,4,5,6,7] 在变化后可能得到：
    若旋转 4 次，则可以得到 [4,5,6,7,0,1,4]
    若旋转 7 次，则可以得到 [0,1,4,4,5,6,7]
注意，数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次 的结果为数组 [a[n-1], a[0],
a[1], a[2], ..., a[n-2]] 。
给你一个可能存在 重复 元素值的数组 nums
，它原来是一个升序排列的数组，并按上述情形进行了多次旋转。请你找出并返回数组中的
最小元素 。
你必须尽可能减少整个过程的操作步骤。
示例 1：
  输入：nums = [1,3,5]
  输出：1
示例 2：
  输入：nums = [2,2,2,0,1]
  输出：0 */
// 3,1,3
int findMin(vector<int>& nums) {
  int l = 0, r = nums.size() - 1;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    if (nums[m] == nums[r]) {
      r--;
    } else if (nums[m] > nums[r]) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  return nums[l];
}

// 相比旋转排序数组最小值1，本题多了数字可重复条件。依旧二分法，左右指针相遇即结束。
// 如果中间值大于右标杆，说明最小值必在其右，l=m+1。若中间值小于右标杆，说明最小值在左，或者就是该点，r=m
// 如果中间值等于右标杆，不知最小值在左或右。只能将右标杆向左迫近1。
int findMin1(vector<int>& nums) {
  int l = 0, r = nums.size() - 1;
  while (l < r) {
    int mid = l + ((r - l) >> 1);
    if (nums[mid] > nums[r])
      l = mid + 1;
    else if (nums[mid] < nums[r])
      r = mid;
    else
      r--;
  }
  return nums[l];
}

int main() {
  vector<int> doc1 = {1, 3, 5}, doc2 = {2, 2, 2, 0, 1}, doc3 = {3, 3, 1, 3},
              doc4 = {3, 1, 3};

  cout << findMin(doc1) << " " << findMin(doc2) << " " << findMin(doc3) << " "
       << findMin(doc4) << endl;
  cout << findMin1(doc1) << " " << findMin1(doc2) << " " << findMin1(doc3)
       << " " << findMin1(doc4) << endl;

  return 0;
}