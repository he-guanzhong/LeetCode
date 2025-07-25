#include "head.h"
/* 926. 将字符串翻转到单调递增
如果一个二进制字符串，是以一些 0（可能没有 0）后面跟着一些 1（也可能没有
1）的形式组成的，那么该字符串是 单调递增 的。
给你一个二进制字符串 s，你可以将任何 0 翻转为 1 或者将 1 翻转为 0 。
返回使 s 单调递增的最小翻转次数。
示例 1：
  输入：s = "00110"
  输出：1
  解释：翻转最后一位得到 00111.
示例 2：
  输入：s = "010110"
  输出：2
  解释：翻转得到 011111，或者是 000111。
示例 3：
  输入：s = "00011000"
  输出：2
  解释：翻转得到 00000000。
提示：
    1 <= s.length <= 105
    s[i] 为 '0' 或 '1' */

int minFlipsMonoIncr(string s) {
  int start = 0, end = s.size() - 1;
  while (start < s.size() && s[start] == '0')
    start++;
  while (end >= start && s[end] == '1')
    end--;
  int cnt1 = 0, cnt0 = 0;
  for (int i = start; i <= end; i++) {
    if (s[i] == '1')
      cnt1++;
    else
      cnt0++;
  }
  return min(cnt1, cnt0);
}

// 到字符i时，dp[i][0]、dp[i][1]分别为其位为0、1时的最小翻转次数。
// 显然初始状态，只有需求0但实际值是1，或需求1但实际值为0，才需要计数
// 从第二位开始，该位是0，要求该位前必须也是0，若此位为1，则计数增加一次
// 若该位是1，则对该位前无要求，可以是0或1，具体看哪方更小。若此位为0，则计数增加一次
int minFlipsMonoIncr1(string s) {
  int dp[2][2] = {0};
  dp[0][0] = s[0] == '1';
  dp[0][1] = s[0] == '0';
  for (int i = 1; i < s.size(); i++) {
    dp[1][0] = dp[0][0] + (s[i] == '1');
    dp[1][1] = min(dp[0][0], dp[0][1]) + (s[i] == '0');
    dp[0][0] = dp[1][0];
    dp[0][1] = dp[1][1];
  }
  return min(dp[0][0], dp[0][1]);
}

// 方便解法。dp表示到达i位前保持顺序，至少翻转多少次。当s[i]为1时，必满足要求，故对1计数
// 当s[i]为0时，可能需要反转，具体参看是反转[0,i-1]前所有的1合适，还是翻转当前位合适，则翻转次数dp+1。取二者最小值
int minFlipsMonoIncr2(string s) {
  int n = s.size();
  int one = 0;
  int dp = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == '0') {
      dp = fmin(one, dp + 1);
    } else {
      one++;
    }
  }
  return dp;
}

int main() {
  cout << minFlipsMonoIncr("00110") << " " << minFlipsMonoIncr("010110") << " "
       << minFlipsMonoIncr("00011000") << " " << minFlipsMonoIncr("0101100011")
       << " " << minFlipsMonoIncr("10011111110010111011") << endl;
  cout << minFlipsMonoIncr1("00110") << " " << minFlipsMonoIncr1("010110")
       << " " << minFlipsMonoIncr1("00011000") << " "
       << minFlipsMonoIncr1("0101100011") << " "
       << minFlipsMonoIncr1("10011111110010111011") << endl;
  return 0;
}