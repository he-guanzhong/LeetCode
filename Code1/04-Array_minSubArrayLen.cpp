#include "head.h"
/* 209. 长度最小的子数组
给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s
的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。
示例：
  输入：s = 7, nums = [2,3,1,2,4,3]
  输出：2
  解释：子数组 [4,3]
    是该条件下的长度最小的子数组。
  提示： 1 <= target <= 10^9
        1 <= nums.length <= 10^5 1 <= nums[i] <= 10^5 */

int minSubArrayLen(int target, vector<int>& nums) {
  int j = 0;
  int ans = INT_MAX, sum = 0;
  for (int i = 0; i < nums.size(); i++) {
    sum += nums[i];
    while (j <= i && sum >= target) {
      ans = min(ans, i - j + 1);
      sum -= nums[j++];
    }
  }
  return ans == INT_MAX ? 0 : ans;
}

// 求的是子数组长度，故不贪心，不动态规划。滑动窗口（双指针）即可。保证窗口内总和小于target。
// 同一窗口右界，允许多次挪动窗口左界，while。结果result初始化为INT_MAX。返回值需判断result是否更新过。
// 无更新则说明所有总和依然小于target，直接返回0

// 暴力求解, 双循环遍历，注意定义结果初始值位INT_MAX
int minSubArrayLen1(int s, vector<int>& nums) {
  int res = INT_MAX;
  for (int i = 0; i < nums.size(); i++) {
    int sum = 0;
    int subLength = 0;
    for (int j = i; j < nums.size(); j++) {
      sum += nums[j];
      if (sum >= s) {
        subLength = j - i + 1;
        res = min(res, subLength);
        break;  // 只要找到大的，就可以停止
      }
    }
  }
  return res == INT_MAX ? 0 : res;
}
// 滑动窗口，即双指针。窗口右端为遍历标的，左端为保证窗口内总和小于target的边界。只要窗口内总和大于target，即不断地缩小窗口。
// 使用整型result保存窗口宽度，由于题目求最小宽度，故初始化为INT_MAX。时间复杂度O(n)=n，因为每个元素只有进入窗口一次，出去一次，总计2n
int minSubArrayLen2(int s, vector<int>& nums) {
  int res = INT_MAX;
  int i = 0;  // 起始位置
  int sum = 0;
  int subLength = 0;
  for (int j = 0; j < nums.size(); j++) {
    sum += nums[j];
    while (sum >= s) {
      subLength = j - i + 1;
      res = min(subLength, res);
      sum -= nums[i++];  // 核心，不断变更起始点的位置
    }
  }
  return res == INT_MAX ? 0 : res;
}
int main() {
  vector<int> nums = {2, 3, 1, 2, 4, 3};
  int s1 = 7, s2 = 100;
  cout << minSubArrayLen(s1, nums) << " " << minSubArrayLen(s2, nums) << endl;
  cout << minSubArrayLen2(s1, nums) << " " << minSubArrayLen2(s2, nums) << endl;
  return 0;
}