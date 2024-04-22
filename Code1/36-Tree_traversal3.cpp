#include "head.h"
// 二叉树的前序、中序、后续遍历。统一风格迭代法，核心为将访问和处理脱钩。仍旧使用栈顶元素访问，每取并同步弹出。因为后面还会重新压入带标记的
// 如不为空结点，按照逆序，分别将确实有的左孩子，确实有的有孩子，和自己压入栈，并多压入一个null作为处理标记。
// 取栈头元素，处理到null标记时，代表该栈头元素（nullptr已被弹出了）是要处理的元素，值压入结果中。
// 前序遍历，中左右。访问顺序为反，右左中。一般方法为访问时，直接处理，剩余不为空的右、左孩子压入栈
// 中序遍历，左中右。访问顺序为反，右中左。一般方法为额外cur指针作为前置访问。如果不为空，则不断向左迭代并压入栈。为空则代表处理，并压入右孩子
// 后续遍历，左右中。访问顺序为反，中右左。一般方法为，中右左顺序，访问同步处理。并反转。

vector<int> inorderTraversal(TreeNode* root) {
  vector<int> result;
  stack<TreeNode*> stk;
  if (root)
    stk.push(root);
  while (!stk.empty()) {
    TreeNode* cur = stk.top();
    stk.pop();
    if (cur) {
      if (cur->right)
        stk.push(cur->right);
      stk.push(cur);
      stk.push(nullptr);
      if (cur->left)
        stk.push(cur->left);
    } else {
      cur = stk.top();
      stk.pop();
      result.push_back(cur->val);
    }
  }
  return result;
}

vector<int> preorderTraversal(TreeNode* root) {
  vector<int> result;
  stack<TreeNode*> stk;
  if (root)
    stk.push(root);
  while (!stk.empty()) {
    TreeNode* cur = stk.top();
    stk.pop();
    if (cur) {
      if (cur->right)
        stk.push(cur->right);
      if (cur->left)
        stk.push(cur->left);
      stk.push(cur);
      stk.push(nullptr);
    } else {
      cur = stk.top();
      result.push_back(cur->val);
      stk.pop();
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
    if (cur) {
      stk.push(cur);
      stk.push(nullptr);
      if (cur->right)
        stk.push(cur->right);
      if (cur->left)
        stk.push(cur->left);
    } else {
      cur = stk.top();
      stk.pop();
      result.push_back(cur->val);
    }
  }
  return result;
}

vector<int> inorderTraversal1(TreeNode* root) {
  vector<int> result;
  stack<TreeNode*> st;
  if (!root)
    return result;
  st.push(root);
  while (!st.empty()) {
    TreeNode* node = st.top();
    if (node != nullptr) {
      st.pop();
      if (node->right)
        st.push(node->right);
      st.push(node);
      st.push(nullptr);
      if (node->left)
        st.push(node->left);
    } else {
      st.pop();
      node = st.top();
      st.pop();
      result.push_back(node->val);
    }
  }
  return result;
}

vector<int> preorderTraversal1(TreeNode* root) {
  vector<int> result;
  stack<TreeNode*> st;
  if (!root)
    return result;
  st.push(root);
  while (!st.empty()) {
    TreeNode* node = st.top();
    if (node != nullptr) {
      st.pop();
      if (node->right)
        st.push(node->right);
      if (node->left)
        st.push(node->left);
      st.push(node);
      st.push(nullptr);
    } else {
      st.pop();
      node = st.top();
      st.pop();
      result.push_back(node->val);
    }
  }
  return result;
}

vector<int> postorderTraversal1(TreeNode* root) {
  vector<int> result;
  stack<TreeNode*> st;
  if (!root)
    return result;
  st.push(root);
  while (!st.empty()) {
    TreeNode* node = st.top();
    if (node != nullptr) {
      st.pop();
      st.push(node);
      st.push(nullptr);
      if (node->right)
        st.push(node->right);
      if (node->left)
        st.push(node->left);
    } else {
      st.pop();
      node = st.top();
      st.pop();
      result.push_back(node->val);
    }
  }
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
}