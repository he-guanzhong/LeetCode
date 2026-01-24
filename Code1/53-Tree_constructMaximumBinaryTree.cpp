#include "head.h"
/* 654. 最大二叉树
给定一个不重复的整数数组 nums 。 最大二叉树 可以用下面的算法从 nums 递归地构建:
    创建一个根节点，其值为 nums 中的最大值。
    递归地在最大值 左边 的 子数组前缀上 构建左子树。
    递归地在最大值 右边 的 子数组后缀上 构建右子树。
返回 nums 构建的 最大二叉树 。
示例 1：
  输入：nums = [3,2,1,6,0,5]
  输出：[6,3,5,null,2,0,null,null,1]
  解释：递归调用如下所示：
- [3,2,1,6,0,5] 中的最大值是 6 ，左边部分是 [3,2,1] ，右边部分是 [0,5] 。
    - [3,2,1] 中的最大值是 3 ，左边部分是 [] ，右边部分是 [2,1] 。
        - 空数组，无子节点。
        - [2,1] 中的最大值是 2 ，左边部分是 [] ，右边部分是 [1] 。
            - 空数组，无子节点。
            - 只有一个元素，所以子节点是一个值为 1 的节点。
    - [0,5] 中的最大值是 5 ，左边部分是 [0] ，右边部分是 [] 。
        - 只有一个元素，所以子节点是一个值为 0 的节点。
        - 空数组，无子节点。 */

TreeNode* traversal(vector<int>& nums, int l, int r) {
  if (l > r)
    return nullptr;
  int maxVal = INT_MIN, maxIndex = 0;
  for (int i = l; i <= r; i++) {
    if (nums[i] > maxVal) {
      maxVal = nums[i];
      maxIndex = i;
    }
  }
  TreeNode* root = new TreeNode(maxVal);
  root->left = traversal(nums, l, maxIndex - 1);
  root->right = traversal(nums, maxIndex + 1, r);
  return root;
}
TreeNode* constructMaximumBinaryTree(vector<int>& nums) {
  return traversal(nums, 0, nums.size() - 1);
}

// 确定左右区间，求区间内最大值下标，构造结点，切分左右区间。故使用前序遍历，分设左右下标。左开右闭区间
// 带下标版本，左开右闭区间，空结点允许进入递归，代码较为简洁
TreeNode* traversal1(vector<int>& nums, int left, int right) {
  if (left >= right)
    return nullptr;
  int maxValueIndex = left;
  for (int i = left; i < right; i++) {
    if (nums[i] > nums[maxValueIndex])
      maxValueIndex = i;
  }
  TreeNode* node = new TreeNode(nums[maxValueIndex]);
  node->left = traversal1(nums, left, maxValueIndex);
  node->right = traversal1(nums, maxValueIndex + 1, right);
  return node;
}
TreeNode* constructMaximumBinaryTree1(vector<int>& nums) {
  return traversal1(nums, 0, nums.size());
}

// 下标法重写，只有一个元素，返回这个元素值的新节点。
// 找到剩余最大元素值和其对应的下标，将原数组左右分割迭代
TreeNode* traversal2(vector<int>& nums, int left, int right) {
  TreeNode* node = new TreeNode(0);
  if (right - left == 1) {
    node->val = nums[left];
    return node;
  }
  int maxValue = nums[left], maxValueIndex = left;
  for (int i = left; i < right; i++) {
    if (nums[i] > nums[maxValueIndex]) {
      maxValue = nums[i];
      maxValueIndex = i;
    }
  }
  node->val = maxValue;
  if (maxValueIndex - left > 0) {
    node->left = traversal2(nums, left, maxValueIndex);
  }
  if (right - maxValueIndex > 1) {
    node->right = traversal2(nums, maxValueIndex + 1, right);
  }
  return node;
}
TreeNode* constructMaximumBinaryTree2(vector<int>& nums) {
  return traversal2(nums, 0, nums.size());
}

// 构造容器法，耗费较多资源，不推荐
TreeNode* constructMaximumBinaryTree3(vector<int>& nums) {
  TreeNode* root = new TreeNode(0);
  if (nums.size() == 1) {
    root->val = nums[0];
    return root;
  }
  int maxValue = nums[0], maxValueIndex = 0;
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] > maxValue) {
      maxValue = nums[i];
      maxValueIndex = i;
    }
  }
  root->val = maxValue;
  /*   vector<int>::iterator it = max_element(nums.begin(), nums.end());
    root->val = *it;
    maxValueIndex = distance(nums.begin(), it); */

  if (maxValueIndex > 0) {
    vector<int> leftTree(nums.begin(), nums.begin() + maxValueIndex);
    root->left = constructMaximumBinaryTree3(leftTree);
  }
  if (maxValueIndex < nums.size() - 1) {
    vector<int> rightTree(nums.begin() + maxValueIndex + 1, nums.end());
    root->right = constructMaximumBinaryTree3(rightTree);
  }
  return root;
}

int main() {
  vector<int> vec1 = {3, 2, 1, 6, 0, 5};
  // 输出：[6,3,5,null,2,0,null,null,1]
  vector<int> vec2 = {3, 2, 1};
  // 输出：[3,null,2,null,1]
  print_binary_tree(constructMaximumBinaryTree(vec1));
  print_binary_tree(constructMaximumBinaryTree(vec2));
  print_binary_tree(constructMaximumBinaryTree1(vec1));
  print_binary_tree(constructMaximumBinaryTree1(vec2));
  return 0;
}
