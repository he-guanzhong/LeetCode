#include "head.h"
/* 946. 验证栈序列
给定 pushed 和 popped 两个序列，每个序列中的
值都不重复，只有当它们可能是在最初空栈上进行的推入 push 和弹出 pop
操作序列的结果时，返回 true；否则，返回 false 。
示例 1：
  输入：pushed = [1,2,3,4,5], popped = [4,5,3,2,1]
  输出：true
  解释：我们可以按以下顺序执行：
    push(1), push(2), push(3), push(4), pop() -> 4,
    push(5), pop() -> 5, pop() -> 3, pop() -> 2, pop() -> 1
示例 2：
  输入：pushed = [1,2,3,4,5], popped = [4,3,5,1,2]
  输出：false
  解释：1 不能在 2 之前弹出。
提示：
    1 <= pushed.length <= 1000
    0 <= pushed[i] <= 1000
    pushed 的所有元素 互不相同
    popped.length == pushed.length
    popped 是 pushed 的一个排列 */

bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
  stack<int> st;
  int j = 0;
  for (int i = 0; i < pushed.size(); i++) {
    st.push(pushed[i]);
    while (j < popped.size() && st.size() && popped[j] == st.top()) {
      st.pop();
      j++;
    }
  }
  return st.empty();
}

// 要点，一对普通数据类型，push和emplace无区别，对自定义类型，push需要先实例化，emplace还可以额外使用构造函数的参数
// C语言使用top模拟栈待赋值的位置。empty判断等价于top==0，top访问等价于st[top-1]，利用完的栈要及时free
bool validateStackSequences1(vector<int>& pushed, vector<int>& popped) {
  stack<int> st;
  for (int i = 0, j = 0; i < pushed.size(); i++) {
    st.emplace(pushed[i]);
    while (!st.empty() && st.top() == popped[j]) {
      st.pop();
      j++;
    }
  }
  return st.empty();
}

// C语言版本
bool validateStackSequences2(int* pushed,
                             int pushedSize,
                             int* popped,
                             int poppedSize) {
  int top = 0;
  int* st = (int*)malloc(sizeof(int) * pushedSize);
  for (int i = 0, j = 0; i < pushedSize; i++) {
    st[top++] = pushed[i];
    while (top > 0 && st[top] == popped[j]) {
      top--;
      j++;
    }
  }
  free(st);
  return top > 0 ? false : true;
}

int main() {
  vector<int> pushed1 = {1, 2, 3, 4, 5}, popped1 = {4, 5, 3, 2, 1};
  vector<int> pushed2 = {1, 2, 3, 4, 5}, popped2 = {4, 3, 5, 1, 2};
  cout << validateStackSequences(pushed1, popped1) << " "
       << validateStackSequences(pushed2, popped2) << endl;
  cout << validateStackSequences1(pushed1, popped1) << " "
       << validateStackSequences1(pushed2, popped2) << endl;
  return 0;
}