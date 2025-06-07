#include "head.h"
/* 839. 相似字符串组
如果交换字符串 X 中的两个不同位置的字母，使得它和字符串 Y 相等，那么称 X 和 Y
两个字符串相似。如果这两个字符串本身是相等的，那它们也是相似的。
例如，"tars" 和 "rats" 是相似的 (交换 0 与 2 的位置)； "rats" 和 "arts"
也是相似的，但是 "star" 不与 "tars"，"rats"，或 "arts" 相似。
总之，它们通过相似性形成了两个关联组：{"tars", "rats", "arts"} 和
{"star"}。注意，"tars" 和 "arts"
是在同一组中，即使它们并不相似。形式上，对每个组而言，要确定一个单词在组中，只需要这个词和该组中至少一个单词相似。
给你一个字符串列表 strs。列表中的每个字符串都是 strs
中其它所有字符串的一个字母异位词。请问 strs 中有多少个相似字符串组？
示例 1：
  输入：strs = ["tars","rats","arts","star"]
  输出：2
示例 2：
  输入：strs = ["omv","ovm"]
  输出：1
提示：
  1 <= strs.length <= 300
  1 <= strs[i].length <= 300
  strs[i] 只包含小写字母。
  strs 中的所有单词都具有相同的长度，且是彼此的字母异位词。 */

// 每个字符串看作一个元素，两两元素间，只有两个字符相异的，才联通到一起。如此问题转化为求并查集中，有多少个联通分量
// 并查集中没必要使用字符串作为键和值，由于下标可以直接访问到元素，故直接利用下标标记联通分量即可
// 为节省时间复杂度，先判断两个字符串是否已经在同一集合。如不是，再通过check函数，检查其是否满足小于等于两个相异字符的条件，可以联通
vector<int> father;
void init(int n) {
  father.resize(n);
  iota(father.begin(), father.end(), 0);
}
int find(int u) {
  return father[u] == u ? u : father[u] = find(father[u]);
}
bool isSame(int u, int v) {
  return find(u) == find(v);
}
void join(int u, int v) {
  u = find(u);
  v = find(v);
  if (u == v)
    return;
  father[u] = v;
}
bool check(const string& s1, const string& s2) {
  int cnt = 0;
  for (int i = 0; i < s1.size(); i++) {
    cnt += s1[i] != s2[i];
    if (cnt > 2)
      return false;
  }
  return true;
}
int numSimilarGroups(vector<string>& strs) {
  init(strs.size());
  for (int i = 0; i < strs.size(); i++) {
    for (int j = i + 1; j < strs.size(); j++) {
      if (isSame(i, j))
        continue;
      if (check(strs[i], strs[j]))
        join(i, j);
    }
  }
  int ans = 0;
  for (int i = 0; i < strs.size(); i++)
    ans += father[i] == i;
  return ans;
}

int main() {
  vector<string> strs1 = {"tars", "rats", "arts", "star"},
                 strs2 = {"omv", "ovm"}, strs3 = {"abc", "abc"};
  cout << numSimilarGroups(strs1) << " " << numSimilarGroups(strs2) << " "
       << numSimilarGroups(strs3) << endl;
  return 0;
}