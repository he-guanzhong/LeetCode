#include "head.h"
/* 138. 随机链表的复制
给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random
，该指针可以指向链表中的任何节点或空节点。构造这个链表的 深拷贝。
深拷贝应该正好由 n 个 全新
节点组成，其中每个新节点的值都设为其对应的原节点的值。新节点的 next 指针和
random指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点
。例如，如果原链表中有 X 和 Y 两个节点，其中 X.random -->
Y。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。
返回复制链表的头节点。
用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val,
random_index] 表示：
    val：一个表示 Node.val 的整数。
    random_index：随机指针指向的节点索引（范围从 0 到
n-1）；如果不指向任何节点，则为  null 。
你的代码 只 接受原链表的头节点 head 作为传入参数。
示例 1：
输入：head = [[7,null],[13,0],[11,4],[10,2],[1,0]]
输出：[[7,null],[13,0],[11,4],[10,2],[1,0]]
示例 2：
输入：head = [[1,1],[2,1]]
输出：[[1,1],[2,1]]
示例 3：
输入：head = [[3,null],[3,0],[3,null]]
输出：[[3,null],[3,0],[3,null]] */

Node* copyRandomList(Node* head) {
  for (Node* p = head; p; p = p->next->next) {
    Node* q = new Node(p->val);
    q->next = p->next;
    p->next = q;
  }
  for (Node* p = head; p; p = p->next->next) {
    Node* q = p->next;
    q->random = p->random ? p->random->next : nullptr;
  }
  Node* newHead = head->next;
  for (Node* p = head; p; p = p->next) {
    Node* q = p->next;
    p->next = q->next;
    q->next = q->next ? q->next->next : nullptr;
  }
  return newHead;
}

// 方法一，外置哈希记录老、新结点对。递归退出条件，老结点为空返回空。检测该层老结点对应的是否创建过，如无，创建新结点，
// 注意，哈希必须先记录新结点，再回溯对新结点的next/random按照老结点的next/random的赋值。否则递归时永远找不到新结点，无限创建。时间、空间复杂度均为O(1)
unordered_map<Node*, Node*> cacheNode;
Node* copyRandomList2(Node* head) {
  if (!head)
    return nullptr;
  if (cacheNode.count(head) == 0) {
    Node* newNode = new Node(head->val);
    cacheNode[head] = newNode;
    newNode->next = copyRandomList2(head->next);
    newNode->random = copyRandomList2(head->random);
  }
  return cacheNode[head];
}

// 方法二，迭代结点拆分，三次遍历，一次复制A->A'，二次赋值A'的所有random结点。三次拆分A和A'，要先排除传入指针为空的情况
// 二次遍历赋值random时，注意考虑原random为空指针的特殊情况。三次遍历剪切时，考虑q是否是最后一个结点，否则为空
// 时间复杂度O(n)，空间复杂度O(1)，因为返回值不计入空间复杂度
Node* copyRandomList1(Node* head) {
  if (!head)
    return nullptr;
  // p为老结点，q为新结点。一次遍历，复制A->A'
  for (Node* p = head; p != nullptr; p = p->next->next) {
    Node* q = new Node(p->val);
    q->next = p->next;
    p->next = q;
  }
  for (Node* p = head; p != nullptr; p = p->next->next) {
    Node* q = p->next;
    q->random = p->random ? p->random->next : nullptr;
  }
  Node* newHead = head->next;  // 三次遍历前，确定新头结点
  for (Node* p = head; p != nullptr; p = p->next) {
    Node* q = p->next;
    p->next = p->next->next;
    q->next = q->next ? q->next->next : nullptr;
  }
  return newHead;
}

void printNode(Node* head) {
  while (head) {
    cout << head->val << " [" << head->next << ", " << head->random
         << "]    \t";
    head = head->next;
  }
  cout << endl;
}
int main() {
  Node* p1 = new Node(1);
  Node* p2 = new Node(2);
  Node* p3 = new Node(3);
  Node* p4 = nullptr;
  p1->next = p2, p2->next = p3;
  p1->random = p3, p3->random = p3;
  printNode(copyRandomList(p1));
  printNode(copyRandomList(p4));
  printNode(copyRandomList1(p1));
  printNode(copyRandomList1(p4));

  return 0;
}