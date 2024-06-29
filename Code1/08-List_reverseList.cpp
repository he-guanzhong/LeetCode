#include "head.h"
/* 206. 反转链表
给你单链表的头节点 head ，请你反转链表，并返回反转后的链表。
示例 1：
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
示例 2：
输入：head = [1,2]
输出：[2,1]
示例 3：
输入：head = []
输出：[]
提示：
    链表中节点的数目范围是 [0, 5000]
    -5000 <= Node.val <= 5000
进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？ */

// 优选双指针，全局保存过去、现在、未来三个结点。无需对head特殊情况进行处理。最终返回更新后的pre，即为新的头结点
// 次选递归。退出条件为找到原尾节点，即返回。不断向下递归head->next，标记新的头结点last。此时该层head为倒数第二结点。
// 将倒数第一结点转向倒数第二，倒数第二指向空。返回新头结点last
ListNode* reverseList(ListNode* head) {
  if (!head || !head->next)
    return head;
  ListNode* newHead = reverseList(head->next);
  head->next->next = head;
  head->next = nullptr;
  return newHead;
}

// 生成虚拟头节点
ListNode* reverseList1(ListNode* head) {
  ListNode* p = head;
  stack<int> stk;
  while (p) {
    stk.push(p->val);
    p = p->next;
  }
  ListNode* newHead = new ListNode(0);
  p = newHead;
  while (!stk.empty()) {
    ListNode* tmp = new ListNode(stk.top());
    stk.pop();
    p->next = tmp;
    p = p->next;
  }
  p->next = nullptr;
  return newHead->next;
}

// 双指针法。全局化过去，现在，未来三个结点。只要现在结点p存在，则暂存未来tmp,反转p指向。更新过去pre和现在p的位置，最终返回pre
// 注意，该方法不需要对空结点和只有一个结点，进行特殊处理
ListNode* reverseList2(ListNode* head) {
  ListNode* cur = head;
  ListNode* pre = nullptr;
  while (cur) {
    ListNode* tmp = cur->next;
    cur->next = pre;
    pre = cur;
    cur = tmp;
  }
  return pre;
}

// 递归法，类双指针
ListNode* reverse(ListNode* pre, ListNode* cur) {
  if (cur == nullptr)
    return pre;
  ListNode* tmp = cur->next;
  cur->next = pre;
  return reverse(cur, tmp);
}
ListNode* reverseList3(ListNode* head) {
  return reverse(nullptr, head);
}

// 递归法
ListNode* reverseList4(ListNode* head) {
  if (!head)
    return nullptr;
  if (!head->next)
    return head;
  ListNode* last = reverseList4(head->next);
  head->next->next = head;
  head->next = nullptr;
  return last;
}

int main() {
  vector<int> vec1 = {1, 2, 3, 4, 5, 6};
  vector<int> vec2 = {};
  ListNode* p1 = createList(vec1);
  ListNode* p2 = createList(vec2);
  printList(reverseList(p1));
  printList(reverseList(p2));
  p1 = createList(vec1);
  p2 = createList(vec2);
  printList(reverseList3(p1));
  printList(reverseList3(p2));
  return 0;
}