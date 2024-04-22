#include "head.h"
#define null -1
/* 124. 二叉树中的最大路径和
二叉树中的 路径
被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。同一个节点在一条路径序列中
至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
路径和 是路径中各节点值的总和。
给你一个二叉树的根节点 root ，返回其 最大路径和 。
示例 1：
输入：root = [1,2,3]
输出：6
解释：最优路径是 2 -> 1 -> 3 ，路径和为 2 + 1 + 3 = 6
示例 2：
输入：root = [-10,9,20,null,null,15,7]
输出：42
解释：最优路径是 15 -> 20 -> 7 ，路径和为 15 + 20 + 7 = 42 */

int dfs(TreeNode* root, int& maxSum) {
  if (!root)
    return 0;
  int left = max(0, dfs(root->left, maxSum));
  int right = max(0, dfs(root->right, maxSum));
  int sum = root->val + left + right;
  maxSum = max(maxSum, sum);
  return root->val + max(left, right);
}
int maxPathSum(TreeNode* root) {
  int maxSum = INT_MIN;
  dfs(root, maxSum);
  return maxSum;
}

// 递归，计算每个结点贡献值，代表以此为终止，路径能达到的最大值。叶子结点为自身，普通结点为自身值，与左、右孩子贡献最大值之和。
// 同步地，计算每个结点最大路径总和，其为自身值，和左、右孩子贡献，三者之和。更新外置最大路径和maxSum1。
// 注意，无论计算贡献、还是路径和，左右孩子贡献均不能为负（负贡献），故计算左右孩子一开始即要非负操作。
int maxSum1;
int maxGain1(TreeNode* root) {
  if (!root)
    return 0;
  int leftGain = max(maxGain1(root->left), 0);
  int rightGain = max(maxGain1(root->right), 0);
  int sum = root->val + leftGain + rightGain;
  maxSum1 = max(maxSum1, sum);
  return root->val + max(leftGain, rightGain);
}
int maxPathSum1(TreeNode* root) {
  maxSum1 = INT_MIN;
  maxGain1(root);
  return maxSum1;
}

int main() {
  TreeNode* t1 = construct_binary_tree({1, 2, 3});
  TreeNode* t2 = construct_binary_tree({-10, 9, 20, null, null, 15, 7});
  TreeNode* t3 = construct_binary_tree({0});
  TreeNode* t4 = construct_binary_tree(
      {5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1});
  cout << maxPathSum(t1) << " " << maxPathSum(t2) << " " << maxPathSum(t3)
       << " " << maxPathSum(t4) << endl;
  cout << maxPathSum1(t1) << " " << maxPathSum1(t2) << " " << maxPathSum1(t3)
       << " " << maxPathSum1(t4) << endl;

  return 0;
}