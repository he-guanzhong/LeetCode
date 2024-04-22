#include "head.h"
/* 338. 比特位计数
给你一个整数 n ，对于 0 <= i <= n 中的每个 i ，计算其二进制表示中 1 的个数
，返回一个长度为 n + 1 的数组 ans 作为答案。
示例 1：
输入：n = 2
输出：[0,1,1]
解释：
0 --> 0
1 --> 1
2 --> 10
示例 2：
输入：n = 5
输出：[0,1,1,2,1,2]
解释：
0 --> 0
1 --> 1
2 --> 10
3 --> 11
4 --> 100
5 --> 101 */

// C语言有内置的函数__builtin_popcount，判断一个32位整数位1的个数
// 传统BrianKernighan算法，对每一个数字使用i&i-1计算一比特数，时间复杂度O(n)=nlogn
vector<int> countBits1(int n) {
  vector<int> ans;
  for (int i = 0; i <= n; i++)
    ans.push_back(__builtin_popcount(i));
  return ans;
}

// 动态规划。最高有效位。highBit保存2的n次幂（利用i&i-1判断)。递推公式dp[i]=dp[i-highBit]+1。时间复杂度O(n)=n
vector<int> countBits2(int n) {
  vector<int> bits(n + 1, 0);
  int highBit = 0;
  for (int i = 1; i <= n; i++) {
    if ((i & (i - 1)) == 0)  // ==优先级要大于&
      highBit = i;
    bits[i] = bits[i - highBit] + 1;
  }
  return bits;
}

// 动态规划，最低有效位。i为偶数，则dp[i]==dp[i/2]，i为奇数，则dp[i]==dp[i/2]+1。考虑使用>>右移代替/2，按位与&代替求余%2
vector<int> countBits3(int n) {
  vector<int> bits(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    bits[i] = bits[i >> 1] + (i & 1);
  }
  return bits;
}

// 动态规划。最低设置位，y为i&i-1，即最后一位1消除后的数。dp[i]=dp[y]+1
vector<int> countBits(int n) {
  vector<int> bits(n + 1, 0);
  for (int i = 1; i <= n; i++) {
    bits[i] = bits[i & (i - 1)] + 1;
  }
  return bits;
}

int main() {
  printVector(countBits(2));
  printVector(countBits(5));

  return 0;
}