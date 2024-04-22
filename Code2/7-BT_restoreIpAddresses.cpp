#include "head.h"
/* 93. 复原 IP 地址
有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导
0），整数之间用 '.' 分隔。

    例如："0.1.2.201" 和 "192.168.1.1" 是 有效 IP 地址，但是
"0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效 IP 地址。
示例 3：
输入：s = "101023"
输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]

给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能的有效 IP
地址，这些地址可以通过在 s 中插入 '.' 来形成。你 不能 重新排序或删除 s
中的任何数字。你可以按 任何 顺序返回答案。 */

// 点数作为退出条件，3个即止，停止时判断剩余字符串是否有效，有效则压入结果。
// 如果区间[start，i]有效，则接在原字符串上插入、删除操作“.”。位置为i+1。下一深度搜索回溯从i+2开始
// 判断字符串是否有效，则一看是否不合法，二看首字符是否为0，三看转化后的数字是否大于255。注意此处不能用stoi
bool isValid(string s, int start, int end) {
  if (start > end)
    return false;
  if (s[start] == '0' && end != start)
    return false;
  if (start < 0 || end >= s.size())
    return false;
  int num = 0;
  while (end >= start) {
    num *= 10;
    num += s[start] - '0';
    start++;
    if (num > 255)
      return false;
  }
  // num= stoi(s.substr(start, end - start + 1)); 不能stoi因为超出范围
  return true;
}
vector<string> result;
void backtracking(string s, int start, int cnt) {
  if (cnt == 0) {
    if (isValid(s, start, s.size() - 1))
      result.push_back(s);
    return;
  }
  for (int i = start; i < s.size(); i++) {
    if (isValid(s, start, i))
      s.insert(s.begin() + i + 1, '.');
    else
      continue;
    backtracking(s, i + 2, cnt - 1);
    s.erase(s.begin() + i + 1);
  }
}
vector<string> restoreIpAddresses(string s) {
  result.clear();
  backtracking(s, 0, 3);
  return result;
}

// 直接在原字符串内添加或删除逗点，并判断合不合法。不合法三种情况，首字符0，出现异常字符，总数大于255
// 终止条件是点符号有3个，因为最多就切四段，此时判断，如剩余符合条件则压入结果
// 横向搜索时，必须符合条件，才继续横向搜索。否则退出，直接在原字符串中i+1位置insert'.'，回溯时erase
bool isValid1(const string& s, int start, int end) {
  if (start > end)
    return false;
  if (s[start] == '0' && start != end)
    return false;
  int num = 0;
  for (int i = start; i <= end; i++) {  // 集成到一遍循环
    if (s[i] < '0' || s[i] > '9')
      return false;
    num = num * 10 + (s[i] - '0');  // 字符转整型数字
    if (num > 255)
      return false;
  }
  // num = stoi(s.substr(start, end - start + 1));
  return true;
}
vector<string> result1;
void backtracking1(string s, int startIndex, int pointNum) {
  if (pointNum == 3) {
    if (isValid1(s, startIndex, s.size() - 1))
      result1.push_back(s);
    return;
  }
  for (int i = startIndex; i < s.size(); i++) {
    if (isValid1(s, startIndex, i)) {  // [startIndex, i]是否合法
      s.insert(s.begin() + i + 1, '.');
      pointNum++;
      backtracking1(s, i + 2, pointNum);  // 因为加了一个'.'
      s.erase(s.begin() + i + 1);
      pointNum--;
    } else
      break;
  }
}
vector<string> restoreIpAddresses1(string s) {
  result1.clear();
  if (s.size() < 4 || s.size() > 12)  // 剪支操作
    return result1;
  backtracking1(s, 0, 0);
  return result1;
}

void printMat(vector<string> res) {
  for_each(res.begin(), res.end(),
           [](const auto& val) { cout << val << "\t"; });
  cout << endl;
}
int main() {
  string s1 = "25525511135";
  string s2 = "0000";
  string s3 = "101023";
  printMat(restoreIpAddresses(s1));
  printMat(restoreIpAddresses(s2));
  printMat(restoreIpAddresses(s3));
  printMat(restoreIpAddresses1(s1));
  printMat(restoreIpAddresses1(s2));
  printMat(restoreIpAddresses1(s3));
  return 0;
}
