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
  unordered_map<string, vector<string>> umap;
  for (string str : strs) {
    string tmp = str;
    sort(tmp.begin(), tmp.end());
    umap[tmp].push_back(str);
  }
  vector<vector<string>> ans;
  for (auto i : umap)
    ans.push_back(i.second);
  return ans;
}

// 字母异位词的字母相同，仅排列不同，故其排序后字符串相等，可作为标识。故使用哈希表，先建立排序后的临时字符串，哈希表键，为该字符串标志。
// 哈希表值，为包含原始字符串的数组。之后，遍历哈希表，对每一个“值”，压入结果数组
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

void printMat(vector<vector<string>> nums) {
  for (auto row : nums) {
    for (auto i : row)
      cout << i << " , ";
    cout << "\t";
  }
  cout << endl;
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
}