#include "head.h"

/* 814. 二叉树剪枝
给你二叉树的根结点 root ，此外树的每个结点的值要么是 0 ，要么是 1 。
返回移除了所有不包含 1 的子树的原二叉树。
节点 node 的子树为 node 本身加上所有 node 的后代。
示例 1：
  输入：root = [1,null,0,0,1]
  输出：[1,null,0,null,1]
  解释：
    只有红色节点满足条件“所有不包含 1 的子树”。 右图为返回的答案。
示例 2：
  输入：root = [1,0,1,0,0,0,1]
  输出：[1,null,1,null,1]
示例 3：
  输入：root = [1,1,0,1,1,0,1,0]
  输出：[1,1,0,1,1,null,1]
提示：
    树中节点的数目在范围 [1, 200] 内
    Node.val 为 0 或 1 */

// 后序遍历典型问题。删除一个结点的必要条件是，该结点值为0，且其左右孩子均为空指针
// 由于是后续遍历，所以到指定结点root时，其孩子必定已经被删减过，不存在孩子有值但本层为0需要删减的情况
TreeNode* pruneTree(TreeNode* root) {
  if (!root)
    return root;
  root->left = pruneTree(root->left);
  root->right = pruneTree(root->right);
  if (root->val == 0 && !root->left && !root->right)
    return nullptr;
  return root;
}

int main() {
  TreeNode* t1 = construct_binary_tree({1, null, 0, 0, 1});
  TreeNode* t2 = construct_binary_tree({1, 0, 1, 0, 0, 0, 1});
  TreeNode* t3 = construct_binary_tree({1, 1, 0, 1, 1, 0, 1, 0});
  print_binary_tree(pruneTree(t1));
  print_binary_tree(pruneTree(t2));
  print_binary_tree(pruneTree(t3));
  return 0;
}