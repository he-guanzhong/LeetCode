#include "head.h"
/* 160. 相交链表
给你两个单链表的头节点 headA 和 headB
，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回
null。 图示两个链表在节点 c1 开始相交： 题目数据 保证 整个链式结构中不存在环。
注意，函数返回结果后，链表必须 保持其原始结构 。
自定义评测：
评测系统 的输入如下（你设计的程序 不适用 此输入）：
    intersectVal - 相交的起始节点的值。如果不存在相交节点，这一值为 0
    listA - 第一个链表
    listB - 第二个链表
    skipA - 在 listA 中（从头节点开始）跳到交叉节点的节点数
    skipB - 在 listB 中（从头节点开始）跳到交叉节点的节点数
评测系统将根据这些输入创建链式数据结构，并将两个头节点 headA 和 headB
传递给你的程序。如果程序能够正确返回相交节点，那么你的解决方案将被 视作正确答案
。
示例 1：
输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2,
skipB = 3 输出：Intersected at '8' 解释：相交节点的值为 8
（注意，如果两个链表相交则不能为 0）。 从各自的表头开始算起，链表 A 为
[4,1,8,4,5]，链表 B 为 [5,6,1,8,4,5]。 在 A 中，相交节点前有 2 个节点；在 B
中，相交节点前有 3 个节点。 — 请注意相交节点的值不为 1，因为在链表 A 和链表 B
之中值为 1 的节点 (A 中第二个节点和 B 中第三个节点)
是不同的节点。换句话说，它们在内存中指向两个不同的位置，而链表 A 和链表 B 中值为
8 的节点 (A 中第三个节点，B 中第四个节点) 在内存中指向相同的位置。
示例 2：
输入：intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB =
1 输出：Intersected at '2' 解释：相交节点的值为 2
（注意，如果两个链表相交则不能为 0）。 从各自的表头开始算起，链表 A 为
[1,9,1,2,4]，链表 B 为 [3,2,4]。 在 A 中，相交节点前有 3 个节点；在 B
中，相交节点前有 1 个节点。
示例 3：
输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
输出：null
解释：从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。
由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB
可以是任意值。 这两个链表不相交，因此返回 null 。
*/

ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
  ListNode *p1 = headA, *p2 = headB;
  while (p1 != p2) {
    p1 = (p1 == nullptr) ? headB : p1->next;
    p2 = (p2 == nullptr) ? headA : p2->next;
  }
  return p1;
}

// 双指针简写法。A、B若有一方为空，必不相交，排除。pA、pB分别向后遍历，pA到底后指向headB，pB到底后指向headA。
// 若有相交，则双方经过a+b+c相同步数后，pA==pB。若不相交，双方经过m+n相同步数后，pA==pB==nullptr。二者均可返回pA。时间复杂度O(m+n)
// 注意语言优先级，7级==，11级&&，12级||，13级三目运算，14级赋值=，+=，/=等。故赋值符号后使用三目，可以不加括号
ListNode* getIntersectionNode1(ListNode* headA, ListNode* headB) {
  if (!headA || !headB)
    return nullptr;
  ListNode* pA = headA;
  ListNode* pB = headB;
  while (pA != pB) {
    pA = pA == nullptr ? headB : pA->next;
    pB = pB == nullptr ? headA : pB->next;
  }
  return pA;
}

// 传统方法。1、分别求A、B长度；2、保证A比B长，如不是则交换；3、长链表先走x步，x为两链表长度之差。
// 4、双指针同步向后移动，如果结点相等（非值相等）则返回
ListNode* getIntersectionNode2(ListNode* headA, ListNode* headB) {
  int lenA = 0, lenB = 0;
  ListNode* pA = headA;
  ListNode* pB = headB;
  while (pA) {
    lenA++;
    pA = pA->next;
  }
  while (pB) {
    lenB++;
    pB = pB->next;
  }
  if (lenB > lenA)
    swap(headA, headB);
  pA = headA;
  pB = headB;
  int n = abs(lenA - lenB);
  while (n--)
    pA = pA->next;
  while (pA && pB) {
    if (pA == pB)
      return pA;
    pA = pA->next;
    pB = pB->next;
  }
  return nullptr;
}

int main() {
  vector<int> v1 = {4, 1, 8, 4, 5}, v2 = {5, 6, 1, 8, 4, 5};
  vector<int> v3 = {1, 9, 1, 2, 4}, v4 = {3, 2, 4};
  vector<int> v5 = {2, 6, 4}, v6 = {1, 5};
  ListNode* l1 = createList(v1);
  ListNode* l2 = createList(v2);
  ListNode* l3 = createList(v3);
  ListNode* l4 = createList(v4);
  ListNode* l5 = createList(v5);
  ListNode* l6 = createList(v6);
  cout << getIntersectionNode(l1, l2) << " " << getIntersectionNode(l3, l4)
       << " " << getIntersectionNode(l5, l6) << endl;
  cout << getIntersectionNode1(l1, l2) << " " << getIntersectionNode1(l3, l4)
       << " " << getIntersectionNode1(l5, l6) << endl;
  return 0;
}