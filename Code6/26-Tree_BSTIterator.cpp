#include "head.h"

/* 173. 二叉搜索树迭代器
实现一个二叉搜索树迭代器类BSTIterator
，表示一个按中序遍历二叉搜索树（BST）的迭代器： BSTIterator(TreeNode root)
初始化 BSTIterator 类的一个对象。BST 的根节点 root
会作为构造函数的一部分给出。指针应初始化为一个不存在于 BST
中的数字，且该数字小于 BST 中的任何元素。 boolean hasNext()
如果向指针右侧遍历存在数字，则返回 true ；否则返回 false 。 int
next()将指针向右移动，然后返回指针处的数字。 注意，指针初始化为一个不存在于 BST
中的数字，所以对 next() 的首次调用将返回 BST 中的最小元素。
你可以假设 next() 调用总是有效的，也就是说，当调用 next() 时，BST
的中序遍历中至少存在一个下一个数字。
示例：
  输入
    ["BSTIterator", "next", "next", "hasNext", "next", "hasNext", "next",
"hasNext", "next", "hasNext"]
    [[[7, 3, 15, null, null, 9, 20]], [], [], [], [], [], [], [], [], []]
输出
  [null, 3, 7, true, 9, true, 15, true, 20, false]
解释
  BSTIterator bSTIterator = new BSTIterator([7, 3, 15, null, null, 9, 20]);
  bSTIterator->next();    // 返回 3
  bSTIterator->next();    // 返回 7
  bSTIterator->hasNext(); // 返回 True
  bSTIterator->next();    // 返回 9
  bSTIterator->hasNext(); // 返回 True
  bSTIterator->next();    // 返回 15
  bSTIterator->hasNext(); // 返回 True
  bSTIterator->next();    // 返回 20
  bSTIterator->hasNext(); // 返回 False
提示：
  树中节点的数目在范围 [1, 105] 内
  0 <= Node.val <= 106
  最多调用 105 次 hasNext 和 next 操作 */

class BSTIterator {
 public:
  BSTIterator(TreeNode* root) {
    cur = root;
    while (cur) {
      st.push(cur);
      cur = cur->left;
    }
  }

  int next() {
    cur = st.top();
    st.pop();
    int ans = cur->val;
    cur = cur->right;
    while (cur) {
      st.push(cur);
      cur = cur->left;
    }
    return ans;
  }

  bool hasNext() { return cur || !st.empty(); }
  TreeNode* cur;
  stack<TreeNode*> st;
};

// 直接使用栈。仍然利用迭代法中序遍历，成员函数仅保存栈和cur结点。向左遍历所有左孩子入栈，可以不在构造函数中
// 而是next()中，因为题目已经说明，next()调用必有效。故无需保存pre结点。
// 直接再next()函数中序遍历。特殊点在于，每次弹栈代表访问某个结点时，直接要退出循环break。
class BSTIterator1 {
 public:
  BSTIterator1(TreeNode* root) { cur = root; }

  int next() {
    int ans = 0;
    while (cur) {
      st.push(cur);
      cur = cur->left;
    }
    cur = st.top();
    st.pop();
    ans = cur->val;
    cur = cur->right;
    return ans;
  }

  bool hasNext() { return cur || !st.empty(); }

 private:
  TreeNode* cur;
  stack<TreeNode*> st;
};

// 中序遍历保存在数组中，设置下标表示下一个可访问的元素
class BSTIterator2 {
 public:
  BSTIterator2(TreeNode* root) {
    index = 0;
    TreeNode* cur = root;
    stack<TreeNode*> st;
    while (cur || !st.empty()) {
      if (cur) {
        st.push(cur);
        cur = cur->left;
      } else {
        cur = st.top();
        st.pop();
        nums.push_back(cur->val);
        cur = cur->right;
      }
    }
  }

  int next() { return nums[index++]; }

  bool hasNext() { return index < nums.size(); }

 private:
  vector<int> nums;
  int index;
};

int main() {
  TreeNode* t1 = construct_binary_tree({{7, 3, 15, null, null, 9, 20}});
  BSTIterator* bSTIterator = new BSTIterator(t1);
  cout << bSTIterator->next() << " " << bSTIterator->next() << " "
       << bSTIterator->hasNext() << " " << bSTIterator->next() << " "
       << bSTIterator->hasNext() << " " << bSTIterator->next() << " "
       << bSTIterator->hasNext() << " " << bSTIterator->next() << " "
       << bSTIterator->hasNext() << endl;

  BSTIterator1* bSTIterator1 = new BSTIterator1(t1);
  cout << bSTIterator1->next() << " " << bSTIterator1->next() << " "
       << bSTIterator1->hasNext() << " " << bSTIterator1->next() << " "
       << bSTIterator1->hasNext() << " " << bSTIterator1->next() << " "
       << bSTIterator1->hasNext() << " " << bSTIterator1->next() << " "
       << bSTIterator1->hasNext() << endl;
  return 0;
}
