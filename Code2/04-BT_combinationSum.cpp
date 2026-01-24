#include "head.h"
/* 39. 组合总和
给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，找出
candidates 中可以使数字和为目标数 target 的 所有
不同组合，并以列表形式返回。你可以按 任意顺序 返回这些组合。 candidates 中的
同一个 数字可以
无限制重复被选取。如果至少一个数字的被选数量不同，则两种组合是不同的。
示例 1：
  输入：candidates = [2,3,6,7], target = 7
  输出：[[2,2,3],[7]]
  解释：
    2 和 3 可以形成一组候选，2 + 2 + 3 = 7 。注意 2 可以使用多次。
    7 也是一个候选， 7 = 7 。
    仅有这两种组合。
    对于给定的输入，保证和为 target 的不同组合数少于 150 个。 */

void backtracking(vector<int>& candidates,
                  int target,
                  int index,
                  int sum,
                  vector<int>& path,
                  vector<vector<int>>& ans) {
  if (sum == target) {
    ans.push_back(path);
    return;
  }
  for (int i = index; i < candidates.size() && sum + candidates[i] <= target;
       i++) {
    path.push_back(candidates[i]);
    backtracking(candidates, target, i, sum + candidates[i], path, ans);
    path.pop_back();
  }
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
  vector<vector<int>> ans;
  vector<int> path;
  sort(candidates.begin(), candidates.end());
  backtracking(candidates, target, 0, 0, path, ans);
  return ans;
}

// 深度无用，退出条件为总和大于等于target。广度为candidates数组元素个数。
// 深度方向允许重复，故传入start参数不+1，广度方向不允许重复，故传入start为当前一层的i
// 剪支思路是总和过大时，不进入递归。但需要前提是数组有序，从小到大排列。否则若首元素即大于target，不会执行程序
// 组合元素可重复，退出条件不再是递归轮数，而是总和sum>target直接退出，sum==target保存退出
// 传入参数有当前分支总和，起始点坐标（只在一个集合内选择适配），startIndex不代表深度，由于可重复，则不必+1递归
vector<vector<int>> result1;
vector<int> path1;
void backtracking1(vector<int>& candidates,
                   int target,
                   int sum,
                   int startIndex) {
  if (sum > target)
    return;
  if (sum == target) {
    result1.push_back(path1);
    return;
  }
  for (int i = startIndex; i < candidates.size(); i++) {
    sum += candidates[i];
    path1.push_back(candidates[i]);
    backtracking1(candidates, target, sum, i);
    sum -= candidates[i];
    path1.pop_back();
  }
}
vector<vector<int>> combinationSum1(vector<int>& candidates, int target) {
  result1.clear();
  path1.clear();
  backtracking1(candidates, target, 0, 0);
  return result1;
}

// 剪支思路：如果当前总和大于target则不入递归，提前剪支，前提是数组是由低到高有序的
void backtracking2(vector<int>& candidates,
                   int target,
                   int sum,
                   int startIndex) {
  if (sum == target) {
    result1.push_back(path1);
    return;
  }
  for (int i = startIndex;
       i < candidates.size() && sum + candidates[i] <= target; i++) {
    sum += candidates[i];
    path1.push_back(candidates[i]);
    backtracking2(candidates, target, sum, i);  // 起始点是不断移动的，传入的是i
    sum -= candidates[i];
    path1.pop_back();
  }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
  result1.clear();
  path1.clear();
  sort(candidates.begin(), candidates.end());  // 必须先排序，否则不能提前剪支
  backtracking2(candidates, target, 0, 0);
  return result1;
}

int main() {
  vector<int> vec1 = {2, 3, 6, 7};
  vector<int> vec2 = {2, 3, 5};
  vector<int> vec3 = {2};
  int t1 = 7, t2 = 8, t3 = 1;
  printMat(combinationSum(vec1, t1));
  printMat(combinationSum(vec2, t2));
  printMat(combinationSum(vec3, t3));
  printMat(combinationSum2(vec1, t1));
  printMat(combinationSum2(vec2, t2));
  printMat(combinationSum2(vec3, t3));
  return 0;
}
