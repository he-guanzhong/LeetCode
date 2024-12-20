#include "head.h"
/* 1221. 分割平衡字符串
平衡字符串 中，'L' 和 'R' 字符的数量是相同的。
给你一个平衡字符串 s，请你将它分割成尽可能多的子字符串，并满足：
    每个子字符串都是平衡字符串。
返回可以通过分割得到的平衡字符串的 最大数量 。
示例 1：
  输入：s = "RLRRLLRLRL"
  输出：4
  解释：s 可以分割为 "RL"、"RRLL"、"RL"、"RL" ，每个子字符串中都包含相同数量的
'L' 和 'R' 。
示例 2：
  输入：s = "RLRRRLLRLL"
  输出：2
  解释：s 可以分割为"RL"、"RRRLLRLL"，每个子字符串中都包含相同数量的 'L'
  和 'R' 。 注意，s无法分割为 "RL"、"RR"、"RL"、"LR"、"LL" 因为第 2 个和第 5
    个子字符串不是平衡字符串。
示例 3：
  输入：s = "LLLLRRRR"
  输出：1
  解释：s 只能保持原样 "LLLLRRRR" 。 */

int balancedStringSplit(string s) {
  int cntL = 0, cntR = 0;
  int ans = 0;
  for (const char& c : s) {
    if (c == 'L') {
      cntL++;
    } else {
      cntR++;
    }
    if (cntL == cntR)
      ans++;
  }
  return ans;
}

// 贪心，局部最优为发现平衡字符串，就统计加一。
int balancedStringSplit1(string s) {
  int cnt = 0, ans = 0;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == 'L')
      cnt++;
    else
      cnt--;
    if (cnt == 0)
      ans++;
  }
  return ans;
}

int main() {
  string s1 = "RLRRLLRLRL", s2 = "RLRRRLLRLL", s3 = "LLLLRRRR";
  cout << balancedStringSplit(s1) << " " << balancedStringSplit(s2) << " "
       << balancedStringSplit(s3) << endl;
  cout << balancedStringSplit1(s1) << " " << balancedStringSplit1(s2) << " "
       << balancedStringSplit1(s3) << endl;
  return 0;
}