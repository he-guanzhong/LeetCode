#include "head.h"
/* 34. 有多少小于当前数字的数字
给你一个数组nums，对于其中每个元素nums[i]，请你统计数组中比它小的所有数字的数目。
换而言之，对于每个 nums[i] 你必须计算出有效的 j 的数量，其中 j 满足 j != i 且
nums[j] < nums[i] 。
以数组形式返回答案。
示例 1：
  输入：nums = [8,1,2,2,3]
  输出：[4,0,1,1,3]
  解释：
    对于 nums[0]=8 存在四个比它小的数字：（1，2，2 和 3）。
    对于 nums[1]=1 不存在比它小的数字。
    对于 nums[2]=2 存在一个比它小的数字：（1）。
    对于 nums[3]=2 存在一个比它小的数字：（1）。
    对于 nums[4]=3 存在三个比它小的数字：（1，2 和 2）。
示例 2：
  输入：nums = [6,5,4,8]
  输出：[2,1,0,3]
示例 3：
  输入：nums = [7,7,7,7]
  输出：[0,0,0,0]
提示：
  2 <= nums.length <= 500
  0 <= nums[i] <= 100 */

vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
  vector<int> ans(nums.size(), 0);
  for (int i = 0; i < nums.size(); i++) {
    for (int j = 0; j < nums.size(); j++) {
      if (j == i)
        continue;
      if (nums[j] < nums[i])
        ans[i]++;
    }
  }
  return ans;
}

// 新建临时数组，其从小到大排序后，每个元素的下标就是小于该元素的元素数量。假如一些元素值相等，则下标不同情况。此时要保留的最小下标
// 利用哈希表，即从后向前遍历，记录元素值-元素下标。遍历正式数组，取得每个元素对应的哈希表下标值。时间复杂度O(nlogn)
vector<int> smallerNumbersThanCurrent1(vector<int>& nums) {
  vector<int> vec = nums;
  sort(vec.begin(), vec.end());
  int hash[101] = {0};
  for (int i = vec.size() - 1; i >= 0; i--) {
    hash[vec[i]] = i;
  }
  for (int i = 0; i < nums.size(); i++) {
    vec[i] = hash[nums[i]];
  }
  return vec;
}

// 计数排序。本题元素取值范围[0,100]，记录每个元素出现频次。从小到大遍历cnt，cnt[j]改意义为元素小于等于j的总数量cnt[j]+=cnt[j-1]
// 小于nums[i]的元素数量，为小于等于nums[i]-1的元素数量，其为cnt[j]。注意nums[i]==0时不可能有元素更小，故直接赋值0
// 时间复杂度O(n+k)，k为值域大小，即元素取值范围
vector<int> smallerNumbersThanCurrent2(vector<int>& nums) {
  int n = nums.size();
  vector<int> cnt(101, 0);
  for (int i = 0; i < nums.size(); i++)
    cnt[nums[i]]++;
  for (int j = 1; j < 101; j++) {
    cnt[j] += cnt[j - 1];
  }
  vector<int> ans(n, 0);
  for (int i = 0; i < nums.size(); i++) {
    ans[i] = nums[i] < 1 ? 0 : cnt[nums[i] - 1];
  }
  return ans;
}

// 暴力解法，时间复杂度N(n^2)
vector<int> smallerNumbersThanCurrent3(vector<int>& nums) {
  vector<int> ans(nums.size(), 0);
  for (int i = 0; i < nums.size(); i++) {
    for (int j = 0; j < nums.size(); j++) {
      if (j == i)
        continue;
      if (nums[j] < nums[i])
        ans[i]++;
    }
  }
  return ans;
}

int main() {
  vector<int> nums1 = {8, 1, 2, 2, 3}, nums2 = {6, 5, 4, 8},
              nums3 = {7, 7, 7, 7};

  printVector(smallerNumbersThanCurrent(nums1));
  printVector(smallerNumbersThanCurrent(nums2));
  printVector(smallerNumbersThanCurrent(nums3));
  printVector(smallerNumbersThanCurrent1(nums1));
  printVector(smallerNumbersThanCurrent1(nums2));
  printVector(smallerNumbersThanCurrent1(nums3));

  return 0;
}