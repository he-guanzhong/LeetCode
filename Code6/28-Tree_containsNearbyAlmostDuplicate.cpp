#include "head.h"

/* 220. 存在重复元素 III
给你一个整数数组 nums 和两个整数 indexDiff 和 valueDiff 。
找出满足下述条件的下标对 (i, j)：
    i != j,
    abs(i - j) <= indexDiff
    abs(nums[i] - nums[j]) <= valueDiff
如果存在，返回 true ；否则，返回 false 。
示例 1：
  输入：nums = [1,2,3,1], indexDiff = 3, valueDiff = 0
  输出：true
  解释：可以找出 (i, j) = (0, 3) 。
    满足下述 3 个条件：
    i != j --> 0 != 3
    abs(i - j) <= indexDiff --> abs(0 - 3) <= 3
    abs(nums[i] - nums[j]) <= valueDiff --> abs(1 - 1) <= 0
示例 2：
  输入：nums = [1,5,9,1,5,9], indexDiff = 2, valueDiff = 3
  输出：false
  解释：尝试所有可能的下标对 (i, j) ，均无法满足这 3 个条件，因此返回 false 。
提示：
    2 <= nums.length <= 105
    -109 <= nums[i] <= 109
    1 <= indexDiff <= nums.length
    0 <= valueDiff <= 109 */

long getId(long num, long t) {
  if (num >= 0)
    return num / (t + 1);
  else
    return (num + 1) / (t + 1) - 1;
}
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
  unordered_map<long, long> umap;
  for (int i = 0; i < nums.size(); i++) {
    long num = nums[i];
    long id = getId(num, t);
    if (umap.count(id))
      return true;
    else if (umap.count(id - 1) && abs(umap[id - 1] - num) <= t)
      return true;
    else if (umap.count(id + 1) && abs(umap[id + 1] - num) <= t)
      return true;
    umap[id] = num;
    if (i >= k) {
      umap.erase(getId(nums[i - k], t));
    }
  }
  return false;
}
// 不得使用滑动窗口+有序集合。会超时
// 正确的方式是用桶。桶Id为num/(valueDiff+1)，例如以3为间隔，则0-1-2-3为一桶
// 但对于复数，要保证-4-3-2-1为一桶。先转化为-3-2-1-0，得到商0为桶Id，再向左偏移一位，即(num+1)/(valueDiff+1)-1
// 考虑到题目要求valueDiff和nums[i]，均可能在INT极值范围内，故二者在getId函数中，均要定义为long类型
// 哈希表记录桶Id及其之前记下的值，遍历时，先排除indexDiff范围之前的哈希表记录值。
// 两元素是否差距valueDiff范围内，要看三种情况：1前桶Id出现过。2.在id-1桶或id+1桶出现过，且其值相差再范围内。
int getId1(long x, long valueDiff) {
  if (x >= 0)
    return x / (valueDiff + 1);
  else
    return (x + 1) / (valueDiff + 1) - 1;
}
bool containsNearbyAlmostDuplicate1(vector<int>& nums,
                                    int indexDiff,
                                    int valueDiff) {
  unordered_map<int, int> umap;
  for (int i = 0; i < nums.size(); i++) {
    long x = nums[i];
    int id = getId1(x, valueDiff);
    if (i > indexDiff) {
      umap.erase(getId1(nums[i - indexDiff - 1], valueDiff));
    }
    if (umap.count(id) ||
        umap.count(id - 1) && abs(umap[id - 1] - x) <= valueDiff ||
        umap.count(id + 1) && abs(umap[id + 1] - x) <= valueDiff)
      return true;
    umap[id] = x;
  }
  return false;
}

int main() {
  vector<int> nums1 = {1, 2, 3, 1};
  int indexDiff1 = 3, valueDiff1 = 0;
  vector<int> nums2 = {1, 5, 9, 1, 5, 9};
  int indexDiff2 = 2, valueDiff2 = 3;
  vector<int> nums3 = {1, 2, 1, 1};
  vector<int> nums4 = {-2, 3};
  vector<int> nums5 = {8, 7, 15, 1, 6, 1, 9, 15};
  vector<int> nums6 = {2147483647, -1, 2147483647};
  vector<int> nums7 = {-1, -1};

  cout << containsNearbyAlmostDuplicate(nums1, indexDiff1, valueDiff1) << " "
       << containsNearbyAlmostDuplicate(nums2, indexDiff2, valueDiff2) << " "
       << containsNearbyAlmostDuplicate(nums3, 1, 0) << " "
       << containsNearbyAlmostDuplicate(nums4, 2, 5) << " "
       << containsNearbyAlmostDuplicate(nums5, 1, 3) << " "
       << containsNearbyAlmostDuplicate(nums6, 1, 2147483647) << " "
       << containsNearbyAlmostDuplicate(nums7, 1, 0) << endl;
  cout << containsNearbyAlmostDuplicate1(nums1, indexDiff1, valueDiff1) << " "
       << containsNearbyAlmostDuplicate1(nums2, indexDiff2, valueDiff2) << " "
       << containsNearbyAlmostDuplicate1(nums3, 1, 0) << " "
       << containsNearbyAlmostDuplicate1(nums4, 2, 5) << " "
       << containsNearbyAlmostDuplicate1(nums5, 1, 3) << " "
       << containsNearbyAlmostDuplicate1(nums6, 1, 2147483647) << " "
       << containsNearbyAlmostDuplicate1(nums7, 1, 0) << endl;
  return 0;
}