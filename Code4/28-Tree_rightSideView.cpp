#include "head.h"
#define null -1
/* 199. 二叉树的右视图
给定一个二叉树的 根节点
root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
示例 1:
输入: [1,2,3,null,5,null,4]
输出: [1,3,4]
示例 2:
输入: [1,null,3]
输出: [1,3]
示例 3:
输入: []
输出: [] */

vector<int> rightSideView(TreeNode* root) {
  vector<int> ans;
  queue<TreeNode*> que;
  if (root)
    que.push(root);
  while (!que.empty()) {
    int n = que.size();
    for (int i = 0; i < n; i++) {
      TreeNode* cur = que.front();
      que.pop();
      if (i == 0)
        ans.push_back(cur->val);
      if (cur->right)
        que.push(cur->right);
      if (cur->left)
        que.push(cur->left);
    }
  }
  return ans;
}

// 深度优先搜索，变前序遍历，迭代法，中右左。使用栈记录结点和层数，哈希表记录层数和该层最右值。如此遍历哈希表可得所有最右元素
vector<int> rightSideView1(TreeNode* root) {
  stack<pair<TreeNode*, int>> st;
  vector<int> ans;
  int maxDep = -1;
  unordered_map<int, int> rightValAtDepth;
  if (root) {
    st.push({root, 0});
    rightValAtDepth[0] = root->val;
  }
  while (!st.empty()) {
    TreeNode* cur = st.top().first;
    int depth = st.top().second;
    maxDep = max(maxDep, depth);
    st.pop();
    if (rightValAtDepth.find(depth) == rightValAtDepth.end())
      rightValAtDepth[depth] = cur->val;
    if (cur->left)
      st.push({cur->left, depth + 1});
    if (cur->right)
      st.push({cur->right, depth + 1});
  }
  for (int i = 0; i <= maxDep; i++)
    ans.push_back(rightValAtDepth[i]);
  return ans;
}

// 广度优先搜索。依旧从左至右遍历，每层最后一个即为最右元素，故无需判断该层哈希表是否存在过，不断更新即可
// 无需记录最大深度，因为哈希表size即为结点深度数。
vector<int> rightSideView2(TreeNode* root) {
  queue<pair<TreeNode*, int>> que;
  vector<int> ans;
  unordered_map<int, int> rightValAtDepth;
  if (root) {
    que.push({root, 0});
    rightValAtDepth[0] = root->val;
  }
  while (!que.empty()) {
    TreeNode* cur = que.front().first;
    int depth = que.front().second;
    que.pop();
    rightValAtDepth[depth] = cur->val;  // 每层最后一个是最右不断更新即可
    if (cur->left)
      que.push({cur->left, depth + 1});
    if (cur->right)
      que.push({cur->right, depth + 1});
  }
  for (int i = 0; i < rightValAtDepth.size(); i++)
    ans.push_back(rightValAtDepth[i]);
  return ans;
}

int main() {
  TreeNode* t1 = construct_binary_tree({1, 2, 3, null, 5, null, 4});
  TreeNode* t2 = construct_binary_tree({1, null, 3});
  TreeNode* t3 = construct_binary_tree({});
  printVector(rightSideView(t1));
  printVector(rightSideView(t2));
  printVector(rightSideView(t3));
  printVector(rightSideView1(t1));
  printVector(rightSideView1(t2));
  printVector(rightSideView1(t3));
  return 0;
}