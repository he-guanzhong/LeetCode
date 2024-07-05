#include "head.h"
/* 112. 路径总和
给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。判断该树中是否存在
根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum
。如果存在，返回 true ；否则，返回 false 。
叶子节点 是指没有子节点的节点。
示例 1：
  输入：root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
  输出：true
  解释：等于目标和的根节点到叶节点路径如上图所示。
示例 2：
  输入：root = [1,2,3], targetSum = 5
  输出：false
  解释：树中存在两条根节点到叶子节点的路径：
    (1 --> 2): 和为 3
    (1 --> 3): 和为 4
    不存在 sum = 5 的根节点到叶子节点的路径。
示例 3：
  输入：root = [], targetSum = 0
  输出：false
  解释：由于树是空的，所以不存在根节点到叶子节点的路径。*/

bool hasPathSum(TreeNode* root, int targetSum) {
  stack<pair<TreeNode*, int>> st;
  if (root)
    st.push({root, root->val});
  while (!st.empty()) {
    TreeNode* cur = st.top().first;
    int value = st.top().second;
    st.pop();
    if (targetSum == value)
      return true;
    if (cur->right)
      st.push({cur->right, value + cur->right->val});
    if (cur->left)
      st.push({cur->left, value + cur->left->val});
  }
  return false;
}

// 递归法，判断叶子结点处总和是否为targetSum
// 常规思路外置sum，递归前后加减root->val，事实可以简化，直接在targetSum加减，递归形参处减去本值，则自动回溯
// 迭代法。回溯需再栈中，额外记录直至该结点的总和sum。如此可以不必对targetSum进行加减
// 传统递归法，使用count计数，到减去该节点值后，还剩余的值
bool traversal_std(TreeNode* root, int count) {
  if (!root->left && !root->right && count == 0)
    return true;
  if (!root->left && !root->right)
    return false;
  if (root->left) {
    if (traversal_std(root->left, count - root->left->val))
      return true;
  }
  if (root->right) {
    if (traversal_std(root->right, count - root->right->val))
      return true;
  }
  return false;
}
bool hasPathSum_std(TreeNode* root, int targetSum) {
  if (!root)
    return false;
  return traversal_std(root, targetSum - root->val);
}

// 递归法，简写形式，传入参数为当前结点，还剩下多少值需要满足
bool hasPathSum1(TreeNode* root, int targetSum) {
  if (!root)
    return false;
  if (!root->left && !root->right && root->val == targetSum)
    return true;
  return hasPathSum1(root->left, targetSum - root->val) ||
         hasPathSum1(root->right, targetSum - root->val);
}

// 迭代法，使用栈模拟递归，栈需要额外记录到此结点时，其总和为多少
bool hasPathSum2(TreeNode* root, int targetSum) {
  stack<pair<TreeNode*, int>> st;
  if (!root)
    return false;
  st.push(make_pair(root, root->val));  // 对组存储，该节点和该节点的数值
  while (!st.empty()) {
    pair<TreeNode*, int> node = st.top();
    st.pop();
    if (!node.first->left && !node.first->right && node.second == targetSum)
      return true;
    if (node.first->right)
      st.push(
          make_pair(node.first->right, node.second + node.first->right->val));
    if (node.first->left)
      st.push(make_pair(node.first->left, node.second + node.first->left->val));
  }
  return false;
}

int main() {
  int targetSum1 = 22, targetSum2 = 5, targetSum3 = 0;
  vector<int> vec1 = {5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1};
  TreeNode* node1 = construct_binary_tree(vec1);
  vector<int> vec2 = {1, 2, 3};
  TreeNode* node2 = construct_binary_tree(vec2);
  // print_binary_tree(node2);
  vector<int> vec3 = {};
  TreeNode* node3 = construct_binary_tree(vec3);
  cout << hasPathSum(node1, targetSum1) << " " << hasPathSum(node2, targetSum2)
       << " " << hasPathSum(node3, targetSum3) << endl;
  cout << hasPathSum1(node1, targetSum1) << " "
       << hasPathSum1(node2, targetSum2) << " "
       << hasPathSum1(node3, targetSum3) << endl;
  return 0;
}