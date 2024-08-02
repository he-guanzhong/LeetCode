#include "head.h"
/* 129. 求根节点到叶节点数字之和
给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
每条从根节点到叶节点的路径都代表一个数字：
    例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
计算从根节点到叶节点生成的 所有数字之和 。
叶节点 是指没有子节点的节点。
示例 1：
  输入：root = [1,2,3]
  输出：25
  解释：
    从根到叶子节点路径 1->2 代表数字 12
    从根到叶子节点路径 1->3 代表数字 13
    因此，数字总和 = 12 + 13 = 25
示例 2：
  输入：root = [4,9,0,5,1]
  输出：1026
解释：
  从根到叶子节点路径 4->9->5 代表数字 495
  从根到叶子节点路径 4->9->1 代表数字 491
  从根到叶子节点路径 4->0 代表数字 40
  因此，数字总和 = 495 + 491 + 40 = 1026 */

// 回溯收集所有路径，遇到根节点就累加求和。使用vector保存临时路径，专门设vec转int的函数。一定是先保证有节点，压节点，再进入递归
int vector2Int(const vector<int>& vec) {
  int sum = 0;
  for (int i = 0; i < vec.size(); i++)
    sum = sum * 10 + vec[i];
  return sum;
}
void dfs(TreeNode* root, int& ans, vector<int>& vec) {
  if (!root->left && !root->right) {
    ans += vector2Int(vec);
    return;
  }
  if (root->left) {
    vec.push_back(root->left->val);
    dfs(root->left, ans, vec);
    vec.pop_back();
  }
  if (root->right) {
    vec.push_back(root->right->val);
    dfs(root->right, ans, vec);
    vec.pop_back();
  }
}
int sumNumbers(TreeNode* root) {
  if (!root)
    return 0;
  int ans = 0;
  vector<int> vec;
  vec.push_back(root->val);
  dfs(root, ans, vec);
  return ans;
}

int main() {
  TreeNode* t1 = construct_binary_tree({1, 2, 3});
  TreeNode* t2 = construct_binary_tree({4, 9, 0, 5, 1});
  cout << sumNumbers(t1) << " " << sumNumbers(t2) << endl;
  return 0;
}