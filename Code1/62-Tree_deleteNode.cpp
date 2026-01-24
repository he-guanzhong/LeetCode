#include "head.h"
/* 450. 删除二叉搜索树中的节点
给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的 key
对应的节点，并保证二叉搜索树的性质不变。返回二叉搜索树（有可能被更新）的根节点的引用。
一般来说，删除节点可分为两个步骤：
    首先找到需要删除的节点；
    如果找到了，删除它。 */

TreeNode* deleteNode(TreeNode* root, int key) {
  TreeNode *pre = nullptr, *cur = root;
  while (cur) {
    if (cur->val < key)
      cur = cur->right;
    else if (cur->val > key)
      cur = cur->left;
    else
      break;
    pre = cur;
  }
  if (!cur)
    return root;
  TreeNode* newNode = cur->right;
  TreeNode* right = newNode;
  if (!right) {
    pre->left = cur->left;
    return root;
  }
  while (right->left) {
    right = right->left;
  }
  right->left = cur->left;
  pre->left = newNode;
  return root;
}

// 叶子结点，直接删除。传统做法，分情况讨论
// 返回值可以设为新树的根节点。需要左右承接
// 分五种情况分别讨论。1，找不到；2.叶子节点直接删，3.其左有右无，4.左无右右。
// 5.所有都有子树，则把左子树，转移至右子树的左节点最下一层，然后删除该结点
TreeNode* deleteNode1(TreeNode* root, int key) {
  if (!root)
    return root;
  if (root->val == key) {
    if (!root->left && !root->right) {
      delete root;
      return nullptr;
    } else if (root->left) {
      TreeNode* retNode = root->left;
      delete root;
      return retNode;
    } else if (root->right) {
      TreeNode* retNode = root->right;
      delete root;
      return retNode;
    } else {
      TreeNode* cur = root->right;
      while (cur->left)
        cur = cur->left;
      cur->left = root->left;
      TreeNode* retNode = root->right;
      delete root;
      return retNode;
    }
  }
  if (key < root->val)
    root->left = deleteNode1(root->left, key);
  if (key > root->val)
    root->right = deleteNode1(root->right, key);
  return root;
}

// 普通二叉树的删除方式。不必考虑五种情况。
// 第一步，找到等值结点，将其交换至右子树的最左叶子结点上，不需返回
// 第二步，二次确认等值结点的位置，返回其左子树结点，一般为值或nullptr。
TreeNode* deleteNode2(TreeNode* root, int key) {
  if (!root)
    return root;
  if (root->val == key) {
    if (root->right == nullptr)  // 二次处理，最终删除
      return root->left;
    TreeNode* cur = root->right;
    while (cur->left)  // 一次处理，交换位置
      cur = cur->left;
    swap(root->val, cur->val);
  }
  root->left = deleteNode2(root->left, key);
  root->right = deleteNode2(root->right, key);
  return root;
}

// 迭代法，单独设计删除结点函数，其右子树空，则返回左子树。
// 右子树不空，找右子树最左结点，原左子树放置于最左结点之左，返回右子树
// 主函数中，记录上一结点。cur确定相等结点，pre确定其上一结点。如只有一个结点直接删，如确定cur是左、右子结点，删除之
TreeNode* deleteOneNode3(TreeNode* node) {
  if (!node)
    return node;
  if (node->right == nullptr)
    return node->left;
  TreeNode* cur = node->right;
  while (cur->left)
    cur = cur->left;
  cur->left = node->left;
  return node->right;
}
TreeNode* deleteNode3(TreeNode* root, int key) {
  if (!root)
    return root;
  TreeNode* cur = root;
  TreeNode* pre = nullptr;
  while (cur) {
    if (cur->val == key)
      break;
    pre = cur;
    if (key < cur->val)
      cur = cur->left;
    else
      cur = cur->right;
  }
  if (pre == nullptr)  // 只有一个结点，直接删
    return deleteOneNode3(cur);
  if (pre->left && pre->left->val == key)  // 即将删除点为左节点
    pre->left = deleteOneNode3(cur);
  if (pre->right && pre->right->val == key)
    pre->right = deleteOneNode3(cur);
  return root;
}

int main() {
  vector<int> vec1 = {5, 3, 6, 2, 4, null, 7};
  vector<int> vec2 = {5, 3, 6, 2, 4, null, 7};
  vector<int> vec3 = {};
  TreeNode* node1 = construct_binary_tree(vec1);
  TreeNode* node2 = construct_binary_tree(vec2);
  TreeNode* node3 = construct_binary_tree(vec3);
  int val1 = 3, val2 = 0, val3 = 0;
  print_binary_tree(deleteNode(node1, val1));
  print_binary_tree(deleteNode(node2, val2));
  print_binary_tree(deleteNode(node3, val3));
  node1 = construct_binary_tree(vec1);
  node2 = construct_binary_tree(vec2);
  node3 = construct_binary_tree(vec3);
  print_binary_tree(deleteNode1(node1, val1));
  print_binary_tree(deleteNode1(node2, val2));
  print_binary_tree(deleteNode1(node3, val3));
  return 0;
}