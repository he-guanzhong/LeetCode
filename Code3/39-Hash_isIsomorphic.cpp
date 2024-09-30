#include "head.h"
/* 205. 同构字符串
给定两个字符串 s 和 t ，判断它们是否是同构的。
如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。
每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。
示例 1:
  输入：s = "egg", t = "add"
  输出：true
示例 2：
  输入：s = "foo", t = "bar"
  输出：false
示例 3：
  输入：s = "paper", t = "title"
  输出：true
提示：
    1 <= s.length <= 5 * 104
    t.length == s.length
    s 和 t 由任意有效的 ASCII 字符组成 */

bool isIsomorphic(string s, string t) {
  unordered_map<char, char> umap1, umap2;
  for (int i = 0; i < s.size(); i++) {
    umap1[s[i]] = t[i];
    umap2[t[i]] = s[i];
  }
  string s1 = s, t1 = t;
  for (int i = 0; i < s.size(); i++) {
    s1[i] = umap1[s[i]];
    t1[i] = umap2[t[i]];
  }
  return s1 == t && s == t1;
}

// 每个字符都得映射另一字符，说明满射。不同字符不能映射到同一字符，说明单射。同时满足二者条件，双射代表一一对应。
// 两个哈希表，维护t和s之间映射关系。如发现映射关系不匹配，即返回false。全部通过，返回true
bool isIsomorphic1(string s, string t) {
  unordered_map<char, char> s2t;
  unordered_map<char, char> t2s;
  for (int i = 0; i < s.size(); i++) {
    if (s2t.find(s[i]) == s2t.end())  // 没出现过
      s2t[s[i]] = t[i];
    if (t2s.find(t[i]) == t2s.end())
      t2s[t[i]] = s[i];
    if (s2t[s[i]] != t[i] || t2s[t[i]] != s[i])
      return false;
  }
  return true;
}

// 自做法
bool isIsomorphic2(string s, string t) {
  string tmp = s;
  unordered_map<char, char> umap;
  unordered_set<char> uset;
  for (int i = 0; i < s.size(); i++) {
    if (umap.find(s[i]) == umap.end() && uset.find(t[i]) != uset.end())
      return false;
    uset.insert(t[i]);
    umap[s[i]] = t[i];
  }
  for (int i = 0; i < s.size(); i++)
    tmp[i] = umap[s[i]];
  return tmp == t;
}

int main() {
  string s1 = "egg", t1 = "add";
  string s2 = "foo", t2 = "bar";
  string s3 = "paper", t3 = "title";
  string s4 = "badc", t4 = "baba";
  cout << isIsomorphic(s1, t1) << " " << isIsomorphic(s2, t2) << " "
       << isIsomorphic(s3, t3) << " " << isIsomorphic(s4, t4) << endl;
  cout << isIsomorphic1(s1, t1) << " " << isIsomorphic1(s2, t2) << " "
       << isIsomorphic1(s3, t3) << " " << isIsomorphic1(s4, t4) << endl;
  return 0;
}