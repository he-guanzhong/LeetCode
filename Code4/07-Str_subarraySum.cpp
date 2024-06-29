#include "head.h"
/* 560. 和为 K 的子数组
给你一个整数数组 nums 和一个整数 k ，请你统计并返回 该数组中和为 k
的子数组的个数 。
子数组是数组中元素的连续非空序列。
示例 1：
输入：nums = [1,1,1], k = 2
输出：2
示例 2：
输入：nums = [1,2,3], k = 3
输出：2  */

int subarraySum(vector<int>& nums, int k) {
  int pre = 0, ans = 0;
  unordered_map<int, int> umap;
  umap[0] = 1;
  for (int& num : nums) {
    pre += num;
    if (umap.count(pre - k))
      ans += umap[pre - k];
    umap[pre]++;
  }
  return ans;
}

// 前缀和+哈希表。pre记录[0,i]连续数组和，核心是pre[i]-pre[j]==k的判断。umap键为某连续数组和，值为该和出现次数。初始化和为0数组次数为i。
// 寻找pre[i]-k的值，之前是否出现过，若有，就叠加上其出现的次数。最后，记录当前pre[i]出现次数+1
int subarraySum1(vector<int>& nums, int k) {
  unordered_map<int, int> umap;
  umap[0] = 1;
  int pre = 0, cnt = 0;
  for (int& num : nums) {
    pre += num;
    if (umap.find(pre - k) != umap.end()) {
      cnt += umap[pre - k];
    }
    umap[pre]++;
  }
  return cnt;
}
// 暴力枚举，超时。固定终止点，向前移动起始点，对每一轮计算，由于测试用例中包含负数，所以不能通过sum>k来终止计算。
int subarraySum2(vector<int>& nums, int k) {
  int ans = 0;
  for (int i = 0; i < nums.size(); i++) {
    int sum = 0;
    for (int j = i; j >= 0; j--) {
      sum += nums[j];
      if (sum == k)
        ans++;
    }
  }
  return ans;
}

int main() {
  vector<int> nums1{1, 1, 1}, nums2{1, 2, 3}, nums3{1, -1, 0};
  int k1 = 2, k2 = 3, k3 = 0;
  cout << subarraySum(nums1, k1) << " " << subarraySum(nums2, k2) << " "
       << subarraySum(nums3, k3) << endl;
  cout << subarraySum1(nums1, k1) << " " << subarraySum1(nums2, k2) << " "
       << subarraySum1(nums3, k3) << endl;
  return 0;
}