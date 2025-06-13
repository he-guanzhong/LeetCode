#include "head.h"
/* 567. 字符串的排列
给你两个字符串 s1 和 s2 ，写一个函数来判断 s2 是否包含 s1 的 排列。如果是，返回
true ；否则，返回 false 。
换句话说，s1 的排列之一是 s2 的 子串 。
示例 1：
  输入：s1 = "ab" s2 = "eidbaooo"
  输出：true
  解释：s2 包含 s1 的排列之一 ("ba").
示例 2：
  输入：s1= "ab" s2 = "eidboaoo"
  输出：false
提示：
  1 <= s1.length, s2.length <= 104
  s1 和 s2 仅包含小写字母 */

bool checkInclusion(string s1, string s2) {
  vector<int> ori(26, 0);
  vector<int> win(26, 0);
  if (s1.size() > s2.size())
    return false;
  for (const auto& c : s1)
    ori[c - 'a']++;
  for (int i = 0; i < s1.size(); i++)
    win[s2[i] - 'a']++;
  if (ori == win)
    return true;
  for (int i = s1.size(); i < s2.size(); i++) {
    win[s2[i - s1.size()] - 'a']--;
    win[s2[i] - 'a']++;
    if (ori == win)
      return true;
  }
  return false;
}

// 优化思路。双指针，使用一个数组记录26个字母出现次数，s1为负，s2为正。需保证窗口内部不得有正数，即不得有s2出现，但s1没有的字符
// 一旦出现正数，则向右移动左指针j，直至[j,i]区间内有负有0。此时区间长度i-j+1若恰好等与s1长度n，说明窗口匹配
bool checkInclusion1(string s1, string s2) {
  int m = s1.size(), n = s2.size();
  if (m > n)
    return false;
  int cnt[26] = {0};
  for (int i = 0; i < m; i++) {
    cnt[s1[i] - 'a']--;
  }
  int j = 0, len = 0;
  for (int i = 0; i < n; i++) {
    int x = s2[i] - 'a';
    cnt[x]++;
    while (cnt[x] > 0) {
      cnt[s2[j] - 'a']--;
      j++;
    }
    len = i - j + 1;
    if (len == m)
      return true;
  }
  return false;
}

// 滑动窗口，大小为s1的长度，窗口内为26个字母的出现频率，s1固定窗口，s2滑动，如果窗口中字母出现频率完全相同，即返回真
// 时间复杂度O(n+m+26),空间复杂度O(26)
bool checkInclusion2(string s1, string s2) {
  int m = s1.size(), n = s2.size();
  if (m > n)
    return false;
  vector<int> nums1(26, 0), nums2(26, 0);
  for (int i = 0; i < m; i++) {
    nums1[s1[i] - 'a']++;
    nums2[s2[i] - 'a']++;
  }
  if (nums1 == nums2)
    return true;
  for (int i = m; i < n; i++) {
    nums2[s2[i] - 'a']++;
    nums2[s2[i - m] - 'a']--;
    if (nums1 == nums2)
      return true;
  }
  return false;
}

int main() {
  cout << checkInclusion("ab", "eidbaooo") << " "
       << checkInclusion("ab", "eidboaoo") << " " << checkInclusion("ab", "a")
       << endl;
  cout << checkInclusion1("ab", "eidbaooo") << " "
       << checkInclusion1("ab", "eidboaoo") << " " << checkInclusion1("ab", "a")
       << endl;
  return 0;
}