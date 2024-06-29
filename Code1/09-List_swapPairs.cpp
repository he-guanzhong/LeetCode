#include "head.h"
/* 24. 两两交换链表中的节点
给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。
示例 1：
输入：head = [1,2,3,4]
输出：[2,1,4,3]
示例 2：
输入：head = []
输出：[]
示例 3：
输入：head = [1]
输出：[1] */

// 交换结点涉及4个结点的同时操作，虚拟头结点设为1，2和4需要额外保存。因为1可以直接指3，此时会丢失2、4的链接。
// 由于需要额外保存2、3，所以遍历的条件即为2、3存在。1必存在，4可以为空结点。2存在4不存在时，也不行
// 按照1->3，3-2，2->4的顺序，更改结点指向，并随时挪动两步不1结点的位置
ListNode* swapPairs(ListNode* head) {
  if (!head || !head->next)
    return head;
  ListNode* dummy = new ListNode(-1, head);
  ListNode *p0 = dummy, *p1 = p0->next, *p2 = p0->next->next;
  while (p0->next && p0->next->next) {
    p1 = p0->next;
    p2 = p0->next->next;
    p0->next = p2;
    p1->next = p2->next;
    p2->next = p1;
    p0 = p1;
  }
  return dummy->next;
}

ListNode* swapPairs1(ListNode* head) {
  ListNode* dummy = new ListNode(0);
  dummy->next = head;
  ListNode* p = dummy;
  while (p->next &&
         p->next->next) {  // 当前节点1，只关心2和3不为空即可对调，4可以为空
    ListNode* tmp2 = p->next;
    ListNode* tmp4 = p->next->next->next;
    p->next = p->next->next;     // 步骤一，1 -> 3
    p->next->next = tmp2;        // 步骤二，2 <- 3
    p->next->next->next = tmp4;  // 步骤三，2 -> 4
    p = p->next->next;           // 移动两次，准备下一轮
  }
  return dummy->next;
}

int main() {
  vector<int> vec1 = {1, 2, 3, 4, 5, 6};
  vector<int> vec2 = {};
  vector<int> vec3 = {1};
  ListNode* p1 = createList(vec1);
  ListNode* p2 = createList(vec2);
  ListNode* p3 = createList(vec3);
  printList(swapPairs(p1));
  printList(swapPairs(p2));
  printList(swapPairs(p3));
  p1 = createList(vec1);
  p2 = createList(vec2);
  p3 = createList(vec3);
  printList(swapPairs1(p1));
  printList(swapPairs1(p2));
  printList(swapPairs1(p3));
  return 0;
}