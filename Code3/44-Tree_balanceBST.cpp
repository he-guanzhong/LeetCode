#include "head.h"
/* 1382. 将二叉搜索树变平衡
给你一棵二叉搜索树，请你返回一棵 平衡后
的二叉搜索树，新生成的树应该与原来的树有着相同的节点值。如果有多种构造方法，请你返回任意一种。
如果一棵二叉搜索树中，每个节点的两棵子树高度差不超过 1
，我们就称这棵二叉搜索树是 平衡的 。
示例 1：
  输入：root = [1,null,2,null,3,null,4,null,null]
  输出：[2,1,3,null,null,null,4]
  解释：这不是唯一的正确答案，[3,1,4,null,2,null,null] 也是一个可行的构造方案。
示例 2：
  输入: root = [2,1,3]
  输出: [2,1,3]
提示：
    树节点的数目在 [1, 104] 范围内。
    1 <= Node.val <= 105 */

void inorder(TreeNode* root, vector<int>& path) {
  if (!root)
    return;
  stack<TreeNode*> st;
  TreeNode* cur = root;
  while (st.size() || cur) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      path.push_back(cur->val);
      cur = cur->right;
    }
  }
}
TreeNode* build(vector<int>& path, int left, int right) {
  if (left > right)
    return nullptr;
  else if (left == right)
    return new TreeNode(path[left]);
  int mid = left + ((right - left) >> 1);
  TreeNode* root = new TreeNode(path[mid]);
  root->left = build(path, left, mid - 1);
  root->right = build(path, mid + 1, right);
  return root;
}
TreeNode* balanceBST(TreeNode* root) {
  vector<int> path;
  inorder(root, path);
  // printVector(path);
  return build(path, 0, path.size() - 1);
}

// 将二叉搜索树中序遍历为有序数组，然后重新建立二叉搜索树
void traversal1(TreeNode* root, vector<int>& nums) {
  if (!root)
    return;
  traversal1(root->left, nums);
  nums.push_back(root->val);
  traversal1(root->right, nums);
}
TreeNode* getTree1(vector<int>& nums, int left, int right) {
  if (left > right)
    return nullptr;
  int mid = left + ((right - left) >> 1);
  TreeNode* root = new TreeNode(nums[mid]);
  root->left = getTree1(nums, left, mid - 1);
  root->right = getTree1(nums, mid + 1, right);
  return root;
}
TreeNode* balanceBST1(TreeNode* root) {
  vector<int> nums;
  traversal1(root, nums);
  return getTree1(nums, 0, nums.size() - 1);
}

int main() {
  TreeNode* t1 =
      construct_binary_tree({1, null, 2, null, 3, null, 4, null, null});
  TreeNode* t2 = construct_binary_tree({2, 1, 3});
  print_binary_tree(balanceBST(t1));
  print_binary_tree(balanceBST(t2));
  t1 = construct_binary_tree({1, null, 2, null, 3, null, 4, null, null});
  t2 = construct_binary_tree({2, 1, 3});
  print_binary_tree(balanceBST1(t1));
  print_binary_tree(balanceBST1(t2));
  return 0;
}