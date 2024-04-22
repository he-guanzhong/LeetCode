#include <unordered_set>
#include "head.h"
/* 47. 全排列 II
给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。
示例 1：
输入：nums = [1,1,2]
输出：
[[1,1,2],
 [1,2,1],
 [2,1,1]]
示例 2：
输入：nums = [1,2,3]
输出：[[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
提示：
    1 <= nums.length <= 8
    -10 <= nums[i] <= 10
*/

// 重复元素全排列，设置used数组记录i位置上元素使用情况。双跳过：一、树枝上排列要求跳过已用过元素
// 二、不重复要求跳过同树层，相邻两个元素相等的情况。三个条件：i合规，i-1==i，used[i-1]==false
// 本题实际使用used[i-1]==true条件也可，意为树枝去重。但如此树层不去重，复杂度更高
void backtracking(vector<int>& nums,
                  vector<int>& path,
                  vector<vector<int>>& result,
                  int* used) {
  if (path.size() == nums.size()) {
    result.push_back(path);
    return;
  }
  for (int i = 0; i < nums.size(); i++) {
    if (used[i] == 1)
      continue;
    if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == 0)
      continue;
    path.push_back(nums[i]);
    used[i] = 1;
    backtracking(nums, path, result, used);
    used[i] = 0;
    path.pop_back();
  }
}
vector<vector<int>> permuteUnique(vector<int>& nums) {
  vector<vector<int>> result;
  vector<int> path;
  int used[21] = {0};
  sort(nums.begin(), nums.end());
  backtracking(nums, path, result, used);
  return result;
}

// 排列问题收集叶子结点。每轮都从最开始，无startIndex，额外使用used数组记录该结点是否使用，用过即跳过
// 去重的关键，先排序，优选树层去重，条件有三个，必须同时满足，即i>0，连续两个值相等，且i-1位置的数字使用状态false
// 使用树枝去重也可以，i-1位置使用状态true。但如此效率太低。这个条件是必要的，不加则全会被去重
// used数组，时间复杂度简单，uset集合，insert每次需要做哈希映射，额外花费时间，故以后优选used数组
// used数组，空间复杂度O(n)=n，实际上是n+n，因为全局变量共同。uset集合，每层都要新生成，故空间复杂度O(n)=n^2
vector<vector<int>> result1;
vector<int> path1;
void backtracking1(vector<int>& nums, vector<bool>& used) {
  if (path1.size() == nums.size()) {
    result1.push_back(path1);
    return;
  }
  for (int i = 0; i < nums.size(); i++) {
    if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false ||
        used[i] == true)
      continue;
    path1.push_back(nums[i]);
    used[i] = true;
    backtracking1(nums, used);
    path1.pop_back();
    used[i] = false;
  }
}
vector<vector<int>> permuteUnique1(vector<int>& nums) {
  result1.clear();
  path1.clear();
  vector<bool> used(nums.size(), false);
  sort(nums.begin(), nums.end());
  backtracking1(nums, used);
  return result1;
}

// 使用set去重。由于排列问题，used必要，所以uset的横向去重显得无足轻重
void backtracking2(vector<int>& nums, vector<bool>& used) {
  if (path1.size() == nums.size()) {
    result1.push_back(path1);
    return;
  }
  unordered_set<int> uset;
  for (int i = 0; i < nums.size(); i++) {
    if (used[i] == true)
      continue;
    if (uset.find(nums[i]) != uset.end())
      continue;
    uset.insert(nums[i]);
    path1.push_back(nums[i]);
    used[i] = true;
    backtracking2(nums, used);
    path1.pop_back();
    used[i] = false;
  }
}
vector<vector<int>> permuteUnique2(vector<int>& nums) {
  result1.clear();
  path1.clear();
  sort(nums.begin(), nums.end());
  vector<bool> used(nums.size(), false);
  backtracking2(nums, used);
  return result1;
}
int main() {
  vector<int> vec1 = {1, 1, 2};
  vector<int> vec2 = {1, 2, 3};
  vector<int> vec3 = {1, 1, 1};

  printMat(permuteUnique(vec1));
  printMat(permuteUnique(vec2));
  printMat(permuteUnique(vec3));
  printMat(permuteUnique1(vec1));
  printMat(permuteUnique1(vec2));
  printMat(permuteUnique1(vec3));
  return 0;
}
