#include "head.h"
/* 55. 跳跃游戏
给你一个非负整数数组 nums ，你最初位于数组的 第一个下标
。数组中的每个元素代表你在该位置可以跳跃的最大长度。
判断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。
示例 1：
输入：nums = [2,3,1,1,4]
输出：true
解释：可以先跳 1 步，从下标 0 到达下标 1, 然后再从下标 1 跳 3
步到达最后一个下标。
示例 2：
输入：nums = [3,2,1,0,4]
输出：false
解释：无论怎样，总会到达下标为 3 的位置。但该下标的最大跳跃长度是 0 ，
所以永远不可能到达最后一个下标。 */

bool canJump(vector<int>& nums) {
  int right = 0;
  for (int i = 0; i <= right; i++) {
    if (right >= nums.size() - 1)
      return true;
    right = max(right, i + nums[i]);
  }
  return false;
}

// 覆盖范围cover代表最后一个可访问的下标，有前向后遍历，不断拓展cover范围，一旦发现cover大于nums.size-1即返回真。
// 注意遍历时，若cover过大，则i不应超过自身nums.size
// 计算每一步能cover到的最大范围，如果能覆盖最后一个结点，就返回真。
bool canJump1(vector<int>& nums) {
  int cover = 0;
  for (int i = 0; i <= cover; i++) {  // 这里是<=
    cover = max(cover, nums[i] + i);
    if (cover >= nums.size() - 1)
      return true;
  }
  return false;
}

int main() {
  vector<int> nums1 = {2, 3, 1, 1, 4};
  vector<int> nums2 = {3, 2, 1, 0, 4};
  vector<int> nums3 = {1};
  cout << canJump(nums1) << " " << canJump(nums2) << " " << canJump(nums3)
       << " " << endl;
  cout << canJump1(nums1) << " " << canJump1(nums2) << " " << canJump1(nums3)
       << " " << endl;
  return 0;
}