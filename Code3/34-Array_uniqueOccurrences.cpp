#include "head.h"
/* 1207. 独一无二的出现次数
给你一个整数数组 arr，请你帮忙统计数组中每个数的出现次数。
如果每个数的出现次数都是独一无二的，就返回 true；否则返回 false。
示例 1：
  输入：arr = [1,2,2,1,1,3]
  输出：true
  解释：在该数组中，1 出现了 3 次，2 出现了 2 次，3 只出现了 1
    次。没有两个数的出现次数相同。
示例 2：
  输入：arr = [1,2]
  输出：false
示例 3：
  输入：arr = [-3,0,1,-3,1,1,1,-3,10,0]
  输出：true
提示：
    1 <= arr.length <= 1000
    -1000 <= arr[i] <= 1000 */

bool uniqueOccurrences(vector<int>& arr) {
  vector<int> cnt(2001, 0);
  for (int i = 0; i < arr.size(); i++) {
    cnt[arr[i] + 1000]++;
  }
  vector<bool> visited(1001, false);
  for (int i = 0; i < cnt.size(); i++) {
    if (visited[cnt[i]])
      return false;
    if (cnt[i])
      visited[cnt[i]] = true;
  }
  return true;
}

// 哈希表。由于数值范围[-1000,1000]，总计2001个，故使用数组作为map映射，统计每个数的出现次数，数字下标+1000保证其非负。
// arr.length范围[1,1000]，故数字最多出现1000次，故使用数组作为set集合，遍历每个出现次数，是否此前出现过。
bool uniqueOccurrences1(vector<int>& arr) {
  int cnt[2002] = {0};
  for (int i = 0; i < arr.size(); i++)
    cnt[arr[i] + 1000]++;
  bool freq[1001] = {false};
  for (int j = 0; j < 2002; j++) {
    if (cnt[j]) {
      if (freq[cnt[j]])
        return false;
      else
        freq[cnt[j]] = true;
    }
  }
  return true;
}

int main() {
  vector<int> nums1 = {1, 2, 2, 1, 1, 3}, nums2 = {1, 2},
              nums3 = {-3, 0, 1, -3, 1, 1, 1, -3, 10, 0},
              nums4 = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  cout << uniqueOccurrences(nums1) << " " << uniqueOccurrences(nums2) << " "
       << uniqueOccurrences(nums3) << " " << uniqueOccurrences(nums4) << endl;
  cout << uniqueOccurrences1(nums1) << " " << uniqueOccurrences1(nums2) << " "
       << uniqueOccurrences1(nums3) << " " << uniqueOccurrences1(nums4) << endl;
  return 0;
}