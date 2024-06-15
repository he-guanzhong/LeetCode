#include "head.h"
/* 45. 跳跃游戏 II
给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。
每个元素 nums[i] 表示从索引 i 向前跳转的最大长度。换句话说，如果你在 nums[i]
处，你可以跳转到任意 nums[i + j] 处:
    0 <= j <= nums[i]
    i + j < n
返回到达 nums[n - 1] 的最小跳跃次数。生成的测试用例可以到达 nums[n - 1]。
示例 1:
输入: nums = [2,3,1,1,4]
输出: 2
解释: 跳到最后一个位置的最小跳跃数是 2。从下标为 0 跳到下标为 1 的位置，跳 1
步，然后跳 3 步到达数组的最后一个位置。
示例 2:
输入: nums = [2,3,0,1,4] 输出: 2 */

int jump(vector<int>& nums) {
  if (nums.size() == 1)
    return 0;
  int ans = 1;
  int cover = nums[0];
  int maxCover = 0;
  for (int i = 1; i < nums.size(); i++) {
    maxCover = max(maxCover, i + nums[i]);
    if (i >= cover) {
      ans++;
      cover = maxCover;
    }
    if (cover >= nums.size() - 1)
      break;
  }
  return ans;
}

// 排除一个元素不用跳的情况。如不想考虑特殊情况，则跳到nums.size()-1位置为止。记录当前覆盖，和下段覆盖。下段覆盖不断更新，
// 当前下标遇到当前覆盖范围，即更新当前覆盖范围，并结果加一。当前覆盖范围一旦大于末尾，返回结果。
// 取巧，题目规定必可到达终点。在倒数第二位nums.size()-2处停下。如此不必判断当前覆盖是否超过了最大边界。

// 最小的步数覆盖最大的范围。排除已经在终点不同跳的意外情况。
// 记录当前能到的最远距离，下一阶段能到的最远距离。当前距离内，更新下一步能到的最远距离
// 当光标移动到当前距离末端，意味着一定要再跳一步，更新此时的当前最远距离。额外判断，如当前最远距离大于重点，则不必判断，直接输出
int jump1(vector<int>& nums) {
  if (nums.size() == 1)  // 只有一个元素，则不用跳
    return 0;
  int nextDistance = 0;
  int curDistance = 0;
  int result = 0;
  for (int i = 0; i < nums.size(); i++) {
    nextDistance = max(nextDistance, nums[i] + i);
    if (i == curDistance) {
      result++;
      curDistance = nextDistance;
    }
    if (curDistance >= nums.size() - 1)
      break;
  }
  return result;
}

// 方法二，统一处理，遍历时在nums[n-2]的位置停下，如果已经到达了当前边界，则统一加一
// 如果没到当前边界，则正好输出。
int jump2(vector<int>& nums) {
  int nextDistance = 0, curDistance = 0, result = 0;
  for (int i = 0; i < nums.size() - 1; i++) {
    nextDistance = max(nextDistance, nums[i] + i);
    if (i == curDistance) {
      result++;
      curDistance = nextDistance;
    }
  }
  return result;
}

int main() {
  vector<int> nums1 = {2, 3, 1, 1, 4};
  vector<int> nums2 = {7, 0, 9, 6, 9, 6, 1, 7, 9, 0, 1, 2, 9, 0, 3};
  vector<int> nums3 = {1};
  vector<int> nums4 = {1, 1, 1, 1};
  cout << jump(nums1) << " " << jump(nums2) << " " << jump(nums3) << " "
       << jump(nums4) << endl;
  cout << jump1(nums1) << " " << jump1(nums2) << " " << jump1(nums3) << " "
       << jump1(nums4) << endl;
  return 0;
}