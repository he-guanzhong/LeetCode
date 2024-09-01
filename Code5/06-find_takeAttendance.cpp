#include "head.h"
/* LCR 173. 点名
某班级 n 位同学的学号为 0 ~ n-1。点名结果记录于升序数组
records。假定仅有一位同学缺席，请返回他的学号。
示例 1:
  输入: records = [0,1,2,3,5]
  输出: 4
示例 2:
  输入: records = [0, 1, 2, 3, 4, 5, 6, 8]
  输出: 7
提示：
1 <= records.length <= 10000 */

int takeAttendance(vector<int>& records) {
  int l = 0, r = records.size() - 1;
  while (l <= r) {
    int m = l + ((r - l) >> 1);
    if (records[m] <= m) {
      l = m + 1;
    } else {
      r = m - 1;
    }
  }
  return l;
}

// 有序数组，采用二分法。数组处于闭区间[0,m]。左半段下标与数值相等，右半段下标与数值不等
// 对于某下标i，若nums[i]==i，右半段起始点必位于[i+1,m],left向右收紧。若nums[i]!=i，做半段终止点必位于[0,i-1]，right向左收紧
// left代表右半段第一个元素，right代表左半段最后一个元素。最终返回的left，右半段第一个元素下标，即缺失的数字
// 时间复杂度O(logn)，空间复杂度O(1)
int takeAttendance1(vector<int>& records) {
  int l = 0, r = records.size() - 1;
  while (l <= r) {
    int mid = l + ((r - l) >> 1);
    if (records[mid] == mid)
      l = mid + 1;
    else
      r = mid - 1;
  }
  return l;
}

int main() {
  vector<int> doc1 = {0, 1, 2, 3, 5}, doc2 = {0, 1, 2, 3, 4, 5, 6, 8},
              doc3 = {0};

  cout << takeAttendance(doc1) << " " << takeAttendance(doc2) << " "
       << takeAttendance(doc3) << endl;
  cout << takeAttendance1(doc1) << " " << takeAttendance1(doc2) << " "
       << takeAttendance1(doc3) << endl;

  return 0;
}