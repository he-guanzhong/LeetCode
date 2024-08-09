#include "head.h"
/* 128. 最长连续序列
给定一个未排序的整数数组 nums
，找出数字连续的最长序列（不要求序列元素在原数组中连续）的长度。
请你设计并实现时间复杂度为 O(n) 的算法解决此问题。
示例 1：
  输入：nums = [100,4,200,1,3,2]
  输出：4
  解释：最长数字连续序列是 [1, 2, 3, 4]。它的长度为 4。
示例 2：
  输入：nums = [0,3,7,2,5,8,4,6,0,1]
  输出：9
提示：
    0 <= nums.length <= 105
    -109 <= nums[i] <= 109 */

int longestConsecutive(vector<int>& nums) {
  unordered_set<int> uset(nums.begin(), nums.end());
  int ans = 0;
  for (const int& num : nums) {
    uset.insert(num);
    if (uset.find(num - 1) == uset.end()) {
      int cnt = 1;
      int tmp = num + 1;
      while (uset.find(tmp) != uset.end()) {
        cnt++;
        tmp++;
      }
      ans = max(ans, cnt);
    }
  }
  return ans;
}

// 核心是判断一个数，是不是连续序列的首元素。首先要对数组全部元素是否存在状态已知，使用哈希表uset记录，并去重所有元素。
// 遍历uset。最长连续序列起点，其前一位数字一定不在uset内，故只对num-1不在set中的情况，记录当前数字，当前长度为1
// 基于当前数字，其后一位数字只要还在set内，长度和数字即不断加1，即得到该段连续数字的长度。
// 变量记录所有连续数字段的长度，取其最大值为最终返回值。空间和时间复杂度均为O(n)
int longestConsecutive1(vector<int>& nums) {
  unordered_set<int> nums_set;
  int result = 0;
  for (const int& num : nums)
    nums_set.insert(num);
  for (const int& num : nums_set) {
    if (nums_set.count(num - 1) == 0) {
      int cur = num;
      int length = 1;
      while (nums_set.count(cur + 1) > 0) {
        length++;
        cur++;
      }
      result = max(result, length);
    }
  }
  return result;
}

int main() {
  vector<int> num1 = {100, 4, 200, 1, 3, 2},
              num2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1}, num3 = {}, num4 = {0},
              num5 = {0, -1};
  cout << longestConsecutive(num1) << " " << longestConsecutive(num2) << " "
       << longestConsecutive(num3) << " " << longestConsecutive(num4) << " "
       << longestConsecutive(num5) << endl;
  cout << longestConsecutive1(num1) << " " << longestConsecutive1(num2) << " "
       << longestConsecutive1(num3) << " " << longestConsecutive1(num4) << " "
       << longestConsecutive1(num5) << endl;
  return 0;
}