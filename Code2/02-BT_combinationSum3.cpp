#include "head.h"
/* 216. 组合总和 III
找出所有相加之和为 n 的 k 个数的组合，且满足下列条件：
    只使用数字1到9
    每个数字 最多使用一次
返回所有可能的有效组合的列表。该列表不能包含相同的组合两次，组合可以以任何顺序返回。
示例 1:
  输入: k = 3, n = 7
  输出: [[1,2,4]]
  解释:
    1 + 2 + 4 = 7
    没有其他符合的组合了。
示例 3:
  输入: k = 4, n = 1
  输出: []
  解释: 不存在有效的组合。
    在[1,9]范围内使用4个不同的数字，我们可以得到的最小和是1+2+3+4 = 10，因为10 >
    1，没有有效的组合。 */
void backtracking(int k,
                  int n,
                  int index,
                  int sum,
                  vector<int>& path,
                  vector<vector<int>>& ans) {
  if (path.size() == k) {
    if (sum == n)
      ans.push_back(path);
    return;
  }
  for (int i = index; i <= 9 && sum + i <= n; i++) {
    path.push_back(i);
    backtracking(k, n, i + 1, sum + i, path, ans);
    path.pop_back();
  }
}
vector<vector<int>> combinationSum3(int k, int n) {
  vector<vector<int>> ans;
  vector<int> path;
  backtracking(k, n, 1, 0, path, ans);
  return ans;
}

// 方法一：直接在递归中，操作k、n为剩余深度，剩余总和。如此判断条件为k和n为0，则记为结果。递归时，每一层传入i+1。层数k-1，总和n-i
// 方法二：额外记录总和sum并传入。退出条件为path.size记录了深度，与k比较。
// 剪支分两步：深度方向，如果当前总和sum已经过大，则不进入递归，或进入后立刻退出。广度方向，k剩余要求数量，大于n到9还剩数量
// 传入参数注意起始位置startIndex，和暂时路径和sum，可以外置可以作为传参
// 终止条件为size达到深度k，广度是数字9。时间复杂度n * 2 ^ n
// 剪支操作两个，一是横向搜索止于path还剩余元素数，二是暂时综合一旦大于目标即停止
vector<vector<int>> result1;
vector<int> path1;
void backtracking1(int n, int k, int startIndex, int sum) {
  if (path1.size() == k) {
    if (sum == n)
      result1.push_back(path1);
    return;
  }
  for (int i = startIndex; i <= 9; i++) {
    path1.push_back(i);
    sum += i;
    backtracking1(n, k, i + 1, sum);
    path1.pop_back();
    sum -= i;
  }
}
vector<vector<int>> combinationSum31(int k, int n) {
  result1.clear();
  path1.clear();
  backtracking1(n, k, 1, 0);
  return result1;
}

// 带剪支操作的版本
void backtracking2(int n, int k, int startIndex, int sum) {
  if (sum > n)  // 剪支二，总和一旦大就停止
    return;
  if (path1.size() == k) {
    if (sum == n)
      result1.push_back(path1);
    return;
  }
  // 剪支一，停止搜索于横向数量
  for (int i = startIndex; i <= 9 - (k - path1.size()) + 1; i++) {
    path1.push_back(i);
    sum += i;
    backtracking2(n, k, i + 1, sum);
    path1.pop_back();
    sum -= i;
  }
}
vector<vector<int>> combinationSum32(int k, int n) {
  result1.clear();
  path1.clear();
  backtracking2(n, k, 1, 0);
  return result1;
}

int main() {
  int n1 = 3, k1 = 7;
  int n2 = 3, k2 = 9;
  int n3 = 4, k3 = 1;
  printMat(combinationSum3(n1, k1));
  printMat(combinationSum3(n2, k2));
  printMat(combinationSum3(n3, k3));
  printMat(combinationSum31(n1, k1));
  printMat(combinationSum31(n2, k2));
  printMat(combinationSum31(n3, k3));
  return 0;
}
