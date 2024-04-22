#include "head.h"
#define null -1
/* 700. 二叉搜索树中的搜索
给定二叉搜索树（BST）的根节点 root 和一个整数值 val。
你需要在 BST 中找到节点值等于 val 的节点。 返回以该节点为根的子树。
如果节点不存在，则返回 null 。*/

// 二叉搜索树的性质：左节点不为空，则所有左节点值小于根节点。右节点不为空，则所有右节点值大于根节点
// 二叉搜索树的左右子树也为二叉搜素树。
// 递归法，判断当前节点值大小，传入当前结点的左右孩子。迭代法，while循环内，直接移动root，直至找到val或者为空

TreeNode* searchBST(TreeNode* root, int val) {
  TreeNode* cur = root;
  while (cur) {
    if (cur->val == val)
      return cur;
    else if (cur->val > val)
      cur = cur->left;
    else
      cur = cur->right;
  }
  return cur;
}

// 递归法，因此可以利用其特殊性质，缩小递归范围
TreeNode* searchBST1(TreeNode* root, int val) {
  if (!root || root->val == val)  // 判空和值相等，统一处理
    return root;
  if (root->val < val)
    return searchBST(root->right, val);
  if (root->val > val)
    return searchBST(root->left, val);
  return nullptr;
}

// 迭代法，无需利用栈和队列，无需回溯，无需搜索其他结点，因为搜索的朝向是确定的。
// 当前节点值大于搜索值，左移。当前节点值小于搜索值，右移
TreeNode* searchBST2(TreeNode* root, int val) {
  while (root) {
    if (root->val > val)
      root = root->left;
    else if (root->val < val)
      root = root->right;
    else
      return root;
  }
  return nullptr;
}

int main() {
  vector<int> vec1 = {4, 2, 7, 1, 3};
  int val1 = 2, val2 = 5;
  TreeNode* node1 = construct_binary_tree(vec1);
  TreeNode* node2 = construct_binary_tree(vec1);
  print_binary_tree(searchBST(node1, val1));
  print_binary_tree(searchBST(node2, val2));
  cout << endl;

  node1 = construct_binary_tree(vec1);
  node2 = construct_binary_tree(vec1);
  print_binary_tree(searchBST1(node1, val1));
  print_binary_tree(searchBST1(node2, val2));
  return 0;
}