#include "head.h"
/* 763. 划分字母区间
给你一个字符串s。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。
注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 s 。
返回一个表示每个字符串片段的长度的列表。
示例 1：
输入：s = "ababcbacadefegdehijhklij"
输出：[9,7,8]
解释：
划分结果为 "ababcbaca"、"defegde"、"hijhklij" 。
每个字母最多出现在一个片段中。
像 "ababcbacadefegde", "hijhklij" 这样的划分是错误的，因为划分的片段数较少。
示例 2：
输入：s = "eccbbbbdec"
输出：[10] */

// 一轮遍历，数组记录每个字母出现的最远下标。二轮遍历，子串长度计算需要左右节点，左节点可初始化为-1，简便长度计算。
// 更新每个字符的最远下标，若当前下标遇到最远下标，此即为右分割点，更新左分割点为当前下标+1
vector<int> partitionLabels(string s) {
  int tmp[26] = {0};
  for (int i = 0; i < s.size(); i++) {
    tmp[s[i] - 'a'] = i;
  }
  vector<int> result;
  int index = 0;
  int pre = -1;
  for (int i = 0; i < s.size(); i++) {
    index = max(index, tmp[s[i] - 'a']);
    if (index == i) {
      result.push_back(i - pre);
      pre = index;
    }
  }
  return result;
}

// 数组hash记录每个字母出现的最晚位置，hash[s[i] - 'a']表达了字母的映射
// 从头遍历，更新字符的最远出现位置下标。如果当前下标等于最远出现位置下标，此即为分割点
vector<int> partitionLabels1(string s) {
  int hash[26] = {0};
  for (int i = 0; i < s.size(); i++)
    hash[s[i] - 'a'] = i;
  int left = 0, right = 0;
  vector<int> result;
  for (int i = 0; i < s.size(); i++) {
    right = max(right, hash[s[i] - 'a']);
    if (i == right) {
      result.push_back(right - left + 1);
      left = i + 1;
    }
  }
  return result;
}
int main() {
  string s1 = "ababcbacadefegdehijhklij";
  string s2 = "eccbbbbdec";
  printVector(partitionLabels(s1));
  printVector(partitionLabels(s2));
  printVector(partitionLabels1(s1));
  printVector(partitionLabels1(s2));
  return 0;
}