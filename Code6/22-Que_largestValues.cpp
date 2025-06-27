#include "head.h"

/* 515. 在每个树行中找最大值
给定一棵二叉树的根节点 root ，请找出该二叉树中每一层的最大值。
示例1：
  输入: root = [1,3,2,5,3,null,9]
  输出: [1,3,9]
示例2：
  输入: root = [1,2,3]
  输出: [1,3]
提示：
  二叉树的节点个数的范围是 [0,104]
  -231 <= Node.val <= 231 - 1 */

void dfs(TreeNode* root, int depth, vector<int>& ans) {
  if (!root)
    return;
  if (depth == ans.size())
    ans.push_back(root->val);
  ans[depth] = max(ans[depth], root->val);
  dfs(root->left, depth + 1, ans);
  dfs(root->right, depth + 1, ans);
}
vector<int> largestValues(TreeNode* root) {
  vector<int> ans;
  dfs(root, 0, ans);
  return ans;
}

// BFS利用队列，或DFS记录深度、最大深度。两个办法均可
vector<int> largestValues1(TreeNode* root) {
  vector<int> ans;
  queue<TreeNode*> que;
  if (root)
    que.push(root);
  while (!que.empty()) {
    int n = que.size();
    int maxVal = INT_MIN;
    while (n--) {
      TreeNode* cur = que.front();
      que.pop();
      maxVal = max(maxVal, cur->val);
      if (cur->left)
        que.push(cur->left);
      if (cur->right)
        que.push(cur->right);
    }
    ans.push_back(maxVal);
  }
  return ans;
}

int main() {
  TreeNode* root1 = construct_binary_tree({1, 3, 2, 5, 3, null, 9});
  TreeNode* root2 = construct_binary_tree({1, 2, 3});
  printVector(largestValues(root1));
  printVector(largestValues(root2));
  printVector(largestValues1(root1));
  printVector(largestValues1(root2));
  return 0;
}