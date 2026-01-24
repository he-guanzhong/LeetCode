#include "head.h"
/* 669. 修剪二叉搜索树
给你二叉搜索树的根节点 root ，同时给定最小边界low 和最大边界
high。通过修剪二叉搜索树，使得所有节点的值在[low, high]中。修剪树 不应该
改变保留在树中的元素的相对结构
(即，如果没有被移除，原有的父代子代关系都应当保留)。 可以证明，存在 唯一的答案。
所以结果应当返回修剪好的二叉搜索树的新的根节点。注意，根节点可能会根据给定的边界发生改变。*/

TreeNode* trimBST(TreeNode* root, int low, int high) {
  if (!root)
    return root;
  else if (root->val < low)
    return trimBST(root->right, low, high);
  else if (root->val > high)
    return trimBST(root->left, low, high);
  root->left = trimBST(root->left, low, high);
  root->right = trimBST(root->right, low, high);
  return root;
}

// 递归法。返回值是当前结点，若当前结点小于下限，返回其右子树修剪后结果，反之亦然。当前结点在上下限中，用左右指针接收修剪后的结果。
// 发现值小于下限，则其左子树必更小，故将其右子树作为根节点递归。值大于上限，右子树必定更大，将其左子树作为根节点递归
// 返回值设计为新树根节点，则当前结点左子树接住下一层左子树返回值，右子树亦然
TreeNode* trimBST1(TreeNode* root, int low, int high) {
  if (!root)
    return root;
  if (root->val < low)
    return trimBST1(root->right, low, high);
  if (root->val > high)
    return trimBST1(root->left, low, high);
  root->left = trimBST1(root->left, low, high);
  root->right = trimBST1(root->right, low, high);
  return root;
}

// 迭代法。先保证根节点在区间内，可能左右搜索，不能分左右两个先后顺序的while。
// 然后分别向左、右修剪，一层循环cur不断向下，一层循环发现超出范围时及时处理
// 迭代法，二叉搜索树的性质不动，先确定根坐标位于左右区间内，然后分别对左子树小于左、右子树大于右进行修剪
TreeNode* trimBST2(TreeNode* root, int L, int R) {
  if (!root)
    return nullptr;
  // 确保根节点在区间内，小了往右走，大了往左走
  while (root && (root->val < L || root->val > R)) {
    if (root->val < L)
      root = root->right;
    else
      root = root->left;
  }
  TreeNode* cur = root;
  while (cur) {  // 如果左结点小，其左结点的右不一定小，更新之
    while (cur->left && cur->left->val < L)
      cur->left = cur->left->right;
    cur = cur->left;
  }
  cur = root;
  while (cur) {  // 右节点大，右节点的左不一定大，更新之
    while (cur->right && cur->right->val > R)
      cur->right = cur->right->left;
    cur = cur->right;
  }
  return root;
}

int main() {
  vector<int> vec1 = {1, 0, 2};
  vector<int> vec2 = {3, 0, 4, null, 2, null, null, null, null, 1};
  vector<int> vec3 = {};
  TreeNode* node1 = construct_binary_tree(vec1);
  TreeNode* node2 = construct_binary_tree(vec2);
  TreeNode* node3 = construct_binary_tree(vec3);
  int low1 = 1, high1 = 2, low2 = 1, high2 = 3;
  print_binary_tree(trimBST(node1, low1, high1));
  print_binary_tree(trimBST(node2, low2, high2));
  print_binary_tree(trimBST(node3, low2, high2));
  node1 = construct_binary_tree(vec1);
  node2 = construct_binary_tree(vec2);
  node3 = construct_binary_tree(vec3);
  cout << endl;
  print_binary_tree(trimBST1(node1, low1, high1));
  print_binary_tree(trimBST1(node2, low2, high2));
  print_binary_tree(trimBST1(node3, low2, high2));
  return 0;
}