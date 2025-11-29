#include "head.h"
/* LCR 091. 粉刷房子
假如有一排房子，共 n
个，每个房子可以被粉刷成红色、蓝色或者绿色这三种颜色中的一种，你需要粉刷所有的房子并且使其相邻的两个房子颜色不能相同。
当然，因为市场上不同颜色油漆的价格不同，所以房子粉刷成不同颜色的花费成本也是不同的。每个房子粉刷成不同颜色的花费是以一个
n x 3 的正整数矩阵 costs 来表示的。
例如，costs[0][0] 表示第 0 号房子粉刷成红色的成本花费；costs[1][2] 表示第 1
号房子粉刷成绿色的花费，以此类推。
请计算出粉刷完所有房子最少的花费成本。
示例 1：
  输入: costs = [[17,2,17],[16,16,5],[14,3,19]]
  输出: 10
  解释: 将 0 号房子粉刷成蓝色，1 号房子粉刷成绿色，2 号房子粉刷成蓝色。
     最少花费: 2 + 5 + 3 = 10。
示例 2：
  输入: costs = [[7,6,2]]
  输出: 2
  提示:
    costs.length == n
    costs[i].length == 3
    1 <= n <= 100
    1 <= costs[i][j] <= 20 */

int minCost(vector<vector<int>>& costs) {
  int dp[2][3] = {0};
  dp[0][0] = costs[0][0], dp[0][1] = costs[0][1], dp[0][2] = costs[0][2];
  for (int i = 1; i < costs.size(); i++) {
    for (int j = 0; j < 3; j++)
      dp[1][j] = costs[i][j] + min(dp[0][(j + 1) % 3], dp[0][(j + 2) % 3]);
    for (int j = 0; j < 3; j++)
      dp[0][j] = dp[1][j];
  }
  return min({dp[0][0], dp[0][1], dp[0][2]});
}

// 动态规划基础题。位置i刷其中一个颜色，则其前一位i-1就不能刷对应的颜色。
// 问题转化为，假设长度n=3的序列[0,1,2]，对任意一个下标j，找出其余位置下标(j+k)%n，其中k意偏置[1,n)
// 求余符号%与乘除优先级一致，大于加减
int minCost1(vector<vector<int>>& costs) {
  vector<int> pre = costs[0];
  vector<int> cur(3, 0);
  for (int i = 1; i < costs.size(); i++) {
    /*  cur[0] = min(pre[1], pre[2]) + costs[i][0];
        cur[1] = min(pre[0], pre[2]) + costs[i][1];
        cur[2] = min(pre[0], pre[1]) + costs[i][2]; */
    for (int j = 0; j < 3; j++)
      cur[j] = min(pre[(j + 1) % 3], pre[(j + 2) % 3]) + costs[i][j];
    pre = cur;
  }
  return min({pre[0], pre[1], pre[2]});
}

int main() {
  vector<vector<int>> costs1 = {{17, 2, 17}, {16, 16, 5}, {14, 3, 19}},
                      costs2 = {{7, 6, 2}};
  cout << minCost(costs1) << " " << minCost(costs2) << endl;
  cout << minCost1(costs1) << " " << minCost1(costs2) << endl;
  return 0;
}