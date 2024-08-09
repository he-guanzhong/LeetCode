#include "head.h"
/* 76. 最小覆盖子串
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s
中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
注意：
    对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
    如果 s 中存在这样的子串，我们保证它是唯一的答案。
示例 1：
  输入：s = "ADOBECODEBANC", t = "ABC"
  输出："BANC"
  解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
示例 2：
  输入：s = "a", t = "a"
  输出："a"
  解释：整个字符串 s 是最小覆盖子串。
示例 3:
  输入: s = "a", t = "aa"
  输出: ""
  解释: t 中两个字符 'a' 均应包含在 s 的子串中，
    因此没有符合条件的子字符串，返回空字符串。 */

bool isCover(unordered_map<char, int>& smap, unordered_map<char, int>& tmap) {
  for (auto t : tmap) {
    if (smap[t.first] < t.second)
      return false;
  }
  return true;
}
string minWindow(string s, string t) {
  unordered_map<char, int> tmap;
  for (char c : t)
    tmap[c]++;
  unordered_map<char, int> smap;
  int j = 0, len = INT_MAX, index = 0;
  for (int i = 0; i < s.size(); i++) {
    smap[s[i]]++;
    while (isCover(smap, tmap)) {
      if (i - j + 1 < len) {
        len = i - j + 1;
        index = j;
      }
      if (--smap[s[j]] == 0)
        smap.erase(s[j]);
      j++;
    }
  }
  return len == INT_MAX ? "" : s.substr(index, len);
}

// 判断函数，对于origin内每个元素，检测其数量是否大于滑动窗口中元素数量。是即为假，左指针可以不移动了
// 双哈希表记录每个字母及其出现次数，一个表为t，记为ori，一个表为s内窗口，记为cnt。先填充ori表。初始化left、right=-1两个变量。
unordered_map<char, int> origin, window;
bool check1() {
  for (const auto& i : origin) {  // origin中每个元素，如果其数量大于了滑动窗口
    if (i.second > window[i.first])
      return false;
  }
  return true;
}
string minWindow1(string s, string t) {
  for (const char& c : t) {
    origin[c]++;
  }
  int left = 0, right = -1;      // 右指针初始一定要-1
  int len = INT_MAX, ansL = -1;  // ansR无用，因为需要的是子串长度
  while (right < (int)s.size()) {
    if (origin.find(s[++right]) !=
        origin.end())  // 右指针遍历到的元素，属于t内的核心元素
      window[s[right]]++;  // 窗口内右指针元素数量加一
    while (check1() && left <= right) {  // 窗口内存在元素，注意左右指针可以相等
      if (right - left + 1 < len) {  // 总长度小于之前记录长度，更新最短下标
        ansL = left;
        len = right - left + 1;
      }
      if (origin.find(s[left]) !=
          origin.end())  // 滑动窗口左指针要弹出的元素，是核心元素
        window[s[left]]--;  // 核心元素数量减一
      left++;  // 无论左指针是否合适核心元素，都必须弹出
    }
  }
  return ansL == -1 ? string() : s.substr(ansL, len);
}

int main() {
  string s1 = "ADOBECODEBANC", t1 = "ABC", s2 = "a", t2 = "a", s3 = "a",
         t3 = "aa";
  cout << minWindow(s1, t1) << " " << minWindow(s2, t2) << " "
       << minWindow(s3, t3) << endl;
  cout << minWindow1(s1, t1) << " " << minWindow1(s2, t2) << " "
       << minWindow1(s3, t3) << endl;
  return 0;
}