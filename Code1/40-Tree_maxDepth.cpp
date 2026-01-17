#include "head.h"
/* 104. 二叉树的最大深度
给定一个二叉树，找出其最大深度。
二叉树的深度为根节点到最远叶子节点的最长路径上的节点数。
说明: 叶子节点是指没有子节点的节点。。 */

int maxDepth(TreeNode* root) {
  queue<TreeNode*> que;
  if (root)
    que.push(root);
  int depth = 0;
  while (!que.empty()) {
    int size = que.size();
    depth++;
    while (size--) {
      TreeNode* cur = que.front();
      que.pop();
      if (cur->left)
        que.push(cur->left);
      if (cur->right)
        que.push(cur->right);
    }
  }
  return depth;
}

// 前序遍历：求深度，先深度再分别处理左右结点。故返回值为空，深度作为传参，外置最大深度结果，每一轮分别比较
// 后序遍历：求高度，先处理左右结点再求深度，故返回值可作为深度，无需额外传参。深度为左右子树深度+1
// 迭代法：层序遍历，求层数
int maxDepth1(TreeNode* root) {  // 递归，简易写法
  if (!root)
    return 0;
  return max(maxDepth1(root->left), maxDepth1(root->right)) + 1;
}

int getDepth2(TreeNode* root) {  // 递归标准写法,后序遍历
  if (!root)
    return 0;
  int leftDepth = getDepth2(root->left);
  int rightDepth = getDepth2(root->right);
  int depth = max(leftDepth, rightDepth);
  return depth + 1;
}
int maxDepth2(TreeNode* root) {
  return getDepth2(root);
}

int res = 0;  // 递归，前序遍历，中左右顺序处理
void getDepth_pre(TreeNode* root, int depth) {
  if (!root)
    return;
  res = max(depth, res);
  if (root->left)
    getDepth_pre(root->left, depth + 1);
  if (root->right)
    getDepth_pre(root->right, depth + 1);
  return;
}
int maxDepth_pre(TreeNode* root) {
  res = 0;
  if (!root)
    return res;
  getDepth_pre(root, 1);
  return res;
}

int maxDepth3(TreeNode* root) {
  if (!root)
    return 0;
  queue<TreeNode*> que;
  que.push(root);
  int depth = 0;
  while (!que.empty()) {
    depth++;
    int size = que.size();
    while (size--) {
      TreeNode* node = que.front();
      que.pop();
      if (node->left)
        que.push(node->left);
      if (node->right)
        que.push(node->right);
    }
  }
  return depth;
}

int main() {
  vector<int> vec1 = {1, 2, 3, 4, 3, 2, 1};
  vector<int> vec2 = {1};
  vector<int> vec3 = {};
  TreeNode* root1 = sortedArray2BST(vec1);
  TreeNode* root2 = sortedArray2BST(vec2);
  TreeNode* root3 = sortedArray2BST(vec3);
  cout << maxDepth(root1) << " " << maxDepth(root2) << " " << maxDepth(root3)
       << endl;
  cout << maxDepth1(root1) << " " << maxDepth1(root2) << " " << maxDepth1(root3)
       << endl;
  return 0;
}