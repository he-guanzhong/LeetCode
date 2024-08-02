#include "head.h"
/* 143. 重排链表
给定一个单链表 L 的头节点 head ，单链表 L 表示为：
L0 → L1 → … → Ln - 1 → Ln
请将其重新排列后变为：
L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
示例 1：
  输入：head = [1,2,3,4]
  输出：[1,4,2,3]
示例 2：
  输入：head = [1,2,3,4,5]
  输出：[1,5,2,4,3]
提示：
    链表的长度范围为 [1, 5 * 104]
    1 <= node.val <= 1000 */

void reorderList(ListNode* head) {}

// 对半分割链表，重新排序
ListNode* reverseList1(ListNode* head) {
  ListNode *p = head, *pre = nullptr, *tmp = nullptr;
  while (p) {
    tmp = p->next;
    p->next = pre;
    pre = p;
    p = tmp;
  }
  return pre;
}
void reorderList1(ListNode* head) {
  if (!head || !head->next)
    return;
  ListNode *fast = head, *slow = head;
  while (fast && fast->next) {  // 保证前队长度>=后队
    fast = fast->next->next;
    slow = slow->next;
  }
  // 本题由于cur1除去了首节点，故cur1长度必小于cur2长度。由于cur2为新生成，其末尾指向nullptr，故可以免去对末尾指向空的处理
  // 若任由cur1长度>=cur2，则需要提前对cur1->next提前截断，并在末尾处理cur->next=nullptr
  ListNode* cur1 = head->next;  // 前半队的待处理节点
  ListNode* cur2 = reverseList1(slow);
  ListNode* cur = head;
  int cnt = 0;
  while (cur1 && cur2) {
    if (cnt % 2 == 0) {
      cur->next = cur2;
      cur2 = cur2->next;
    } else {
      cur->next = cur1;
      cur1 = cur1->next;
    }
    cur = cur->next;
    cnt++;
  }
  return;
}

// 数组模拟。由于要求实际节点交换，故数组内存储节点信息
void reorderList2(ListNode* head) {
  if (!head)  // 末尾对head->next=nullptr有操作，所以要提前判空
    return;
  vector<ListNode*> vec;
  ListNode* cur = head;
  while (cur) {
    vec.push_back(cur);
    cur = cur->next;
  }
  cur = head;
  int cnt = 0;  // 偶数从后取值，单数从前取值
  for (int i = 1, j = vec.size() - 1; i <= j;) {
    if (cnt % 2 == 0) {
      cur->next = vec[j];
      j--;
    } else {
      cur->next = vec[i];
      i++;
    }
    cur = cur->next;
    cnt++;
  }
  cur->next = nullptr;  // 注意末尾要指向空
  return;
}

// 双端队列模拟
void reorderList3(ListNode* head) {
  if (!head)
    return;
  deque<ListNode*> que;
  ListNode* cur = head;
  while (cur->next) {  // 队列内保存的是待处理节点，故首节点不入队
    que.push_back(cur->next);
    cur = cur->next;
  }
  cur = head;
  ListNode* node = nullptr;  // 待处理节点
  int cnt = 0;
  while (que.size()) {
    if (cnt % 2 == 0) {
      node = que.back();
      que.pop_back();
    } else {
      node = que.front();
      que.pop_front();
    }
    cur->next = node;
    cur = cur->next;
    cnt++;
  }
  cur->next = nullptr;  // 末尾终处理
  return;
}

int main() {
  vector<int> nums1 = {1, 2, 3, 4}, nums2 = {1, 2, 3, 4, 5}, nums3 = {1, 2};
  ListNode *l1 = createList(nums1), *l2 = createList(nums2),
           *l3 = createList(nums3);
  reorderList(l1);
  reorderList(l2);
  reorderList(l3);
  printList(l1);
  printList(l2);
  printList(l3);
  l1 = createList(nums1), l2 = createList(nums2), l3 = createList(nums3);
  reorderList1(l1);
  reorderList1(l2);
  reorderList1(l3);
  printList(l1);
  printList(l2);
  printList(l3);
  return 0;
}