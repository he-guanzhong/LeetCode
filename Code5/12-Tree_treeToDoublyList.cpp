#include "head.h"
/* LCR 155. 将二叉搜索树转化为排序的双向链表
将一个 二叉搜索树 就地转化为一个 已排序的双向循环链表 。
对于双向循环列表，你可以将左右孩子指针作为双向循环链表的前驱和后继指针，第一个节点的前驱是最后一个节点，最后一个节点的后继是第一个节点。
特别地，我们希望可以 就地
完成转换操作。当转化完成以后，树中节点的左指针需要指向前驱，树中节点的右指针需要指向后继。还需要返回链表中最小元素的指针。
示例 1：
输入：root = [4,2,5,1,3]
输出：[1,2,3,4,5]
解释：下图显示了转化后的二叉搜索树，实线表示后继关系，虚线表示前驱关系。
示例 2：
输入：root = [2,1,3]
输出：[1,2,3]
示例 3：
输入：root = []
输出：[]
解释：输入是空树，所以输出也是空链表。
示例 4：
输入：root = [1]
输出：[1] */

// 中序遍历，迭代法
Node1* treeToDoublyList(Node1* root) {
  if (!root)
    return root;
  Node1* cur = root;
  Node1 *pre = nullptr, *head = nullptr;
  stack<Node1*> st;
  while (!st.empty() || cur) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      if (!pre) {
        head = cur;
      } else {
        pre->right = cur;
        cur->left = pre;
      }
      pre = cur;
      cur = cur->right;
    }
  }
  head->left = pre;
  pre->right = head;
  return head;
}

// 中序遍历，递归法，保证二叉搜索树从小到大有序。入参为当前结点，无返回值。遇到空结点直接返回
// 双向链表，需要在当前结点cur基础上，额外保存pre。处理节点时要对两结点相互勾连。最后更新pre为当前cur
// 循环链表。需要额外保存head，当pre==nullptr，即首次遍历到根节点时，对head赋值。全部dfs结束后，tail即pre位置，头尾相互勾连
Node1 *head1, *pre1;
void dfs(Node1* root) {
  if (!root)
    return;
  dfs(root->left);
  if (!pre1)
    head1 = root;
  else {
    root->left = pre1;
    pre1->right = root;
  }
  pre1 = root;
  dfs(root->right);
}
Node1* treeToDoublyList1(Node1* root) {
  if (!root)
    return nullptr;
  head1 = pre1 = nullptr;
  dfs(root);
  head1->left = pre1;
  pre1->right = head1;
  return head1;
}

void printNode(Node1* root) {
  if (!root)
    return;
  Node1* start = root;
  do {
    cout << root->val << " ";
    root = root->right;
  } while (root != start);
  cout << endl;
}
int main() {
  Node1* root = new Node1(4);
  root->left = new Node1(2);
  root->right = new Node1(5);
  root->left->left = new Node1(1);
  root->left->right = new Node1(3);
  printNode(treeToDoublyList(root));
  Node1* root1 = new Node1(4);
  root1->left = new Node1(2);
  root1->right = new Node1(5);
  root1->left->left = new Node1(1);
  root1->left->right = new Node1(3);
  printNode(treeToDoublyList1(root1));
  return 0;
}