#include "head.h"
/* 242. 有效的字母异位词
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。
示例 1:
输入: s = "anagram", t = "nagaram"
输出: true
示例 2:
输入: s = "rat", t = "car"
输出: false
提示:
    1 <= s.length, t.length <= 5 * 104
    s 和 t 仅包含小写字母
进阶: 如果输入字符串包含unicode字符怎么办？你能否调整你的解法来应对这种情况？*/

bool isAnagram(string s, string t) {
  int arr[26] = {0};
  for (char c : t)
    arr[c - 'a']++;
  for (char c : s)
    arr[c - 'a']--;
  for (int i : arr) {
    if (i != 0)
      return false;
  }
  return true;
}

// 数组当作哈希表，因为26个字母是有限的。核心判断条件，s和t分别遍历一遍后，每个字母位出现的次数是否为0。大于或者小于0都是不允许的。
// 数组当哈希表，26个字母构成连续空间。s出现的字母++，t出现的字母--，查看是否存在非零值
bool isAnagram1(string s, string t) {
  int record[26] = {0};
  for (int i = 0; i < s.size(); i++)
    record[s[i] - 'a']++;
  for (int i = 0; i < t.size(); i++)
    record[t[i] - 'a']--;
  for (int i = 0; i < 26; i++) {
    if (record[i] != 0)
      return false;
  }
  return true;
}
bool isAnagram2(string s, string t) {
  unordered_map<char, int> hash;
  for (auto i : s)
    hash[i]++;
  for (auto i : t)
    hash[i]--;
  for (auto it = hash.begin(); it != hash.end(); it++) {
    if (it->second != 0)
      return false;
  }
  return true;
}

int main() {
  string s1 = "anagram", s2 = "nagaram", s3 = "rat", s4 = "car";
  cout << isAnagram(s1, s2) << " " << isAnagram(s3, s4) << endl;
  cout << isAnagram1(s1, s2) << " " << isAnagram1(s3, s4) << endl;
  return 0;
}