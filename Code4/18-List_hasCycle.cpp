#include "head.h"
/* 141. 环形链表
给你一个链表的头节点 head ，判断链表中是否有环。
如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
为了表示给定链表中的环，评测系统内部使用整数 pos
来表示链表尾连接到链表中的位置（索引从 0 开始）。注意：pos 不作为参数进行传递
。仅仅是为了标识链表的实际情况。
如果链表中存在环 ，则返回 true 。 否则，返回 false 。
示例 1：
输入：head = [3,2,0,-4], pos = 1
输出：true
解释：链表中有一个环，其尾部连接到第二个节点。
示例 2：
输入：head = [1,2], pos = 0
输出：true
解释：链表中有一个环，其尾部连接到第一个节点。
示例 3：
输入：head = [1], pos = -1
输出：false
解释：链表中没有环。
*/

bool hasCycle(ListNode* head) {
  ListNode *p = head, *q = head;
  if (!p || !p->next)
    return false;
  p = p->next->next;
  q = q->next;
  while (p && q) {
    if (p == q)
      return true;
    q = q->next;
    p = p->next;
    if (p)
      p = p->next;
  }
  return false;
}

// 快慢指针法。先排除空结点，或只有一个结点且其后续为空的特殊情况。因为快指针起始点在第二个结点
// 慢指针起始点在首结点。while循环快慢指针相遇，快指针每次走两步，慢指针每次走一步，只要快指针，或其后为空，即说明无环
bool hasCycle1(ListNode* head) {
  if (!head || !head->next)
    return false;
  ListNode* fast = head->next;
  ListNode* slow = head;
  while (fast && fast->next && fast != slow) {
    if (!fast || !fast->next)
      return false;
    fast = fast->next->next;
    slow = slow->next;
  }
  return true;
}

int main() {
  vector<int> v1 = {3, 2, 0, -4}, v2 = {1, 2};
  vector<int> v3 = {1};
  ListNode* l1 = createList(v1);
  ListNode* l2 = createList(v2);
  ListNode* l3 = createList(v3);
  l1->next->next->next->next = l1->next;
  l2->next->next = l2;
  cout << hasCycle(l1) << " " << hasCycle(l2) << " " << hasCycle(l3) << endl;
  cout << hasCycle1(l1) << " " << hasCycle1(l2) << " " << hasCycle1(l3) << endl;

  return 0;
}