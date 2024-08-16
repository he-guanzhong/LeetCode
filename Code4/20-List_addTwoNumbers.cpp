#include "head.h"
/*  2. 两数相加
给你两个 非空 的链表，表示两个非负的整数。它们每位数字都是按照 逆序
的方式存储的，并且每个节点只能存储 一位 数字。
请你将两个数相加，并以相同形式返回一个表示和的链表。
你可以假设除了数字 0 之外，这两个数都不会以 0 开头。
示例 1：
  输入：l1 = [2,4,3], l2 = [5,6,4]
  输出：[7,0,8]
  解释：342 + 465 = 807.
示例 2：
  输入：l1 = [0], l2 = [0]
  输出：[0]
示例 3：
  输入：l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
  输出：[8,9,9,9,0,0,0,1] */

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
  int carry = 0;
  ListNode* dummy = new ListNode(0);
  ListNode* k = dummy;
  ListNode *p = l1, *q = l2;
  while (p || q) {
    int val1 = p ? p->val : 0;
    int val2 = q ? q->val : 0;
    int sum = val1 + val2 + carry;
    carry = sum / 10;
    sum %= 10;
    k->next = new ListNode(sum);
    k = k->next;
    p = p ? p->next : p;
    q = q ? q->next : q;
  }
  k->next = carry ? new ListNode(1) : nullptr;
  return dummy->next;
}

// 模拟，为避免两链表不等长，对短的一个补零，即循环中任意链表不为空即可，移动指针必须不为空才能移动
// 外置进位carry标识，进位与否可以直接/10得到。头指针head和移动指针p初始化为空，生成头节点时，head和p均赋值
// 其余结点时，p->next生成新节点赋值，并移动p。时间复杂度O(max(m,n))，空间复杂度O(1)
ListNode* addTwoNumbers1(ListNode* l1, ListNode* l2) {
  ListNode* head = nullptr;
  ListNode* p = nullptr;
  int carry = 0;
  while (l1 || l2) {  // 可以集成carry
    int n1 = l1 ? l1->val : 0;
    int n2 = l2 ? l2->val : 0;
    int sum = n1 + n2 + carry;
    if (!head)  // 头节点可以使用dummy
      head = p = new ListNode(sum % 10);
    else {
      p->next = new ListNode(sum % 10);
      p = p->next;
    }
    carry = sum / 10;
    if (l1)
      l1 = l1->next;
    if (l2)
      l2 = l2->next;
  }
  if (carry)
    p->next = new ListNode(1);
  return head;
}

int main() {
  vector<int> v1 = {2, 4, 3}, v2 = {5, 6, 4};
  vector<int> v3 = {0}, v4 = {0};
  vector<int> v5 = {9, 9, 9, 9, 9, 9, 9}, v6 = {9, 9, 9, 9};
  ListNode* l1 = createList(v1);
  ListNode* l2 = createList(v2);
  ListNode* l3 = createList(v3);
  ListNode* l4 = createList(v4);
  ListNode* l5 = createList(v5);
  ListNode* l6 = createList(v6);
  printList(addTwoNumbers(l1, l2));
  printList(addTwoNumbers(l3, l4));
  printList(addTwoNumbers(l5, l6));
  l1 = createList(v1), l2 = createList(v2), l3 = createList(v3),
  l4 = createList(v4), l5 = createList(v5), l6 = createList(v6);
  printList(addTwoNumbers1(l1, l2));
  printList(addTwoNumbers1(l3, l4));
  printList(addTwoNumbers1(l5, l6));
  return 0;
}