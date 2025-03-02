#include "head.h"
/* LCR 169. 招式拆解 II
某套连招动作记作仅由小写字母组成的序列 arr，其中 arr[i] 第 i
个招式的名字。请返回第一个只出现一次的招式名称，如不存在请返回空格。
示例 1：
  输入：arr = "abbccdeff"
  输出：'a'
示例 2：
  输入：arr = "ccdd"
  输出：' ' */

char dismantlingAction(string arr) {
  unordered_map<char, int> umap;
  int cnt = 1;
  for (const char& c : arr) {
    umap[c]++;
  }
  char ans = ' ';
  for (auto i : arr) {
    if (umap[i] == 1) {
      return i;
    }
  }
  return ans;
}

// 出现两次和0次都无用，故可使用bool记录状态，而非int记录次数。注意，出现3次及以上的元素，均为false，故不得使用取反操作。而是count或find
// 有序哈希表，使用vector记录出现过元素，第二轮遍历不必遍历所有元素，尽遍历出现过的元素即可。
// 有序哈希表，一轮遍历统计所有元素，未出现或出现过两次为false，出现过一次为true。关系运算符==第8级，赋值运算符=第12级。故可以不加括号
// 第二轮遍历仅遍历出现过的元素即可，而不是所有元素。如此时间复杂度O(n)=2n可以缩减为n，空间复杂度O(1)，因为题目说仅包含小写26个字母
char dismantlingAction1(string arr) {
  vector<char> key;
  unordered_map<char, bool> umap;
  for (char c : arr) {
    umap[c] = umap.find(c) == umap.end();
    if (umap[c])
      key.push_back(c);
  }
  for (char c : key) {
    if (umap[c])
      return c;
  }
  return ' ';
}

int main() {
  string arr1 = "abbccdeff", arr2 = "ccdd", arr3 = "aadadaad";
  cout << dismantlingAction(arr1) << " " << dismantlingAction(arr2) << " "
       << dismantlingAction(arr3) << endl;
  cout << dismantlingAction1(arr1) << " " << dismantlingAction1(arr2) << " "
       << dismantlingAction1(arr3) << endl;

  return 0;
}