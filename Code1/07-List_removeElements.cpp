#include "head.h"
/* 203. 移除链表元素
题意：删除链表中等于给定值 val 的所有节点。
示例 1：
  输入：head = [1,2,6,3,4,5,6], val = 6
  输出：[1,2,3,4,5]
示例 2：
  输入：head = [], val = 1
  输出：[]
示例 3：
  输入：head = [7,7,7,7], val = 7
  输出：[] */

ListNode* removeElements(ListNode* head, int val) {
  ListNode* dummy = new ListNode(0, head);
  ListNode* p = dummy;
  while (p->next) {
    if (p->next->val == val)
      p->next = p->next->next;
    else
      p = p->next;
  }
  return dummy->next;
}

// 优选生成哑节点。省去一系列头结点等于目标值的麻烦。p->next的含义是待删除的结点
ListNode* removeElements1(ListNode* head, int val) {
  ListNode* dummy = new ListNode(0);  // 生成虚拟头节点
  dummy->next = head;
  ListNode* p = dummy;
  while (p->next) {  // 不必考虑p。因其必然存在，且不会被删除
    if (p->next->val == val) {
      ListNode* tmp = p->next;
      p->next = p->next->next;
      delete tmp;
    } else {
      p = p->next;
    }
  }
  head = dummy->next;
  delete dummy;  // 必须释放原来的节点
  return head;
}

// 直接在原链表处删除。无元素，只有一个不等元素，都不需要特殊处理，因为返回head。
// 首系列元素等于目标值，则不断循环while，挪动head的起始位置。直至其不存在（删干净了）或到达第一个不等于目标值的结点
// 删除后序结点，p和p->next必须同时存在。注意删除时p不能挪动，因为下一个补上来的结点可能仍要删除。不删除时，p才能挪动
ListNode* removeElements2(ListNode* head, int val) {
  while (head && head->val == val) {  // 删除头节点，注意是 while
    ListNode* tmp = head;
    head = head->next;
    delete tmp;
  }
  ListNode* p = head;
  while (p && p->next) {  // 删除后续节点，必须有p，避免已为空的情况
    if (p->next->val == val) {
      ListNode* tmp = p->next;
      p->next = p->next->next;
      delete tmp;
    } else {
      p = p->next;
    }
  }
  return head;
}

// 剑指offer-13，已知链表头结点和结点指针，如何在O(1)时间复杂度内，删除该结点
// 先排除空指针异常，然后分三种情况：一、删除结点不是尾结点，将删除结点下一节点赋值，并删除，删除节点指向下一节点之后，复杂度O(n)
// 二、删除结点是尾结点，也是头结点(唯一结点)，删除该结点，头指针指向空。
// 三、删除结点是尾结点，链表有多个结点，从头遍历，停止于p->next到达删除结点，直接将p->next指向空
// 时间复杂度分析，对于n-1个非尾结点，时间复杂度O1，对尾结点，时间复杂度On，故整体为((n-1)+n)/n，仍为O1
void deleteNode(ListNode* pListHead, ListNode* pToBeDeleted) {
  if (!pListHead || !pToBeDeleted)
    return;
  if (pToBeDeleted->next != nullptr) {
    ListNode* pDeleteNext = pToBeDeleted->next;
    pToBeDeleted->val = pDeleteNext->val;
    pToBeDeleted->next = pDeleteNext->next;
    delete pDeleteNext;
    pDeleteNext = nullptr;
  } else if (pListHead == pToBeDeleted) {
    delete pToBeDeleted;
    pToBeDeleted = nullptr;
    pListHead = nullptr;
  } else {
    ListNode* pNode = pListHead;
    while (pNode->next != pToBeDeleted)
      pNode = pNode->next;
    pNode->next = nullptr;
    delete pToBeDeleted;
    pToBeDeleted = nullptr;
  }
}

int main() {
  vector<int> vec1 = {1, 2, 6, 3, 4, 5, 6};
  vector<int> vec2 = {};
  vector<int> vec3 = {7, 7, 7, 7};
  int val1 = 6, val2 = 1, val3 = 7;
  ListNode* p1 = createList(vec1);
  ListNode* p2 = createList(vec2);
  ListNode* p3 = createList(vec3);
  printList(removeElements(p1, val1));
  printList(removeElements(p2, val2));
  printList(removeElements(p3, val3));
  p1 = createList(vec1);
  p2 = createList(vec2);
  p3 = createList(vec3);
  printList(removeElements1(p1, val1));
  printList(removeElements1(p2, val2));
  printList(removeElements1(p3, val3));
  cout << endl;
  ListNode* p4 = createList({1, 2, 3});
  ListNode* node1 = p4->next;
  deleteNode(p4, node1);
  printList(p4);
  ListNode* node2 = p4->next;
  deleteNode(p4, node2);
  printList(p4);
  ListNode* node3 = p4;
  deleteNode(p4, node3);
  return 0;
}