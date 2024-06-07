#include "head.h"
/* 108. 将有序数组转换为二叉搜索树
给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 高度平衡
二叉搜索树。
高度平衡 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过
1的二叉树。 */

TreeNode* traversal(vector<int>& nums, int l, int r) {
  if (l > r)
    return nullptr;
  int m = l + (r - l) / 2;
  TreeNode* root = new TreeNode(nums[m]);
  root->left = traversal(nums, l, m - 1);
  root->right = traversal(nums, m + 1, r);
  return root;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
}

// 递归法。传入左右下标，左闭右闭区间，中间生成新节点，左右分割区间递归。
// 递归法。新数组，左闭右开区间。迭代器it+mid下标，即为真实mid下标
// 递归法，去中间值生成根节点，最好利用左右坐标，左闭右闭区间
TreeNode* traversal1(vector<int>& nums, int left, int right) {
  if (left > right)
    return nullptr;
  int mid = left + (right - left) / 2;  // 防止越界
  TreeNode* root = new TreeNode(nums[mid]);
  root->left = traversal1(nums, left, mid - 1);
  root->right = traversal1(nums, mid + 1, right);
  return root;
}
TreeNode* sortedArrayToBST1(vector<int>& nums) {
  return traversal1(nums, 0, nums.size() - 1);
}

TreeNode* sortedArrayToBST2(vector<int>& nums) {  // 生成新数组，左闭右开区间
  if (nums.empty())
    return nullptr;
  int middle = nums.size() / 2;
  TreeNode* root = new TreeNode(nums[middle]);
  vector<int> left(nums.begin(), nums.begin() + middle);
  vector<int> right(nums.begin() + middle + 1, nums.end());
  root->left = sortedArrayToBST2(left);
  root->right = sortedArrayToBST2(right);
  return root;
}

// 迭代法，由于从上往下遍历，故利用层序遍历的方方法，用三个队列进行辅助
TreeNode* sortedArrayToBST3(vector<int>& nums) {
  if (nums.size() == 0)
    return nullptr;
  queue<TreeNode*> nodeQue;
  queue<int> leftQue;
  queue<int> rightQue;
  TreeNode* root = new TreeNode(0);  // 初始根节点置零
  nodeQue.push(root);
  leftQue.push(0);
  rightQue.push(nums.size() - 1);
  while (!nodeQue.empty()) {
    TreeNode* curNode = nodeQue.front();
    nodeQue.pop();
    int left = leftQue.front();
    leftQue.pop();
    int right = rightQue.front();
    rightQue.pop();
    int mid = left + (right - left) / 2;
    curNode->val = nums[mid];           // 根节点赋值
    if (left <= mid - 1) {              // 左闭右闭区间，要加等号
      curNode->left = new TreeNode(0);  // 直接生成
      nodeQue.push(curNode->left);
      leftQue.push(left);
      rightQue.push(mid - 1);
    }
    if (right >= mid + 1) {
      curNode->right = new TreeNode(0);
      nodeQue.push(curNode->right);
      leftQue.push(mid + 1);
      rightQue.push(right);
    }
  }
  return root;
}

int main() {
  vector<int> vec1 = {-10, -3, 0, 5, 9};
  vector<int> vec2 = {1, 3};
  vector<int> vec3 = {};
  vector<int> vec4 = {0, 1, 2, 3, 4, 5};
  /*   TreeNode* node1 = construct_binary_tree(vec1);
    TreeNode* node2 = construct_binary_tree(vec2);
    TreeNode* node3 = construct_binary_tree(vec3); */
  print_binary_tree(sortedArrayToBST(vec1));
  print_binary_tree(sortedArrayToBST(vec2));
  print_binary_tree(sortedArrayToBST(vec3));
  print_binary_tree(sortedArrayToBST(vec4));
  cout << endl;
  print_binary_tree(sortedArrayToBST1(vec1));
  print_binary_tree(sortedArrayToBST1(vec2));
  print_binary_tree(sortedArrayToBST1(vec3));
  print_binary_tree(sortedArrayToBST1(vec4));
  return 0;
}
