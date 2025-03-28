#include "head.h"

/* LCR 041. 数据流中的移动平均值
给定一个整数数据流和一个窗口大小，根据该滑动窗口的大小，计算滑动窗口里所有数字的平均值。
实现 MovingAverage 类：
    MovingAverage(int size) 用窗口大小 size 初始化对象。
    double next(int val) 成员函数 next
每次调用的时候都会往滑动窗口增加一个整数，请计算并返回数据流中最后 size
个值的移动平均值，即滑动窗口里所有数字的平均值。
示例：
输入：
  inputs = ["MovingAverage", "next", "next", "next", "next"]
  inputs = [[3], [1], [10], [3], [5]]
输出：
  [null, 1.0, 5.5, 4.66667, 6.0]
解释：
  MovingAverage movingAverage = new MovingAverage(3);
  movingAverage.next(1); // 返回 1.0 = 1 / 1
  movingAverage.next(10); // 返回 5.5 = (1 + 10) / 2
  movingAverage.next(3); // 返回 4.66667 = (1 + 10 + 3) / 3
  movingAverage.next(5); // 返回 6.0 = (10 + 3 + 5) / 3 */

// 内置三个成员变量，队列本身，队列指定大小size。求队列平均数，需要知道队列总和sum。
// 压入新元素时，首先看当前队列是否已满，若时，则弹出队首元素，总和sum减去相应值。然后再压入队尾元素。
class MovingAverage {
 public:
  MovingAverage(int size) {
    this->size = size;
    this->sum = 0.0;
  }

  double next(int val) {
    if (que.size() == size) {
      sum -= que.front();
      que.pop();
    }
    que.push(val);
    sum += val;
    return sum / que.size();
  }

 private:
  int size;
  double sum;
  queue<int> que;
};

int main() {
  MovingAverage* movingAverage = new MovingAverage(3);
  cout << movingAverage->next(1) << " " << movingAverage->next(10) << " "
       << movingAverage->next(3) << " " << movingAverage->next(5);
  return 0;
}