#include "head.h"
/* 701. 二叉搜索树中的插入操作
给定二叉搜索树（BST）的根节点 root 和要插入树中的值 value ，将值插入二叉搜索树。
返回插入后二叉搜索树的根节点。 输入数据 保证
，新值和原始二叉搜索树中的任意节点值都不同。
注意，可能存在多种有效的插入方式，只要树在插入后仍保持为二叉搜索树即可。
你可以返回 任意有效的结果 。 */

TreeNode* insertIntoBST(TreeNode* root, int val) {
  if (!root)
    return new TreeNode(val);
  TreeNode* cur = root;
  TreeNode* pre = cur;
  while (cur) {
    pre = cur;
    if (val > cur->val)
      cur = cur->right;
    else if (val < cur->val)
      cur = cur->left;
  }
  if (val > pre->val)
    pre->right = new TreeNode(val);
  else
    pre->left = new TreeNode(val);
  return root;
}

// 迭代法。先判空，新添结点。否则记录cur和pre两个结点，因为cur最终向左、右搜索停止于nullptr，需pre记录上一不为空结点，注意一定是进入while后先赋值
// 递归法。若为空结点，已找到新增位置，添加并返回。若不为空，则需返回当前结点，但前提是其左、右指针，指向新增后返回的树
TreeNode* insertIntoBST1(TreeNode* root, int val) {
  if (!root) {
    TreeNode* node = new TreeNode(val);
    return node;
  }
  if (root->val < val)
    root->right = insertIntoBST1(root->right, val);
  if (root->val > val)
    root->left = insertIntoBST1(root->left, val);
  return root;
}

// 不利用返回值作为结点，单独设立外置的父节点，随时记录上一层的位置，注意对于空结点特殊处理
TreeNode* parent = nullptr;
void traversal2(TreeNode* root, int val) {
  if (!root) {
    TreeNode* node = new TreeNode(val);
    if (val > parent->val)
      parent->right = node;
    else
      parent->left = node;
    return;
  }
  parent = root;
  if (val < root->val)
    traversal2(root->left, val);
  if (val > root->val)
    traversal2(root->right, val);
  return;
}
TreeNode* insertIntoBST2(TreeNode* root, int val) {
  parent = nullptr;
  if (!root)
    root = new TreeNode(val);
  traversal2(root, val);
  return root;
}

// 迭代法，还是记录父节点的位置，一定要先更新，再移动当前结点坐标
TreeNode* insertIntoBST3(TreeNode* root, int val) {
  if (!root)
    return new TreeNode(val);
  TreeNode* cur = root;
  TreeNode* parent = nullptr;
  while (cur != nullptr) {
    parent = cur;  // 必须先记录上一结点，再左右分开，不能最后再更新
    if (val < cur->val)
      cur = cur->left;
    else
      cur = cur->right;
  }
  TreeNode* node = new TreeNode(val);
  if (val < parent->val)
    parent->left = node;
  else
    parent->right = node;
  return root;
}

int main() {
  vector<int> vec1 = {4, 2, 7, 1, 3};
  vector<int> vec2 = {40, 20, 60, 10, 30, 50, 70};
  vector<int> vec3 = {4, 2, 7, 1, 3, null, null, null, null, null, null};
  TreeNode* node1 = construct_binary_tree(vec1);
  TreeNode* node2 = construct_binary_tree(vec2);
  TreeNode* node3 = construct_binary_tree(vec3);
  int val1 = 5, val2 = 25, val3 = 5;
  print_binary_tree(insertIntoBST(node1, val1));
  print_binary_tree(insertIntoBST(node2, val2));
  print_binary_tree(insertIntoBST(node3, val3));
  print_binary_tree(insertIntoBST1(node1, val1));
  print_binary_tree(insertIntoBST1(node2, val2));
  print_binary_tree(insertIntoBST1(node3, val3));
  return 0;
}