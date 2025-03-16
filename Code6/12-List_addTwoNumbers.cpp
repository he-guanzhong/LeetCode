#include "head.h"
/* 445. 两数相加 II
给你两个 非空 链表来代表两个非负整数。数字最高位位于链表开始位置。
它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。
你可以假设除了数字 0 之外，这两个数字都不会以零开头。
示例1：
  输入：l1 = [7,2,4,3], l2 = [5,6,4]
  输出：[7,8,0,7]
示例2：
  输入：l1 = [2,4,3], l2 = [5,6,4]
  输出：[8,0,7]
示例3：
  输入：l1 = [0], l2 = [0]
  输出：[0]
提示：
    链表的长度范围为 [1, 100]
    0 <= node.val <= 9
    输入数据保证链表代表的数字无前导 0
进阶：如果输入链表不能翻转该如何解决？ */

// 不反转，就要利用栈，或数组将结点数据保存，如此空间复杂度O(m+n)
// 注意st.pop()弹栈前，一定要判断栈是否为空。否则会报错
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  ListNode* p = l1;
  stack<int> st1, st2;
  while (p) {
    st1.push(p->val);
    p = p->next;
  }
  p = l2;
  while (p) {
    st2.push(p->val);
    p = p->next;
  }
  int carry = 0;
  ListNode* ans = nullptr;
  while (!st1.empty() || !st2.empty() || carry) {
    int val1 = st1.empty() ? 0 : st1.top();
    int val2 = st2.empty() ? 0 : st2.top();
    if (!st1.empty()) {
      st1.pop();
    }
    if (!st2.empty()) {
      st2.pop();
    }
    carry = val1 + val2 + carry;
    ListNode* tmp = new ListNode((carry % 10), ans);
    carry /= 10;
    ans = tmp;
  }
  return ans;
}

int main() {
  ListNode *p1 = createList({7, 2, 4, 3}), *q1 = createList({5, 6, 4});
  ListNode *p2 = createList({2, 4, 3}), *q2 = createList({5, 6, 4});
  ListNode *p3 = createList({0}), *q3 = createList({0});
  printList(addTwoNumbers(p1, q1));
  printList(addTwoNumbers(p2, q2));
  printList(addTwoNumbers(p3, q3));
  return 0;
}