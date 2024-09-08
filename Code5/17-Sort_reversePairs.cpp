#include "head.h"
/* LCR 170. 交易逆序对的总数
在股票交易中，如果前一天的股价高于后一天的股价，则可以认为存在一个「交易逆序对」。
请设计一个程序，输入一段时间内的股票交易记录
record，返回其中存在的「交易逆序对」总数。
示例 1:
  输入：record = [9, 7, 5, 4, 6]
  输出：8
  解释：交易中的逆序对为 (9, 7), (9, 5), (9, 4), (9, 6), (7, 5), (7, 4), (7, 6),
    (5, 4)。
限制：
  0 <= record.length <= 50000 */

int helper(vector<int>& record, int l, int r, vector<int>& vec) {
  if (l >= r)
    return 0;
  int m = l + ((r - l) >> 1);
  int ans = helper(record, l, m, vec) + helper(record, m + 1, r, vec);
  int i = l, j = m + 1;
  for (int k = l; k <= r; k++)
    vec[k] = record[k];
  for (int k = l; k <= r; k++) {
    if (i == m + 1)
      record[k] = vec[j++];
    else if (j == r + 1)
      record[k] = vec[i++];
    else if (vec[i] <= vec[j])
      record[k] = vec[i++];
    else {
      record[k] = vec[j++];
      ans += m + 1 - i;
    }
  }
  return ans;
}
int reversePairs(vector<int>& record) {
  vector<int> vec(record.size());
  return helper(record, 0, record.size() - 1, vec);
}

// 不用使用普通方法，否则时间超限。设置分治排序函数，退出条件是左边界大于等于右边界，即只有一个元素。额外使用tmp记录原始record信息
// 对原始record改记录排序后信息，使用l和r的中间点m，切割数组。两半起点分别为i,j。以k，先使用tmp记录record原始数据。在左右两端[i,j]起始。
// 若i或j任意到达改半截数组的右边界，则对直接对另一赋值。若左半i小于等于右半j，不构成逆序对，直接将左半填入，
// 若左半i大于右半j，则填右半信息，并更新逆序数对。左侧总计m+1个元素，大于等于下标为i的m-i+1个
int mergeSort1(vector<int>& record, int l, int r, vector<int>& tmp) {
  if (l >= r)
    return 0;
  int m = (r + l) / 2;
  int ans = mergeSort1(record, l, m, tmp) + mergeSort1(record, m + 1, r, tmp);
  for (int k = l; k <= r; k++)
    tmp[k] = record[k];
  int i = l, j = m + 1;
  for (int k = l; k <= r; k++) {
    if (i == m + 1)
      record[k] = tmp[j++];
    else if (j == r + 1)
      record[k] = tmp[i++];
    else if (tmp[i] <= tmp[j])
      record[k] = tmp[i++];
    else {
      record[k] = tmp[j++];
      ans += m + 1 - i;
    }
  }
  return ans;
}
int reversePairs1(vector<int>& record) {
  vector<int> tmp(record.size(), 0);
  return mergeSort1(record, 0, record.size() - 1, tmp);
}

int main() {
  vector<int> record1 = {9, 7, 5, 4, 6}, record2 = {1};
  cout << reversePairs(record1) << " " << reversePairs(record2) << endl;
  record1 = {9, 7, 5, 4, 6}, record2 = {1};
  cout << reversePairs1(record1) << " " << reversePairs(record2) << endl;

  return 0;
}