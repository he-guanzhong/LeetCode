#include <cstring>
#include "head.h"
/* 376. 摆动序列
如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为 摆动序列
。第一个差（如果存在的话）可能是正数或负数。仅有一个元素或者含两个不等元素的序列也视作摆动序列。
    例如， [1, 7, 4, 9, 2, 5] 是一个 摆动序列 ，因为差值 (6, -3, 5, -7, 3)
是正负交替出现的。 相反，[1, 4, 7, 2, 5] 和 [1, 7, 4, 5, 5]
不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。
子序列
可以通过从原始序列中删除一些（也可以不删除）元素来获得，剩下的元素保持其原始顺序。
给你一个整数数组 nums ，返回 nums 中作为 摆动序列 的 最长子序列的长度 。
示例 1：
  输入：nums = [1,7,4,9,2,5]
  输出：6
  解释：整个序列均为摆动序列，各元素之间的差值为 (6, -3, 5, -7, 3) 。
示例 2：
  输入：nums = [1,17,5,10,13,15,10,5,16,8]
  输出：7
  解释：这个序列包含几个长度为 7 摆动序列。
    其中一个是 [1, 17, 10, 13, 10, 16, 8] ，各元素之间的差值为 (16, -7, 3, -3,
    6,-8) 。 示例 3： 输入：nums = [1,2,3,4,5,6,7,8,9] 输出：2 */

int wiggleMaxLength(vector<int>& nums) {
  if (nums.size() <= 1)
    return nums.size();
  int ans = 1;
  int pre_diff = 0;
  for (int i = 1; i < nums.size(); i++) {
    int cur_diff = nums[i] - nums[i - 1];
    if (pre_diff <= 0 && cur_diff > 0 || pre_diff >= 0 && cur_diff < 0) {
      ans++;
      pre_diff = cur_diff;
    }
  }
  return ans;
}

// nums.size()是0和1单独特殊处理(可选)，起步就处理内含2个及其以上元素的情况
// pre记录上一周期相差，与本周期相差比较，若符号相反则result++
// 注意：1. 考虑平坡最后一个元素为准，故pre允许是0。
// 2.首字母前假设为平坡，其pre为0，result要初始化为1。
// 3. pre不能随时更新，而必须是发生摆动后更新，否则易出现[2,1,2,2,3]的误报

// 首顶点设为1，设置前后差。从前向后遍历计算后差，出现波峰或者波谷，计数加一的同时更新前差。
// 不得每步都更新前差
int wiggleMaxLength1(vector<int>& nums) {
  if (nums.size() <= 1)
    return nums.size();
  int curDiff = 0;
  int preDiff = 0;
  int result = 1;
  for (int i = 0; i < nums.size() - 1; i++) {
    curDiff = nums[i + 1] - nums[i];
    if (preDiff <= 0 && curDiff > 0 || preDiff >= 0 && curDiff < 0) {
      result++;
      preDiff = curDiff;
    }
  }
  return result;
}

// 数组初始化函数，必须包含头文件string.h或cstring。memset函数（首地址，值，赋值空间大小）
int wiggleMaxLength2(vector<int>& nums) {
  int dp[nums.size()][2];
  memset(dp, 0, sizeof dp);  // sizeof(dp)
  for (int i = 1; i < nums.size(); i++) {
    dp[0][0] = dp[0][1] = 1;
    for (int j = 0; j < i; j++) {
      if (nums[j] > nums[i])
        dp[i][0] = max(dp[i][0], dp[j][1] + 1);
    }
    for (int j = 0; j < i; j++) {
      if (nums[j] < nums[i])
        dp[i][1] = max(dp[i][1], dp[j][0] + 1);
    }
  }
  return max(dp[nums.size() - 1][0], dp[nums.size() - 1][1]);
}

int main() {
  vector<int> g1 = {1, 7, 4, 9, 2, 5};
  vector<int> g2 = {1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
  vector<int> g3 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> g4 = {2, 1, 2, 2, 3};

  cout << wiggleMaxLength(g1) << " " << wiggleMaxLength(g2) << " "
       << wiggleMaxLength(g3) << " " << wiggleMaxLength(g4) << endl;
  cout << wiggleMaxLength1(g1) << " " << wiggleMaxLength1(g2) << " "
       << wiggleMaxLength1(g3) << " " << wiggleMaxLength(g4) << endl;
  return 0;
}