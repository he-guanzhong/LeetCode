#include "head.h"
/* LCR 120. 寻找文件副本
设备中存有 n 个文件，文件 id 记于数组 documents。若文件 id
相同，则定义为该文件存在副本。请返回任一存在副本的文件 id。
示例 1：
  输入：documents = [2, 5, 3, 0, 5, 0]
  输出：0 或 5
提示：
    0 ≤ documents[i] ≤ n-1
    2 <= n <= 100000 */

int findRepeatDocument(vector<int>& documents) {
  for (int i = 0; i < documents.size(); i++) {
    while (documents[i] != i) {
      if (documents[i] == documents[documents[i]])
        return documents[i];
      swap(documents[i], documents[documents[i]]);
    }
  }
  return 0;
}

// 原地交换，长度n数组内元素范围[0,n-1]，说明数值与下标存在对应关系。下标i理应对应doc[i]。如果相等说明已经占位，跳过此轮并i++
// 如果doc[i]索引的位置，已经被doc[i]占据，说明doc[i]多余，直接返回。其余情况，交换doc[i]与其所指元素。
// 时间复杂度O(n)，空间复杂度O(1)，比传统哈希表法O(n)节省了空间复杂度
int findRepeatDocument1(vector<int>& documents) {
  int i = 0;
  while (i < documents.size()) {
    if (documents[i] == i) {
      i++;
      continue;
    }
    if (documents[documents[i]] == documents[i])
      return documents[i];
    swap(documents[i], documents[documents[i]]);
  }
  return -1;
}

int main() {
  vector<int> doc1 = {2, 5, 3, 0, 5, 0},
              doc2 = {0, 1, 2, 3, 4, 11, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15},
              doc3 = {1, 0, 1, 4, 2, 5, 3};
  cout << findRepeatDocument(doc1) << " " << findRepeatDocument(doc2) << " "
       << findRepeatDocument(doc3) << endl;
  cout << findRepeatDocument1(doc1) << " " << findRepeatDocument1(doc2) << " "
       << findRepeatDocument1(doc3) << endl;

  return 0;
}