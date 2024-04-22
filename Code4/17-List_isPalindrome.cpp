#include "head.h"
/* 234. 回文链表
给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true
；否则，返回 false 。
示例 1：
输入：head = [1,2,2,1]
输出：true
示例 2：
输入：head = [1,2]
输出：false
*/

// 空间复杂度O(1)算法。辅助函数一，快慢指针找链表中心点（偶数为左，奇数为正中）。辅助函数二，反转链表，代价是将原链表中间截断。
// 利用链表中心点，保存第一段结尾，第二段反转后的开头。p\q分别指向第一、第二段开始，逐位val比较。结束后，第一段结尾指向再次反转后的第二段开头，恢复链表原始形态。
ListNode* endOfFirstHalf(ListNode* head) {
  ListNode *fast = head, *slow = head;
  while (fast->next && fast->next->next) {
    fast = fast->next->next;
    slow = slow->next;
  }
  return slow;
}
ListNode* reverseList(ListNode* head) {
  ListNode *pre = nullptr, *p = head;
  while (p) {
    ListNode* q = p->next;
    p->next = pre;
    pre = p;
    p = q;
  }
  return pre;
}

bool isPalindrome(ListNode* head) {
  if (!head || !head->next)
    return true;
  ListNode* firstEnd = endOfFirstHalf(head);
  ListNode* SecondStart = reverseList(firstEnd->next);
  ListNode* p = head;
  ListNode* q = SecondStart;
  while (q) {
    if (p->val != q->val)
      return false;
    p = p->next;
    q = q->next;
  }
  firstEnd->next = reverseList(SecondStart);
  return true;
}

// 转化为数组，双指针法判断是否回文，空间复杂度O(n)
bool isPalindrome1(ListNode* head) {
  vector<int> vec;
  ListNode* p = head;
  while (p) {
    vec.push_back(p->val);
    p = p->next;
  }
  for (int i = 0, j = vec.size() - 1; i < j; i++, j--) {
    if (vec[i] != vec[j])
      return false;
  }
  return true;
}

int main() {
  vector<int> v1 = {1, 2, 2, 1}, v2 = {1, 2};
  vector<int> v3 = {};
  ListNode* l1 = createList(v1);
  ListNode* l2 = createList(v2);
  ListNode* l3 = createList(v3);
  cout << isPalindrome(l1) << " " << isPalindrome(l2) << " " << isPalindrome(l3)
       << endl;
  cout << isPalindrome1(l1) << " " << isPalindrome1(l2) << " "
       << isPalindrome1(l3) << endl;
  return 0;
}