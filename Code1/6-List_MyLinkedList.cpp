#include "head.h"
/* 707. 设计链表
题意：在链表类中实现这些功能：
get(index)：获取链表中第 index 个节点的值。如果索引无效，则返回-1。
addAtHead(val)：在链表的第一个元素之前添加一个值为 val
   的节点。插入后，新节点将成为链表的第一个节点。
addAtTail(val)：将值为 val的节点追加到链表的最后一个元素。
addAtIndex(index,val)：在链表中的第 index个节点之前添加值为 val  的节点。如果
index等于链表的长度，则该节点将附加到链表的末尾。如果
index大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。
deleteAtIndex(index)：如果索引 index 有效，则删除链表中的第 index 个节点。
*/

// 自设链表，其必须依赖已经创建好的ListNode，为了头插简便，成员变量要有虚头结点dummy_，为了方便判断越界，要有size_
// 构造函数中，size_置0，而虚头结点，不能为nullptr，必须为值为0的真实结点，否则其next,也即真实的链表头结点不存在
// get函数中，要判断index小于0或大于等于size。移动步数index，即为真实下标。因为是访问结点val，故p初始化为dummy_next
// addAtTail和addAtHead等操作函数，一定及时更新size_，头插直接插，尾插则要遍历到p->next为空，再插
// addAtIndex，不必使用已完成的头插和尾插函数。先判定index处于正确区间，之后p初始化为dummy_，标准插入流程，完全可以覆盖头插和尾插情况
// deleteAtIndex，判断index合规后，之后p初始化为dummy_，待删除结点要delete并置为nullptr
class MyLinkedList {
 public:
  MyLinkedList() {
    size_ = 0;
    dummy_ = new ListNode(0);
  }
  int get(int index) {
    if (index >= size_)
      return -1;
    ListNode* p = dummy_->next;
    while (index--)
      p = p->next;
    return p->val;
  }
  void addAtHead(int val) {
    ListNode* tmp = new ListNode(val);
    tmp->next = dummy_->next;
    dummy_->next = tmp;
    size_++;
  }
  void addAtTail(int val) {
    ListNode* p = dummy_;
    while (p->next)
      p = p->next;
    ListNode* tmp = new ListNode(val);
    p->next = tmp;
    size_++;
  }
  void addAtIndex(int index, int val) {
    if (index > size_)
      return;
    else if (index == size_)
      addAtTail(val);
    else if (index < 0)
      addAtHead(val);
    else {
      ListNode* p = dummy_;
      while (index--)
        p = p->next;
      ListNode* tmp = new ListNode(val);
      tmp->next = p->next;
      p->next = tmp;
      size_++;
    }
  }
  void deleteAtIndex(int index) {
    if (index >= size_)
      return;
    ListNode* p = dummy_;
    while (index--)
      p = p->next;
    p->next = p->next->next;
    size_--;
  }

  int size_;
  ListNode* dummy_;
};

class MyLinkedList1 {
 public:
  MyLinkedList1() {
    dummy_ = new ListNode(0);
    size_ = 0;
  }
  int get(int index) {
    if (index < 0 ||
        index > (size_ - 1))  // index代表了下标位置，其范围是[0, size - 1]
      return -1;
    ListNode* p = dummy_->next;
    while (index--)  // 执行index次，不能写为 --index
      p = p->next;
    return p->val;
  }
  void addAtHead(int val) {
    ListNode* tmp = new ListNode(val);
    tmp->next = dummy_->next;
    dummy_->next = tmp;
    size_++;
  }
  void addAtTail(int val) {
    ListNode* tmp = new ListNode(val);
    ListNode* p = dummy_->next;  // 由于是一路到最后，也可以写为 dummy_
    while (p->next)
      p = p->next;
    p->next = tmp;
    size_++;
  }
  void addAtIndex(int index, int val) {  // 不要调用已有函数
    if (index < 0)
      index = 0;
    else if (index > size_)
      return;
    ListNode* tmp = new ListNode(val);
    ListNode* p = dummy_;  // 头插要利用dummy
    while (index--)
      p = p->next;
    tmp->next = p->next;
    p->next = tmp;
    size_++;
  }
  void deleteAtIndex(int index) {
    if (index < 0 || index >= size_)
      return;
    ListNode* p = dummy_;
    while (index--)
      p = p->next;
    ListNode* tmp = p->next;  // 要释放节点
    p->next = p->next->next;
    delete tmp;  // 释放后tmp指针值不会默认为null，而是随机值，野指针
    tmp == nullptr;  // 之后程序若不小心使用tmp，则有严重问题
    size_--;
  }

  ListNode* dummy_;
  int size_;
};

int main() {
  MyLinkedList* myLinkedList = new MyLinkedList();
  myLinkedList->addAtHead(1);
  printList(myLinkedList->dummy_->next);
  myLinkedList->addAtTail(3);
  printList(myLinkedList->dummy_->next);
  myLinkedList->addAtIndex(1, 2);  // 链表变为 1->2->3
  printList(myLinkedList->dummy_->next);
  cout << myLinkedList->get(1) << endl;  // 返回 2
  myLinkedList->deleteAtIndex(1);        // 现在，链表变为 1->3
  printList(myLinkedList->dummy_->next);
  cout << myLinkedList->get(1) << endl;  // 返回 3

  MyLinkedList1* myLinkedList1 = new MyLinkedList1();
  myLinkedList1->addAtHead(1);
  printList(myLinkedList1->dummy_->next);
  myLinkedList1->addAtTail(3);
  printList(myLinkedList1->dummy_->next);
  myLinkedList1->addAtIndex(1, 2);  // 链表变为 1->2->3
  printList(myLinkedList1->dummy_->next);
  cout << myLinkedList1->get(1) << endl;  // 返回 2
  myLinkedList1->deleteAtIndex(1);        // 现在，链表变为 1->3
  printList(myLinkedList1->dummy_->next);
  cout << myLinkedList1->get(1) << endl;  // 返回 3
  return 0;
}
