#include "head.h"
/* 399. 除法求值
给你一个变量对数组 equations 和一个实数值数组 values 作为已知条件，其中
equations{i] = [Ai, Bi] 和 values[i] 共同表示等式 Ai / Bi = values[i] 。每个 Ai
或 Bi 是一个表示单个变量的字符串。
另有一些以数组 queries 表示的问题，其中 queries[j] = [Cj, Dj] 表示第 j
个问题，请你根据已知条件找出 Cj / Dj = ? 的结果作为答案。
返回 所有问题的答案 。如果存在某个无法确定的答案，则用 -1.0
替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 -1.0
替代这个答案。
注意：输入总是有效的。你可以假设除法运算中不会出现除数为 0
的情况，且不存在任何矛盾的结果。
注意：未在等式列表中出现的变量是未定义的，因此无法确定它们的答案。
示例 1：
  输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries =
    [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
  输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
  解释：
  条件：a / b = 2.0, b / c = 3.0
  问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
  结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
  注意：x 是未定义的 => -1.0
示例 2：
  输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0],
    queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
  输出：[3.75000,0.40000,5.00000,0.20000]
示例 3：
  输入：equations = [["a","b"]], values = [0.5], queries =
    [["a","b"],["b","a"],["a","c"],["x","y"]]
  输出：[0.50000,2.00000,-1.00000,-1.00000] */

bool dfs(const string& cur,
         const string& dest,
         unordered_map<string, vector<pair<string, double>>>& umap,
         unordered_map<string, bool>& visited,
         double& val) {
  if (umap.count(cur) == 0)
    return false;
  if (cur == dest)
    return true;
  visited[cur] = true;
  for (int i = 0; i < umap[cur].size(); i++) {
    string next = umap[cur][i].first;
    double num = umap[cur][i].second;
    if (visited[next] == true || umap.count(next) == 0)
      continue;
    val *= num;
    if (dfs(next, dest, umap, visited, val))
      return true;
    val /= num;
  }
  visited[cur] = false;
  return false;
}
vector<double> calcEquation(vector<vector<string>>& equations,
                            vector<double>& values,
                            vector<vector<string>>& queries) {
  unordered_map<string, vector<pair<string, double>>> umap;
  for (int i = 0; i < equations.size(); i++) {
    umap[equations[i][0]].push_back({equations[i][1], values[i]});
    umap[equations[i][1]].push_back({equations[i][0], 1.0 / values[i]});
  }

  vector<double> ans;
  for (int i = 0; i < queries.size(); i++) {
    unordered_map<string, bool> visited;
    double path = 1.0;
    if (dfs(queries[i][0], queries[i][1], umap, visited, path))
      ans.push_back(path);
    else
      ans.push_back(-1.0);
  }
  return ans;
}

// 构造无向图g保存以字符串a起始,到b/c等若干结点，及其权重。为避免死循环，设置visite数组，保存该结点a是否被遍历过
// 遍历所有equations现有条件，双向构造图。设置found变量为已找到最终结点。对每一个结果数组queries遍历。
// 如果queries首元素找不到，直接压-1，首元素有，设置已访问，并进入递归。dfs函数引入图、已访问、起点值，目标值，该路径上乘积，是否找到found
// dfs函数，如果该轮已经found为真，直接返回。如果找到了最终结果，压入结果返回。剩余图中找不到的情况，依次为准遍历下一层。
// 注意如果visited以访问，不进入下一层。另，不能在内部压入-1，因为这只是一条支路的结果。
void dfs1(unordered_map<string, vector<pair<string, double>>>& g,
          unordered_map<string, bool>& visited,
          string cur,
          string target,
          double path,
          bool& found,
          vector<double>& ans) {
  if (found)  // 已经找到不在搜索
    return;
  if (cur == target) {
    found = true;
    ans.push_back(path);
    return;
  }

  for (int i = 0; i < g[cur].size(); i++) {
    auto next = g[cur][i];
    if (visited[next.first])
      continue;
    visited[next.first] = true;
    dfs1(g, visited, next.first, target, path * next.second, found, ans);
    visited[next.first] = false;
  }
}

vector<double> calcEquation1(vector<vector<string>>& equations,
                             vector<double>& values,
                             vector<vector<string>>& queries) {
  vector<double> ans;
  unordered_map<string, vector<pair<string, double>>> g;
  unordered_map<string, bool> visited;
  for (int i = 0; i < equations.size(); i++) {
    g[equations[i][0]].push_back(make_pair(equations[i][1], values[i]));
    g[equations[i][1]].push_back(make_pair(equations[i][0], 1.0 / values[i]));
  }

  for (int i = 0; i < queries.size(); i++) {
    if (g.find(queries[i][0]) == g.end()) {
      ans.push_back(-1);
      continue;
    }
    bool found = false;
    visited[queries[i][0]] = true;
    dfs1(g, visited, queries[i][0], queries[i][1], 1, found, ans);
    visited[queries[i][0]] = false;
    if (!found)
      ans.push_back(-1);
  }
  return ans;
}

int main() {
  vector<vector<string>> equations1 = {{"a", "b"}, {"b", "c"}};
  vector<double> values1 = {2.0, 3.0};
  vector<vector<string>> queries1 = {
      {"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
  vector<vector<string>> equations2 = {{"a", "b"}, {"b", "c"}, {"bc", "cd"}};
  vector<double> values2 = {1.5, 2.5, 5.0};
  vector<vector<string>> queries2 = {
      {"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}};
  vector<vector<string>> equations3 = {{"a", "b"}};
  vector<double> values3 = {0.5};
  vector<vector<string>> queries3 = {
      {"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}};
  printVector(calcEquation(equations1, values1, queries1));
  printVector(calcEquation(equations2, values2, queries2));
  printVector(calcEquation(equations3, values3, queries3));
  printVector(calcEquation1(equations1, values1, queries1));
  printVector(calcEquation1(equations2, values2, queries2));
  printVector(calcEquation1(equations3, values3, queries3));
  return 0;
}