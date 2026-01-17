#include "head.h"
/* 101. 对称二叉树
给你一个二叉树的根节点 root ， 检查它是否轴对称。 */

bool compare(TreeNode* a, TreeNode* b) {
  if (!a && !b)
    return true;
  if (!a || !b || a->val != b->val)
    return false;
  return compare(a->left, b->right) && compare(a->right, b->left);
}
bool isSymmetric(TreeNode* root) {
  if (!root)
    return true;
  return compare(root->left, root->right);
}

// 优选递归法，对比左、右两个结点，分三种情况讨论。次选迭代法，任意容器两两压入、取出容器比较
// 递归法，双空为真，一空为假，不等为假，其余递归比较左左右右，左右右左
bool compare1(TreeNode* left, TreeNode* right) {
  if (!left && !right)
    return true;
  else if (!left || !right || left->val != right->val)
    return false;
  else
    return compare1(left->left, right->right) &&
           compare1(left->right, right->left);
}
bool isSymmetric1(TreeNode* root) {
  if (!root)
    return true;
  return compare1(root->left, root->right);
}

// 迭代法，利用队列，类似层序遍历，但不是层序遍历，任意容器均可，两两元素压入、弹出、相比较
// 首先排除空头结点情况。然后将成对左、右孩子压入某容器，然后两两取出，若均为空，跳过。如一方空一方不空，或值不相等，返回假。
// 若二者值相等，则分别对左左右右压入，左右右左压入。保证两两取出结点时，是要对比的结点
bool isSymmetric2(TreeNode* root) {
  if (!root)
    return true;
  queue<TreeNode*> que;
  que.push(root->left);
  que.push(root->right);
  while (!que.empty()) {
    TreeNode* leftNode = que.front();
    que.pop();
    TreeNode* rightNode = que.front();
    que.pop();
    if (!leftNode && !rightNode)
      continue;
    else if (!leftNode || !rightNode || rightNode->val != leftNode->val)
      return false;
    que.push(leftNode->left);
    que.push(rightNode->right);
    que.push(leftNode->right);
    que.push(rightNode->left);
  }
  return true;
}

// 同样，利用栈和数组，也可以实现类似功能
bool isSymmetric3(TreeNode* root) {
  if (!root)
    return true;
  stack<TreeNode*> st;
  st.push(root->left);
  st.push(root->right);
  while (!st.empty()) {
    TreeNode* leftNode = st.top();
    st.pop();
    TreeNode* rightNode = st.top();
    st.pop();
    if (!leftNode && !rightNode)
      continue;
    else if (!leftNode || !rightNode || rightNode->val != leftNode->val)
      return false;
    st.push(leftNode->left);
    st.push(rightNode->right);
    st.push(leftNode->right);
    st.push(rightNode->left);
  }
  return true;
}

int main() {
  vector<int> vec1 = {1, 2, 3, 4, 3, 2, 1};
  vector<int> vec2 = {1, 2, 3, 4, 5, 6, 7};
  vector<int> vec3 = {1, 2, 3, 4, 5, 6};
  TreeNode* root1 = sortedArray2BST(vec1);
  TreeNode* root2 = sortedArray2BST(vec2);
  TreeNode* root3 = sortedArray2BST(vec3);
  cout << isSymmetric(root1) << " " << isSymmetric(root2) << " "
       << isSymmetric(root3) << endl;
  cout << isSymmetric1(root1) << " " << isSymmetric1(root2) << " "
       << isSymmetric1(root3) << endl;
  return 0;
}