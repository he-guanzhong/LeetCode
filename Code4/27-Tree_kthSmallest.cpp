#include "head.h"
/* 230. 二叉搜索树中第K小的元素
给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k
个最小元素（从 1 开始计数）。
示例 1：
  输入：root = [3,1,4,null,2], k = 1
  输出：1
示例 2：
  输入：root = [5,3,6,2,4,null,null,1], k = 3
  输出：3
进阶：如果二叉搜索树经常被修改（插入/删除操作）并且你需要频繁地查找第 k
  小的值，你将如何优化算法？*/

int kthSmallest(TreeNode* root, int k) {
  TreeNode* cur = root;
  stack<TreeNode*> st;
  while (st.size() || cur) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      if (--k == 0)
        break;
      cur = cur->right;
    }
  }
  return cur->val;
}

// 二叉搜索树性质，中序遍历，使用迭代法可不遍历整棵树。处理结点方式为k--，一旦k==0即停止，不必向右转移。此时cur即指向第k个最小元素
int kthSmallest1(TreeNode* root, int k) {
  stack<TreeNode*> st;
  TreeNode* cur = root;
  while (!st.empty() || cur) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      k--;
      if (k == 0)
        break;
      cur = cur->right;
    }
  }
  return cur->val;
}

// 统计每一个结点，以此为根的结点数。单独设立一个类，内含哈希表，统计每一个结点及其下属数量。private两个函数，一是统计数量，二是反馈哈希表值
// public两个函数，一是构造确定根结点，统计数量填充哈希表。二是反馈第k小的结点值。逻辑为，看当前node->left数量，若left<k+1说明结点在右子树，node右移，并更新k
// 若left>k+1说明在左子树，node左移，若二者相等。则break，即为该结点值。
class MyBst {
 public:
  MyBst(TreeNode* root) {
    this->root = root;
    calNodeNum(root);
  }
  int kthSmallest(int k) {
    TreeNode* node = root;
    while (node) {
      int left = getNodeNum(node->left);
      if (left > k - 1) {
        node = node->left;
      } else if (left < k - 1) {
        node = node->right;
        k -= left + 1;  // + -第四优先级，+=第十四优先级，不加括号
      } else
        break;
    }
    return node->val;
  }

 private:
  TreeNode* root;
  unordered_map<TreeNode*, int> nodeNum;
  int calNodeNum(TreeNode* root) {
    if (!root)
      return 0;
    nodeNum[root] = calNodeNum(root->left) + calNodeNum(root->right) + 1;
    return nodeNum[root];
  }
  int getNodeNum(TreeNode* root) {
    if (root)
      return nodeNum[root];
    else
      return 0;
  }
};
int kthSmallest2(TreeNode* root, int k) {
  MyBst myBst(root);
  return myBst.kthSmallest(k);
}

int main() {
  TreeNode* t1 = construct_binary_tree({3, 1, 4, null, 2});
  TreeNode* t2 = construct_binary_tree({5, 3, 6, 2, 4, null, null, 1});
  TreeNode* t3 = construct_binary_tree({1});
  cout << kthSmallest(t1, 1) << " " << kthSmallest(t2, 3) << endl;
  cout << kthSmallest1(t1, 1) << " " << kthSmallest1(t2, 3) << endl;

  return 0;
}