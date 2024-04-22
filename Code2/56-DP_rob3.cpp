#include "head.h"
#define null -1
/* 337. 打家劫舍 III
小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 root 。
除了 root
之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识到“这个地方的所有房屋的排列类似于一棵二叉树”。
如果 两个直接相连的房子在同一天晚上被打劫 ，房屋将自动报警。
给定二叉树的 root 。返回 在不触动警报的情况下 ，小偷能够盗取的最高金额 。
示例 1:
输入: root = [3,2,3,null,3,null,1]
输出: 7
解释: 小偷一晚能够盗取的最高金额 3 + 3 + 1 = 7
示例 2:
输入: root = [3,4,5,1,3,null,1]
输出: 9
解释: 小偷一晚能够盗取的最高金额 4 + 5 = 9 */

// 后序遍历，返回值用vector同时记录不偷和偷的最大数值。递归遇到根节点必返回0，提取左右子树返回结果。
// 偷该节点，则左右子树必不偷。不偷该结点，左、右均可偷可不偷，取最大值返回。
vector<int> robTest(TreeNode* root) {
  if (!root)
    return {0, 0};
  if (!root->left && !root->right)
    return {0, root->val};
  vector<int> left = robTest(root->left);
  vector<int> right = robTest(root->right);
  int yes = left[0] + right[0] + root->val;
  int no = max(left[0], left[1]) + max(right[0], right[1]);
  return {no, yes};
}
int rob(TreeNode* root) {
  vector<int> result = robTest(root);
  return max(result[0], result[1]);
}

// 树形dp。返回值可以为两个值的数组，记录了到该结点时，不偷与偷分别的价值大小。
// 退出条件为，空结点，无论偷不偷都是0。叶子结点，不偷必为0，偷就是该点值大小。依旧是后序遍历，保存左右分支值
// 若偷该结点，则左右结点必不能偷，取其[0]值。若不偷该结点，则左右均可偷可不偷取最大值，该结点值为左右最大值之和
// 以不偷和偷顺序，返回数组。时间复杂度n，因为每个结点只计算了一遍，空间复杂度logn，算上了递归系统栈空间
vector<int> robTree(TreeNode* root) {
  if (!root)
    return {0, 0};
  if (!root->left & !root->right)
    return {0, root->val};
  vector<int> left = robTree(root->left);
  vector<int> right = robTree(root->right);
  int val1 = root->val + left[0] + right[0];
  int val2 = max(left[0], left[1]) + max(right[0], right[1]);
  return {val2, val1};
}
int rob1(TreeNode* root) {
  vector<int> dp = robTree(root);
  return max(dp[0], dp[1]);
}

// 暴力递归搜索。一定是后序遍历，因为要利用返回值，当作该点最大值的结果。退出条件是空结点，返回0。叶子结点，返回结点值。
// 情况可以分为，1、抢该节点，则该节点值需要加上可能的孙结点返回值。2、不抢该结点，该节点值应为左右孩子返回值之和
// 该算法超时，因为每一层，都重复计算了子结点和孙结点
int rob2(TreeNode* root) {
  if (!root)
    return 0;
  if (!root->left && !root->right)
    return root->val;
  int val1 = root->val;
  if (root->left)
    val1 += rob2(root->left->left) + rob2(root->left->right);
  if (root->right)
    val1 += rob2(root->right->left) + rob2(root->right->right);
  int val2 = rob2(root->left) + rob2(root->right);
  return max(val1, val2);
}

// 使用记忆化递归，如果计算过的结果，就不再重复计算。时间复杂度n因为每个节点都算了一次，空间复杂度logn，算上系统递归栈所用空间
unordered_map<TreeNode*, int> umap;
int rob3(TreeNode* root) {
  if (!root)
    return 0;
  if (!root->left && !root->right)
    return root->val;
  if (umap[root])  // 计算过一次的，就不重复计算了
    return umap[root];
  int val1 = root->val;
  if (root->left)
    val1 += rob3(root->left->left) + rob3(root->left->right);
  if (root->right)
    val1 += rob3(root->right->left) + rob3(root->right->right);
  int val2 = rob3(root->left) + rob3(root->right);
  umap[root] = max(val1, val2);
  return max(val1, val2);
}

int main() {
  TreeNode* root1 = construct_binary_tree({3, 2, 3, null, 3, null, 1});
  TreeNode* root2 = construct_binary_tree({3, 4, 5, 1, 3, null, 1});
  cout << rob(root1) << " " << rob(root2) << endl;
  cout << rob1(root1) << " " << rob1(root2) << endl;
  return 0;
}