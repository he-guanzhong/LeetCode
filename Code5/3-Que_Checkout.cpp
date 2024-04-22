#include "head.h"
/* LCR 184. 设计自助结算系统
请设计一个自助结账系统，该系统需要通过一个队列来模拟顾客通过购物车的结算过程，需要实现的功能有：
    get_max()：获取结算商品中的最高价格，如果队列为空，则返回 -1
    add(value)：将价格为 value 的商品加入待结算商品队列的尾部
    remove()：移除第一个待结算的商品价格，如果队列为空，则返回 -1
注意，为保证该系统运转高效性，以上函数的均摊时间复杂度均为 O(1)
示例 1：
输入:
["Checkout","add","add","get_max","remove","get_max"]
[[],[4],[7],[],[],[]]
输出: [null,null,null,7,4,7]
示例 2：
输入:
["Checkout","remove","get_max"]
[[],[],[]]
输出: [null,-1,-1]
提示：
    1 <= get_max, add, remove 的总操作数 <= 10000
    1 <= value <= 10^5 */

class Checkout {
 public:
  Checkout() {}

  int get_max() { return deq.empty() ? -1 : deq.front(); }

  void add(int value) {
    que.push(value);
    while (!deq.empty() && value > deq.back())
      deq.pop_back();
    deq.push_back(value);
  }

  int remove() {
    if (que.empty())
      return -1;
    if (!deq.empty() && que.front() == deq.front())
      deq.pop_front();
    int ans = que.front();
    que.pop();
    return ans;
  }

  queue<int> que;
  deque<int> deq;
};

// 类似滑动窗口最大值，queue为滑动窗口，单独设置双端队列deque，保存队列最大值。
// add函数，若val>deq末尾，则不断弹出末尾，保证deque内元素递减。get_max函数即返回deq首元素，如果队列为空则返回-1
// remove函数，que首元素必弹出，deq如果首元素相等才弹出
class Checkout1 {
 public:
  Checkout1() {}

  int get_max() { return deq.empty() ? -1 : deq.front(); }

  void add(int value) {
    que.push(value);
    while (!deq.empty() && value > deq.back())
      deq.pop_back();
    deq.push_back(value);
  }

  int remove() {
    if (que.empty())
      return -1;
    int val = que.front();
    if (val == deq.front())
      deq.pop_front();
    que.pop();
    return val;
  }
  queue<int> que;
  deque<int> deq;
};

int main() {
  Checkout* obj = new Checkout();
  cout << obj->get_max() << " " << obj->remove() << " ";
  obj->add(4);
  obj->add(7);
  cout << obj->get_max() << " " << obj->remove() << " " << obj->get_max()
       << endl;

  Checkout1* obj1 = new Checkout1();
  cout << obj1->get_max() << " " << obj1->remove() << " ";
  obj1->add(4);
  obj1->add(7);
  cout << obj1->get_max() << " " << obj1->remove() << " " << obj1->get_max()
       << endl;

  return 0;
}