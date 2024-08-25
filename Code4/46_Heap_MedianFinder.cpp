#include "head.h"
/* 295. 数据流的中位数
中位数是有序整数列表中的中间值。如果列表的大小是偶数，则没有中间值，中位数是两个中间值的平均值。
    例如 arr = [2,3,4] 的中位数是 3 。
    例如 arr = [2,3] 的中位数是 (2 + 3) / 2 = 2.5 。
实现 MedianFinder 类:
    MedianFinder() 初始化 MedianFinder 对象。
    void addNum(int num) 将数据流中的整数 num 添加到数据结构中。
    double findMedian() 返回到目前为止所有元素的中位数。与实际答案相差 10-5
以内的答案将被接受。
示例 1：
输入
  ["MedianFinder", "addNum", "addNum", "findMedian", "addNum", "findMedian"]
  [[], [1], [2], [], [3], []]
输出
  [null, null, null, 1.5, null, 2.0]
解释
  MedianFinder medianFinder = new MedianFinder();
  medianFinder.addNum(1);    // arr = [1]
  medianFinder.addNum(2);    // arr = [1, 2]
  medianFinder.findMedian(); // 返回 1.5 ((1 + 2) / 2)
  medianFinder.addNum(3);    // arr[1, 2, 3]
  medianFinder.findMedian(); // return 2.0
提示:
    -105 <= num <= 105
    在调用 findMedian 之前，数据结构中至少有一个元素
    最多 5 * 104 次调用 addNum 和 findMedian */

class MedianFinder {
 public:
  MedianFinder() {}

  void addNum(int num) {
    if (que2.size() && num > que2.top()) {
      que2.push(num);
      if (que2.size() > que1.size() + 1) {
        que1.push(que2.top());
        que2.pop();
      }
    } else {
      que1.push(num);
      if (que1.size() > que2.size()) {
        que2.push(que1.top());
        que1.pop();
      }
    }
  }

  double findMedian() {
    return que2.size() > que1.size() ? que2.top()
                                     : (que1.top() + que2.top()) / 2.0;
  }
  priority_queue<int, vector<int>, less<>> que1;
  priority_queue<int, vector<int>, greater<>> que2;
};

// 方法一，优先队列，大顶堆Less维护元素小于等于中位数，其元素最大，靠近中位数。小顶堆greater维护元素>中位数，其首元素最小，靠近中位数
// 正常情况下，minQue==maxQue说明总数数为偶数，minQue=maxQue+1说明总数量为奇数。
// addNum元素，如果minQue存在且待压入元素小于minQue首元素，压入minQue。如果minQue过长，则将其首压入maxQue，再弹出minQue首。反之亦然。
// findMedian要看总数量为奇数或偶数，选择弹出minQue首，或者minQue和maxQue两个首元素的平均数
class MedianFinder1 {
 public:
  MedianFinder1() {}

  void addNum(int num) {
    if (!minQue.empty() && num <= minQue.top()) {  // 注意判空
      minQue.push(num);
      if (minQue.size() > maxQue.size() + 1) {
        maxQue.push(minQue.top());
        minQue.pop();
      }
    } else {
      maxQue.push(num);
      if (maxQue.size() > minQue.size()) {
        minQue.push(maxQue.top());
        maxQue.pop();
      }
    }
  }

  double findMedian() {
    if (minQue.size() > maxQue.size())
      return minQue.top();
    else
      return (minQue.top() + maxQue.top()) / 2.0;
  }

 private:
  priority_queue<int, vector<int>, less<>> minQue;
  priority_queue<int, vector<int>, greater<>> maxQue;
};

// 初始思路是multiuset排序，利用下标为(n-1)/2和n/2的两个元素，无视奇偶，迭代器访问并求平均。但可以有序集合+双指针优化
// addNum之中，先求原数组长度n，再插入。如果n==0首次插入，left和right初始化begin。
// 表达式n&1意为原长度为奇数，right和left处于同一位置，根据num大小决定左、右指针移动方向。若原长度为偶数，left和right错一，分三种情况
// num处于(left,right)之中，左右指针中央对中。num>=right，left右移挪至right位。num<=left，right左移。
// multiset特性，相等元素插入，新元素位于老元素之右，故若num==left，新插入的num已经将left和right隔开。left要人工保持和right对正
class MedianFinder2 {
 public:
  MedianFinder2() {
    left = nums.end();
    right = nums.end();
  }

  void addNum(int num) {
    int n = nums.size();  // 先看原长度，再插入新元素
    nums.insert(num);
    if (n == 0) {
      left = nums.begin();
      right = nums.begin();
    } else if (n & 1) {   // 如果长度为奇数
      if (num >= *right)  // 此处一定为>=，因为新元素处于其右
        right++;
      else
        left--;
    } else {  // 如果长度为偶数
      if (num > *left && num < *right) {
        left++;
        right--;
      } else if (num >= *right) {
        left++;  // 中位数右移，原left需要右移和right对正
      } else {
        right--;  // 中位数左移，原right要左移
        left =
            right;  // 若num==*left，则新元素呗插入了(left,right)间，left需要额外对正
      }
    }
  }

  double findMedian() { return (*left + *right) / 2.0; }

 private:
  multiset<int> nums;
  multiset<int>::iterator left, right;
};
int main() {
  MedianFinder medianFinder;
  medianFinder.addNum(1);                     // arr = [1]
  medianFinder.addNum(2);                     // arr = [1, 2]
  cout << medianFinder.findMedian() << " ";   // 返回 1.5 ((1 + 2) / 2)
  medianFinder.addNum(3);                     // arr[1, 2, 3]
  cout << medianFinder.findMedian() << endl;  // return 2.0

  MedianFinder1 medianFinder1;
  medianFinder1.addNum(1);                     // arr = [1]
  medianFinder1.addNum(2);                     // arr = [1, 2]
  cout << medianFinder1.findMedian() << " ";   // 返回 1.5 ((1 + 2) / 2)
  medianFinder1.addNum(3);                     // arr[1, 2, 3]
  cout << medianFinder1.findMedian() << endl;  // return 2.0
  return 0;
}