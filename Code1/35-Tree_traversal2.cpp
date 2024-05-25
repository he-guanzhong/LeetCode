#include "head.h"
// 二叉树的前序、中序、后续遍历。关键在于中间节点是什么时候处理。迭代法
// 前序遍历，中左右。先判空。利用栈，先取值，然后压右节点、左节点
// 中序遍历，左中右。不必判空，作为压栈处理的前置节点，不为空指针时，直接压栈，并向左迭代。为空时，取头值，并向右迭代
// 后续遍历, 左右中。转换为 中右左 的前序遍历模式。最后反转结果。

vector<int> preorderTraversal(TreeNode* root) {
  vector<int> result;
  stack<TreeNode*> stk;
  if (root)
    stk.push(root);
  while (!stk.empty()) {
    TreeNode* cur = stk.top();
    stk.pop();
    result.push_back(cur->val);
    if (cur->right)
      stk.push(cur->right);
    if (cur->left)
      stk.push(cur->left);
  }
  return result;
}

vector<int> inorderTraversal(TreeNode* root) {
  vector<int> result;
  stack<TreeNode*> stk;
  TreeNode* cur = root;
  while (!stk.empty() || cur) {
    if (cur) {
      stk.push(cur);
      cur = cur->left;
    } else {
      cur = stk.top();
      stk.pop();
      result.push_back(cur->val);
      cur = cur->right;
    }
  }
  return result;
}

vector<int> postorderTraversal(TreeNode* root) {
  vector<int> result;
  stack<TreeNode*> stk;
  if (root)
    stk.push(root);
  while (!stk.empty()) {
    TreeNode* cur = stk.top();
    stk.pop();
    result.push_back(cur->val);
    if (cur->left)
      stk.push(cur->left);
    if (cur->right)
      stk.push(cur->right);
  }
  reverse(result.begin(), result.end());
  return result;
}

vector<int> preorderTraversal1(TreeNode* root) {
  vector<int> result;
  stack<TreeNode*> st;
  if (root == nullptr)
    return result;
  st.push(root);
  while (!st.empty()) {
    TreeNode* node = st.top();
    st.pop();
    result.push_back(node->val);
    if (node->right)
      st.push(node->right);
    if (node->left)
      st.push(node->left);
  }
  return result;
}

vector<int> inorderTraversal1(TreeNode* root) {
  vector<int> result;
  stack<TreeNode*> st;
  TreeNode* cur = root;
  while (cur != nullptr || !st.empty()) {
    if (cur != nullptr) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      result.push_back(cur->val);
      cur = cur->right;
    }
  }
  return result;
}

vector<int> postorderTraversal1(TreeNode* root) {
  vector<int> result;
  stack<TreeNode*> st;
  if (root == nullptr)
    return result;
  st.push(root);
  while (!st.empty()) {
    TreeNode* node = st.top();
    st.pop();
    result.push_back(node->val);
    if (node->left)
      st.push(node->left);
    if (node->right)
      st.push(node->right);
  }
  reverse(result.begin(), result.end());
  return result;
}

int main() {
  vector<int> vec = {1, 2, 3, 4, 5, 6, 7};
  TreeNode* t1 = sortedArray2BST(vec);
  printVector(preorderTraversal(t1));
  printVector(inorderTraversal(t1));
  printVector(postorderTraversal(t1));
  printVector(preorderTraversal1(t1));
  printVector(inorderTraversal1(t1));
  printVector(postorderTraversal1(t1));
  return 0;
}