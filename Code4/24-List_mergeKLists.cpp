#include "head.h"
/* 23. 合并 K 个升序链表
给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链表。
示例 1：
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
[  1->4->5,
  1->3->4,
  2->6 ]
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6
示例 2：
输入：lists = []
输出：[]
示例 3：
输入：lists = [[]]
输出：[] */

ListNode* merge(ListNode* l1, ListNode* l2) {
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
ListNode* mergeKLists(vector<ListNode*>& lists) {
  if (lists.empty())
    return nullptr;
  else if (lists.size() == 1)
    return lists[0];
  else if (lists.size() == 2)
    return merge(lists[0], lists[1]);
  vector<ListNode*> second;
  for (int i = 0; i < lists.size() / 2; i++) {
    second.push_back(lists.back());
    lists.pop_back();
  }
  ListNode* head1 = mergeKLists(lists);
  ListNode* head2 = mergeKLists(second);
  return merge(head1, head2);
}

// 传统方法，设置一个链表ans,与vec每一个元素合并，其时间复杂度是O(k2n)，因为要执行k次，最长为kn的链表，空间复杂度O(1);
// 分治方法，对将vec不断两两分割，设置左右标记，左闭右闭区间，作为传参。时间复杂度O(logk*kn)，空间复杂度O(logk)，因为递归logk次栈空间
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
ListNode* mergeK1(vector<ListNode*>& lists, int l, int r) {
  if (l > r)
    return nullptr;
  else if (l == r)
    return lists[l];
  int mid = (l + r) >> 1;  // 位操作代替/2
  return merge1(mergeK1(lists, l, mid), mergeK1(lists, mid + 1, r));
}
ListNode* mergeKLists1(vector<ListNode*>& lists) {
  return mergeK1(lists, 0, lists.size() - 1);
}

// 方法三，优先队列合并。先将vec各个链表头结点压入，注意，如果为空，则不应该压入。
// 由于要优先级队列要比较大小，则要重置结构体，内含值和结点。主函数中，弹出top元素，将其ptr指针链接到p，并检测ptr是否有next，有即压入。
// 队列长度k，空间复杂度O(k)。每个元素插入和删除均为logk，共有nk个元素，故时间复杂度O(nk*logk)。
// 默认大顶堆，重载<因为小的元素要下沉，less<>。小顶堆，重载>因为大的元素要下沉，greater<>。
struct Status {
  int val;
  ListNode* ptr;
  Status(int val_, ListNode* ptr_) : val(val_), ptr(ptr_) {}
  // 重载<构造大顶堆
  bool operator<(const Status& rhs) const { return val > rhs.val; };
};
struct cmp {
  bool operator()(const ListNode* a, const ListNode* b) {
    return a->val > b->val;  // 小顶堆，greater
  }
};
auto cmp = [](const ListNode* a, const ListNode* b) { return a->val > b->val; };
ListNode* mergeKLists2(vector<ListNode*>& lists) {
  // priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> que(cmp);
  priority_queue<Status> que;
  ListNode* dummy = new ListNode(0);
  ListNode* p = dummy;
  for (ListNode* node : lists) {
    if (node)
      que.push({node->val, node});
  }
  while (!que.empty()) {
    Status f = que.top();
    que.pop();
    p->next = f.ptr;
    p = p->next;
    if (f.ptr->next) {
      que.push({f.ptr->next->val, f.ptr->next});
    }
  }
  return dummy->next;
}

int main() {
  vector<int> vec1{1, 4, 5}, vec2{1, 3, 4}, vec3{2, 6}, vec4{};
  ListNode* l1 = createList(vec1);
  ListNode* l2 = createList(vec2);
  ListNode* l3 = createList(vec3);
  ListNode* l4 = createList(vec4);
  vector<ListNode*> test1;
  test1.push_back(l1);
  test1.push_back(l2);
  test1.push_back(l3);
  vector<ListNode*> test2;
  vector<ListNode*> test3;
  test3.push_back(l4);

  vector<ListNode*> test4 = test1;
  vector<ListNode*> test5 = test2;
  vector<ListNode*> test6 = test3;

  printList(mergeKLists(test1));
  printList(mergeKLists(test2));
  printList(mergeKLists(test3));

  return 0;
}