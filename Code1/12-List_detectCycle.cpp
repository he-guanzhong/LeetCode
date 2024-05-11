#include "head.h"
/* 142. 环形链表 II
给定一个链表的头节点  head ，返回链表开始入环的第一个节点。 如果链表无环，则返回
null。
如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
为了表示给定链表中的环，评测系统内部使用整数
pos来表示链表尾连接到链表中的位置（索引从 0 开始）。如果 pos 是
-1，则在该链表中没有环。注意：pos不作为参数进行传递，仅仅是为了标识链表的实际情况。
不允许修改 链表。
示例 1：
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。
示例 2：
输入：head = [1,2], pos = 0
输出：返回索引为 0 的链表节点
解释：链表中有一个环，其尾部连接到第一个节点。
示例 3：
输入：head = [1], pos = -1
输出：返回 null
解释：链表中没有环。*/

// 链表是否有环求入口分两步，一、首元素出发，快指针走两步，慢指针走一步。如果相遇则必有环。
// 二、相遇点和起始点同时出发结点，每次走一步，新相遇点即为环入口
// 注意：1.快指针每次要走两步，故须判断fast和fast->next必须同时存在。不存在则返回nullptr
// 2.快慢指针首次出发时，必须先移动指针，再判断相等与否，否则一开始即相等，不入循环。
// 3.如果有环，则fast可以置为head，于slow同步出发，必然存在某一时刻slow==fast，while循环条件也可以设置如此，最终返回fast
ListNode* detectCycle(ListNode* head) {
  ListNode *fast = head, *slow = head;
  while (fast && fast->next) {
    fast = fast->next->next;
    slow = slow->next;
    if (fast == slow)
      break;
  }
  if (!fast || !fast->next)
    return nullptr;
  fast = head;
  while (fast != slow) {
    fast = fast->next;
    slow = slow->next;
  }
  return fast;
}

// 快慢指针法，快走两步，慢走一步，相遇时确定位置。从相遇点和头部各出发指针，相遇记为入口
ListNode* detectCycle1(ListNode* head) {
  ListNode* fast = head;
  ListNode* slow = head;
  while (fast && fast->next) {  // 由于fast要走两步，所以要判断fast->next
    fast = fast->next->next;
    slow = slow->next;
    if (fast == slow) {  // 快慢指针相遇就是有环
      ListNode* index1 = fast;
      ListNode* index2 = head;
      while (index1 != index2) {  // 两指针相遇
        index1 = index1->next;
        index2 = index2->next;
      }
      return index1;  // 返回环入口
    }
  }
  return nullptr;
}

int main() {
  vector<int> vec1 = {3, 2, 0, -4};
  vector<int> vec2 = {1, 2};
  vector<int> vec3 = {2, 6, 4};
  ListNode* p1 = createList(vec1);
  ListNode* p2 = createList(vec2);
  ListNode* p3 = createList(vec3);

  ListNode* tmp1 = p1->next;
  ListNode* tail1 = p1->next->next->next;
  tail1->next = tmp1;
  ListNode* tail2 = p2->next;
  tail2->next = p2;
  cout << detectCycle(p1)->val << " " << detectCycle(p2)->val << " "
       << detectCycle(p3) << endl;
  cout << detectCycle1(p1)->val << " " << detectCycle1(p2)->val << " "
       << detectCycle1(p3) << endl;
  return 0;
}