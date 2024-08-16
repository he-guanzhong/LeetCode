#include "head.h"
/* 114. 二叉树展开为链表
给你二叉树的根结点 root ，请你将它展开为一个单链表：
    展开后的单链表应该同样使用 TreeNode ，其中 right
子指针指向链表中下一个结点，而左子指针始终为 null 。 展开后的单链表应该与二叉树
先序遍历 顺序相同。
示例 1：
  输入：root = [1,2,5,3,4,null,6]
  输出：[1,null,2,null,3,null,4,null,5,null,6]
示例 2：
  输入：root = []
  输出：[]
示例 3：
  输入：root = [0]
  输出：[0] */

// 自制。递归法中序遍历
void flatten(TreeNode* root) {
  if (!root || !root->left && !root->right)
    return;
  flatten(root->left);
  if (root->left) {
    TreeNode* tmp = root->left;
    while (tmp->right)
      tmp = tmp->right;
    tmp->right = root->right;
    root->right = root->left;
    root->left = nullptr;
  }
  flatten(root->right);
}

// 易错点，第一不能直接在root上操作，要使用单独的cur，第二，每次右子树接到左子树的最右节点，并转移左子树之后，cur->left要置空
// 前序遍历+展开同步，只有迭代法才能实时保存右结点信息，不得使用递归法。设立pre前驱结点。时间、空间复杂度均为O(n)
// 只有pre存在时（即非第一次），才将pre右孩子指向cur，注意pre左孩子也要同步置nullptr。不必对最后一个结点左右孩子特殊置nullptr，因为中左右前序遍历，最后一个肯定叶子结点
void flatten2(TreeNode* root) {
  stack<TreeNode*> st;
  if (!root)
    return;
  st.push(root);
  TreeNode* pre = nullptr;
  while (!st.empty()) {
    TreeNode* cur = st.top();
    st.pop();
    if (pre) {
      pre->right = cur;
      pre->left = nullptr;
    }
    pre = cur;
    if (cur->right)
      st.push(cur->right);
    if (cur->left)
      st.push(cur->left);
  }
}

// 推荐做法，设置前驱结点。若当前结点有左结点。1.保存左孩子为下一结点next。2.找到左子树的最右叶子结点，其为右子树的前驱结点predecessor
// 3.当前结点右子树续接到前驱结点predecessor之右。4.当前结点cur左孩子置空，右孩子接入原左子树next。
// 当前结点不断右移，直至终止，时间复杂度O(n)，空间复杂度O(1)
void flatten1(TreeNode* root) {
  TreeNode* cur = root;
  while (cur) {
    if (cur->left) {
      TreeNode* next = cur->left;
      TreeNode* predecessor = next;
      while (predecessor->right)
        predecessor = predecessor->right;
      predecessor->right = cur->right;
      cur->left = nullptr;
      cur->right = next;
    }
    cur = cur->right;
  }
}
int main() {
  TreeNode* t1 = construct_binary_tree({1, 2, 5, 3, 4, null, 6});
  TreeNode* t2 = construct_binary_tree({});
  TreeNode* t3 = construct_binary_tree({0});
  flatten(t1);
  flatten(t2);
  flatten(t3);
  print_binary_tree(t1);
  print_binary_tree(t2);
  print_binary_tree(t3);
  t1 = construct_binary_tree({1, 2, 5, 3, 4, null, 6});
  t2 = construct_binary_tree({});
  t3 = construct_binary_tree({0});
  flatten1(t1);
  flatten1(t2);
  flatten1(t3);
  print_binary_tree(t1);
  print_binary_tree(t2);
  print_binary_tree(t3);
  return 0;
}