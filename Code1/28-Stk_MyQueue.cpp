#include "head.h"
/* 232. 用栈实现队列
请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）：
实现 MyQueue 类：
   void push(int x) 将元素 x 推到队列的末尾
   int pop() 从队列的开头移除并返回元素
   int peek() 返回队列开头的元素
   boolean empty() 如果队列为空，返回 true ；否则，返回 false
说明：
   你 只能 使用标准的栈操作 —— 也就是只有 push to top, peek/pop from top, size,
和 is empty 操作是合法的。 你所使用的语言也许不支持栈。你可以使用 list 或者
deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。
提示：
    1 <= x <= 9
    最多调用 100 次 push、pop、peek 和 empty
    假设所有操作都是有效的 （例如，一个空的队列不会调用 pop 或者 peek 操作） */

class MyQueue {
 public:
  MyQueue() {}

  void push(int x) { st1.push(x); }

  int pop() {
    if (st2.empty()) {
      while (!st1.empty()) {
        st2.push(st1.top());
        st1.pop();
      }
    }
    int ans = st2.top();
    st2.pop();
    return ans;
  }

  int peek() {
    int ans = pop();
    st2.push(ans);
    return ans;
  }

  bool empty() { return st1.empty() && st2.empty(); }
  stack<int> st1;
  stack<int> st2;
};

// 无构造，push直接压入进栈，pop要先判断出栈是否为空，空则将进栈所有元素转移。出栈顶元素临时保存作为返回值，再出栈。注意题目要求，不必考虑进栈也为空的情况
// peek同样要判断出栈是否为空，可以借用this指针pop函数,，将弹出的元素压回出栈。empty判断进栈、出栈二者皆空
// 进、出双栈。只有pop时才会将进栈所有元素转移。注意peek函数对于pop函数判空的复用
class MyQueue1 {
 public:
  MyQueue1() {}
  stack<int> stIn;
  stack<int> stOut;
  void push(int x) { stIn.push(x); }
  int pop() {
    if (stOut.empty()) {  // out为空时，所有元素转移
      while (!stIn.empty()) {
        stOut.push(stIn.top());
        stIn.pop();
      }
    }
    int result = stOut.top();
    stOut.pop();
    return result;
  }

  int peek() {                 // 不要再写一遍判空
    int result = this->pop();  // 将弹出的元素再放回去
    stOut.push(result);
    return result;
  }
  bool empty() { return stIn.empty() && stOut.empty(); }
};

int main() {
  MyQueue myQueue;
  myQueue.push(1);  // queue is: [1]
  myQueue.push(2);  // queue is: [1, 2] (leftmost is front of the queue)
  cout << myQueue.peek() << " ";    // return 1
  cout << myQueue.pop() << " ";     // return 1, queue is [2]
  cout << myQueue.empty() << endl;  // return false

  MyQueue1 myQueue1;
  myQueue1.push(1);  // queue is: [1]
  myQueue1.push(2);  // queue is: [1, 2] (leftmost is front of the queue)
  cout << myQueue1.peek() << " ";    // return 1
  cout << myQueue1.pop() << " ";     // return 1, queue is [2]
  cout << myQueue1.empty() << endl;  // return false
  return 0;
}