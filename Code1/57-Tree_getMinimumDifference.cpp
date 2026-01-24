#include "head.h"
/* 530. 二叉搜索树的最小绝对差
给你一个二叉搜索树的根节点 root ，返回 树中任意两不同节点值之间的最小差值 。
差值是一个正数，其数值等于两值之差的绝对值。
示例 1：
  输入：root = [4,2,6,1,3]
  输出：1
示例 2：
  输入：root = [1,0,48,null,null,12,49]
  输出：1 */

int getMinimumDifference(TreeNode* root) {
  stack<TreeNode*> stk;
  TreeNode* cur = root;
  TreeNode* pre = nullptr;
  int minValue = INT_MAX;
  while (!stk.empty() || cur) {
    if (cur) {
      stk.push(cur);
      cur = cur->left;
    } else {
      cur = stk.top();
      stk.pop();
      if (pre)
        minValue = min(minValue, cur->val - pre->val);
      pre = cur;
      cur = cur->right;
    }
  }
  return minValue;
}

// 中序遍历，求相邻值差的最小值。递归法，可用vec存储，可以保存上一结点。
void traversal1(TreeNode* root, vector<int>& vec) {
  if (!root)
    return;
  traversal1(root->left, vec);
  vec.push_back(root->val);
  traversal1(root->right, vec);
}
int getMinimumDifference1(TreeNode* root) {
  vector<int> vec;
  traversal1(root, vec);
  if (vec.size() < 2)  // 注意排除大小为1的情况
    return 0;
  int minDiff = INT_MAX;
  for (int i = 1; i < vec.size(); i++) {
    minDiff = min(minDiff, vec[i] - vec[i - 1]);
  }
  return minDiff;
}

int result = INT_MAX;
TreeNode* pre2 = nullptr;
void traversal2(TreeNode* root) {
  if (!root)
    return;
  traversal2(root->left);
  if (pre2)
    result = min(result, root->val - pre2->val);
  pre2 = root;
  traversal2(root->right);
}
int getMinimumDifference2(TreeNode* root) {
  result = INT_MAX;
  pre2 = nullptr;
  traversal2(root);
  return result;
}

// 迭代法，中序遍历，cur作为压入的前导指针
int getMinimumDifference3(TreeNode* root) {
  int result = INT_MAX;
  TreeNode* pre = nullptr;
  TreeNode* cur = root;
  stack<TreeNode*> st;
  while (!st.empty() || cur) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      if (pre)
        result = min(result, cur->val - pre->val);
      pre = cur;
      cur = cur->right;
    }
  }
  return result;
}

int main() {
  vector<int> vec1 = {4, 2, 6, 1, 3};
  vector<int> vec2 = {1, 0, 48, null, null, 12, 49};
  vector<int> vec3 = {5, 4, 7};

  TreeNode* node1 = construct_binary_tree(vec1);
  TreeNode* node2 = construct_binary_tree(vec2);
  TreeNode* node3 = construct_binary_tree(vec3);

  cout << getMinimumDifference(node1) << " " << getMinimumDifference(node2)
       << " " << getMinimumDifference(node3) << endl;
  cout << getMinimumDifference1(node1) << " " << getMinimumDifference1(node2)
       << " " << getMinimumDifference1(node3) << endl;
  return 0;
}
