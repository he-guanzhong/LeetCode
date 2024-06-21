#include "head.h"
/* 96. 不同的二叉搜索树
给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的 二叉搜索树
有多少种？返回满足题意的二叉搜索树的种数。
示例 1：
  输入：n = 3
  输出：5
示例 2：
  输入：n = 1
  输出：1 */

int numTrees(int n) {
  vector<int> dp(n + 1, 0);
  dp[0] = 1, dp[1] = 1;
  for (int i = 2; i <= n; i++) {
    for (int j = 0; j < i; j++)
      dp[i] += dp[j] * dp[i - 1 - j];
  }
  return dp[n];
}

// dp[i]为i个节点的二叉搜索树数量。拆解为用头节点j切分[1,i]区间，所有左子树[1,j]二叉树数量*右子树[j,i]二叉树数量之和。
// 初始化dp[0]=1，空子树也算二叉搜索树，数量为1。一轮遍历从[1,n]为节点数。二轮遍历为[1,i]该节点数下变换头节点，不断累积二叉树数量

// dp[i]意为到i的不同二叉搜索树数量。其可以拆解为，左子树数量先0右子树i-1个，相乘，然后左子树不断增多至i-1右子树不断减少至0，相乘。
// 递推公式为dp[i]=sum(dp[j-1]*dp[i-j])。初始化dp[0]=0，空也可以算作二叉搜索树
// 空间复杂度O(n)，时间复杂度O(n^2)
int numTrees1(int n) {
  vector<int> dp(n + 1);
  dp[0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= i; j++)
      dp[i] += dp[j - 1] * dp[i - j];
  }
  return dp[n];
}

int main() {
  cout << numTrees(1) << " " << numTrees(2) << " " << numTrees(3) << " "
       << numTrees(4) << " " << numTrees(5) << endl;
  cout << numTrees1(1) << " " << numTrees1(2) << " " << numTrees1(3) << " "
       << numTrees1(4) << " " << numTrees1(5) << endl;
  return 0;
}