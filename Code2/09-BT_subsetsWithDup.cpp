#include "head.h"
/* 90. 子集 II
给你一个整数数组 nums，
其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。 解集 不能
包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。
示例 1：
  输入：nums =[1,2,2]
  输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]
示例 2：
  输入：nums = [0]
  输出：[[],[0]]  */

void backtracking(vector<int>& nums,
                  int index,
                  vector<int>& path,
                  vector<vector<int>>& ans) {
  ans.push_back(path);
  for (int i = index; i < nums.size(); i++) {
    if (i > index && nums[i] == nums[i - 1])
      continue;
    path.push_back(nums[i]);
    backtracking(nums, i + 1, path, ans);
    path.pop_back();
  }
}
vector<vector<int>> subsetsWithDup(vector<int>& nums) {
  vector<vector<int>> ans;
  vector<int> path;
  sort(nums.begin(), nums.end());
  backtracking(nums, 0, path, ans);
  return ans;
}

// 子集问题，求所有结点。去重的关键在于树层去重，而非树枝去重。必须先排序
// 可以使用三种方法去重：一、 used数组，当其false意为树层，相等则去重
// 二、使用startIndex直接去重，i>startIndex时的问题直接横向去重
// 三、使用vector<bool> used去重，或者unordered_set同层去重
vector<vector<int>> result1;
vector<int> path1;
void backtracking1(vector<int>& nums, int startIndex, vector<bool> used) {
  result1.push_back(path1);  // 必须写在返回之前，否则会漏掉自己
  for (int i = startIndex; i < nums.size(); i++) {
    if (i > 0 && used[i - 1] == false && nums[i] == nums[i - 1])
      continue;
    path1.push_back(nums[i]);
    used[i] = true;
    backtracking1(nums, i + 1, used);
    path1.pop_back();
    used[i] = false;
  }
}

vector<vector<int>> subsetsWithDup1(vector<int>& nums) {
  result1.clear();
  path1.clear();
  sort(nums.begin(), nums.end());
  vector<bool> used(nums.size(), false);
  backtracking1(nums, 0, used);
  return result1;
}

// 重复元素子集，先排序，然后求树上所有结点。深度遍历允许重复，传入下一层为i+1。
// 广度方向不允许重复，如果与前一元素相等，直接跳过
// 或使用vector<bool>记录重复元素。i有效，i-1==i，used[i-1]==false同层没用过为假
void backtracking2(vector<int>& nums, int startIndex) {
  result1.push_back(path1);
  for (int i = startIndex; i < nums.size(); i++) {
    if (i > startIndex && nums[i] == nums[i - 1])
      continue;
    path1.push_back(nums[i]);
    backtracking2(nums, i + 1);
    path1.pop_back();
  }
}
vector<vector<int>> subsetsWithDup2(vector<int>& nums) {
  result1.clear();
  path1.clear();
  sort(nums.begin(), nums.end());
  backtracking2(nums, 0);
  return result1;
}

void backtracking3(vector<int>& nums, int startIndex) {
  result1.push_back(path1);
  unordered_set<int> uset;
  for (int i = startIndex; i < nums.size(); i++) {
    if (uset.find(nums[i]) != uset.end())
      continue;
    path1.push_back(nums[i]);
    uset.insert(nums[i]);
    backtracking3(nums, i + 1);
    path1.pop_back();
  }
}
vector<vector<int>> subsetsWithDup3(vector<int>& nums) {
  result1.clear();
  path1.clear();
  sort(nums.begin(), nums.end());
  backtracking3(nums, 0);
  return result1;
}

int main() {
  vector<int> vec1 = {1, 2, 2};
  vector<int> vec2 = {0};
  printMat(subsetsWithDup(vec1));
  printMat(subsetsWithDup(vec2));
  printMat(subsetsWithDup1(vec1));
  printMat(subsetsWithDup1(vec2));
  return 0;
}