#include "head.h"
/* 1. 两数之和
给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那
两个 整数，并返回他们的数组下标。
你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
示例 1：
  输入：nums = [2,7,11,15], target = 9
  输出：[0,1]
  解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
示例 2：
  输入：nums = [3,2,4], target = 6
  输出：[1,2]
示例 3：
  输入：nums = [3,3], target = 6
  输出：[0,1] */

vector<int> twoSum(vector<int>& nums, int target) {
  unordered_map<int, int> umap;
  for (int i = 0; i < nums.size(); i++) {
    if (umap.find(nums[i]) != umap.end())
      return {i, umap[nums[i]]};
    umap[target - nums[i]] = i;
  }
  return {};
}

// 遍历i，unordered_map记录该位置目标减当前值的差，作为key，下标为value。如果找到key值，说明二者之和为target
// 返回数组，当前下标i和map记录的value
vector<int> twoSum1(vector<int> nums, int target) {
  unordered_map<int, int> map;
  for (int i = 0; i < nums.size(); i++) {
    auto it = map.find(target -
                       nums[i]);  // key记录值，value记录下标.找对应可成组的key
    if (it != map.end())
      return {it->second, i};  // vector可以直接大括号返回，注意先后顺序
    map.insert(pair<int, int>(nums[i], i));
    // map[nums[i]] = i;
  }
  return {};
}

int main() {
  vector<int> nums = {2, 7, 11, 15};
  int target1 = 9, target2 = 15;
  printVector(twoSum(nums, target1));
  printVector(twoSum(nums, target2));
  printVector(twoSum1(nums, target1));
  printVector(twoSum1(nums, target2));
  return 0;
}