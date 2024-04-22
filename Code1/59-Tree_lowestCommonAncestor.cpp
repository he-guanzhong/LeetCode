#include "head.h"
#define null -1
/* 236. 二叉树的最近公共祖先
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点
p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x
的深度尽可能大（一个节点也可以是它自己的祖先）。” */

// 底部向上搜索，后序遍历、回溯。必须要搜索整个树，且题目说明树中必定存在p、q，故使用临时左右结点，接受左右递归上来的结点
// 如果底部搜索到p或q，直接返回（如此处理了q是p更底层这类情况）。若某结点左右递归结果结点都存在，则比为公共祖先返回之
// 同样，对一边返回结点、一边返回空结点的情况，返回有结点的那一方。如此即可把公共祖先结点上传。
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  if (!root || root == p || root == q)
    return root;
  TreeNode* left = lowestCommonAncestor(root->left, p, q);
  TreeNode* right = lowestCommonAncestor(root->right, p, q);
  if (left && right)
    return root;
  return left ? left : right;
}

// 后序遍历使用回溯。传入三个待比较结点。传出共同结点寻找到的结果。推出条件为，找到p、q结点，或空结点
// 后序遍历，设立临时两个结点存储结构。左右都找到了，该结点即为所求公共祖先。一边找到一边没找到，则传回找到的那一支。
TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
  if (root == p || root == q || !root)
    return root;
  TreeNode* left = lowestCommonAncestor1(root->left, p, q);
  TreeNode* right = lowestCommonAncestor1(root->right, p, q);
  if (left && right)
    return root;
  return left ? left : right;
  /*   else if (left && !right)
      return left;
    else if (!left && right)
      return right;
    return nullptr; */
}

int main() {
  vector<int> vec1 = {3, 5, 1, 6, 2, 0, 8, null, null, 7, 4};
  vector<int> vec2 = {1, 2};

  TreeNode* node1 = construct_binary_tree(vec1);
  TreeNode* node2 = construct_binary_tree(vec2);
  TreeNode* p1 = node1->left;
  TreeNode* q1 = node1->right;
  TreeNode* p2 = node1->left;
  TreeNode* q2 = node1->left->right->right;
  TreeNode* p3 = node2;
  TreeNode* q3 = node2->left;
  print_binary_tree(node1);
  cout << lowestCommonAncestor(node1, p1, q1)->val << " "
       << lowestCommonAncestor(node1, p2, q2)->val << " "
       << lowestCommonAncestor(node2, p3, q3)->val << endl;
  cout << lowestCommonAncestor1(node1, p1, q1)->val << " "
       << lowestCommonAncestor1(node1, p2, q2)->val << " "
       << lowestCommonAncestor1(node2, p3, q3)->val << endl;

  return 0;
}