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
输入：nums = [0,3,7,2,5,8,4,6,0,1]/
输出：9 */

int longestConsecutive(vector<int>& nums) {
  unordered_set<int> uset;
  for (int i : nums)
    uset.insert(i);
  int ans = 0;
  for (auto i : uset) {
    if (uset.count(i - 1) == 0) {
      int cnt = 0;
      while (uset.count(i++))
        cnt++;
      ans = max(ans, cnt);
    }
  }
  return ans;
}

// 遍历uset，只能去重，不能排序。最长连续序列起点，其前一位数字一定不在set内，故只对num-1不在set中的情况，记录当前数字，当前长度为1
// 基于当前数字，其后一位数字，只要其还在set内，长度和数字即不断加1，与此前的最大返回值比较，得到最终返回值。空间和时间复杂度均为O(n)
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
  vector<int> temp1 = {100, 4, 200, 1, 3, 2},
              temp2 = {0, 3, 7, 2, 5, 8, 4, 6, 0, 1}, temp3 = {};
  cout << longestConsecutive(temp1) << " " << longestConsecutive(temp2) << " "
       << longestConsecutive(temp3) << endl;
  cout << longestConsecutive1(temp1) << " " << longestConsecutive1(temp2) << " "
       << longestConsecutive1(temp3) << endl;
}