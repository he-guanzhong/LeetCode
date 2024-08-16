#include "head.h"
/* 21. 合并两个有序链表
将两个升序链表合并为一个新的 升序
链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的。
示例 1：
  输入：l1 = [1,2,4], l2 = [1,3,4]
  输出：[1,1,2,3,4,4]
示例 2：
  输入：l1 = [], l2 = []
  输出：[]
示例 3：
  输入：l1 = [], l2 = [0]
  输出：[0] */

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
  if (!list1)
    return list2;
  else if (!list2)
    return list1;
  else if (list1->val < list2->val) {
    list1->next = mergeTwoLists(list1->next, list2);
    return list1;
  } else {
    list2->next = mergeTwoLists(list1, list2->next);
    return list2;
  }
}

// 迭代法。设立虚拟头节点，对l1和l2元素一一比较，值小的承接p指针，并挪动l1、l2和p。
// 由于l1和l2最终指向未处理结点，故一为空时，p指向不为空的结点，返回虚拟头节点的下一节点。时间复杂度O(m+n)空间复杂度O(1)
ListNode* mergeTwoLists1(ListNode* list1, ListNode* list2) {
  ListNode* dummy = new ListNode(-1);
  ListNode* p = dummy;
  while (list1 && list2) {
    if (list1->val < list2->val) {
      p->next = list1;
      list1 = list1->next;
    } else {
      p->next = list2;
      list2 = list2->next;
    }
    p = p->next;
  }
  p->next = list1 ? list1 : list2;
  return dummy->next;
}

// 递归，将L1与L2小的一个结点在该层保留，传入下一个结点入递归。时间、空间复杂度均为O(m+n)
ListNode* mergeTwoLists2(ListNode* list1, ListNode* list2) {
  if (!list1)
    return list2;
  else if (!list2)
    return list1;
  else if (list1->val < list2->val) {
    list1->next = mergeTwoLists1(list1->next, list2);
    return list1;
  } else {
    list2->next = mergeTwoLists1(list1, list2->next);
    return list2;
  }
}

int main() {
  vector<int> v1 = {1, 2, 4}, v2 = {1, 3, 4};
  vector<int> v3 = {}, v4 = {};
  vector<int> v5 = {}, v6 = {1};
  ListNode* l1 = createList(v1);
  ListNode* l2 = createList(v2);
  ListNode* l3 = createList(v3);
  ListNode* l4 = createList(v4);
  ListNode* l5 = createList(v5);
  ListNode* l6 = createList(v6);
  printList(mergeTwoLists(l1, l2));
  printList(mergeTwoLists(l3, l4));
  printList(mergeTwoLists(l5, l6));
  l1 = createList(v1);
  l2 = createList(v2);
  l3 = createList(v3);
  l4 = createList(v4);
  l5 = createList(v5);
  l6 = createList(v6);
  printList(mergeTwoLists1(l1, l2));
  printList(mergeTwoLists1(l3, l4));
  printList(mergeTwoLists1(l5, l6));
  return 0;
}