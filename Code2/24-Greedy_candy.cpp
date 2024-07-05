#include "head.h"
/* 135. 分发糖果
n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。
你需要按照以下要求，给这些孩子分发糖果：
    每个孩子至少分配到 1 个糖果。
    相邻两个孩子评分更高的孩子会获得更多的糖果。
请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。
示例 1：
  输入：ratings = [1,0,2]
  输出：5
  解释：你可以分别给第一个、第二个、第三个孩子分发 2、1、2 颗糖果。
示例 2：
  输入：ratings = [1,2,2]
  输出：4
  解释：你可以分别给第一个、第二个、第三个孩子分发 1、2、1 颗糖果。
     第三个孩子只得到 1 颗糖果，这满足题面中的两个条件。 */

int candy(vector<int>& ratings) {
  int n = ratings.size();
  vector<int> dp(n, 1);
  for (int i = 1; i < n; i++) {
    if (ratings[i] > ratings[i - 1])
      dp[i] = dp[i - 1] + 1;
  }
  for (int i = n - 2; i >= 0; i--) {
    if (ratings[i] > ratings[i + 1])
      dp[i] = max(dp[i], dp[i + 1] + 1);
  }
  return accumulate(dp.begin(), dp.end(), 0);
}

// 不能取中间最小向两边遍历。贪心策略为，分两遍遍历，找寻单边大的情况
// 只能从左到右遍历，找所有右孩子比左孩子大的情况。从右到左遍历，找所有左孩子比有孩子大的情况，取二者最大值
// 要保证相邻孩子的大小比较，要遍历两个方向：左孩子小于右孩子，从左向右遍历。左孩子大于右孩子，从右向左遍历。二者取最大值，即为糖果数
int candy1(vector<int>& ratings) {
  vector<int> candy(ratings.size(), 1);
  for (int i = 1; i < ratings.size(); i++) {  // 从左向右遍历遇到更大的就加一
    if (ratings[i] > ratings[i - 1])
      candy[i] = candy[i - 1] + 1;
  }
  for (int i = ratings.size() - 2; i >= 0;
       i--) {  // 从右向左遍历，遇到更大的就加一
    if (ratings[i] > ratings[i + 1])
      candy[i] = max(candy[i], candy[i + 1] + 1);
  }
  return accumulate(candy.begin(), candy.end(), 0);
}

int main() {
  vector<int> nums1 = {1, 0, 2};
  vector<int> nums2 = {1, 2, 2};
  vector<int> nums3 = {1, 3, 2, 2, 1};
  vector<int> nums4 = {0, 1, 2, 5, 3, 2, 7};
  cout << candy(nums1) << " " << candy(nums2) << " " << candy(nums3) << " "
       << candy(nums4) << endl;
  cout << candy1(nums1) << " " << candy1(nums2) << " " << candy1(nums3) << " "
       << candy1(nums4) << endl;
  return 0;
}