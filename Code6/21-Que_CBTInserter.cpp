#include "head.h"

/* 919. 完全二叉树插入器
完全二叉树
是每一层（除最后一层外）都是完全填充（即，节点数达到最大）的，并且所有的节点都尽可能地集中在左侧。
设计一种算法，将一个新节点插入到一棵完全二叉树中，并在插入后保持其完整。
实现 CBTInserter1类:
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
    CBTInserter1cBTInserter = new CBTInserter([1, 2]);
    cBTInserter.insert(3);  // 返回 1
    cBTInserter.insert(4);  // 返回 2
    cBTInserter.get_root(); // 返回 [1, 2, 3, 4]
提示：
    树中节点数量范围为 [1, 1000]
    0 <= Node.val <= 5000
    root 是完全二叉树
    0 <= val <= 5000
    每个测试用例最多调用 insert 和 get_root 操作 104 次 */

// 二进制做法。输入已经是满二叉树，每一行起始元素均为2的幂次，2^(i-1)，1/2/4/8...
// 首先使用BFS遍历，得到树结点总数量。记录即将插入新元素序号n，其最高位1后，有多少个0
// 32位有符号整数，前导零函数__builtin_clz(),leading。后导零__builtin_ctz(),tailing
// 例如，(8)1000，最高位1后是3个0，计算方式是highBit=31-builtin_clz()。
// 将n分别对(1<<i)按位与，移位从highBit-1开始，最少移位1次，按位与为1是，结点右移，否则，结点左移
// 最终查看n&1结果，此时结果为1，则结点cur右孩子即为新序号位置，否则cur左孩子为新序号位置。
class CBTInserter {
 public:
  CBTInserter(TreeNode* root) {
    this->root = root;
    this->cnt = 0;
    queue<TreeNode*> que;
    if (root)
      que.push(root);
    while (!que.empty()) {
      TreeNode* cur = que.front();
      que.pop();
      cnt++;
      if (cur->left)
        que.push(cur->left);
      if (cur->right)
        que.push(cur->right);
    }
  }

  int insert(int v) {
    TreeNode* node = new TreeNode(v);
    cnt++;
    TreeNode* cur = root;
    // 定位到最高位1之后，还有几个数字，例如01001，则还有001三个数字（n）
    // 挪动次数为 n-1次。
    int highBit = 31 - __builtin_clz(cnt);
    for (int i = highBit - 1; i >= 1; i--) {
      if (cnt & (1 << i)) {
        cur = cur->right;
      } else {
        cur = cur->left;
      }
    }
    if (cnt & 1)
      cur->right = node;
    else
      cur->left = node;
    return cur->val;
  }

  TreeNode* get_root() { return this->root; }

 private:
  int cnt;
  TreeNode* root;
};

// 传统做法，使用BFS或DFS遍历全树，额外一个candidate队列保存所有可以插入的结点
class CBTInserter1 {
 public:
  CBTInserter1(TreeNode* root) {
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