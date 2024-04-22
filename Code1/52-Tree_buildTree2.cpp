#include "head.h"
#define null -1
/* 105. 从前序与中序遍历序列构造二叉树
给定两个整数数组 preorder 和 inorder ，其中 preorder 是二叉树的先序遍历，
inorder 是同一棵树的中序遍历，请构造二叉树并返回其根节点。
示例 1:
输入: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
输出: [3,9,20,null,null,15,7]*/

// 前序第一位作为根节点，find找到中序遍历根节点坐标，切前、中序遍历，左右分而治之递归。中序遍历直接切，可选左闭右闭、或左闭右开区间
// 切前序遍历时，不可以直接使用中序遍历的根节点下标，因为前序、中序遍历首位不一定对齐，一定要先求中序遍历左分支长度。
// find函数求迭代器位置，减初始迭代器位置，即为下标。left_tree_size为左子树长度，与下标相加后，走到的是正好是“右开”的边界
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
  if (preorder.size() == 0)
    return nullptr;
  int preorder_root = 0;
  int inorder_root =
      find(inorder.begin(), inorder.end(), preorder[preorder_root]) -
      inorder.begin();
  TreeNode* root = new TreeNode(preorder[preorder_root]);
  int left_tree_size = inorder_root;
  vector<int> preorder_left(preorder.begin() + 1,
                            preorder.begin() + 1 + left_tree_size);
  vector<int> inorder_left(inorder.begin(), inorder.begin() + left_tree_size);
  vector<int> preorder_right(preorder.begin() + 1 + left_tree_size,
                             preorder.end());
  vector<int> inorder_right(inorder.begin() + left_tree_size + 1,
                            inorder.end());
  root->left = buildTree(preorder_left, inorder_left);
  root->right = buildTree(preorder_right, inorder_right);
  return root;
}

// 下标索引法。不用每次生成新数组，节省资源。左闭右开写法
TreeNode* traversal1(vector<int>& preorder,
                     vector<int>& inorder,
                     int preorder_begin,
                     int preorder_end,
                     int inorder_begin,
                     int inorder_end) {
  if (preorder_begin == preorder_end)
    return nullptr;
  int preorder_root = preorder_begin;  // 左闭右开区间，注意后续遍历根节点的取值
  int inorder_root =
      find(inorder.begin(), inorder.end(), preorder[preorder_root]) -
      inorder.begin();
  TreeNode* root = new TreeNode(preorder[preorder_root]);
  int left_tree_size = inorder_root - inorder_begin;
  root->left = traversal1(preorder, inorder, preorder_begin + 1,
                          preorder_begin + 1 + left_tree_size, inorder_begin,
                          inorder_root);
  root->right =
      traversal1(preorder, inorder, preorder_begin + 1 + left_tree_size,
                 preorder_end, inorder_root + 1, inorder_end);
  return root;
}
TreeNode* buildTree1(vector<int>& preorder, vector<int>& inorder) {
  return traversal1(preorder, inorder, 0, preorder.size(), 0, inorder.size());
}
int main() {
  vector<int> preorder1 = {3, 9, 20, 15, 7};
  vector<int> inorder1 = {9, 3, 15, 20, 7};
  vector<int> preorder2 = {-1};
  vector<int> inorder2 = {-1};
  print_binary_tree(buildTree(preorder1, inorder1));
  print_binary_tree(buildTree(preorder2, inorder2));
  print_binary_tree(buildTree1(preorder1, inorder1));
  print_binary_tree(buildTree1(preorder2, inorder2));
}