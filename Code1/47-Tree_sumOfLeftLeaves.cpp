#include "head.h"
#define null -1
/* 404. 左叶子之和
给定二叉树的根节点 root ，返回所有左叶子之和。  */

// 核心在于通过父节点，判断左叶子是否成立，左叶子为有父节点，且其无左右孩子的结点，故需要三层关系确认。
// 判断得到左孩子后，收集其值，并叠加入后序遍历
// 迭代法，前、中、后序遍历均可，只要得看到左叶子，累加和即可。
int sumOfLeftLeaves(TreeNode* root) {
  stack<TreeNode*> stk;
  if (root)
    stk.push(root);
  int leftValue = 0;
  while (!stk.empty()) {
    TreeNode* cur = stk.top();
    stk.pop();
    if (cur->left && !cur->left->left && !cur->left->right)
      leftValue += cur->left->val;
    if (cur->right)
      stk.push(cur->right);
    if (cur->left)
      stk.push(cur->left);
  }
  return leftValue;
}

// 判断左叶子节点，不能只看其叶子结点，必须依赖其父节点，即该结点有左孩子，且左孩子无左、右孩子。
// 退出条件为，结点为空，返回0；或结点为叶子结点，临时收集左叶子值，并叠加至后序遍历，左右中，左遍历
int sumOfLeftLeaves1(TreeNode* root) {
  if (!root)
    return 0;
  int leftValue = 0;
  if (root->left && !root->left->left && !root->left->right)
    leftValue = root->left->val;
  return leftValue + sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
}

int sumOfLeftLeaves_std(TreeNode* root) {
  if (!root)
    return 0;
  if (root && !root->left &&
      !root->right)  // 若为叶子结点，不判断。此句可写可不写，不写多一层递归
    return 0;
  int leftValue = sumOfLeftLeaves_std(root->left);  // 左
  if (root->left && !root->left->left &&
      !root->left->right)  // 左孩子存在，且左孩子为叶子节点，提取左孩子结点值
    leftValue = root->left->val;
  int rightValue = sumOfLeftLeaves_std(root->right);  // 右
  return leftValue + rightValue;                      // 中
}

int sumOfLeftLeaves2(TreeNode* root) {  // 迭代法，前序遍历，中左右
  if (!root)
    return 0;
  stack<TreeNode*> st;
  st.push(root);
  int result = 0;
  while (!st.empty()) {
    TreeNode* node = st.top();
    st.pop();
    if (node->left && !node->left->left && !node->left->right)
      result += node->left->val;
    if (node->right)
      st.push(node->right);
    if (node->left)
      st.push(node->left);
  }
  return result;
}

int main() {
  vector<int> vec1 = {3, 9, 20, null, null, 15, 7};
  TreeNode* node1 = construct_binary_tree(vec1);
  vector<int> vec2 = {1};
  TreeNode* node2 = construct_binary_tree(vec2);
  /*   vector<int> vec3 = {1, 2, 3};
    TreeNode* node3 = construct_binary_tree(vec3); */
  cout << sumOfLeftLeaves(node1) << " " << sumOfLeftLeaves(node2) << endl;
  cout << sumOfLeftLeaves1(node1) << " " << sumOfLeftLeaves1(node2) << endl;
}
