#include "head.h"
/* LCR 053. 二叉搜索树中的中序后继
给定一棵二叉搜索树和其中的一个节点 p
，找到该节点在树中的中序后继。如果节点没有中序后继，请返回 null 。
节点 p 的后继是值比 p.val 大的节点中键值最小的节点，即按中序遍历的顺序节点 p
的下一个节点。
示例 1：
  输入：root = [2,1,3], p = 1
  输出：2
  解释：这里 1 的中序后继是 2。请注意 p 和返回值都应是 TreeNode 类型。
示例 2：
  输入：root = [5,3,6,2,4,null,null,1], p = 6
  输出：null
解释：因为给出的节点没有中序后继，所以答案就返回 null 了。
提示：
  树中节点的数目在范围 [1, 104] 内。
  -105 <= Node.val <= 105
  树中各节点的值均保证唯一。 */

TreeNode* inorderSuccessor(TreeNode* root, TreeNode* p) {
  TreeNode *cur = root, *pre = nullptr;
  stack<TreeNode*> st;
  while (cur || !st.empty()) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      if (pre == p)
        return cur;
      pre = cur;
      cur = cur->right;
    }
  }
  return nullptr;
}

// 利用二叉搜索树性质。初始化后继节点为空。若p有右子树，其中序后继一定在右子树内。找到右子树中最靠左的节点，即为中序后继
// 若无右子树，须从根节点寻找，设定临时节点node，node值若大于p值，说明其符合答案要求，先记下，其左子树内可能还有更小的，想左一布
// 反之，node值小于等于p值，不符合要求，需要在右子树中找更大的值。直至若比任何节点都大，其后继节点从未被更新过，直接返回空
TreeNode* inorderSuccessor1(TreeNode* root, TreeNode* p) {
  TreeNode* successor = nullptr;
  if (p->right) {
    successor = p->right;
    while (successor->left)
      successor = successor->left;
    return successor;
  }
  TreeNode* node = root;
  while (node) {
    if (node->val > p->val) {
      successor = node;
      node = node->left;
    } else {
      node = node->right;
    }
  }
  return successor;
}

// 中序遍历，时间复杂度和空间复杂度均为O(n)
TreeNode* inorderSuccessor2(TreeNode* root, TreeNode* p) {
  TreeNode *cur = root, *pre = nullptr;
  stack<TreeNode*> st;
  while (cur || !st.empty()) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      if (pre == p)
        return cur;
      pre = cur;
      cur = cur->right;
    }
  }
  return nullptr;
}

int main() {
  TreeNode* t1 = construct_binary_tree({2, 1, 3});
  TreeNode* t2 = construct_binary_tree({5, 3, 6, 2, 4, null, null, 1});
  print_binary_tree(inorderSuccessor(t1, t1->left));
  print_binary_tree(inorderSuccessor(t2, t2->right));
  cout << endl;
  print_binary_tree(inorderSuccessor1(t1, t1->left));
  print_binary_tree(inorderSuccessor1(t2, t2->right));
  return 0;
}
