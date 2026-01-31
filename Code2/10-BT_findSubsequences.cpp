#include "head.h"
/* 491. 非递减子序列
给你一个整数数组 nums ，找出并返回所有该数组中不同的递增子序列，递增子序列中
至少有两个元素 。你可以按 任意顺序 返回答案。
数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。
示例 1：
  输入：nums = [4,6,7,7]
  输出：[[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
示例 2：
  输入：nums = [4,4,3,2,1]
  输出：[[4,4]]
  -100 <= nums[i] <= 100 */

void backtracking(vector<int>& nums,
                  int index,
                  vector<int>& path,
                  vector<vector<int>>& ans) {
  if (path.size() >= 2)
    ans.push_back(path);
  if (index == nums.size())
    return;
  unordered_set<int> uset;
  for (int i = index; i < nums.size(); i++) {
    if (uset.find(nums[i]) != uset.end())
      continue;
    if (path.empty() || nums[i] >= path.back()) {
      path.push_back(nums[i]);
      uset.insert(nums[i]);
      backtracking(nums, i + 1, path, ans);
      path.pop_back();
    }
  }
}
vector<vector<int>> findSubsequences(vector<int>& nums) {
  vector<vector<int>> ans;
  vector<int> path;
  backtracking(nums, 0, path, ans);
  return ans;
}

// 求子序列，为搜索全部结点，但只有path.size>=2才入结果。不能排序，因为破坏原有顺序
// 两种跳过：同层重复跳过和不递增跳过。同层之间不得相同，使用unordered_set记录。
// 只有下一个元素值大于path末尾元素，才深度进入下一层
// 数字范围有限，使用数组比集合效率更高

// unordered_set和set 不是一个头文件，map同理
// 全结点搜索，但是必须path内含两个元素以上，才压入结果。求递增序列，故不可以排序，因为破坏了原有顺序
// 跳过有两个条件：一、树层不得重复，由于数组无序，则本层set，记录前元素是否出现过。
// 二、接下来的所有元素，比path末尾元素小，故不能使用nums[i] < num[i-1]作为判断
// 考虑到本题nums[i] 在[-100, 100]之内，可以使用数组代替set提高效率
vector<vector<int>> result1;
vector<int> path1;
void backtracking1(vector<int>& nums, int startIndex) {
  if (path1.size() >= 2)
    result1.push_back(path1);
  unordered_set<int> uset;  // set去重，不能使用vector<bool>
  // int used[201] = {0};
  for (int i = startIndex; i < nums.size(); i++) {
    // 不能比较相邻两个元素，因为无序
    if (!path1.empty() && path1.back() > nums[i] ||
        uset.find(nums[i]) != uset.end())
      // used[i + 100] == 1
      continue;
    path1.push_back(nums[i]);
    uset.insert(nums[i]);
    // used[i + 100] = 1;
    backtracking1(nums, i + 1);
    path1.pop_back();
  }
}
vector<vector<int>> findSubsequences1(vector<int>& nums) {
  result1.clear();
  path1.clear();
  backtracking1(nums, 0);
  return result1;
}

int main() {
  vector<int> vec1 = {4, 6, 7, 7};
  vector<int> vec2 = {4, 4, 3, 2, 1};
  vector<int> vec3 = {4, 7, 2, 3};

  printMat(findSubsequences(vec1));
  printMat(findSubsequences(vec2));
  printMat(findSubsequences(vec3));
  printMat(findSubsequences1(vec1));
  printMat(findSubsequences1(vec2));
  printMat(findSubsequences1(vec3));
  return 0;
}