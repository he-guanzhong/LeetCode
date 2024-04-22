#include "head.h"
#define null -1
/* 110. 平衡二叉树
给定一个二叉树，判断它是否是高度平衡的二叉树。
本题中，一棵高度平衡二叉树定义为：
    一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1.*/

// 高度：本结点到叶子结点最短距离，后序遍历。深度：本结点到根节点最短距离，前序遍历
// 平衡二叉树，要看左右子树高度差是否小于等于1，否则即为否
// 递归法，后序遍历，先求左右子树高度，由于返回值是高度，故若子树已不平衡，需要特殊标记，例如-1。
// 则不平衡右两个条件，左右子树已不平衡（其返回值是-1），左右子树高度差大于1。否则，求正常树的高度。
// 最终，看根节点是否为-1，若有正常高度，则为真
// 迭代法，后序遍历。还是要借助getHeight函数求高度

int getHeight(TreeNode* root) {  // 后序遍历求深度
  stack<TreeNode*> stk;
  if (root)
    stk.push(root);
  int depth = 0;
  int result = 0;
  while (!stk.empty()) {
    TreeNode* cur = stk.top();
    stk.pop();
    if (cur) {
      stk.push(cur);
      stk.push(nullptr);
      depth++;
      if (cur->right)
        stk.push(cur->right);
      if (cur->left)
        stk.push(cur->left);
    } else {
      cur = stk.top();
      stk.pop();
      depth--;
    }
    result = max(result, depth);
  }
  return result;
}
bool isBalanced(TreeNode* root) {
  stack<TreeNode*> stk;
  if (root)
    stk.push(root);
  while (!stk.empty()) {
    TreeNode* cur = stk.top();
    stk.pop();
    int leftHeight = getHeight(cur->left);
    int rightHeight = getHeight(cur->right);
    if (abs(leftHeight - rightHeight) > 1)
      return false;
    if (cur->right)
      stk.push(cur->right);
    if (cur->left)
      stk.push(cur->left);
  }
  return true;
}

// 递归法，传入结点指针，返回量是该节点最大高度，若已经发现不平衡，返回-1
// 求高度方法是后序遍历，左右中，判断条件为左右子树差是否小于等于1，否则返回-1
int getHeight1(TreeNode* root) {
  if (root == nullptr)
    return 0;
  int leftHeight = getHeight1(root->left);
  int rightHeight = getHeight1(root->right);
  if (leftHeight == -1 || rightHeight == -1)
    return -1;
  if (abs(leftHeight - rightHeight) > 1)
    return -1;
  return max(leftHeight, rightHeight) + 1;
}
bool isBalanced1(TreeNode* root) {
  if (!root)
    return true;
  return getHeight1(root) == -1 ? false : true;
}

// 迭代法，模拟后续遍历，利用当前结点的最大深度，求高度
int getHeight2(TreeNode* root) {
  if (!root)
    return 0;
  stack<TreeNode*> st;
  st.push(root);
  int depth = 0;
  int result = 0;
  while (!st.empty()) {
    TreeNode* node = st.top();
    if (node != nullptr) {
      st.pop();
      st.push(node);  // 中
      st.push(nullptr);
      depth++;
      if (node->right)  // 右
        st.push(node->right);
      if (node->left)  // 左
        st.push(node->left);
    } else {
      st.pop();
      node = st.top();
      st.pop();
      depth--;
    }
    result = max(result, depth);
  }
  return result;
}
bool isBalanced2(TreeNode* root) {  // 后序遍历
  if (!root)
    return true;
  stack<TreeNode*> st;
  st.push(root);
  while (!st.empty()) {
    TreeNode* node = st.top();
    st.pop();
    if (abs(getHeight2(node->left) - getHeight2(node->right)) > 1)
      return false;
    if (node->right)
      st.push(node->right);
    if (node->left)
      st.push(node->left);
  }
  return true;
}
int main() {
  vector<int> vec1 = {3, 9, 20, null, null, 15, 7};
  TreeNode* root1 = construct_binary_tree(vec1);
  // print_binary_tree(root1);
  vector<int> vec2 = {1, 2, 2, 3, 3, null, null, 4, 4};
  TreeNode* root2 = construct_binary_tree(vec2);
  // print_binary_tree(root2);
  vector<int> vec3 = {};
  TreeNode* root3 = construct_binary_tree(vec3);
  // print_binary_tree(root3);
  cout << isBalanced(root1) << " " << isBalanced(root2) << " "
       << isBalanced(root3) << endl;
  cout << isBalanced1(root1) << " " << isBalanced1(root2) << " "
       << isBalanced1(root3) << endl;
  return 0;
}