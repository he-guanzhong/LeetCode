#include "head.h"
#define null -1
/* 617. 合并二叉树
给你两棵二叉树： root1 和 root2 。
想象一下，当你将其中一棵覆盖到另一棵之上时，两棵树上的一些节点将会重叠（而另一些不会）。
你需要将这两棵树合并成一棵新二叉树。合并的规则是：如果两个节点重叠，那么将这两个节点的值相加作为合并后节点的新值；否则，不为
null 的节点将直接作为新二叉树的节点。返回合并后的二叉树。
示例 1：
输入：root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
输出：[3,4,5,5,4,null,7]
注意: 合并过程必须从两个树的根节点开始。*/

// 递归法。无需判断二者均为空的情况，二者任一为空则返回另一。直接在t1上操作，省去新树操作，前中后序遍历均可
// 迭代法。预处理，保证压入结点必不为空。最好使用层序遍历queue，如果用stack注意先弹出的是root2问题。
// 一定只有在两个结点的左、右孩子都有值才压入，不得将空结点入队列，否则失去指向。如果node1左右无值，则将node2的左右孩子赋值过来。
TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2) {
  if (!root1)
    return root2;
  else if (!root2)
    return root1;
  stack<TreeNode*> stk;
  stk.push(root1);
  stk.push(root2);
  while (!stk.empty()) {
    TreeNode* node2 = stk.top();
    stk.pop();
    TreeNode* node1 = stk.top();
    stk.pop();
    node1->val += node2->val;
    if (node1->left && node2->left) {
      stk.push(node1->left);
      stk.push(node2->left);
    }
    if (node1->right && node2->right) {
      stk.push(node1->right);
      stk.push(node2->right);
    }
    if (!node1->left && node2->left)
      node1->left = node2->left;
    if (!node1->right && node2->right)
      node1->right = node2->right;
  }
  return root1;
}

// 递归，注意退出条件，不必判断二者都为空的情况。此外，前中后序遍历顺序均可。可以直接在t1上操作，也可以生成新树。
TreeNode* mergeTrees1(TreeNode* root1, TreeNode* root2) {
  if (!root1)
    return root2;
  if (!root2)
    return root1;
  root1->val += root2->val;
  root1->left = mergeTrees(root1->left, root2->left);
  root1->right = mergeTrees(root1->right, root2->right);
  return root1;
  /*   TreeNode* node = new TreeNode(root1->val + root2->val);
    node->left = mergeTrees(root1->left, root2->left);
    node->right = mergeTrees(root1->right, root2->right);
    return node; */
}

// 迭代法，队列模拟层序遍历，只有非空结点才能入队，以t1为返回结点，t2叠加到t1上
TreeNode* mergeTrees2(TreeNode* root1, TreeNode* root2) {
  if (!root1)
    return root2;
  if (!root2)
    return root1;
  queue<TreeNode*> que;
  que.push(root1);
  que.push(root2);
  while (!que.empty()) {
    TreeNode* node1 = que.front();
    que.pop();
    TreeNode* node2 = que.front();
    que.pop();
    node1->val += node2->val;  // 两节点必不为空，t2叠加到t1上
    if (node1->left && node2->left) {  // 只有结点都存在时，才压入
      que.push(node1->left);
      que.push(node2->left);
    }
    if (node1->right && node2->right) {
      que.push(node1->right);
      que.push(node2->right);
    }
    // t1结点存在且 root2 不存在不用处理
    if (!node1->left && node2->left)  // t2结点存在且t1不存在，t2结点转移到t1内
      node1->left = node2->left;
    if (!node1->right && node2->right)
      node1->right = node2->right;
  }
  return root1;
}

int main() {
  vector<int> vec1 = {1, 3, 2, 5};
  vector<int> vec2 = {2, 1, 3, null, 4, null, 7};
  vector<int> vec3 = {1};
  vector<int> vec4 = {1, 2};
  TreeNode* node1 = construct_binary_tree(vec1);
  TreeNode* node2 = construct_binary_tree(vec2);
  TreeNode* node3 = construct_binary_tree(vec3);
  TreeNode* node4 = construct_binary_tree(vec4);
  print_binary_tree(mergeTrees(node1, node2));
  print_binary_tree(mergeTrees(node3, node4));
  node1 = construct_binary_tree(vec1);
  node3 = construct_binary_tree(vec3);
  print_binary_tree(mergeTrees1(node1, node2));
  print_binary_tree(mergeTrees1(node3, node4));
  return 0;
}
