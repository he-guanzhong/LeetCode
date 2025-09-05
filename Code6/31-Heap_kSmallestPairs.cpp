#include "head.h"

/* 373. 查找和最小的 K 对数字
给定两个以 非递减顺序排列 的整数数组 nums1 和 nums2 , 以及一个整数 k 。
定义一对值 (u,v)，其中第一个元素来自 nums1，第二个元素来自 nums2 。
请找到和最小的 k 个数对 (u1,v1),  (u2,v2)  ...  (uk,vk) 。
示例 1:
  输入: nums1 = [1,7,11], nums2 = [2,4,6], k = 3
  输出: [1,2],[1,4],[1,6]
  解释: 返回序列中的前 3 对数：
     [1,2],[1,4],[1,6],[7,2],[7,4],[11,2],[7,6],[11,4],[11,6]
示例 2:
  输入: nums1 = [1,1,2], nums2 = [1,2,3], k = 2
  输出: [1,1],[1,1]
  解释: 返回序列中的前 2 对数：
     [1,1],[1,1],[1,2],[2,1],[1,2],[2,2],[1,3],[1,3],[2,3] */

vector<vector<int>> kSmallestPairs(vector<int>& nums1,
                                   vector<int>& nums2,
                                   int k) {
  vector<vector<int>> ans;
  auto cmp = [&](pair<int, int>& a, pair<int, int>& b) {
    return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
  };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);
  for (int i = 0; i < nums1.size() && i < k; i++) {
    pq.push({i, 0});
  }
  while (k-- && !pq.empty()) {
    int a = pq.top().first, b = pq.top().second;
    pq.pop();
    ans.push_back({nums1[a], nums2[b]});
    if (b + 1 < nums2.size()) {
      pq.push({a, b + 1});
    }
  }
  return ans;
}

// 假定数组一内元素是[1,2,3..]，数组二内元素是[a,b,c..]，那么可能都数组组合为1a,2a,3a...1b,2b,3b..总计m*n个
// 优先队列建立最小堆，元素为数组一、二的下标对组。使用引用捕获[&]数组一二。
// 固定数组二的首元素a，将数组一内所有元素压入优先队列，即堆内元素1a,2a,3a...
// 从堆顶依次取值，即为最小的对组结果，C++17新增了结构化绑定
// 取1a后，随即要将1b压入。取2a后，要将2b压入。因为数组二所对应的各个组合，一定是某元素a使用过了，再顺延一位
// 时间复杂度klogk，因为优先队列插入需要logk，总计操作了2k次。空间复杂度k，因为堆内最多只保存k个元素
vector<vector<int>> kSmallestPairs1(vector<int>& nums1,
                                    vector<int>& nums2,
                                    int k) {
  auto cmp = [&nums1, &nums2](const pair<int, int>& a,
                              const pair<int, int>& b) {
    return nums1[a.first] + nums2[a.second] > nums1[b.first] + nums2[b.second];
  };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> que(
      cmp);
  for (int i = 0; i < nums1.size() && i < k; i++)
    que.push({i, 0});
  vector<vector<int>> ans;
  while (k-- && !que.empty()) {
    pair<int, int> index = que.top();
    int a = index.first, b = index.second;
    que.pop();
    ans.push_back({nums1[a], nums2[b]});
    if (b + 1 < nums2.size()) {
      que.push({a, b + 1});
    }
  }
  return ans;
}

int main() {
  vector<int> nums1 = {1, 7, 11}, nums2 = {2, 4, 6};
  vector<int> nums3 = {1, 1, 2}, nums4 = {1, 2, 3};
  vector<int> nums5 = {1, 2, 4, 5, 6}, nums6 = {3, 5, 7, 9};
  printMat(kSmallestPairs(nums1, nums2, 3));
  printMat(kSmallestPairs(nums3, nums4, 2));
  printMat(kSmallestPairs(nums5, nums6, 3));
  printMat(kSmallestPairs1(nums1, nums2, 3));
  printMat(kSmallestPairs1(nums3, nums4, 2));
  printMat(kSmallestPairs1(nums5, nums6, 3));
  return 0;
}