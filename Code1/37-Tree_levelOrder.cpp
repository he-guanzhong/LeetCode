#include "head.h"
/* 102. 二叉树的层序遍历
给你二叉树的根节点root，返回其节点值的层序遍历。（即逐层地，从左到右访问所有节点）。*/

void traversal(TreeNode* root, vector<vector<int>>& ans, int depth) {
  if (!root)
    return;
  if (depth == ans.size())
    ans.push_back(vector<int>());
  ans[depth].push_back(root->val);
  traversal(root->left, ans, depth + 1);
  traversal(root->right, ans, depth + 1);
}
vector<vector<int>> levelOrder(TreeNode* root) {
  vector<vector<int>> ans;
  traversal(root, ans, 0);
  return ans;
}

// 队列辅助，判空可以后续统一处理。双层循环：外层循环为队列不为空，内含该层大小和该层结果。
// 内层循环为该层元素逐一处理，取值，对不为空的左、右结点分别压入
vector<vector<int>> levelOrder1(TreeNode* root) {
  vector<vector<int>> result;
  queue<TreeNode*> que;
  if (root != nullptr)
    que.push(root);
  while (!que.empty()) {
    int size = que.size();
    vector<int> level;
    while (size--) {
      TreeNode* node = que.front();
      que.pop();
      level.push_back(node->val);
      if (node->left)
        que.push(node->left);
      if (node->right)
        que.push(node->right);
    }
    result.push_back(level);
  }
  return result;
}

// 除了普通的队列辅助法，递归法也可处理层序遍历，
// 递归法，传入参数为矩阵结果，额外的深度信息，作为拓展result层数的条件。不必传入一层结果，因为有深度值，可以直接操作一层结果。
// 然后前序遍历，对该层的结果末尾，push该结点值。之后分别访问左、右孩子，并传入深度+1
void order2(TreeNode* cur, vector<vector<int>>& result, int depth) {
  if (cur == nullptr)
    return;
  if (depth == result.size())
    result.push_back(vector<int>());
  result[depth].push_back(cur->val);
  order2(cur->left, result, depth + 1);
  order2(cur->right, result, depth + 1);
}
vector<vector<int>> levelOrder2(TreeNode* root) {
  vector<vector<int>> result;
  int depth = 0;
  order2(root, result, depth);
  return result;
}

int main() {
  vector<int> vec1 = {1, 2, 3, 4, 5, 6, 7};
  TreeNode* t1 = sortedArray2BST(vec1);
  vector<int> vec2 = {1};
  TreeNode* t2 = sortedArray2BST(vec2);
  TreeNode* t3 = nullptr;

  printMat(levelOrder(t1));
  printMat(levelOrder(t2));
  printMat(levelOrder(t3));
  printMat(levelOrder1(t1));
  printMat(levelOrder1(t2));
  printMat(levelOrder1(t3));
  return 0;
}