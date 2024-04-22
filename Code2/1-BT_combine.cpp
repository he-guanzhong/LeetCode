#include "head.h"
/* 77. 组合
给定两个整数 n 和 k，返回范围[1, n] 中所有可能的 k 个数的组合。
你可以按 任何顺序 返回答案。 */

// 横向遍历，需要传入起始坐标start，下一层纵向遍历时要输入i+1。退出条件不必记录深度，因为path.size可以表征
// 剪支思路。剩余n的数量小于path内还需要的数量，故n要终止于
// k-path.size()+1。例：总计4个元素，已有0，仍需3个元素为例。
vector<vector<int>> res;
vector<int> path;
void backtracking(int n, int k, int start) {
  if (path.size() == k) {
    res.push_back(path);
    return;
  }
  for (int i = start; i <= n - (k - path.size()) + 1; i++) {
    path.push_back(i);
    backtracking(n, k, i + 1);
    path.pop_back();
  }
}
vector<vector<int>> combine(int n, int k) {
  res.clear();
  path.clear();
  backtracking(n, k, 1);
  return res;
}

// 外置结果和路径。递归结束条件为path深度等于k，广度for循环内使用startIndex记录开始点
// 广度遍历，先压入，然后递归，最后弹出原值
vector<vector<int>> res1;
vector<int> path1;
void traversal1(int n, int k, int startIndex) {
  if (path1.size() == k) {
    res1.push_back(path1);
    return;
  }
  // for (int i = startIndex; i <= n; i++) {
  // 此处可以剪支，当剩余元素还剩 x = k-path1.size()时，可以横向搜索终止于n-x+1
  for (int i = startIndex; i <= n - (k - path1.size()) + 1; i++) {
    path1.push_back(i);
    traversal1(n, k, i + 1);  // 此处为除去i值
    path1.pop_back();
  }
}

vector<vector<int>> combine1(int n, int k) {
  res1.clear();
  path1.clear();
  traversal1(n, k, 1);
  return res1;
}

int main() {
  int n1 = 4, k1 = 4;
  int n2 = 1, k2 = 1;
  printMat(combine(n1, k1));
  printMat(combine(n2, k2));
  printMat(combine1(n1, k1));
  printMat(combine1(n2, k2));
  return 0;
}