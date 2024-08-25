#include <ctime>
#include "head.h"
/* 215. 数组中的第K个最大元素
给定整数数组 nums 和整数 k，请返回数组中第 k 个最大的元素。
请注意，你需要找的是数组排序后的第 k 个最大的元素，而不是第 k 个不同的元素。
你必须设计并实现时间复杂度为 O(n) 的算法解决此问题。
示例 1:
  输入: [3,2,1,5,6,4], k = 2
  输出: 5
示例 2:
  输入: [3,2,3,1,2,4,5,5,6], k = 4
  输出: 4 */
void quickSort(vector<int>& nums, int k, int start, int end) {
  if (start > end)
    return;
  srand(time(nullptr));
  int random = rand() % (end - start + 1) + start;
  swap(nums[random], nums[start]);
  int j = start;
  for (int i = start + 1; i <= end; i++) {
    if (nums[i] >= nums[start]) {
      swap(nums[i], nums[j + 1]);
      j++;
    }
  }
  swap(nums[start], nums[j]);
  /*   cout << "j: " << j << " \t";
    printVector(nums); */
  if (j > k - 1)
    quickSort(nums, k, start, j - 1);
  else if (j < k - 1)
    quickSort(nums, k, j + 1, end);
}
int findKthLargest(vector<int>& nums, int k) {
  quickSort(nums, k, 0, nums.size() - 1);
  return nums[k - 1];
}

// 对于set和map，greater<>是从大到小排序。对于优先队列，greater<>是小顶堆。但如此空间复杂度O(nlogn)不符合题意
// 快速排序。专职函数无返回值，每轮排序仅在[start,end]中进行，如作为传入参数，第k大的元素下标为k-1，也传入。退出条件为已排下标index等于第k大下标
// 选定哨兵（随机生成）放置队首，设置index为待交换点。遍历其后所有元素，大于等于标杆的靠前，小的自然靠后。挪动哨兵至应有位置index
// 注意，index要回退一位，到已排序部分的最后一位，然后与队首交换，如此index即为队首应该在的位置。
// 若已排位index大于k，说明在前半部分，消除相等元素影响，index--，在[start,index)继续排序，同理，若已排位index小于k，后半部分，index++消除相等元素影响，在(index,end]内排序
// 时间复杂度O(n)因为引入了随机化加速，空间复杂度O(logn)因为递归栈空间
void quickSort1(vector<int>& nums, int start, int end, int target) {
  if (start > end)
    return;
  srand(time(nullptr));
  int random = rand() % (end - start + 1) + start;
  int base = nums[random];
  swap(nums[start], nums[random]);
  int index =
      start;  // 此处是核心，index初始化为已经完成排序的最后一位。不可以写成start+1，因为后面有强制交换
  for (int i = start + 1; i <= end; i++) {
    if (nums[i] >= base) {
      swap(nums[index + 1], nums[i]);
      index++;
    }
  }
  swap(nums[index], nums[start]);
  if (index < target) {
    while (index < target && nums[index] == nums[index + 1])
      index++;
    quickSort1(nums, index + 1, end, target);
  } else if (index > target) {
    while (index > target && nums[index] == nums[index - 1])
      index--;
    quickSort1(nums, start, index - 1, target);
  } else
    return;
}
int findKthLargest1(vector<int>& nums, int k) {
  quickSort1(nums, 0, nums.size() - 1, k - 1);
  return nums[k - 1];
}

// 直接建堆。
int findKthLargest2(vector<int>& nums, int k) {
  make_heap(nums.begin(), nums.end());
  for (int i = 0; i < k - 1; i++) {
    pop_heap(nums.begin(), nums.end());
    nums.pop_back();
  }
  return nums[0];
}

int main() {
  vector<int> nums1 = {3, 2, 1, 5, 6, 4}, nums2 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
  cout << findKthLargest(nums1, 2) << " " << findKthLargest(nums2, 4) << " "
       << findKthLargest(nums1, 2) << " " << findKthLargest(nums2, 4) << endl;
  cout << findKthLargest1(nums1, 2) << " " << findKthLargest1(nums2, 4) << " "
       << findKthLargest1(nums1, 2) << " " << findKthLargest1(nums2, 4) << endl;
  return 0;
}