#include "head.h"
/* 287. 寻找重复数
给定一个包含 n + 1 个整数的数组 nums ，其数字都在 [1, n] 范围内（包括 1 和
n），可知至少存在一个重复的整数。
假设 nums 只有 一个重复的整数 ，返回 这个重复的数 。
你设计的解决方案必须 不修改 数组 nums 且只用常量级 O(1) 的额外空间。
示例 1：
输入：nums = [1,3,4,2,2]
输出：2
示例 2：
输入：nums = [3,1,3,4,2]
输出：3 */

int findDuplicate(vector<int>& nums) {
  int slow = 0, fast = 0;
  do {
    slow = nums[slow];
    fast = nums[nums[fast]];
  } while (fast != slow);
  fast = 0;
  while (fast != slow) {
    slow = nums[slow];
    fast = nums[fast];
  }
  return slow;
}

// 重复数可能不止一个，故不能通过数学方式求差。问题转化为链表找入口。将i和num[i]建立映射。有重复元素，则某num[i]必入度为2，链表成环
// do-while语句可以实现快慢指针同一位置起步，但起步允许快走两步、慢走一步。最终停止在交汇点。慢指针返回起始点0，快、慢每轮各走一步，交汇点即为重复点
// 时间复杂度O(n),空间复杂度O(1)
int findDuplicate1(vector<int>& nums) {
  int slow = 0;
  int fast = 0;
  do {
    slow = nums[slow];
    fast = nums[nums[fast]];
  } while (slow != fast);
  slow = 0;
  while (slow != fast) {
    slow = nums[slow];
    fast = nums[fast];
  }
  return slow;
}

int main() {
  vector<int> nums1 = {1, 3, 4, 2, 2}, nums2 = {3, 1, 3, 4, 2},
              nums3 = {2, 2, 2, 2, 2}, nums4 = {1, 5, 1};
  cout << findDuplicate(nums1) << " " << findDuplicate(nums2) << " "
       << findDuplicate(nums3) << endl;
  cout << findDuplicate1(nums1) << " " << findDuplicate1(nums2) << " "
       << findDuplicate1(nums3) << endl;
  return 0;
}