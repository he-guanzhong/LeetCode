#include "head.h"
/* 39. 组合总和II
给定一个数组 candidates 和一个目标数 target ，找出 candidates
中所有可以使数字和为 target 的组合。
candidates 中的每个数字在每个组合中只能使用一次。
说明： 所有数字（包括目标数）都是正整数。解集不能包含重复的组合。
示例 1:
  输入: candidates = [10,1,2,7,6,1,5], target = 8,
  所求解集为: [[1,1,6],
            [1,2,5],
            [1,7],
            [2,6]] */

void traversal(vector<int>& candidates,
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
    if (i > index && candidates[i] == candidates[i - 1])
      continue;
    path.push_back(candidates[i]);
    traversal(candidates, target, i + 1, sum + candidates[i], path, ans);
    path.pop_back();
  }
}
vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
  vector<vector<int>> ans;
  vector<int> path;
  sort(candidates.begin(), candidates.end());
  traversal(candidates, target, 0, 0, path, ans);
  return ans;
}

// 重复数字不重复选取，必须先排序，在于横向树层不得选取相同数字，纵向树深允许选取相同数字。
// 可以采用used<bool>记录是否访问过，只有相邻两个candidates相等且前一个未被访问，才跳过
// 或采用只有从startIndex开始重复才跳过。
// 剪支思路，总和大于target直接跳过，不递归。
vector<vector<int>> result1;
vector<int> path1;
void backtracking1(vector<int>& candidates,
                   int target,
                   int sum,
                   int startIndex,
                   vector<bool>& used) {
  if (sum == target) {
    result1.push_back(path1);
    return;
  }
  for (int i = startIndex;
       i < candidates.size() && sum + candidates[i] <= target; i++) {
    if (i > 0 && candidates[i] == candidates[i - 1] && used[i - 1] == false)
      continue;
    sum += candidates[i];
    path1.push_back(candidates[i]);
    used[i] = true;
    backtracking1(candidates, target, sum, i + 1, used);
    sum -= candidates[i];
    path1.pop_back();
    used[i] = false;
  }
}

// 每个元素只用一次，故递归传入start位i+1，退出条件位总和等于target。剪支要求先排序，总和大于target不进入递归。
// 元素值允许深度重复，下标是不重复的，依然传入i+1。但广度方向不重复。
// 去重方法一：该层循环内两个条件按，i从大于start起始，i==i-1则跳过。不能i+1==i
// 去重方法二：利用<bool>used，该层循环内三个条件，i有效，且i-1==i，且i-1位置为false未访问过，则跳过
vector<vector<int>> combinationSum21(vector<int>& candidates, int target) {
  result1.clear();
  path1.clear();
  vector<bool> used(candidates.size(), false);
  sort(candidates.begin(), candidates.end());
  backtracking1(candidates, target, 0, 0, used);
  return result1;
}
void backtracking2(vector<int>& candidates,
                   int target,
                   int sum,
                   int startIndex) {
  if (sum == target) {
    result1.push_back(path1);
    return;
  }
  for (int i = startIndex;
       i < candidates.size() && sum + candidates[i] <= target; i++) {  // 剪支
    // 横向不能重复，去重。一定要先判断i>start，否则报错。一定要判断i==i-1不能i+1==i，否则漏掉11X等情况
    if (i > startIndex && candidates[i] == candidates[i - 1])
      continue;
    path1.push_back(candidates[i]);
    sum += candidates[i];
    backtracking2(candidates, target, sum, i + 1);
    path1.pop_back();
    sum -= candidates[i];
  }
}
vector<vector<int>> combinationSum22(vector<int>& candidates, int target) {
  result1.clear();
  path1.clear();
  sort(candidates.begin(), candidates.end());
  backtracking2(candidates, target, 0, 0);
  return result1;
}

// 使用set同层去重
void backtracking3(vector<int>& candidates,
                   int target,
                   int sum,
                   int startIndex) {
  if (sum == target) {
    result1.push_back(path1);
    return;
  }
  unordered_set<int> uset;
  for (int i = startIndex;
       i < candidates.size() && sum + candidates[i] <= target; i++) {
    if (uset.find(candidates[i]) != uset.end())
      continue;
    path1.push_back(candidates[i]);
    uset.insert(candidates[i]);
    sum += candidates[i];
    backtracking3(candidates, target, sum, i + 1);
    path1.pop_back();
    sum -= candidates[i];
  }
}
vector<vector<int>> combinationSum23(vector<int>& candidates, int target) {
  result1.clear();
  path1.clear();
  sort(candidates.begin(), candidates.end());
  backtracking3(candidates, target, 0, 0);
  return result1;
}

int main() {
  vector<int> vec1 = {10, 1, 2, 7, 6, 1, 5};
  vector<int> vec2 = {2, 5, 2, 1, 2};
  vector<int> vec3 = {2};
  int t1 = 8, t2 = 5, t3 = 1;
  printMat(combinationSum2(vec1, t1));
  printMat(combinationSum2(vec2, t2));
  printMat(combinationSum2(vec3, t3));
  printMat(combinationSum22(vec1, t1));
  printMat(combinationSum22(vec2, t2));
  printMat(combinationSum22(vec3, t3));
  return 0;
}
