#include "head.h"
/* 3. 无重复字符的最长子串
给定一个字符串 s ，请你找出其中不含有重复字符的 最长子串 的长度。
示例 1:
输入: s = "abcabcbb"
输出: 3
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
示例 2:
输入: s = "bbbbb"
输出: 1
解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
输入: s = "pwwkew"
输出: 3
解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
     请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。  */

int lengthOfLongestSubstring(string s) {
  unordered_set<char> uset;
  int ans = 0;
  int j = 0;
  for (int i = 0; i < s.size(); i++) {
    while (uset.count(s[i])) {
      uset.erase(s[j]);
      j++;
    }
    uset.insert(s[i]);
    ans = max(ans, i - j + 1);
  }
  return ans;
}

// 滑动窗口，核心是保证窗口内uset内无重复元素。遍历控制右指针i，并将元素加入uset。
// 只要新s[i]出现过在uset内，就不断弹出左指针元素j，并移动左指针,直至uset内没有新s[i]为止。
int lengthOfLongestSubstring1(string s) {
  unordered_set<char> uset;
  int j = 0;
  int result = 0;
  for (int i = 0; i < s.size(); i++) {
    while (uset.find(s[i]) != uset.end()) {
      uset.erase(s[j]);
      j++;
    }
    result = max(result, i - j + 1);
    uset.insert(s[i]);
  }
  return result;
}

int main() {
  string temp1 = "abcabcbb", temp2 = "bbbbb", temp3 = "pwwkew", temp4 = "au",
         temp5 = "";
  cout << lengthOfLongestSubstring(temp1) << " "
       << lengthOfLongestSubstring(temp2) << " "
       << lengthOfLongestSubstring(temp3) << " "
       << lengthOfLongestSubstring(temp4) << " "
       << lengthOfLongestSubstring(temp5) << " " << endl;
  cout << lengthOfLongestSubstring1(temp1) << " "
       << lengthOfLongestSubstring1(temp2) << " "
       << lengthOfLongestSubstring1(temp3) << " "
       << lengthOfLongestSubstring1(temp4) << " "
       << lengthOfLongestSubstring1(temp5) << " " << endl;
  return 0;
}