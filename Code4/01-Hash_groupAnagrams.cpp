#include "head.h"
/* 49. 字母异位词分组
给你一个字符串数组，请你将 字母异位词 组合在一起。可以按任意顺序返回结果列表。
字母异位词 是由重新排列源单词的所有字母得到的一个新单词。
示例 1:
  输入: strs = ["eat", "tea", "tan", "ate", "nat", "bat"]
  输出: [["bat"],["nat","tan"],["ate","eat","tea"]]
示例 2:
  输入: strs = [""]
  输出: [[""]]
示例 3:
  输入: strs = ["a"]
  输出: [["a"]]
提示：
    1 <= strs.length <= 104
    0 <= strs[i].length <= 100
    strs[i] 仅包含小写字母 */

vector<vector<string>> groupAnagrams(vector<string>& strs) {
  vector<vector<string>> ans;
  unordered_map<string, vector<string>> umap;
  for (string str : strs) {
    string tmp = str;
    sort(tmp.begin(), tmp.end());
    umap[tmp].push_back(str);
  }
  for (pair<string, vector<string>> i : umap) {
    ans.push_back(i.second);
  }
  return ans;
}

// 字母异位词是否同组，取决于其字母和数量是否严格相等。方法一可以通过哈希表map判断，方法二可以通过重新排序后字符串相等判断
// 整体哈希表的键，为该组字符串的特殊标识。然而，umap的键不能是另一个umap，故只能使用方法二，利用排序后的临时字符串作为键key
// 哈希表值val，为该组下的所有原始字符串。一次遍历，得到整体哈希表。二次遍历整体哈希表，收集每一个“值”压入数组即可作为结果
vector<vector<string>> groupAnagrams1(vector<string>& strs) {
  vector<vector<string>> result;
  unordered_map<string, vector<string>> umap;
  for (string str : strs) {
    string key = str;
    sort(key.begin(), key.end());
    umap[key].emplace_back(str);
  }
  for (auto it = umap.begin(); it != umap.end(); it++) {
    result.push_back(it->second);
  }
  return result;
}

int main() {
  vector<string> temp1 = {"eat", "tea", "tan", "ate", "nat", "bat"},
                 temp2 = {""}, temp3 = {"a"};
  printMat(groupAnagrams(temp1));
  printMat(groupAnagrams(temp2));
  printMat(groupAnagrams(temp3));
  printMat(groupAnagrams1(temp1));
  printMat(groupAnagrams1(temp2));
  printMat(groupAnagrams1(temp3));
  return 0;
}