#include "head.h"
/* 559. N 叉树的最大深度
给定一个 N 叉树，找到其最大深度。
最大深度是指从根节点到最远叶子节点的最长路径上的节点总数。
N 叉树输入按层序遍历序列化表示，每组子节点由空值分隔（请参见示例）。
输入：root = [1,null,3,2,4,null,5,6]
输出：3
输入：root =
[1,null,2,3,4,5,null,null,6,7,null,8,null,9,10,null,null,11,null,12,null,13,null,null,14]
输出：5
 */
// N叉树，关键在于原来左右分别处理，转换为一个for循环，不断比较每个孩子的最大高度。返回值+1为本层高度
// 可以使用后序遍历递归，或者层序遍历的方法。
class Node {
 public:
  int val;
  vector<Node*> children;
  Node() {}
  Node(int _val) { val = _val; }
  Node(int _val, vector<Node*> _children) {
    val = _val;
    children = _children;
  }
};

int maxDepth(Node* root) {
  queue<Node*> que;
  if (root)
    que.push(root);
  int depth = 0;
  while (!que.empty()) {
    int size = que.size();
    depth++;
    while (size--) {
      Node* cur = que.front();
      que.pop();
      for (Node* node : cur->children)
        que.push(node);
    }
  }
  return depth;
}

int maxDepth1(Node* root) {
  if (!root)
    return 0;
  int depth = 0;
  for (int i = 0; i < root->children.size(); i++)
    depth = max(depth, maxDepth(root->children[i]));
  return depth + 1;  // 注意，加一是在回溯的时候，而不是计算的时候
}
int maxDepth2(Node* root) {
  if (!root)
    return 0;
  queue<Node*> que;
  que.push(root);
  int depth = 0;
  while (!que.empty()) {
    depth++;
    int size = que.size();
    while (size--) {
      Node* node = que.front();
      que.pop();
      for (int i = 0; i < node->children.size(); i++) {
        if (node->children[i])
          que.push(node->children[i]);
      }
    }
  }
  return depth;
}