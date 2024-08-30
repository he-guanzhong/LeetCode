#include "head.h"
/* 75. 颜色分类
给定一个包含红色、白色和蓝色、共 n 个元素的数组 nums
，原地对它们进行排序，使得相同颜色的元素相邻，并按照红色、白色、蓝色顺序排列。
我们使用整数 0、 1 和 2 分别表示红色、白色和蓝色。
必须在不使用库内置的 sort 函数的情况下解决这个问题。
示例 1：
  输入：nums = [2,0,2,1,1,0]
  输出：[0,0,1,1,2,2]
示例 2：
  输入：nums = [2,0,1]
  输出：[0,1,2]
进阶：
    你能想出一个仅使用常数空间的一趟扫描算法吗？ */

void sortColors(vector<int>& nums) {
  int k = nums.size() - 1, j = 0;
  for (int i = 0; i <= k; i++) {
    while (nums[i] == 2) {
      swap(nums[i], nums[k--]);
    }
    if (nums[i] == 0)
      swap(nums[i], nums[j++]);
    cout << "test " << i << " : ";
    printVector(nums);
  }
}

// 方法一，两次遍历，利用慢指针ptr，和swap函数，先排所有0到最前，然后从0的末尾开始，排1到最前，时间复杂度O(n)
void sortColors1(vector<int>& nums) {
  int ptr = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] == 0)
      swap(nums[i], nums[ptr++]);
  }
  for (int i = ptr; i < nums.size(); i++) {
    if (nums[i] == 1)
      swap(nums[i], nums[ptr++]);
  }
}
// 方法二，双指针，ptr0和ptr1记录下一个即将赋值的位置。先换1，再换0。如果换0后，ptr1>ptr0，说明将1队列的队首换走了。
// 此时要将该元素与ptr1再对换，将其换到1队列队尾。注意，换0时，无论换1与否，ptr1和ptr0均要增大
void sortColors2(vector<int>& nums) {
  int ptr0 = 0, ptr1 = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] == 1) {
      swap(nums[i], nums[ptr1]);
      ptr1++;
    } else if (nums[i] == 0) {
      swap(nums[i], nums[ptr0]);
      if (ptr0 < ptr1)
        swap(nums[i], nums[ptr1]);
      ptr1++;
      ptr0++;
    }
  }
}

// 方法三，双指针p0和p2，初始化为首\尾位置。循环遍历i一旦大于p2即终止。num[i]==2，将其置换到p2位置并更新，考虑到换过来的还可能是2，故要while
// 若num[i]==0则交换i和p0，若num[i]==1，不做任何操作
void sortColors3(vector<int>& nums) {
  int p0 = 0, p2 = nums.size() - 1;
  for (int i = 0; i <= p2; i++) {
    while (nums[i] == 2 && i <= p2) {
      swap(nums[i], nums[p2]);
      p2--;
    }
    if (nums[i] == 0) {
      swap(nums[i], nums[p0]);
      p0++;
    }
  }
}
int main() {
  vector<int> nums1 = {2, 0, 2, 1, 1, 0}, nums2 = {2, 0, 1},
              nums3 = {2, 1, 0, 1, 2}, nums4 = {2};
  sortColors(nums1);
  sortColors(nums2);
  sortColors(nums3);
  sortColors(nums4);
  printVector(nums1);
  printVector(nums2);
  printVector(nums3);
  printVector(nums4);

  nums1 = {2, 0, 2, 1, 1, 0}, nums2 = {2, 0, 1}, nums3 = {2, 1, 0, 1, 2},
  nums4 = {2};
  sortColors1(nums1);
  sortColors1(nums2);
  sortColors1(nums3);
  sortColors1(nums4);
  printVector(nums1);
  printVector(nums2);
  printVector(nums3);
  printVector(nums4);

  return 0;
}