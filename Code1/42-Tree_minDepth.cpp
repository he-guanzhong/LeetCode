#include "head.h"
/* 111. 二叉树的最小深度
给定一个二叉树，找出其最小深度。
最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
说明：叶子节点是指没有子节点的节点。 */

int minDepth(TreeNode* root) {
  queue<TreeNode*> que;
  if (root)
    que.push(root);
  int depth = 0;
  int result = INT_MAX;
  while (!que.empty()) {
    int size = que.size();
    depth++;
    while (size--) {
      TreeNode* cur = que.front();
      que.pop();
      if (!cur->left && !cur->right)
        result = min(result, depth);
      if (cur->left)
        que.push(cur->left);
      if (cur->right)
        que.push(cur->right);
    }
  }
  return result == INT_MAX ? 0 : result;
}

// 后序遍历：求高度，返回值为高度。不能简单认为该结点最小高度是左高度、有高度最小+1
//          因为左为空则会认为该结点高度为1。应该对左右子树分别讨论
// 前序遍历：求深度。传入参数为深度。先排除空结点深度为0的例外情况
//          初始化最小深度结果为INT_MAX。中左右顺序，中为到达叶子结点，比较深度大小。
// 迭代法：层序遍历。注意，无需设置result一直比较min，因为第一次遍历得到叶子节点的深度，就是最小深度。
// 最小深度，注意不是根节点的深度1，而是左右子树的最小深度+1，所以要分开讨论
int minDepth1(TreeNode* root) {  // 递归，后续遍历简洁写法
  if (!root)
    return 0;
  else if (root->left == nullptr && root->right)
    return 1 + minDepth1(root->right);
  else if (root->left && root->right == nullptr)
    return 1 + minDepth1(root->left);
  else
    return 1 + min(minDepth1(root->left), minDepth1(root->right));
}

int minDepth_recursive_std(TreeNode* root) {  // 递归，后续遍历标准写法
  if (!root)
    return 0;
  int leftDepth = minDepth_recursive_std(root->left);
  int rightDepth = minDepth_recursive_std(root->right);
  if (root->left == nullptr && root->right)
    return 1 + rightDepth;
  else if (root->left && root->right == nullptr)
    return 1 + leftDepth;
  else
    return 1 + min(leftDepth, rightDepth);
}

int res = 0;  // 递归法，前序遍历
void getDepth_pre(TreeNode* root, int depth) {
  if (!root)
    return;
  if (root->left == nullptr && root->right == nullptr)  // 如果其为叶子节点
    res = min(res, depth);
  if (root->left)
    getDepth_pre(root->left, depth + 1);
  if (root->right)
    getDepth_pre(root->right, depth + 1);
  return;
}
int minDepth_pre(TreeNode* root) {
  if (!root)
    return 0;
  res = INT_MAX;
  getDepth_pre(root, 1);
  return res;
}

// 层序遍历，由于接层由上至下，所以当第一次发现左右孩子均为空的叶子节点时，当前的深度就可以直接输出
int minDepth2(TreeNode* root) {
  if (!root)
    return 0;
  queue<TreeNode*> que;
  que.push(root);
  int depth = 0;
  while (!que.empty()) {
    int size = que.size();
    depth++;
    while (size--) {
      TreeNode* node = que.front();
      que.pop();
      if (node->left == nullptr && node->right == nullptr)
        return depth;
      if (node->left)
        que.push(node->left);
      if (node->right)
        que.push(node->right);
    }
  }
  return depth;
}

int main() {
  vector<int> vec1 = {1, 2, 3, 4, 3, 2, 1, 1};
  vector<int> vec2 = {1};
  vector<int> vec3 = {};
  TreeNode* root1 = sortedArray2BST(vec1);
  TreeNode* root2 = sortedArray2BST(vec2);
  TreeNode* root3 = sortedArray2BST(vec3);
  cout << minDepth(root1) << " " << minDepth(root2) << " " << minDepth(root3)
       << endl;
  cout << minDepth2(root1) << " " << minDepth2(root2) << " " << minDepth2(root3)
       << endl;
  return 0;
}