#include "head.h"
/*  25. K 个一组翻转链表
给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k
的整数倍，那么请将最后剩余的节点保持原有顺序。
你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。
示例 1：
输入：head = [1,2,3,4,5], k = 2
输出：[2,1,4,3,5]
示例 2：
输入：head = [1,2,3,4,5], k = 3
输出：[3,2,1,4,5] */

ListNode* reverse(ListNode* head, ListNode* tail) {
  ListNode* pre = nullptr;
  ListNode* p = head;
  while (pre != tail) {
    ListNode* q = p->next;
    p->next = pre;
    pre = p;
    p = q;
  }
  return pre;
}
ListNode* reverseKGroup(ListNode* head, int k) {
  ListNode* dummy = new ListNode(0);
  dummy->next = head;
  ListNode* before = dummy;
  ListNode* p = dummy;
  while (p) {
    for (int i = 0; i < k && p; i++)
      p = p->next;
    if (p) {
      ListNode* after = p->next;
      before->next = reverse(before->next, p);
      for (int j = 0; j < k; j++)
        before = before->next;
      before->next = after;
      p = before;
    }
  }
  return dummy->next;
}

// 先写反转区间链表函数，其输入和输出均为头尾两个结点值。注意pre初始化为tail->next，p也必须终止于该结点
// 新首元素pre与老tail相遇即结束，不能写作p!=tail->next，因为tail指向已改变
// 主函数，使用[head,tail]记录区间的首尾，while内为head存在，先移动tail,不足k不直接退出。如以满足，反转[head,tail]
// 可以使用C++17新特性tie。利用pre和tail->next对新区间连接，并更新pre,head位置，时间复杂度O(1)
pair<ListNode*, ListNode*> myReverse1(ListNode* head, ListNode* tail) {
  ListNode* pre = tail->next;
  ListNode* p = head;
  while (pre != tail) {  // 不能写作p!=tail->next，因为tail指向已改变
    ListNode* tmp = p->next;
    p->next = pre;
    pre = p;
    p = tmp;
  }
  return {pre, head};  // 新pre为头，原head为尾。
}
ListNode* reverseKGroup1(ListNode* head, int k) {
  ListNode* dummy = new ListNode(-1);
  dummy->next = head;
  ListNode* pre = dummy;
  ListNode* tail = dummy;
  while (head) {
    for (int i = 0; i < k; i++) {
      tail = tail->next;
      if (!tail)
        return dummy->next;
    }
    ListNode* newStart = tail->next;
    tie(head, tail) = myReverse1(head, tail);  // C++17写法
    // pair<ListNode*, ListNode*> tmp = myReverse1(head, tail);
    // head = tmp.first;
    // tail = tmp.second;
    pre->next = head;       // 链接首
    tail->next = newStart;  // 链接尾
    pre = tail;             // 确立新区间的外起始点
    head = newStart;        // 新区间起始点
  }
  return dummy->next;
}

int main() {
  vector<int> v1 = {1, 2, 3, 4, 5}, v2 = {1, 2, 3, 4, 5};
  ListNode* l1 = createList(v1);
  ListNode* l2 = createList(v2);
  printList(reverseKGroup(l1, 2));
  printList(reverseKGroup(l1, 3));
  l1 = createList(v1), l2 = createList(v2);
  printList(reverseKGroup1(l1, 2));
  printList(reverseKGroup1(l1, 3));
  return 0;
}