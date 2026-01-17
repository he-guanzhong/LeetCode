#include "head.h"
/* 226. 翻转二叉树
给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。 */

TreeNode* invertTree(TreeNode* root) {
  if (!root)
    return root;
  TreeNode* tmp = invertTree(root->left);
  root->left = invertTree(root->right);
  root->right = tmp;
  return root;
}

// 前、后序遍历：迭代法和递归法均可。迭代法中一般法、统一法均可。
// 中序遍历：递归法，注意反转右孩子时，原右孩子已经变成了左孩子，故再反转一次左孩子。但如果迭代法利用栈。则不受影响
// 翻转左右孩子核心在于swap，交换了两个结点的地址，故原左指针指向了右孩子，右指针指向左孩子。
// 不可以将右孩子的递归，直接用左孩子承接。因为这涉及两次反转
TreeNode* invertTree1(TreeNode* root) {  // 递归法，前序遍历
  if (root == nullptr)
    return nullptr;
  swap(root->left, root->right);
  invertTree(root->left);
  invertTree(root->right);
  return root;
}
TreeNode* invertTree2(TreeNode* root) {  // 后序遍历
  if (root == nullptr)
    return root;
  stack<TreeNode*> st;
  st.push(root);
  while (!st.empty()) {
    TreeNode* node = st.top();
    st.pop();
    swap(node->left, node->right);  // 中
    if (node->right)
      st.push(node->right);  // 右
    if (node->left)
      st.push(node->left);  // 左
  }
  return root;
}
TreeNode* invertTree3(TreeNode* root) {  // 层序遍历
  if (root == nullptr)
    return root;
  queue<TreeNode*> que;
  que.push(root);
  while (!que.empty()) {
    TreeNode* node = que.front();
    que.pop();
    swap(node->left, node->right);
    if (node->left)
      que.push(node->left);
    if (node->right)
      que.push(node->right);
  }
  return root;
}

TreeNode* invertTree4(TreeNode* root) {  // 中序遍历递归法 注意防止两次访问
  if (root == nullptr)
    return root;
  invertTree4(root->left);
  swap(root->left, root->right);
  invertTree4(root->left);  // 此处应为left，因为已经反转
  return root;
}

TreeNode* invertTree5(TreeNode* root) {  // 中序遍历统一写法
  stack<TreeNode*> st;
  if (root)
    st.push(root);
  while (!st.empty()) {
    TreeNode* node = st.top();
    st.pop();
    if (node != nullptr) {
      if (node->right)  // 右
        st.push(node->right);
      st.push(node);  // 中
      st.push(nullptr);
      if (node->left)  // 左
        st.push(node->left);
    } else {
      node = st.top();
      st.pop();
      swap(node->left, node->right);
    }
  }
  return root;
}

int main() {
  vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7};
  TreeNode* t1 = sortedArray2BST(vec1);
  vector<int> vec2 = {1};
  TreeNode* t2 = sortedArray2BST(vec2);
  TreeNode* t3 = nullptr;
  vec1.clear();
  vec2.clear();
  print_binary_tree(invertTree(t1));
  print_binary_tree(invertTree(t2));
  print_binary_tree(invertTree(t3));
  print_binary_tree(invertTree1(t1));
  print_binary_tree(invertTree1(t2));
  print_binary_tree(invertTree1(t3));
  return 0;
}