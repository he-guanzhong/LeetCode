#include "head.h"
/* 897. 递增顺序搜索树
给你一棵二叉搜索树的 root ，请你 按中序遍历
将其重新排列为一棵递增顺序搜索树，使树中最左边的节点成为树的根节点，并且每个节点没有左子节点，只有一个右子节点。
示例 1：
  输入：root = [5,3,6,2,4,null,8,1,null,null,null,7,9]
  输出：[1,null,2,null,3,null,4,null,5,null,6,null,7,null,8,null,9]
示例 2：
  输入：root = [5,1,7]
  输出：[1,null,5,null,7]
提示：
  树中节点数的取值范围是 [1, 100]
  0 <= Node.val <= 1000 */

TreeNode* increasingBST(TreeNode* root) {
  TreeNode *cur = root, *pre = nullptr, *newHead = nullptr;
  stack<TreeNode*> st;
  while (cur || !st.empty()) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      if (!pre)
        newHead = cur;
      else
        pre->right = cur;
      cur->left = nullptr;
      pre = cur;
      cur = cur->right;
    }
  }
  return newHead;
}

// 迭代法中序遍历。pre保存前一节点。注意，最后cur为空，而pre停在最后一个节点。其左指针必须再次人工指向空
// 由于中序遍历，cur的左子树必然已经访问过了，甚至是直接就是pre结点。
// 因此必须cur的同一层级，即刻将cur->left置空。而不是在pre的时候再pre->left置空
TreeNode* increasingBST1(TreeNode* root) {
  TreeNode* cur = root;
  stack<TreeNode*> st;
  TreeNode* pre = nullptr;
  while (cur || !st.empty()) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      if (pre) {
        pre->right = cur;
      } else {
        root = cur;
      }
      cur->left = nullptr;  // 关键，一定要置空
      pre = cur;
      cur = cur->right;
    }
  }
  return root;
}

// 递归法。使用虚拟头结点。注意先pre与root链接，之后root左指针要及时置空
TreeNode* pre = nullptr;
void inorder2(TreeNode* root) {
  if (!root)
    return;
  inorder2(root->left);
  pre->right = root;     // 先连接
  root->left = nullptr;  // 左子树已无用，必须置空
  pre = root;
  inorder2(root->right);
}
TreeNode* increasingBST2(TreeNode* root) {
  TreeNode* dummy = new TreeNode(-1);
  pre = dummy;
  inorder2(root);
  return dummy->right;
}

int main() {
  TreeNode* t1 = construct_binary_tree(
      {5, 3, 6, 2, 4, null, 8, 1, null, null, null, 7, 9});
  TreeNode* t2 = construct_binary_tree({5, 1, 7});
  TreeNode* t3 = construct_binary_tree({2, 1, 4, null, null, 3});
  print_binary_tree(increasingBST(t1));
  print_binary_tree(increasingBST(t2));
  print_binary_tree(increasingBST(t3));
  t1 = construct_binary_tree(
      {5, 3, 6, 2, 4, null, 8, 1, null, null, null, 7, 9});
  t2 = construct_binary_tree({5, 1, 7});
  t3 = construct_binary_tree({2, 1, 4, null, null, 3});
  print_binary_tree(increasingBST1(t1));
  print_binary_tree(increasingBST1(t2));
  print_binary_tree(increasingBST1(t3));
  return 0;
}
