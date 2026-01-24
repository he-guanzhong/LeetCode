#include "head.h"
/* 106. 从中序与后序遍历序列构造二叉树
给定两个整数数组 inorder 和 postorder ，其中 inorder 是二叉树的中序遍历，
postorder 是同一棵树的后序遍历，请你构造并返回这颗 二叉树 。
示例 1:
  输入：inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
  输出：[3,9,20,null,null,15,7]*/

TreeNode* traversal(vector<int>& inorder,
                    vector<int>& postorder,
                    int in_l,
                    int in_r,
                    int post_l,
                    int post_r) {
  if (in_l > in_r)
    return nullptr;
  int value = postorder[post_r];
  TreeNode* root = new TreeNode(value);
  int index = 0;
  for (int i = in_l; i <= in_r; i++) {
    if (inorder[i] == value) {
      index = i;
      break;
    }
  }
  int leftLen = index - in_l;
  root->left = traversal(inorder, postorder, in_l, index - 1, post_l,
                         post_l + leftLen - 1);
  root->right = traversal(inorder, postorder, index + 1, in_r, post_l + leftLen,
                          post_r - 1);
  return root;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
  return traversal(inorder, postorder, 0, inorder.size() - 1, 0,
                   postorder.size() - 1);
}

// 后序最后一位作为根节点，find找到中序遍历根节点坐标，切中、后序遍历，左右分而治之递归。
// 中序遍历直接切，可选左闭右闭、或左闭右开区间
// 切后序遍历时，不可以直接使用中序遍历的根节点下标，因为后序、中序遍历首位不一定对齐，一定要先求中序遍历左分支长度。
// find函数求迭代器位置，减初始迭代器位置，即为下标
TreeNode* buildTree_std(vector<int>& inorder, vector<int>& postorder) {
  if (inorder.size() == 0)  // 无论那个数组，为空返回空指针
    return nullptr;
  int rootValue = postorder[postorder.size() - 1];  // 生成根节点坐标
  TreeNode* root = new TreeNode(rootValue);
  if (inorder.size() == 1)  // 若已为叶子结点，直接返回，此步骤可写可不写
    return root;
  int delimiterIndex = 0;  // 中序遍历确定切入点
  for (; delimiterIndex < inorder.size(); delimiterIndex++) {
    if (inorder[delimiterIndex] == rootValue)
      break;
  }
  // 左闭右开区间构造。切左子树，中序、后序坐标相等。切右子树，中序起点+1，后续终点-1
  vector<int> inorderLeft(inorder.begin(), inorder.begin() + delimiterIndex);
  vector<int> inorderRight(inorder.begin() + delimiterIndex + 1, inorder.end());
  vector<int> postorderLeft(postorder.begin(),
                            postorder.begin() + delimiterIndex);
  vector<int> postorderRight(postorder.begin() + delimiterIndex,
                             postorder.end() - 1);
  root->left = buildTree_std(inorderLeft, postorderLeft);
  root->right = buildTree_std(inorderRight, postorderRight);
  return root;
}

// 下标索引法。不用每次生成新数组，节省资源。左闭右开写法
TreeNode* traversal1(vector<int>& inorder,
                     vector<int>& postorder,
                     int inorder_begin,
                     int inorder_end,
                     int postorder_begin,
                     int postorder_end) {
  if (inorder_begin == inorder_end)
    return nullptr;
  int postorder_root =
      postorder_end - 1;  // 左闭右开区间，注意后续遍历根节点的取值
  int inorder_root =
      find(inorder.begin(), inorder.end(), postorder[postorder_root]) -
      inorder.begin();
  TreeNode* root = new TreeNode(postorder[postorder_root]);
  int left_tree_size = inorder_root - inorder_begin;
  root->left = traversal1(inorder, postorder, inorder_begin, inorder_root,
                          postorder_begin, postorder_begin + left_tree_size);
  root->right = traversal1(inorder, postorder, inorder_root + 1, inorder_end,
                           postorder_begin + left_tree_size, postorder_end - 1);
  return root;
}
TreeNode* buildTree1(vector<int>& inorder, vector<int>& postorder) {
  return traversal1(inorder, postorder, 0, inorder.size(), 0, postorder.size());
}

int main() {
  vector<int> inorder1 = {9, 3, 15, 20, 7};
  vector<int> postorder1 = {9, 15, 7, 20, 3};
  vector<int> inorder2 = {-1};
  vector<int> postorder2 = {-1};
  print_binary_tree(buildTree(inorder1, postorder1));
  print_binary_tree(buildTree(inorder2, postorder2));
  print_binary_tree(buildTree1(inorder1, postorder1));
  print_binary_tree(buildTree1(inorder2, postorder2));
  return 0;
}