#include "head.h"
/* 116. 填充每个节点的下一个右侧节点指针
给定一个 完美二叉树
，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：
struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
填充它的每个next指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将
next 指针设置为 NULL。 初始状态下，所有 next 指针都被设置为 NULL。
示例 1：
  输入：root = [1,2,3,4,5,6,7]
  输出：[1,#,2,3,#,4,5,6,7,#]
  解释：给定二叉树如图 A 所示，你的函数应该填充它的每个 next
    指针，以指向其下一个右侧节点，如图 B
    所示。序列化的输出按层序遍历排列，同一层节点由 next 指针连接，'#'
    标志着每一层的结束。
示例 2:
  输入：root = []
  输出：[]
提示：
    树中节点的数量在 [0, 212 - 1] 范围内
    -1000 <= node.val <= 1000
进阶：
    你只能使用常量级额外空间。
    使用递归解题也符合要求，本题中递归程序占用的栈空间不算做额外的空间复杂度。*/
struct Node {
  int val;
  Node *left, *right, *next;
};

// 本题要求常量级空间，只能使用递归法，关键是前序遍历，利用上一层节点以做好的next搭桥
// 若有左孩子，则左孩子next直接指右孩子。若有右孩子，看当前next是否有值，有则使cur->right的next指向和cur->next->left。没有则说明已为最右节点，next赋空
// 空间复杂度O(1)，因为不算递归程序占用栈空间
void traversal(Node* root) {
  if (!root)
    return;
  if (root->left) {
    root->left->next = root->right;
  }
  if (root->right) {
    if (root->next)
      root->right->next = root->next->left;
    else
      root->right->next = nullptr;
  }
  traversal(root->left);
  traversal(root->right);
}
Node* connect(Node* root) {
  traversal(root);
  return root;
}

// 常规层序遍历，保证该层n个节点，前n-1节点next指向下一个
Node* connect2(Node* root) {
  queue<Node*> que;
  if (root)
    que.push(root);
  while (que.size()) {
    int n = que.size();
    while (n--) {
      Node* cur = que.front();
      que.pop();
      if (n)  //  注意这里不能写que.size()，因为其一直不为空
        cur->next = que.front();
      if (cur->left)
        que.push(cur->left);
      if (cur->right)
        que.push(cur->right);
    }
  }
  return root;
}

int main() {
  return 0;
}