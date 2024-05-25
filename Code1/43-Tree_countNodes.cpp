#include "head.h"
/* 222. 完全二叉树的节点个数
给你一棵 完全二叉树 的根节点 root
，求出该树的节点个数。完全二叉树的定义如下：在完全二叉树中，除了最底层节点可能没填满外，
其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。若最底层为第
h 层，则该层包含 1~ 2h 个节点。
示例 1：
输入：root = [1,2,3,4,5,6]
输出：6
示例 2：
输入：root = []
输出：0
示例 3：
输入：root = [1]
输出：1 */

int countNodes(TreeNode* root) {
  if (!root)
    return 0;
  int l = 0, r = 0;
  TreeNode* cur = root;
  while (cur) {
    cur = cur->left;
    l++;
  }
  cur = root;
  while (cur) {
    r++;
    cur = cur->right;
  }
  if (l == r)
    return pow(2, l) - 1;
  return countNodes(root->left) + countNodes(root->right) + 1;
}

// 考虑完全二叉树特殊性质，不是通过层数求满二叉树结点数量，再减去缺失结点数。而是完全二叉树可以分为若干个满二叉树，只有一个叶子节点也算满二叉树。
// 满二叉树判断条件是，左、右边深度相等。先创立临时左、右结点，求左右边长，深度可以作为层数-1
// 满二叉树层数n，总结点数为2^n-1。乘方可以位运算代替，x<<y意为x*(2^y)。注意加减法优先级为6，左右移优先级为7，故想先左右移，一定要加括号
// 若为普通二叉树，可以后序遍历递归，或层序遍历，时间复杂度和空间复杂度均为n。
int countNodes5(TreeNode* root) {
  if (!root)
    return 0;
  int leftDepth = 0, rightDepth = 0;
  TreeNode* left = root;
  TreeNode* right = root;
  while (left) {
    left = left->left;
    leftDepth++;
  }
  while (right) {
    right = right->right;
    rightDepth++;
  }
  if (leftDepth == rightDepth)
    return (1 << (leftDepth)) - 1;
  return countNodes(root->left) + countNodes(root->right) + 1;
}

// 优选利用完全二叉树的性质，递归处理，时间复杂度log(n)*log(n)最低。次选普通二叉树递归
// 按照普通二叉树处理，可以层序遍历，也可以递归
int countNodes1(TreeNode* root) {
  if (!root)
    return 0;
  return countNodes1(root->left) + countNodes1(root->right) + 1;
}
// 时间复杂度：O(n)。空间复杂度：O(log n)，算上了递归系统栈占用的空间
int getNodesSum(TreeNode* root) {
  if (!root)
    return 0;
  int leftNum = getNodesSum(root->left);
  int rightNum = getNodesSum(root->right);
  int treeNum = leftNum + rightNum;
  return treeNum + 1;
}
int countNodes_std(TreeNode* root) {
  return getNodesSum(root);
}

// 普通二叉树，层序遍历，时间复杂度O(n)，空间复杂度O(n)
int countNodes2(TreeNode* root) {
  if (!root)
    return 0;
  queue<TreeNode*> que;
  que.push(root);
  int result = 0;
  while (!que.empty()) {
    int size = que.size();
    while (size--) {
      TreeNode* node = que.front();
      que.pop();
      result++;
      if (node->left)
        que.push(node->left);
      if (node->right)
        que.push(node->right);
    }
  }
  return result;
}

// 完全二叉树的性质，满二叉树结点数为2^n-1，完全二叉树根据左右结点递归深度计算，若相等为满二叉树，若不等，则继续递归
// 时间复杂度O(log(n)* log(n)), 空间复杂度O(log(n)）
int countNodes3(TreeNode* root) {
  if (root == nullptr)
    return 0;
  int leftDepth = 0, rightDepth = 0;  // 定义为0而不是1，是为了下方计算2^n方便
  TreeNode* left =
      root->left;  // 一定要先创立临时左右结点，而且设定为root下一层
  TreeNode* right = root->right;
  while (left) {
    leftDepth++;
    left = left->left;
  }
  while (right) {
    rightDepth++;
    right = right->right;
  }
  if (leftDepth == rightDepth)  // leftDepth代表了实际层数-1
    return (2 << leftDepth) - 1;  // 位运算替代乘方 pow(2, leftDepth + 1) - 1
  // 也可以1<< (leftDepth+1) - 1
  /*   int leftNum = countNodes(root->left);
    int rightNum = countNodes(root->right);
    return leftNum + rightNum + 1; */
  return countNodes3(root->left) + countNodes3(root->right) + 1;
}

int main() {
  vector<int> vec1 = {1, 2, 3, 4, 3, 2};
  vector<int> vec2 = {1};
  vector<int> vec3 = {};

  TreeNode* root1 = sortedArray2BST(vec1);
  TreeNode* root2 = sortedArray2BST(vec2);
  TreeNode* root3 = sortedArray2BST(vec3);
  cout << countNodes(root1) << " " << countNodes(root2) << " "
       << countNodes(root3) << endl;
  cout << countNodes3(root1) << " " << countNodes3(root2) << " "
       << countNodes3(root3) << endl;
  return 0;
}