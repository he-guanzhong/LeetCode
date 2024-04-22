#include "head.h"
/* LCR 135. 报数
实现一个十进制数字报数程序，请按照数字从小到大的顺序返回一个整数数列，该数列从数字
1 开始，到最大的正整数 cnt 位数字结束。
示例 1:
输入：cnt = 2
输出：[1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99]
 */

// 考察大数全排列。注意从左至右第一位，不可以是0，故其范围为[1,9]。后几位取值范围均为[0,9]
// 主函数一层遍历所有位数cnt，二层遍历第一位取值[1,9]特殊情况。
// 递归函数dfs。入参为当前正处理第k位，该轮数字总计n位，当前已获得的字符串s，使用字符串保存数字，避免大数越界问题
// 退出条件，正在处理的k位，已经到了该轮数字n位数，此时s已经包含了改k位上的数字，直接stoi压入结果
// dfs函数横向遍历剩余从k+1位开始数字i，字符串传参不加引用，即可不使用pop函数。时间复杂度O(n)=cnt*10^cnt
void dfs(int k, int n, string s, vector<int>& ans) {
  if (k == n) {
    ans.push_back(stoi(s));
    return;
  }
  for (int i = 0; i < 10; i++)
    dfs(k + 1, n, s + to_string(i), ans);
}
vector<int> countNumbers(int cnt) {
  vector<int> ans;
  for (int i = 1; i <= cnt; i++) {
    for (int j = 1; j <= 9; j++)
      dfs(1, i, to_string(j), ans);
  }
  return ans;
}

// 数取值范围[1,10^cnt-1]，直接打印，时间复杂度O(n)=10^cnt
vector<int> countNumbers1(int cnt) {
  int m = pow(10, cnt);
  vector<int> result(m - 1);
  for (int i = 1; i < m; i++)
    result[i - 1] = i;
  return result;
}

int main() {
  printVector(countNumbers(2));
  return 0;
}