#include "head.h"

/* 919. 完全二叉树插入器
完全二叉树
是每一层（除最后一层外）都是完全填充（即，节点数达到最大）的，并且所有的节点都尽可能地集中在左侧。
设计一种算法，将一个新节点插入到一棵完全二叉树中，并在插入后保持其完整。
实现 CBTInserter 类:
    CBTInserter(TreeNode root) 使用头节点为 root 的给定树初始化该数据结构；
    CBTInserter.insert(int v)  向树中插入一个值为 Node.val == val的新节点
TreeNode。使树保持完全二叉树的状态，并返回插入节点 TreeNode 的父节点的值；
    CBTInserter.get_root() 将返回树的头节点。
示例 1：
  输入
    ["CBTInserter", "insert", "insert", "get_root"]
    [[[1, 2]], [3], [4], []]
  输出
    [null, 1, 2, [1, 2, 3, 4]]
  解释
    CBTInserter cBTInserter = new CBTInserter([1, 2]);
    cBTInserter.insert(3);  // 返回 1
    cBTInserter.insert(4);  // 返回 2
    cBTInserter.get_root(); // 返回 [1, 2, 3, 4]
提示：
    树中节点数量范围为 [1, 1000]
    0 <= Node.val <= 5000
    root 是完全二叉树
    0 <= val <= 5000
    每个测试用例最多调用 insert 和 get_root 操作 104 次 */

class CBTInserter {
 public:
  CBTInserter(TreeNode* root) {
    this->root = root;
    queue<TreeNode*> que;
    if (root)
      que.push(root);
    while (!que.empty()) {
      TreeNode* cur = que.front();
      que.pop();
      if (cur->left)
        que.push(cur->left);
      if (cur->right)
        que.push(cur->right);
      if (!cur->left || !cur->right)
        candidates.push(cur);
    }
  }

  int insert(int val) {
    TreeNode* cur = candidates.front();
    TreeNode* node = new TreeNode(val);
    if (!cur->left) {
      cur->left = node;
    } else {
      cur->right = node;
      candidates.pop();
    }
    candidates.push(node);
    return cur->val;
  }

  TreeNode* get_root() { return root; }

 private:
  TreeNode* root;
  queue<TreeNode*> candidates;
};

int main() {
  TreeNode* root = new TreeNode(1);
  root->left = new TreeNode(2);
  CBTInserter* cBTInserter = new CBTInserter(root);
  cout << cBTInserter->insert(3) << " " << cBTInserter->insert(4) << endl;
  print_binary_tree(cBTInserter->get_root());
  return 0;
}