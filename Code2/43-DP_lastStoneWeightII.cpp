#include "head.h"
#include <numeric>
/* 1049. 最后一块石头的重量 II
有一堆石头，用整数数组 stones 表示。其中 stones[i] 表示第 i 块石头的重量。
每一回合，从中选出任意两块石头，然后将它们一起粉碎。假设石头的重量分别为 x 和
y，且 x <= y。那么粉碎的可能结果如下：
    如果 x == y，那么两块石头都会被完全粉碎；
    如果 x != y，那么重量为 x 的石头将会完全粉碎，而重量为 y 的石头新重量为y-x。
最后，最多只会剩下一块 石头。返回此石头 最小的可能重量
。如果没有石头剩下，就返回 0。
示例 1：
输入：stones = [2,7,4,1,8,1]
输出：1
解释：
组合 2 和 4，得到 2，所以数组转化为 [2,7,1,8,1]，
组合 7 和 8，得到 1，所以数组转化为 [2,1,1,1]，
组合 2 和 1，得到 1，所以数组转化为 [1,1,1]，
组合 1 和 1，得到 0，所以数组转化为 [1]，这就是最优值。
示例 2：
输入：stones = [31,26,33,21,40]
输出：5
    1 <= stones.length <= 30
    1 <= stones[i] <= 100
 */

// 允许石头共聚为一体，再碰撞减重。问题转化为石头分为总重相近的两堆，求其差。背包容量n为总重的一半，向下取整
// dp[j]表示容量j下石头最大重量，背包遍历后，dp[n]为较小的一堆总重。返回较大的一堆和较小一堆总重差
int lastStoneWeightII(vector<int> &stones) {
  int sum = accumulate(stones.begin(), stones.end(), 0);
  int n = sum / 2;
  vector<int> dp(n + 1, 0);
  for (int i = 0; i < stones.size(); i++) {
    for (int j = n; j >= stones[i]; j--)
      dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
  }
  return sum - dp[n] * 2;
}

// 核心是把石头分为重量接近的两堆，两堆重量之差就是剩余最小重量
// dp[j]表示容量j内能容纳的最多石头体积。故weight和value均为stone
// 考虑到石头总重不能超过30000，dp容量最多为其一般15001
// target=sum/2向下取整了，故dp[target]必小于sum-dp[target]，输出其差
// 时间复杂度m*n，m为石头总重一半，n为石头数量。空间复杂度m
int lastStoneWeightII1(vector<int> &stones) {
  int sum = accumulate(stones.begin(), stones.end(), 0);
  int target = sum / 2;
  vector<int> dp(15001, 0);
  for (int i = 0; i < stones.size(); i++) {
    for (int j = target; j >= stones[i]; j--)
      dp[j] = max(dp[j], dp[j - stones[i]] + stones[i]);
  }
  return sum - dp[target] - dp[target];
}
int main() {
  vector<int> nums1 = {2, 7, 4, 1, 8, 1};
  vector<int> nums2 = {31, 26, 33, 21, 40};
  cout << lastStoneWeightII(nums1) << " " << lastStoneWeightII(nums2) << endl;
  cout << lastStoneWeightII1(nums1) << " " << lastStoneWeightII1(nums2) << endl;
  return 0;
}