#include "head.h"
/* 430. 扁平化多级双向链表
你会得到一个双链表，其中包含的节点有一个下一个指针、一个前一个指针和一个额外的
子指针。这个子指针可能指向一个单独的双向链表，也包含这些特殊的节点。这些子列表可以有一个或多个自己的子列表，
以此类推，以生成如下面的示例所示的多层数据结构 。
给定链表的头节点 head ，将链表 扁平化 ，以便所有节点都出现在单层双链表中。让
curr 是一个带有子列表的节点。子列表中的节点应该出现在扁平化列表中的 curr 之后 和
curr.next 之前 。
返回 扁平列表的 head 。列表中的节点必须将其 所有 子指针设置为 null 。
示例 1：
  输入：head = [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12]
  输出：[1,2,3,7,8,11,12,9,10,4,5,6]
  解释：输入的多级列表如上图所示。
  扁平化后的链表如下图：
示例 2：
  输入：head = [1,2,null,3]
  输出：[1,3,2]
  解释：输入的多级列表如上图所示。
  扁平化后的链表如下图：
示例 3：
  输入：head = []
  输出：[]
  说明：输入中可能存在空列表。
提示：
  节点数目不超过 1000
  1 <= Node2.val <= 105
  如何表示测试用例中的多级链表？
    以 示例 1 为例：
    1---2---3---4---5---6--NULL
             |
         7---8---9---10--NULL
             |
             11--12--NULL
  序列化其中的每一级之后：
    [1,2,3,4,5,6,null]
    [7,8,9,10,null]
    [11,12,null]
  为了将每一级都序列化到一起，我们需要每一级中添加值为 null
  的元素，以表示没有节点连接到上一级的上级节点。
    [1,2,3,4,5,6,null]
    [null,null,7,8,9,10,null]
    [null,11,12,null]
  合并所有序列化结果，并去除末尾的 null 。
    [1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12] */

class Node2 {
 public:
  int val;
  Node2* prev;
  Node2* next;
  Node2* child;
};

Node2* dfs(Node2* head) {
  if (!head)
    return head;
  Node2 *p = head, *pre = p;
  while (p) {
    pre = p;
    if (!p->child) {
      p = p->next;
      continue;
    }
    Node2* newHead = p->next;
    Node2* subChild = p->child;
    p->child = nullptr;
    subChild->prev = p;
    p->next = subChild;
    Node2* subEnd = dfs(subChild);
    subEnd->next = newHead;
    if (newHead)
      newHead->prev = subEnd;
    p = subEnd;
  }
  return pre;
}
Node2* flatten(Node2* head) {
  dfs(head);
  return head;
}

// 原函数入参、返回值要求均是首结点。与递归函数dfs要求入参为子串首节点，返回值是子串末节点不同。故单独设立函数
// 由于辅助函数要求返回的是child串最后一个有值的结点，故除设置遍历结点p，仍需保存其上一结点pre，作为有值的返回值
// 对无child的结点，直接更新pre，并p后移一步。对有child结点，先保存本层级下一待拼接头结点realNext。
// 对当前p及其p->child做三个操作。p后值child，child前指p，p的child指针置空
// child节点作为递归函数入参，新值接收返回子串的最末节点childLast。
// childLast后指realNext，但此时realNext可能以为空，必须其有值时，才设置其前指prev为childLast
// 此时要更新p的位置到childLast，以便下一轮赋值pre。或者p直接跳到realNext，但pre记得赋值childLast
Node2* dfs1(Node2* head) {
  Node2* cur = head;
  Node2* last = nullptr;
  while (cur) {
    Node2* realNext = cur->next;
    if (cur->child) {
      Node2* childLast = dfs1(cur->child);
      cur->next = cur->child;
      cur->child->prev = cur;
      if (realNext) {
        childLast->next = realNext;
        realNext->prev = childLast;
      }
      cur->child = nullptr;
      last = childLast;
    } else {
      last = cur;
    }
    cur = realNext;
  }
  return last;
}

Node2* flatten1(Node2* head) {
  dfs1(head);
  return head;
}

int main() {
  return 0;
}