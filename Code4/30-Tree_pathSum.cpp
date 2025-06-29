#include "head.h"
/* 437. 路径总和 III
给定一个二叉树的根节点 root ，和一个整数 targetSum ，求该二叉树里节点值之和等于
targetSum 的 路径 的数目。
路径
不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
示例 1：
  输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
  输出：3
  解释：和等于 8 的路径有 3 条，如图所示。
示例 2：
  输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
  输出：3
提示:
    二叉树的节点个数的范围是 [0,1000]
    -10^9 <= Node.val <= 10^9
    -1000 <= targetSum <= 1000  */

int dfs(TreeNode* root,
        int targetSum,
        long long& sum,
        unordered_map<long long, int>& umap) {
  if (!root)
    return 0;
  sum += root->val;
  int ans = 0;
  if (umap.count(sum - targetSum))
    ans += umap[sum - targetSum];
  umap[sum]++;
  ans += dfs(root->left, targetSum, sum, umap);
  ans += dfs(root->right, targetSum, sum, umap);
  umap[sum]--;
  sum -= root->val;
  return ans;
}
int pathSum(TreeNode* root, int targetSum) {
  unordered_map<long long, int> umap;
  umap[0] = 1;
  long long sum = 0;
  return dfs(root, targetSum, sum, umap);
}

// 前缀树。返回值为该结点能返回路径树数量，传入参数为该结点前路径总和。哈希表记录每种总和，和对应的数量。
// 初始化哈希表，总和为0的路径，有1种办法。map中寻找当前cur-targerSum路径和的数量，代表以当前cur为终止，起点未知的路径和数量。再加上左右孩子递归返回数量。
// 回溯时，路径和变化，要删除原路径和的数量。该题中路径总和超过了4个字节long能表达范围，需要使用longlong记录，时间和空间复杂度均为O(n)
unordered_map<long long, int> prefix;
int dfs1(TreeNode* root, long long cur, int targetSum) {
  if (!root)
    return 0;
  int result = 0;
  cur += root->val;
  if (prefix.count(cur - targetSum) > 0)
    result = prefix[cur - targetSum];
  prefix[cur]++;
  result += dfs1(root->left, cur, targetSum);
  result += dfs1(root->right, cur, targetSum);
  prefix[cur]--;
  return result;
}
int pathSum1(TreeNode* root, int targetSum) {
  prefix[0] = 1;
  return dfs1(root, 0, targetSum);
}

int main() {
  TreeNode* t1 =
      construct_binary_tree({10, 5, -3, 3, 2, null, 11, 3, -2, null, 1});
  TreeNode* t2 =
      construct_binary_tree({5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1});
  TreeNode* t3 = construct_binary_tree({0});
  TreeNode* t4 = construct_binary_tree({715827882, 715827882, null, 715827882,
                                        null, 1, null, 715827882, null,
                                        715827882, null, 715827882, null});
  cout << pathSum(t1, 8) << " " << pathSum(t2, 22) << " " << pathSum(t3, 0)
       << " " << pathSum(t4, -3) << endl;
  cout << pathSum1(t1, 8) << " " << pathSum1(t2, 22) << " " << pathSum1(t3, 0)
       << " " << pathSum1(t4, -3) << endl;
  return 0;
}