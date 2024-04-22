#include "head.h"
/* 19. 删除链表的倒数第 N 个结点
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
进阶：你能尝试使用一趟扫描实现吗？
示例 1：
19.删除链表的倒数第N个节点
输入：head = [1,2,3,4,5], n = 2 输出：[1,2,3,5] 示例 2：
输入：head = [1], n = 1 输出：[] 示例 3：
输入：head = [1,2], n = 1 输出：[1]。*/

// 双指针，快指针先走n步，然后慢指针走快指针走到底的步数。对慢指针下一个结点进行删除操作。
// 虚拟头结点，可删除走一步的头结点。while条件内，判断推荐p->next，确定p终止于最后一个结点，而非空。如果判断条件为p，则fast要多走一步
ListNode* removeNthFromEnd(ListNode* head, int n) {
  ListNode* dummy = new ListNode(0, head);
  ListNode* fast = dummy;
  ListNode* slow = fast;
  while (fast->next && n--)
    fast = fast->next;
  while (fast->next) {
    fast = fast->next;
    slow = slow->next;
  }
  slow->next = slow->next->next;
  return dummy->next;
}

// 快慢指针法
ListNode* removeNthFromEnd1(ListNode* head, int n) {
  ListNode* dummy = new ListNode(0);
  dummy->next = head;
  ListNode* fast = dummy;
  ListNode* slow = dummy;
  while (n-- && fast) {
    fast = fast->next;
  }
  fast = fast->next;  // fast 需要多跑一步，让slow能在节点前停止
  while (fast) {
    fast = fast->next;
    slow = slow->next;
  }
  // ListNode* tmp = slow->next;
  slow->next = slow->next->next;  // 头节点为了处理此类问题而生
  // delete tmp;
  // tmp = nullptr;
  return dummy->next;
}

int main() {
  vector<int> vec1 = {1, 2, 3, 4, 5};
  vector<int> vec2 = {1};
  vector<int> vec3 = {1, 2};
  int n1 = 2, n2 = 1;
  ListNode* p1 = createList(vec1);
  ListNode* p2 = createList(vec2);
  ListNode* p3 = createList(vec3);
  printList(removeNthFromEnd(p1, n1));
  printList(removeNthFromEnd(p2, n2));
  printList(removeNthFromEnd(p3, n2));
  p1 = createList(vec1);
  p2 = createList(vec2);
  p3 = createList(vec3);
  printList(removeNthFromEnd1(p1, n1));
  printList(removeNthFromEnd1(p2, n2));
  printList(removeNthFromEnd1(p3, n2));
}