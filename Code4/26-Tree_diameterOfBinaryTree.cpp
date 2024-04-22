#include "head.h"
/* 543. 二叉树的直径
给你一棵二叉树的根节点，返回该树的 直径 。
二叉树的 直径 是指树中任意两个节点之间最长路径的 长度
。这条路径可能经过也可能不经过根节点 root 。
两节点之间路径的 长度 由它们之间边数表示。
示例 1：
输入：root = [1,2,3,4,5]
输出：3
解释：3 ，取路径 [4,2,1,3] 或 [5,2,1,3] 的长度。
示例 2：
输入：root = [1,2]
输出：1 */

int depth(TreeNode* root, int& ans) {
  if (!root)
    return 0;
  int l = depth(root->left, ans);
  int r = depth(root->right, ans);
  ans = max(ans, l + r + 1);
  return max(l, r) + 1;
}
int diameterOfBinaryTree(TreeNode* root) {
  int ans = 0;
  depth(root, ans);
  return ans - 1;
}

// 辅助函数返回值为该点深度，若将高度定义为，一个结点也为1。则其为左、右孩子深度最大者+1。最长路径值为其路径上结点数-1，而结点数等于左、右深度之和再+1
// 若高度定义为一个结点为0，则最长路径，直接是左、右高度之和。
int ans1;
int depth1(TreeNode* root) {
  if (!root)
    return 0;
  int L = depth1(root->left);
  int R = depth1(root->right);
  ans1 = max(ans1, L + R + 1);
  return max(L, R) + 1;
}
int diameterOfBinaryTree1(TreeNode* root) {
  ans1 = 1;
  depth1(root);
  return ans1 - 1;
}

int main() {
  TreeNode* t1 = construct_binary_tree({1, 2, 3, 4, 5});
  TreeNode* t2 = construct_binary_tree({1, 2});
  TreeNode* t3 = construct_binary_tree({1});
  cout << diameterOfBinaryTree(t1) << " " << diameterOfBinaryTree(t2) << endl;
  cout << diameterOfBinaryTree1(t1) << " " << diameterOfBinaryTree1(t2) << endl;

  return 0;
}