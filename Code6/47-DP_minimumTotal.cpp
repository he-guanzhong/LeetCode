#include "head.h"

/* 120. 三角形最小路径和
给定一个三角形 triangle ，找出自顶向下的最小路径和。
每一步只能移动到下一行中相邻的结点上。相邻的结点 在这里指的是 下标 与
上一层结点下标 相同或者等于 上一层结点下标 + 1
的两个结点。也就是说，如果正位于当前行的下标 i
，那么下一步可以移动到下一行的下标 i 或 i + 1 。
示例 1：
  输入：triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
  输出：11
  解释：如下面简图所示：
       2
      3 4
     6 5 7
    4 1 8 3
  自顶向下的最小路径和为 11（即，2 + 3 + 5 + 1 = 11）。
示例 2：
  输入：triangle = [[-10]]
  输出：-10
提示：
  1 <= triangle.length <= 200
  triangle[0].length == 1
  triangle[i].length == triangle[i - 1].length + 1
  -104 <= triangle[i][j] <= 104
进阶：
  你可以只使用 O(n) 的额外空间（n 为三角形的总行数）来解决这个问题吗？ */

int minimumTotal(vector<vector<int>>& triangle) {
  int m = triangle.size();
  vector<int> dp = triangle.back();
  for (int i = m - 2; i >= 0; i--) {
    for (int j = 0; j < triangle[i].size(); j++)
      dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
  }
  return dp.front();
}

// 动态规划。节省空间复杂度的做法是逆向思维，从下向上收敛最终结果。
// 下标i层元素有i+1个，因此下标j的遍历范围是[0,i]
// 对于层i，其手机来自更下一层i+1的结果。有dp[i]=min(dp[i],dp[i+1])+tri[i][j]
// 初始化，总计n层，则构造dp[n+1]，最下一层长度为n+1，内容全部为0
// 最终返回根节点dp[0]即为结果
int minimumTotal1(vector<vector<int>>& triangle) {
  int n = triangle.size();
  vector<int> dp(n + 1, 0);
  for (int i = n - 1; i >= 0; i--) {
    for (int j = 0; j <= i; j++) {
      dp[j] = min(dp[j], dp[j + 1]) + triangle[i][j];
    }
  }
  return dp[0];
}

// 普通做法。从上至下，空间复杂度O(n)。由于dp[j]=min(dp[j-1],dp[j])，故j要反向遍历
int minimumTotal2(vector<vector<int>>& triangle) {
  int n = triangle.size();
  vector<int> dp(n, INT_MAX);
  dp[0] = triangle[0][0];
  for (int i = 1; i < n; i++) {
    for (int j = i; j > 0; j--)
      dp[j] = min(dp[j], dp[j - 1]) + triangle[i][j];
    dp[0] += triangle[i][0];
  }
  return *min_element(dp.begin(), dp.end());
}

int main() {
  vector<vector<int>> triangle1 = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}},
                      triangle2 = {{-10}};
  cout << minimumTotal(triangle1) << " " << minimumTotal(triangle2) << endl;
  cout << minimumTotal1(triangle1) << " " << minimumTotal1(triangle2) << endl;

  return 0;
}