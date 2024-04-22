#include <unordered_set>
#include "head.h"
/* 题意：349. 两个数组的交集
给定两个数组，编写一个函数来计算它们的交集。
示例 1：
输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2]

示例 2：
输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[9,4]
解释：[4,9] 也是可通过的
提示：
    1 <= nums1.length, nums2.length <= 1000
    0 <= nums1[i], nums2[i] <= 1000

*/
// 哈希值较少，跨度大，不得使用数组。考虑集合，set和multiset底层是红黑树，且排序，访问效率低。选择unordered_set，自带去重效果
// 由于要对num1的中间层、和最终结果去重，故需要两个set。一为nums_set，保存nums1信息，直接初始化构造。二为result_set，保存符合条件的nums2
// 最终返回由result_set构造的vector
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
  unordered_set<int> set1(nums1.begin(), nums1.end());
  unordered_set<int> result_set;
  for (int i : nums2) {
    if (set1.find(i) != set1.end())
      result_set.insert(i);
  }
  return vector<int>(result_set.begin(), result_set.end());
}

vector<int> intersection1(vector<int>& nums1, vector<int>& nums2) {
  unordered_set<int> result_set;  // 利用set对结果去重
  unordered_set<int> nums_set(nums1.begin(), nums1.end());
  for (int num : nums2) {
    if (nums_set.find(num) != nums_set.end())
      result_set.insert(num);
  }
  return vector<int>(result_set.begin(), result_set.end());
}
int main() {
  vector<int> vec1 = {1, 2, 2, 1};
  vector<int> vec2 = {2, 2};
  vector<int> vec3 = {4, 9, 5};
  vector<int> vec4 = {9, 4, 9, 8, 4};
  printVector(intersection(vec1, vec2));
  printVector(intersection(vec3, vec4));
  printVector(intersection1(vec1, vec2));
  printVector(intersection1(vec3, vec4));
  return 0;
}