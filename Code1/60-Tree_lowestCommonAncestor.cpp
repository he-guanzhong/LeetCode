#include "head.h"
/* 235. 二叉搜索树的最近公共祖先
给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点
p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x
的深度尽可能大（一个节点也可以是它自己的祖先）。” */

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
  while (root) {
    if (root->val > p->val && root->val > q->val)
      root = root->left;
    else if (root->val < p->val && root->val < q->val)
      root = root->right;
    else
      return root;
  }
  return root;
}

// 二叉搜索树，递归法不必搜索全树。核心为若root值在pq之间即为公共祖先。
// 若root小于pq，则向右搜索，root大于pq则向左搜索，否则即为要返回的根节点
// 二叉搜索树有序性，只搜索一条边，若pq均小，则搜索左子树，pq均大，则搜索右子树。
// 其余情况即为一大一小，且为左闭右闭区间，则该结点必为所求公共祖先
// 递归法。注意返回值形式，由于本题确认pq存在，可以如下写
TreeNode* lowestCommonAncestor1(TreeNode* root, TreeNode* p, TreeNode* q) {
  if (!root)
    return root;
  if (p->val < root->val && q->val < root->val)
    return lowestCommonAncestor1(root->left, p, q);
  else if (p->val > root->val && q->val > root->val)
    return lowestCommonAncestor1(root->right, p, q);
  else
    return root;
}

// 迭代法，不必利用栈，因为二叉搜索树有序，直接移动root结点。
TreeNode* lowestCommonAncestor2(TreeNode* root, TreeNode* p, TreeNode* q) {
  while (root) {
    if (p->val < root->val && q->val < root->val)
      root = root->left;
    else if (p->val > root->val && q->val > root->val)
      root = root->right;
    else
      return root;
  }
  return nullptr;
}

int main() {
  vector<int> vec1 = {6, 2, 8, 0, 4, 7, 9, null, null, 3, 5};
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