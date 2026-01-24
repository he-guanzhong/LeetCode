#include "head.h"
/* 113. 路径总和 II
给你二叉树的根节点 root 和一个整数目标和 targetSum ，找出所有 从根节点到叶子节点
路径总和等于给定目标和的路径。
叶子节点 是指没有子节点的节点。*/

void traversal(TreeNode* root,
               int target,
               vector<int> path,
               vector<vector<int>>& result) {
  if (!root)
    return;
  path.push_back(root->val);
  if (!root->left && !root->right && root->val == target)
    result.push_back(path);
  traversal(root->left, target - root->val, path, result);
  traversal(root->right, target - root->val, path, result);
  path.pop_back();
}
vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
  vector<vector<int>> result;
  vector<int> path;
  traversal(root, targetSum, path, result);
  return result;
}

// 习惯写法，允许空结点递归，多遍历一层。明写回溯。注意result和path可以作为传参
// 优化一，如果在递归函数形参target-root->val，可以省去递归函数前的的加，和递归后的减回溯
// 优化二，如果传参path不为传址，为传值，则可以省略path.pop_back()回溯
void traversal1(TreeNode* root,
                int count,
                vector<int>& path,
                vector<vector<int>>& result) {
  if (!root)
    return;
  count -= root->val;
  path.push_back(root->val);
  if (count == 0 && !root->left && !root->right)
    result.push_back(path);
  traversal1(root->left, count, path, result);
  traversal1(root->right, count, path, result);
  count += root->val;
  path.pop_back();
}
vector<vector<int>> pathSum1(TreeNode* root, int targetSum) {
  vector<vector<int>> result;
  vector<int> path;
  traversal1(root, targetSum, path, result);
  return result;
}

// 标准写法，path和result外置，只有有值的结点才递归，递归时已经减去了本层结点值，故判断count是否为0
vector<vector<int>> result;
vector<int> path;
void traversal_std(TreeNode* root, int count) {
  if (!root->left && !root->right && count == 0) {
    result.push_back(path);
    return;
  }
  if (!root->left && !root->right)
    return;
  if (root->left) {
    path.push_back(root->left->val);
    traversal_std(root->left, count - root->left->val);
    path.pop_back();
  }
  if (root->right) {
    path.push_back(root->right->val);
    traversal_std(root->right, count - root->right->val);
    path.pop_back();
  }
}
vector<vector<int>> pathSum_std(TreeNode* root, int targetSum) {
  result.clear();
  path.clear();
  if (!root)
    return result;
  path.push_back(root->val);
  traversal_std(root, targetSum - root->val);
  return result;
}

int main() {
  int targetSum1 = 22, targetSum2 = 5, targetSum3 = 0;
  vector<int> vec1 = {5, 4,    8,    11,   null, 13, 4, 7,
                      2, null, null, null, null, 5,  1};
  TreeNode* node1 = construct_binary_tree(vec1);
  vector<int> vec2 = {1, 2, 3};
  TreeNode* node2 = construct_binary_tree(vec2);
  // print_binary_tree(node1);
  vector<int> vec3 = {};
  TreeNode* node3 = construct_binary_tree(vec3);
  printMat(pathSum(node1, targetSum1));
  printMat(pathSum(node2, targetSum2));
  printMat(pathSum(node3, targetSum3));
  printMat(pathSum1(node1, targetSum1));
  printMat(pathSum1(node2, targetSum2));
  printMat(pathSum1(node3, targetSum3));
  return 0;
}