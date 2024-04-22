#include "head.h"
/* 78. 子集
给你一个整数数组 nums ，数组中的元素 互不相同
。返回该数组所有可能的子集（幂集）。
示例 1：
输入：nums = [1,2,3]
输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。 */

// 子集问题为求树全部结点，并非叶子结点。可以没有退出条件，因为每次传入的start为i+1，遍历到nums.size即终止
vector<vector<int>> result;
vector<int> path;
void backtracking(vector<int>& nums, int start) {
  result.push_back(path);
  for (int i = start; i < nums.size(); i++) {
    path.push_back(nums[i]);
    backtracking(nums, i + 1);
    path.pop_back();
  }
}
vector<vector<int>> subsets(vector<int>& nums) {
  result.clear();
  path.clear();
  backtracking(nums, 0);
  return result;
}

// 子集问题，要记录所有结点，而非叶子结点。组合、分割问题为仅处理叶子结点。所以压入结果要在返回之前。
// 返回的条件为集合为空时，即startIndex要大于nums.size()，此处可写可不写，因为不在横向遍历范围之内
// 传入参数为startIndex，因为已经选取过的元素不能重复选取，下递归时传入i+1。时间复杂度n*2^n
vector<vector<int>> result1;
vector<int> path1;
void backtracking1(vector<int>& nums, int startIndex) {
  result1.push_back(path1);  // 必须写在返回之前，否则会漏掉自己
  if (startIndex >= nums.size())  // 可写可不写，充分
    return;
  for (int i = startIndex; i < nums.size(); i++) {
    path1.push_back(nums[i]);
    backtracking1(nums, i + 1);
    path1.pop_back();
  }
}

vector<vector<int>> subsets1(vector<int>& nums) {
  result1.clear();
  path1.clear();
  backtracking1(nums, 0);
  return result1;
}

int main() {
  vector<int> vec1 = {1, 2, 3};
  vector<int> vec2 = {0};
  printMat(subsets(vec1));
  printMat(subsets(vec2));
  printMat(subsets1(vec1));
  printMat(subsets1(vec2));
  return 0;
}