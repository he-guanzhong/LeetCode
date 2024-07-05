#include "head.h"
/* 647. 回文子串
给你一个字符串 s ，请你统计并返回这个字符串中 回文子串 的数目。
回文字符串 是正着读和倒过来读一样的字符串。
子字符串 是字符串中的由连续字符组成的一个序列。
具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。
示例 1：
  输入：s = "abc"
  输出：3
  解释：三个回文子串: "a", "b", "c"
示例 2：
  输入：s = "aaa"
  输出：6
  解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa" */

int isPalin(const string& s, int i, int j) {
  int ans = 0;
  while (i >= 0 && j < s.size() && s[i] == s[j]) {
    ans++;
    i--;
    j++;
  }
  return ans;
}
int countSubstrings(string s) {
  int ans = 0;
  for (int i = 0; i < s.size(); i++) {
    ans += isPalin(s, i, i);
    ans += isPalin(s, i, i + 1);
  }
  return ans;
}

// dp[i][j]表示以下标[i,j]的字符串是否是回文串，只有0和1两种状态。初始化二维矩阵，左上到右下斜线为1，因为一个字母必回文
// 从左下到右上遍历，j以i起始即可，不必专门初始化，s[i]两元素s[j]相等，如果相差为0或1或2，则必回文，如果相差较大，需看[i+1,j-1]是否回文
// 统计回文出现的次数，返回。空间复杂度n^2太高，考虑双指针法。空间复杂度O(n)=1
// 对每一个元素，沿左右拓展，遇到边界或不等就停止，返回检验到的回文数。对相邻元素相等例子，如abbc，则需传入[i,i+1]双起点

// dp[i][j]并不代表以i开始j结尾的回文子串数，而代表i开始j结束是否为回文子串。故全部初始化为false，额外使用result计数回文子串数
// 当发现子串首位相等，即s[i]==s[j]时，分三种情况，1.只有一个字母，为真；2.两个字母，为真；3.三个字母，为真；4.三个字母以上，看dp[i+1][j-1]即更小子串结果
// 因此，遍历顺序必为从坐下至右上。最终返回值，即为计数的回文子串数
int countSubstrings1(string s) {
  vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
  int result = 0;
  for (int i = s.size() - 1; i >= 0; i--) {
    for (int j = i; j < s.size(); j++) {
      if (s[i] == s[j]) {
        if (j - i <= 1) {
          dp[i][j] = true;
          result++;
        } else if (dp[i + 1][j - 1]) {
          dp[i][j] = true;
          result++;
        }
      }
    }
  }
  return result;
}
int countSubstrings2(string s) {
  vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));
  int result = 0;
  for (int i = s.size() - 1; i >= 0; i--) {
    for (int j = i; j < s.size(); j++) {
      if (s[i] == s[j] && (j - i <= 2 || dp[i + 1][j - 1])) {
        dp[i][j] = true;
        result++;
      }
    }
  }
  return result;
}

// 双指针法，确定回文子串起始点，可以单起始点，可以双起始点，如果满足条件即新增回文子串数。
// 注意拓展方向，起始点i--，终止点j++，时间复杂度O(n) = n^2，空间复杂度O(1)
int extend3(const string& s, int i, int j, int n) {
  int res = 0;
  while (i >= 0 && j < n && s[i] == s[j]) {
    i--;
    j++;
    res++;
  }
  return res;
}
int countSubstrings3(string s) {
  int result = 0;
  for (int i = 0; i < s.size(); i++) {
    result += extend3(s, i, i, s.size());
    result += extend3(s, i, i + 1, s.size());
  }
  return result;
}

int main() {
  string s1 = "abc", s2 = "aaa";
  string s3 = "intention", s4 = "execution";
  cout << countSubstrings(s1) << " " << countSubstrings(s2) << " "
       << countSubstrings(s3) << " " << countSubstrings(s4) << endl;
  cout << countSubstrings1(s1) << " " << countSubstrings1(s2) << " "
       << countSubstrings1(s3) << " " << countSubstrings1(s4) << endl;
  return 0;
}