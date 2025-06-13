#include "head.h"
/* 525. 连续数组
给定一个二进制数组 nums , 找到含有相同数量的 0 和 1
的最长连续子数组，并返回该子数组的长度。
示例 1：
  输入：nums = [0,1]
  输出：2
  说明：[0, 1] 是具有相同数量 0 和 1 的最长连续子数组。
示例 2：
  输入：nums = [0,1,0]
  输出：2
  说明：[0, 1] (或 [1, 0]) 是具有相同数量 0 和 1 的最长连续子数组。
示例 3：
  输入：nums = [0,1,1,1,1,1,0,0,0]
  输出：6
  解释：[1,1,1,0,0,0] 是具有相同数量 0 和 1 的最长连续子数组。
提示：
    1 <= nums.length <= 105
    nums[i] 不是 0 就是 1 */

int findMaxLength(vector<int>& nums) {
  int sum = 0;
  int ans = 0;
  unordered_map<int, int> umap;
  umap[0] = -1;
  for (int i = 0, j = 0; i < nums.size(); i++) {
    sum += nums[i] == 1 ? 1 : -1;
    if (umap.count(sum))
      ans = max(ans, i - umap[sum]);
    else
      umap[sum] = i;
  }
  return ans;
}

// 前缀和+哈希表，计数表示当前位i之前，1的数量和0的数量之差。哈希表记录该数量差时的下标i。
// 当再一次发现数量差出现时，此时下标j，说明[i,j]范围内，1和0数量相等。则j-i即为所求数组长度。
// 哈希表初始化，首次出现1和0数量相等时，要记录从开始的总长度，则umap[0]=-1
int findMaxLength1(vector<int>& nums) {
  int ans = 0;
  int cnt = 0;
  unordered_map<int, int> umap;
  umap[0] = -1;
  for (int i = 0; i < nums.size(); i++) {
    cnt += (nums[i] ? 1 : -1);
    if (umap.count(cnt))
      ans = max(ans, i - umap[cnt]);
    else
      umap[cnt] = i;
  }
  return ans;
}

int main() {
  vector<int> nums1 = {0, 1}, nums2 = {0, 1, 0},
              nums3 = {0, 1, 1, 1, 1, 1, 0, 0, 0};
  cout << findMaxLength(nums1) << " " << findMaxLength(nums2) << " "
       << findMaxLength(nums3) << endl;
  cout << findMaxLength1(nums1) << " " << findMaxLength1(nums2) << " "
       << findMaxLength1(nums3) << endl;
  return 0;
}