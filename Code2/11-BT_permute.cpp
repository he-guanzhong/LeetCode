#include "head.h"
/* 46. 全排列
给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序
返回答案。
示例 1：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
示例 2：
输入：nums = [0,1]
输出：[[0,1],[1,0]]
示例 3：
输入：nums = [1]
输出：[[1]] */

// 排列问题，每一轮都要从头搜索，无需startIndex，但需used数组记录树枝结点上是否访问过。访问过就跳过。
// 退出条件，为used数组全为真不可表述，由于path压入弹出，与数组赋值真假同步，故path.size相等可作为退出条件
void backtracking(vector<int>& nums,
                  vector<int>& path,
                  vector<vector<int>>& result,
                  vector<bool>& used) {
  if (path.size() == nums.size()) {
    result.push_back(path);
    return;
  }
  for (int i = 0; i < nums.size(); i++) {
    if (used[i] == true)
      continue;
    path.push_back(nums[i]);
    used[i] = true;
    backtracking(nums, path, result, used);
    path.pop_back();
    used[i] = false;
  }
}
vector<vector<int>> permute(vector<int>& nums) {
  vector<vector<int>> result;
  vector<int> path;
  vector<bool> used(nums.size(), false);
  backtracking(nums, path, result, used);
  return result;
}

// 排列问题需要重复选取，没有startIndex，但used数组记录元素是否曾经用过。
// 全排列退出条件,为path的大小已经达到nums大小
// 时间复杂度O(n)=n!，空间复杂度O(n)=n
vector<vector<int>> result1;
vector<int> path1;
void backtracking1(vector<int>& nums, vector<bool>& used) {
  if (path1.size() == nums.size()) {
    result1.push_back(path1);
    return;
  }
  for (int i = 0; i < nums.size(); i++) {
    if (used[i] == true)
      continue;
    path1.push_back(nums[i]);
    used[i] = true;
    backtracking1(nums, used);
    path1.pop_back();
    used[i] = false;
  }
}
vector<vector<int>> permute1(vector<int> nums) {
  result1.clear();
  path1.clear();
  vector<bool> used(nums.size(), false);
  backtracking1(nums, used);
  return result1;
}
int main() {
  vector<int> vec1 = {1, 2, 3};
  vector<int> vec2 = {0, 1};
  vector<int> vec3 = {1};
  printMat(permute(vec1));
  printMat(permute(vec2));
  printMat(permute(vec3));
  printMat(permute1(vec1));
  printMat(permute1(vec2));
  printMat(permute1(vec3));
  return 0;
}
