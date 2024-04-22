#include "head.h"
#define null -1

/* 538. 把二叉搜索树转换为累加树
给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater
Sum Tree），使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。
提醒一下，二叉搜索树满足下列约束条件：
    节点的左子树仅包含键 小于 节点键的节点。
    节点的右子树仅包含键 大于 节点键的节点。
    左右子树也必须是二叉搜索树。
示例 2：
输入：root = [0,null,1]
输出：[1,null,1]
示例 3：
输入：root = [1,0,2]
输出：[3,3,2]

注意：本题和 1038:
https://leetcode-cn.com/problems/binary-search-tree-to-greater-sum-tree/ 相同 */

// 递归法。累加树意为从最右侧开始，按右中左的顺序，每个结点val，叠加上一个结点累加后的值。故设定上一结点累加值，并实时更新
// 迭代法。反中序遍历，右中做。记录pre上一结点值

TreeNode* convertBST(TreeNode* root) {
  TreeNode* cur = root;
  TreeNode* pre = new TreeNode(0);
  stack<TreeNode*> stk;
  while (!stk.empty() || cur) {
    if (cur) {
      stk.push(cur);
      cur = cur->right;
    } else {
      cur = stk.top();
      stk.pop();
      cur->val += pre->val;
      pre = cur;
      cur = cur->left;
    }
  }
  return root;
}

// 右中左，反中序遍历，利用pre来记录前值
int pre = 0;
void traversal1(TreeNode* root) {
  if (root == nullptr)
    return;
  traversal1(root->right);
  root->val += pre;
  pre = root->val;
  traversal1(root->left);
}
TreeNode* convertBST1(TreeNode* root) {
  pre = 0;
  traversal1(root);
  return root;
}

// 迭代法。反中序，右中左
TreeNode* convertBST2(TreeNode* root) {
  if (!root)
    return root;
  stack<TreeNode*> st;
  TreeNode* cur = root;
  int pre = 0;
  while (!st.empty() || cur) {
    if (cur) {
      st.push(cur);
      cur = cur->right;
    } else {
      cur = st.top();
      st.pop();
      cur->val += pre;
      pre = cur->val;
      cur = cur->left;
    }
  }
  return root;
}

int main() {
  vector<int> vec1 = {4,    1,    6, 0,    2,    5,    7, null,
                      null, null, 3, null, null, null, 8};
  vector<int> vec2 = {0, null, 1};
  vector<int> vec3 = {1, 0, 2};
  vector<int> vec4 = {3, 2, 4, 1};
  TreeNode* node1 = construct_binary_tree(vec1);
  TreeNode* node2 = construct_binary_tree(vec2);
  TreeNode* node3 = construct_binary_tree(vec3);
  TreeNode* node4 = construct_binary_tree(vec4);
  print_binary_tree(convertBST(node1));
  print_binary_tree(convertBST(node2));
  print_binary_tree(convertBST(node3));
  print_binary_tree(convertBST(node4));
  node1 = construct_binary_tree(vec1);
  node2 = construct_binary_tree(vec2);
  node3 = construct_binary_tree(vec3);
  node4 = construct_binary_tree(vec4);
  print_binary_tree(convertBST1(node1));
  print_binary_tree(convertBST1(node2));
  print_binary_tree(convertBST1(node3));
  print_binary_tree(convertBST1(node4));
  return 0;
}
