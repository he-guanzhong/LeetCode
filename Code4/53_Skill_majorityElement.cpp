#include "head.h"
/* 169. 多数元素
给定一个大小为 n 的数组 nums ，返回其中的多数元素。多数元素是指在数组中出现次数
大于 ⌊ n/2 ⌋ 的元素。
你可以假设数组是非空的，并且给定的数组总是存在多数元素。
示例 1：
输入：nums = [3,2,3]
输出：3
示例 2：
输入：nums = [2,2,1,1,1,2,2]
输出：2
进阶：尝试设计时间复杂度为 O(n)、空间复杂度为 O(1) 的算法解决此问题。*/

int majorityElement(vector<int>& nums) {
  int ans = nums[0];
  int n = 0;
  for (int i : nums) {
    if (ans == i)
      n++;
    else if (--n < 0) {
      n = 1;
      ans = i;
    }
  }
  return ans;
}

// 推荐使用Boyer-Moore投票算法。设置计数器cnt为0。当前众数候选值candidate（任意）。遍历每个元素，如candidate==num，则计数加一
// 如果不等，则计数减一，若cnt为负，candidate要置换为当前num，并更新计数为cnt。可以设想双方夺旗场景。cnt实质是当前众数与其余新值的差
int majorityElement1(vector<int>& nums) {
  int cnt = 0;
  int candidate = 0;
  for (int num : nums) {
    if (num == candidate)
      cnt++;
    else {
      cnt--;
      if (cnt < 0) {
        candidate = num;
        cnt = 1;
      }
    }
  }
  return candidate;
}

// 方法一，哈希表记录每个元素出现次数，若大于n/2就返回。时间、空间复杂度均为O(n)。方法二，排序并取下标为n/2的元素值，时间复杂度O(nlogn)，空间复杂度log(n)
int majorityElement2(vector<int>& nums) {
  sort(nums.begin(), nums.end());
  return nums[nums.size() / 2];
}

int main() {
  vector<int> nums1 = {3, 2, 3}, nums2 = {2, 2, 1, 1, 1, 2, 2}, nums3 = {1};
  cout << majorityElement(nums1) << " " << majorityElement(nums2) << " "
       << majorityElement(nums3) << endl;
  cout << majorityElement1(nums1) << " " << majorityElement1(nums2) << " "
       << majorityElement1(nums3) << endl;
  return 0;
}