#include "head.h"
/* 144. 二叉树的前序遍历
   145. 二叉树的后序遍历
   94. 二叉树的中序遍历
二叉树的前序、中序、后续遍历。关键在于中间节点是什么时候处理。
  前序遍历：中左右
  中序遍历：左中右
  后序遍历：左右中
使用递归的方式。 */

void traversal_pre(TreeNode* root, vector<int>& result) {
  if (!root)
    return;
  result.push_back(root->val);
  traversal_pre(root->left, result);
  traversal_pre(root->right, result);
}
vector<int> preorderTraversal(TreeNode* root) {
  vector<int> result;
  traversal_pre(root, result);
  return result;
}

void traversal_in(TreeNode* root, vector<int>& result) {
  if (!root)
    return;
  traversal_in(root->left, result);
  result.push_back(root->val);
  traversal_in(root->right, result);
}
vector<int> inorderTraversal(TreeNode* root) {
  vector<int> result;
  traversal_in(root, result);
  return result;
}

void traversal_post(TreeNode* root, vector<int>& result) {
  if (!root)
    return;
  traversal_post(root->left, result);
  traversal_post(root->right, result);
  result.push_back(root->val);
}
vector<int> postorderTraversal(TreeNode* root) {
  vector<int> result;
  traversal_post(root, result);
  return result;
}

// 深度优先搜索，递归三部曲：1.确定参数值和返回值。2.确定终止条件。3.确定递归执行逻辑
void traversal_pre1(TreeNode* root, vector<int>& vec) {
  if (root == nullptr)
    return;
  vec.push_back(root->val);  // 前序遍历，先处理中央节点
  traversal_pre1(root->left, vec);
  traversal_pre1(root->right, vec);
}
vector<int> preorderTraversal1(TreeNode* root) {
  vector<int> result;
  traversal_pre1(root, result);
  return result;
}

void traversal_in1(TreeNode* root, vector<int>& vec) {
  if (!root)
    return;
  traversal_in1(root->left, vec);
  vec.push_back(root->val);
  traversal_in1(root->right, vec);
}
vector<int> inorderTraversal1(TreeNode* root) {
  vector<int> result;
  traversal_in1(root, result);
  return result;
}

void traversal_post1(TreeNode* root, vector<int>& vec) {
  if (!root)
    return;
  traversal_post1(root->left, vec);
  traversal_post1(root->right, vec);
  vec.push_back(root->val);
}
vector<int> postorderTraversal1(TreeNode* root) {
  vector<int> result;
  traversal_post1(root, result);
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