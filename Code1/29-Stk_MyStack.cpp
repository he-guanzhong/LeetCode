#include "head.h"
/* 225. 用队列实现栈
请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop
和 empty）。
实现 MyStack 类：
    void push(int x) 将元素 x 压入栈顶。
    int pop() 移除并返回栈顶元素。
    int top() 返回栈顶元素。
    boolean empty() 如果栈是空的，返回 true ；否则，返回 false 。
注意：
    你只能使用队列的基本操作 —— 也就是 push to back、peek/pop from front、size
和 is empty 这些操作。 你所使用的语言也许不支持队列。 你可以使用 list
（列表）或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可
提示：
    1 <= x <= 9
    最多调用100 次 push、pop、top 和 empty
    每次调用 pop 和 top 都保证栈不为空
*/
// 一个队列就够了，push正常压入，pop要求整体队列大小，依次弹出n-1个首元素，分别将其加入队尾，取出front()作为弹出的量
// top由于队列的特殊性质，可以同时访问队头队尾两个元素，故直接返回back()
class MyStack {
 public:
  MyStack() {}
  void push(int x) { que1.push(x); }
  int pop() {
    int n = que1.size();
    while (--n) {
      que1.push(que1.front());
      que1.pop();
    }
    int result = que1.front();
    que1.pop();
    return result;
  }
  int top() { return que1.back(); }
  bool empty() { return que1.empty(); }

 private:
  queue<int> que1;
  queue<int> que2;
};
// 一个队列为主，第二个队列仅在pop时作为临时容纳前n-1的容器使用
class MyStack1 {
 public:
  queue<int> que1;
  queue<int> que2;
  void push(int x) { que1.push(x); }
  int pop() {
    int size = que1.size();
    size--;
    while (size--) {  // 要保留最后一个元素
      que2.push(que1.front());
      que1.pop();
    }
    int result = que1.front();
    que1.pop();
    que1 = que2;             // 直接拷贝过去，不必再一一弹出
    while (!que2.empty()) {  // 清空que2
      que2.pop();
    }
    return result;
  }
  int pop_optimal() {
    int size = que1.size();
    size--;
    while (size--) {  // 直接将前方元素（最后一个除外） 重新添加到尾部
      que1.push(que1.front());
      que1.pop();
    }
    int result = que1.front();
    que1.pop();
    return result;
  }
  int top() { return que1.back(); }
  bool empty() { return que1.empty(); }
};

int main() {
  MyStack myStack;
  myStack.push(1);
  myStack.push(2);
  cout << myStack.top() << " ";     // 返回 2
  cout << myStack.pop() << " ";     // 返回 2
  cout << myStack.empty() << endl;  // 返回 False
  MyStack1 myStack1;
  myStack1.push(1);
  myStack1.push(2);
  cout << myStack1.top() << " ";     // 返回 2
  cout << myStack1.pop() << " ";     // 返回 2
  cout << myStack1.empty() << endl;  // 返回 False
  return 0;
}