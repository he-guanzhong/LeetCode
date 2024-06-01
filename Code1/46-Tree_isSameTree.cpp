#include "head.h"
/* 100. 相同的树
 给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。
如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。   */

bool isSameTree(TreeNode* p, TreeNode* q) {
  if (!p && !q)
    return true;
  queue<TreeNode*> que;
  que.push(p);
  que.push(q);
  while (!que.empty()) {
    TreeNode* cur1 = que.front();
    que.pop();
    TreeNode* cur2 = que.front();
    que.pop();
    if (!cur1 && !cur2)
      continue;
    else if (!cur1 && cur2 || cur1 && !cur2 || cur1->val != cur2->val)
      return false;
    else {
      que.push(cur1->left);
      que.push(cur2->left);
      que.push(cur1->right);
      que.push(cur2->right);
    }
  }
  return true;
}

// 递归法，分别判断p左q左，和p右q右。
// 迭代法，允许空结点入栈，如此可判断是否结点相等
bool isSameTree1(TreeNode* p, TreeNode* q) {
  if (!p && !q)
    return true;
  else if (!q || !p || p->val != q->val)
    return false;
  else
    return isSameTree1(p->left, q->left) && isSameTree1(p->right, q->right);
}

bool isSameTree2(TreeNode* p, TreeNode* q) {
  queue<TreeNode*> que;
  que.push(p);
  que.push(q);
  while (!que.empty()) {
    TreeNode* leftNode = que.front();
    que.pop();
    TreeNode* rightNode = que.front();
    que.pop();
    if (!leftNode && !rightNode)
      continue;
    else if (!leftNode || !rightNode || leftNode->val != rightNode->val)
      return false;
    else {
      que.push(leftNode->left);
      que.push(rightNode->left);
      que.push(leftNode->right);
      que.push(rightNode->right);
    }
  }
  return true;
}

int main() {
  vector<int> vec1 = {1, 2, 3, null, 5};
  TreeNode* node1 = construct_binary_tree(vec1);
  vector<int> vec2 = {1, 2, 3, null, 5};
  TreeNode* node2 = construct_binary_tree(vec2);
  vector<int> vec3 = {1, 2, 3};
  TreeNode* node3 = construct_binary_tree(vec3);
  cout << isSameTree(node1, node2) << " " << isSameTree(node3, node2) << endl;
  cout << isSameTree1(node1, node2) << " " << isSameTree1(node3, node2) << endl;
  return 0;
}
