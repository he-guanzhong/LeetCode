#include "head.h"
/* 148. 排序链表
给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。
示例 1：
  输入：head = [4,2,1,3]
  输出：[1,2,3,4]
示例 2：
  输入：head = [-1,5,3,4,0]
  输出：[-1,0,3,4,5]
示例 3：
  输入：head = []
  输出：[]
进阶：你可以在 O(n log n) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？ */

ListNode* merge(ListNode* l1, ListNode* l2) {
  ListNode* dummy = new ListNode(-1);
  ListNode* p = dummy;
  while (l1 && l2) {
    if (l1->val < l2->val) {
      p->next = l1;
      l1 = l1->next;
    } else {
      p->next = l2;
      l2 = l2->next;
    }
    p = p->next;
  }
  p->next = l1 ? l1 : l2;
  return dummy->next;
}
ListNode* sortList(ListNode* head) {
  if (!head || !head->next)
    return head;
  ListNode *fast = head, *slow = head;
  while (fast->next && fast->next->next) {
    fast = fast->next->next;
    slow = slow->next;
  }
  ListNode *head1 = head, *head2 = slow->next;
  slow->next = nullptr;
  head1 = sortList(head1);
  head2 = sortList(head2);
  return merge(head1, head2);
}

// 推荐自底向上归并排序，时间复杂度O(nlogn)空间复杂度O(1)。排除空指针后，先求链表总长度。设置虚拟头指针，将链表分为subLen从1到总长,以2的倍数遍历一遍.
// 每一轮遍历，p和pre都必须按照当前dummy初始化。遍历过程中，while保证p存在，实现对剩余段的链接。对分别保存一段、二段头节点。merge后更新pre接收，并更新结点位置
// 五个临时结点，遍历p，该段起始pre，片段head1，片段head2，剩余片段rest。
ListNode* merge1(ListNode* l1, ListNode* l2) {
  ListNode* dummy = new ListNode(0);
  ListNode* p = dummy;
  while (l1 && l2) {
    if (l1->val < l2->val) {
      p->next = l1;
      l1 = l1->next;
    } else {
      p->next = l2;
      l2 = l2->next;
    }
    p = p->next;
  }
  p->next = l1 ? l1 : l2;
  return dummy->next;
}

ListNode* sortList1(ListNode* head) {
  if (head == nullptr)
    return head;
  int len = 0;
  ListNode* p = head;
  while (p) {
    len++;
    p = p->next;
  }
  ListNode* dummy = new ListNode(0, head);            // 必须指向原head
  for (int subLen = 1; subLen < len; subLen <<= 1) {  // *=2也可以使用<<1代替
    p = dummy->next;  // 每一轮的起点head不同
    ListNode* pre = dummy;
    while (p) {
      ListNode* head1 = p;
      for (int i = 1; i < subLen && p->next; i++)  // 保证p有值，才有head2可传入
        p = p->next;
      ListNode* head2 = p->next;
      p->next = nullptr;
      p = head2;
      for (int i = 1; i < subLen && p && p->next; i++)  // 第一段p可能已到空结点
        p = p->next;
      ListNode* rest = nullptr;  // 注意保存剩余段的头节点
      if (p) {
        rest = p->next;
        p->next = nullptr;
      }
      ListNode* merged = merge1(head1, head2);
      pre->next = merged;
      while (pre->next)
        pre = pre->next;
      p = rest;
    }
  }
  return dummy->next;
}

// 题目要求时间复杂度O(nlogn)，使用递归分治+合并有序链表方法。从上至下将链表按中央切割，分别对左右两半排序，再用merge函数链接。
// 递归函数的传参为链表片段的[head,tail)。退出条件为head为空，或head至tail仅有一个结点。必须先断开head->next的联系,再返回head。
// 快慢指针找中心点。终止条件fast==tail，因为是右开区间。快慢先走一步，如果可能，快再走一步。慢指针为分割点。但此方法空间复杂度为logN
ListNode* sortList2(ListNode* head, ListNode* tail) {
  if (head == nullptr)
    return head;
  if (head->next == tail) {  // 注意head->next不是NULL，要人工断开
    head->next = nullptr;
    return head;
  }
  ListNode *fast = head, *slow = head;
  while (fast != tail) {
    slow = slow->next;
    fast = fast->next;
    if (fast != tail)
      fast = fast->next;
  }
  ListNode* mid = slow;
  return merge1(sortList2(head, mid), sortList2(mid, tail));
}
ListNode* sortList2(ListNode* head) {
  return sortList2(head, nullptr);
}

// 不推荐方法，转化为数组，空间复杂度O(n)
ListNode* sortList3(ListNode* head) {
  vector<int> vec;
  ListNode* p = head;
  while (p) {
    vec.push_back(p->val);
    p = p->next;
  }
  sort(vec.begin(), vec.end());
  p = head;
  int i = 0;
  while (p) {
    p->val = vec[i++];
    p = p->next;
  }
  return head;
}

int main() {
  vector<int> vec1{4, 2, 1, 3}, vec2{-1, 5, 3, 4, 0}, vec3{};
  ListNode* l1 = createList(vec1);
  ListNode* l2 = createList(vec2);
  ListNode* l3 = createList(vec3);
  printList(sortList(l1));
  printList(sortList(l2));
  printList(sortList(l3));
  l1 = createList(vec1);
  l2 = createList(vec2);
  l3 = createList(vec3);
  printList(sortList1(l1));
  printList(sortList1(l2));
  printList(sortList1(l3));
  return 0;
}