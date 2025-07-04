#include "head.h"

/* 653. 两数之和 IV - 输入二叉搜索树
给定一个二叉搜索树 root 和一个目标结果
k，如果二叉搜索树中存在两个元素且它们的和等于给定的目标结果，则返回 true。
示例 1：
  输入: root = [5,3,6,2,4,null,7], k = 9
  输出: true
示例 2：
  输入: root = [5,3,6,2,4,null,7], k = 28
  输出: false
提示:
    二叉树的节点个数的范围是  [1, 104].
    -104 <= Node.val <= 104
    题目数据保证，输入的 root 是一棵 有效 的二叉搜索树
    -105 <= k <= 105 */

TreeNode* getNextLeft(stack<TreeNode*>& st, TreeNode* cur, int& val) {
  while (cur) {
    st.push(cur);
    cur = cur->left;
  }
  cur = st.top();
  val = cur->val;
  st.pop();
  return cur->right;
}
TreeNode* getNextRight(stack<TreeNode*>& st, TreeNode* cur, int& val) {
  while (cur) {
    st.push(cur);
    cur = cur->right;
  }
  cur = st.top();
  val = cur->val;
  st.pop();
  return cur->left;
}
bool findTarget(TreeNode* root, int k) {
  stack<TreeNode*> leftSt, rightSt;
  int val1 = 0, val2 = 0;
  TreeNode* l = getNextLeft(leftSt, root, val1);
  TreeNode* r = getNextRight(rightSt, root, val2);

  while (val1 < val2) {
    int sum = val1 + val2;
    if (sum == k)
      return true;
    else if (sum < k) {
      l = getNextLeft(leftSt, l, val1);
    } else {
      r = getNextRight(rightSt, r, val2);
    }
  }
  return false;
}

// 双指针法在二叉搜索树中的应用。左、右指针分别建立两个栈。指针左移、右移分别设置独立函数。
// 取元素是从栈顶取，然后当前结点node左移，或右移
TreeNode* getNextLeft1(stack<TreeNode*>& st) {
  TreeNode* cur = st.top();
  st.pop();
  TreeNode* node = cur->right;
  while (node) {
    st.push(node);
    node = node->left;
  }
  return cur;
}
TreeNode* getNextRight1(stack<TreeNode*>& st) {
  TreeNode* cur = st.top();
  st.pop();
  TreeNode* node = cur->left;
  while (node) {
    st.push(node);
    node = node->right;
  }
  return cur;
}
bool findTarget1(TreeNode* root, int k) {
  TreeNode *nodeLeft = root, *nodeRight = root;
  stack<TreeNode*> stLeft, stRight;
  stLeft.push(nodeLeft);
  while (nodeLeft->left) {
    stLeft.push(nodeLeft->left);
    nodeLeft = nodeLeft->left;
  }
  stRight.push(nodeRight);
  while (nodeRight->right) {
    stRight.push(nodeRight->right);
    nodeRight = nodeRight->right;
  }
  while (nodeLeft != nodeRight) {
    int sum = nodeLeft->val + nodeRight->val;
    if (sum == k)
      return true;
    else if (sum < k)
      nodeLeft = getNextLeft1(stLeft);
    else
      nodeRight = getNextRight1(stRight);
  }
  return false;
}

bool findTarget2(TreeNode* root, int k) {
  unordered_set<int> uset;
  TreeNode* cur = root;
  stack<TreeNode*> st;
  while (cur || !st.empty()) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      if (uset.count(k - cur->val))
        return true;
      uset.insert(cur->val);
      cur = cur->right;
    }
  }
  return false;
}

int main() {
  TreeNode* t1 = construct_binary_tree({5, 3, 6, 2, 4, null, 7});
  TreeNode* t2 = construct_binary_tree({0, -3, 2, -4, null, 1});
  cout << findTarget(t1, 9) << " " << findTarget(t1, 28) << " "
       << findTarget(t2, 1) << endl;
  cout << findTarget1(t1, 9) << " " << findTarget1(t1, 28) << " "
       << findTarget1(t2, 1) << endl;
  return 0;
}