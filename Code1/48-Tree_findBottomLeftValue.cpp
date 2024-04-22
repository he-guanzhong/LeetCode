#include "head.h"
#define null -1
/* 513. 找树左下角的值
给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值。
假设二叉树中至少有一个节点。
示例 1:
输入: root = [2,1,3]
输出: 1
示例 2:
输入: [1,2,3,4,null,5,6,null,null,7]
输出: 7  */

// 递归法，任何遍历均可，但要先做后右，核心是求深度，一旦突破最大深度，即更新result保存的该结点值
// 迭代法，层序遍历，保存每一层第一个结点的值，作为result
int max_depth = 0;
void traversal(TreeNode* root, int depth, int& result) {
  if (!root)
    return;
  if (depth == max_depth) {
    result = root->val;
    max_depth++;
  }
  traversal(root->left, depth + 1, result);
  traversal(root->right, depth + 1, result);
}
int findBottomLeftValue(TreeNode* root) {
  int result = 0;
  traversal(root, 0, result);
  return result;
}

// 递归法，前、中、后序遍历均可，因为没有中间节点处理逻辑，一定保证先左后右。参数为根节点、当前层深度，无返回值。
// 额外设定最大深度maxDepth、result值两个变量。一旦发现深度超过了最大深度，更新深度和result保存的该结点值。
int result = 0;
int maxDepth = INT_MIN;
void traversal1(TreeNode* root, int depth) {
  if (!root->left && !root->right) {  // 叶子结点时
    if (depth > maxDepth) {           // 更新最大深度、最大深度的值
      maxDepth = depth;
      result = root->val;
    }
    return;
  }
  if (root->left)
    traversal1(root->left, depth + 1);
  if (root->right)
    traversal1(root->right, depth + 1);
}
int findBottomLeftValue1(TreeNode* root) {
  if (!root)
    return 0;
  traversal1(root, 0);
  return result;
}
// 层序遍历，最后一行的第一个元素就是最低左层结点
int findBottomLeftValue2(TreeNode* root) {
  queue<TreeNode*> que;
  if (root)
    que.push(root);
  int result = 0;
  while (!que.empty()) {
    int size = que.size();
    for (int i = 0; i < size; i++) {  // 要取结点了，使用for循环而不用while
      TreeNode* node = que.front();
      que.pop();
      if (i == 0)
        result = node->val;
      if (node->left)
        que.push(node->left);
      if (node->right)
        que.push(node->right);
    }
  }
  return result;
}

int main() {
  vector<int> vec1 = {2, 1, 3};
  TreeNode* node1 = construct_binary_tree(vec1);
  vector<int> vec2 = {1, 2, 3, 4, null, 5, 6, null, null, null, null, 7};
  TreeNode* node2 = construct_binary_tree(vec2);
  // print_binary_tree(node2);
  /*   vector<int> vec3 = {1, 2, 3};
    TreeNode* node3 = construct_binary_tree(vec3); */
  cout << findBottomLeftValue(node1) << " " << findBottomLeftValue(node2)
       << endl;
  cout << findBottomLeftValue1(node1) << " " << findBottomLeftValue1(node2)
       << endl;
}
