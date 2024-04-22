#include "head.h"
/* LCR 185. 统计结果概率
你选择掷出 num 个色子，请返回所有点数总和的概率。
你需要用一个浮点数数组返回答案，其中第 i 个元素代表这 num
个骰子所能掷出的点数集合中第 i 小的那个的概率。
示例 1：
输入：num = 3
输出：[0.00463,0.01389,0.02778,0.04630,0.06944,0.09722,0.11574,0.12500,0.12500,0.11574,0.09722,0.06944,0.04630,0.02778,0.01389,0.00463]
示例 2：
输入：num = 5
输出:[0.00013,0.00064,0.00193,0.00450,0.00900,0.01620,0.02636,0.03922,0.05401,0.06944,0.08372,0.09452,0.10031,0.10031,0.09452,0.08372,0.06944,0.05401,0.03922,0.02636,0.01620,0.00900,0.00450,0.00193,0.00064,0.00013]
提示：
    1 <= num <= 11 */
vector<double> statisticsProbability(int num) {
  vector<double> dp(6, 1.0 / 6.0);
  for (int i = 2; i <= num; i++) {
    vector<double> tmp(5 * i + 1, 0);
    for (int j = 0; j < dp.size(); j++) {
      for (int k = 0; k < 6; k++)
        tmp[j + k] += dp[j] * 1.0 / 6.0;
    }
    dp = tmp;
  }
  return dp;
}

// 只有1个骰子，六种可能[1,6]，每种概率1/6。设置骰子总计n个，第i个骰子可以由第i-1个的情况推导而出。i个骰子，总和范围[i,6i]，总计5i+1中情况。
// 三层遍历，首先初始化第一层dp，只有1个骰子，每种概率1/6。i代表骰子数，从2个骰子开始。该层概率分布临时tmp，总计5i+1种元素
// 二层遍历，基于上一层dp，每一种可能dp[j]。其对下一层tmp[j]有基础贡献。三层遍历，上层的dp[j]对该层新骰子共6种可能，均有贡献。
// k取值[0,6)。每一层tmp[j+k]+=dp[j]+1/6。tmp层计算完成后，dp=tmp，如此dp即记录了上一层的概率分布
vector<double> statisticsProbability1(int num) {
  vector<double> dp(6, 1.0 / 6.0);
  for (int i = 2; i <= num; i++) {
    vector<double> tmp(5 * i + 1, 0);
    for (int j = 0; j < dp.size(); j++) {
      for (int k = 0; k < 6; k++) {
        tmp[j + k] += dp[j] / 6.0;
      }
    }
    dp = tmp;
  }
  return dp;
}

int main() {
  printVector(statisticsProbability(3));
  printVector(statisticsProbability(5));
  printVector(statisticsProbability1(3));
  printVector(statisticsProbability1(5));
  return 0;
}