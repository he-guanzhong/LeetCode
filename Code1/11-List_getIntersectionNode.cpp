#include "head.h"
/* 给你两个单链表的头节点 headA 和 headB
，请你找出并返回两个单链表相交的起始节点。如果两个链表没有交点，返回 null 。
示例 1：
输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,0,1,8,4,5], skipA = 2,
skipB = 3 输出：Intersected at '8' 解释：相交节点的值为 8
（注意，如果两个链表相交则不能为 0）。 从各自的表头开始算起，链表 A 为
[4,1,8,4,5]，链表 B 为 [5,0,1,8,4,5]。 在 A 中，相交节点前有 2 个节点；在 B
中，相交节点前有 3 个节点。

题目数据 保证 整个链式结构中不存在环。
注意，函数返回结果后，链表必须 保持其原始结构 。*/

// 判断链表相交，分三步：一、统计AB各自长度，二、保证A比B长，如否，则交换头结点。三、A先走差值步，AB一同走剩下步数，如相等即返回
// 注意：一、结点相等判断，不是结点的值相等，而是p==q。二、交换头结点时，最好不要在原头结点上操作，而用临时结点
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
  int lenA = 0, lenB = 0;
  ListNode* p = headA;
  ListNode* q = headB;
  while (p) {
    lenA++;
    p = p->next;
  }
  p = headB;
  while (p) {
    lenB++;
    p = p->next;
  }
  p = headA;
  if (lenA < lenB)
    swap(headA, headB);
  int pre = abs(lenA - lenB);
  while (pre--)
    p = p->next;
  while (p && q) {
    if (p == q)
      return p;
    p = p->next;
    q = q->next;
  }
  return nullptr;
}

// 先确定两个链表长度，计算差值，将长短链表尾部对齐，然后依次对比节点是否相同
ListNode* getIntersectionNode1(ListNode* headA, ListNode* headB) {
  int lenA = 0, lenB = 0;
  ListNode* curA = headA;
  ListNode* curB = headB;
  while (curA) {  // 确定A\B链表长度
    lenA++;
    curA = curA->next;
  }
  while (curB) {
    lenB++;
    curB = curB->next;
  }
  curA = headA;
  curB = headB;
  if (lenA < lenB) {  // 以A为最长链表。
    swap(curA, curB);
    swap(lenA, lenB);
  }
  int gap = lenA - lenB;
  while (gap--)  // 对齐两链表尾部
    curA = curA->next;
  while (curA) {  // 判断是否相等
    if (curA == curB)
      return curA;
    curA = curA->next;
    curB = curB->next;
  }
  return nullptr;
}

int main() {
  vector<int> vec1 = {4, 1, 8, 4, 5};
  vector<int> vec2 = {5, 0, 1};
  vector<int> vec3 = {2, 6};
  ListNode* p1 = createList(vec1);
  ListNode* p2 = createList(vec2);
  ListNode* p3 = createList(vec3);
  ListNode* p01 = p1->next->next;
  ListNode* p02 = p2->next->next;
  p02->next = p01;
  cout << getIntersectionNode(p1, p2) << " " << getIntersectionNode(p1, p3)
       << endl;
  cout << getIntersectionNode1(p1, p2) << " " << getIntersectionNode1(p1, p3)
       << endl;
  return 0;
}