#include <ctime>
#include "head.h"
/* 528. 按权重随机选择
给你一个 下标从 0 开始 的正整数数组 w ，其中 w[i] 代表第 i 个下标的权重。
请你实现一个函数 pickIndex ，它可以 随机地 从范围 [0, w.length - 1] 内（含 0 和
w.length - 1）选出并返回一个下标。选取下标 i 的 概率 为 w[i] / sum(w) 。
例如，对于 w = [1, 3]，挑选下标 0 的概率为 1 / (1 + 3) = 0.25
（即，25%），而选取下标 1 的概率为 3 / (1 + 3) = 0.75（即，75%）。
示例 1：
  输入：
    ["Solution","pickIndex"]
    [[[1]],[]]
  输出：
    [null,0]
  解释：
    Solution solution = new Solution([1]);
    solution.pickIndex(); // 返回
    0，因为数组中只有一个元素，所以唯一的选择是返回下标 0。
示例 2：
  输入：
    ["Solution","pickIndex","pickIndex","pickIndex","pickIndex","pickIndex"]
    [[[1,3]],[],[],[],[],[]]
  输出：
    [null,1,1,1,1,0]
  解释：
    Solution solution = new Solution([1, 3]);
    solution.pickIndex(); // 返回 1，返回下标 1，返回该下标概率为 3/4 。
    solution.pickIndex(); // 返回 1
    solution.pickIndex(); // 返回 1
    solution.pickIndex(); // 返回 1
    solution.pickIndex(); // 返回 0，返回下标 0，返回该下标概率为 1/4 。
    由于这是一个随机问题，允许多个答案，因此下列输出都可以被认为是正确的:
    [null,1,1,1,1,0]
    [null,1,1,1,1,1]
    [null,1,1,1,0,0]
    [null,1,1,1,0,1]
    [null,1,0,1,0,0]
    ......
    诸若此类。
提示：
  1 <= w.length <= 104
  1 <= w[i] <= 105
  pickIndex 将被调用不超过 104 次 */

class Solution {
 public:
  Solution(vector<int>& w) {
    srand(time(nullptr));
    arr.resize(w.size());
    int pre = 0;
    for (int i = 0; i < w.size(); i++) {
      arr[i] = pre + w[i];
      pre = arr[i];
    }
  }

  int pickIndex() {
    int index = rand() % arr.back();
    return upper_bound(arr.begin(), arr.end(), index) - arr.begin();
  }
  vector<int> arr;
};

// 前缀和+二分法。w数组所有元素和n代表总概率1，则对w[i]代表答案是下标i时，落概率w[i]/n
// 利用partial_sum()库函数求前缀和数组，注意back_inserter()尾插标记。如此，落在i的概率是(prefix[i]-prefix[i-1])/n
// 对于随机数x=rand()%n，其范围[0,n-1]。用二分法求出第一个比他大的位置upper_bound()，对应下标即为结果
// 必须使用back_inserter()创建插入迭代器，因为arr为空，其arr.begin()和arr.end()均为无效
class Solution1 {
 public:
  Solution1(vector<int>& w) {
    partial_sum(w.begin(), w.end(), back_inserter(prefixSum));
    srand(time(nullptr));
  }

  int pickIndex() {
    int num = rand() % prefixSum.back();
    return upper_bound(prefixSum.begin(), prefixSum.end(), num) -
           prefixSum.begin();
  }
  vector<int> prefixSum;
};

int main() {
  vector<int> vec1 = {1}, vec2 = {1, 3};
  Solution solution1(vec1);
  cout << solution1.pickIndex() << endl;
  Solution solution2(vec2);
  cout << solution2.pickIndex() << " " << solution2.pickIndex() << " "
       << solution2.pickIndex() << " " << solution2.pickIndex() << " "
       << solution2.pickIndex() << endl;
  Solution1 Solution2(vec1);
  cout << Solution2.pickIndex() << endl;
  Solution1 solution4(vec2);
  cout << solution4.pickIndex() << " " << solution4.pickIndex() << " "
       << solution4.pickIndex() << " " << solution4.pickIndex() << " "
       << solution4.pickIndex() << endl;
  return 0;
}