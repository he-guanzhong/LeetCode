#include "head.h"
/* 155. 最小栈
设计一个支持 push ，pop ，top 操作，并能在常数时间内检索到最小元素的栈。
实现 MinStack 类:
    MinStack() 初始化堆栈对象。
    void push(int val) 将元素val推入堆栈。
    void pop() 删除堆栈顶部的元素。
    int top() 获取堆栈顶部的元素。
    int getMin() 获取堆栈中的最小元素。
示例 1:
  输入：
    ["MinStack","push","push","push","getMin","pop","top","getMin"]
    [[],[-2],[0],[-3],[],[],[],[]]
输出：
  [null,null,null,null,-3,null,0,-2]
解释：
  MinStack minStack = new MinStack();
  minStack.push(-2);
  minStack.push(0);
  minStack.push(-3);
  minStack.getMin();   --> 返回 -3.
  minStack.pop();
  minStack.top();      --> 返回 0.
  minStack.getMin();   --> 返回 -2. */

class MinStack {
 public:
  /** initialize your data structure here. */
  MinStack() { st2.push(INT_MAX); }

  void push(int x) {
    st1.push(x);
    st2.push(min(x, st2.top()));
  }

  void pop() {
    st1.pop();
    st2.pop();
  }

  int top() { return st1.top(); }

  int getMin() { return st2.top(); }
  stack<int> st1;
  stack<int> st2;
};

// 辅助栈，保存当前主栈内的最小值。初始化时，辅助栈要提前多压入一个INT_MAX。push/pop两个操作两栈同步运行，top和getMin分别访问主栈、辅助栈顶。
// push操作时，主栈压入元素，辅助栈压入元素与辅助栈顶（当前的最小值）二者最小值，如此辅助栈顶即一只保存对应主栈的最小值
class MinStack1 {
 public:
  MinStack1() { st2.push(INT_MAX); }

  void push(int val) {
    st1.push(val);
    st2.push(min(val, st2.top()));
  }

  void pop() {
    st1.pop();
    st2.pop();
  }

  int top() { return st1.top(); }

  int getMin() { return st2.top(); }

 private:
  stack<int> st1;
  stack<int> st2;
};

int main() {
  MinStack minStack;
  minStack.push(-2);
  minStack.push(0);
  minStack.push(-3);
  cout << minStack.getMin() << " ";
  minStack.pop();
  cout << minStack.top() << " ";
  cout << minStack.getMin() << endl;
  MinStack1 minStack1;
  minStack1.push(-2);
  minStack1.push(0);
  minStack1.push(-3);
  cout << minStack1.getMin() << " ";
  minStack1.pop();
  cout << minStack1.top() << " ";
  cout << minStack1.getMin() << endl;
  return 0;
}