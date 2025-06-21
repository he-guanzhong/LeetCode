#include "head.h"

/* LCR 029. 循环有序列表的插入
给定循环单调非递减列表中的一个点，写一个函数向这个列表中插入一个新元素 insertVal
，使这个列表仍然是循环升序的。
给定的可以是这个列表中任意一个顶点的指针，并不一定是这个列表中最小元素的指针。
如果有多个满足条件的插入位置，可以选择任意一个位置插入新的值，插入后整个列表仍然保持有序。
如果列表为空（给定的节点是
null），需要创建一个循环有序列表并返回这个节点。否则。请返回原先给定的节点。
示例 1：
  输入：head = [3,4,1], insertVal = 2
  输出：[3,4,1,2]
  解释：在上图中，有一个包含三个元素的循环有序列表，你获得值为 3
    的节点的指针，我们需要向表中插入元素 2 。新插入的节点应该在 1 和 3
    之间，插入之后，整个列表如上图所示，最后返回节点 3 。
示例 2：
  输入：head = [], insertVal = 1
  输出：[1]
  解释：列表为空（给定的节点是 null），创建一个循环有序列表并返回这个节点。
示例 3：
  输入：head = [1], insertVal = 0
  输出：[1,0]
  提示：
      0 <= Number of Nodes <= 5 * 10^4
     -10^6 <= Node.val <= 10^6
     -10^6 <= insertVal <= 10^6 */

Node* insert(Node* head, int insertVal) {
  if (!head) {
    Node* node = new Node(insertVal);
    node->next = node;
    return node;
  }
  Node *p = head, *q = head->next;
  while (q != head) {
    if (p->val <= insertVal && insertVal <= q->val ||
        p->val > q->val && (insertVal > p->val || insertVal < q->val)) {
      break;
    } else {
      p = q;
      q = q->next;
    }
  }
  Node* node = new Node(insertVal);
  node->next = q;
  p->next = node;
  return head;
}

// 首先处理空链表，新增一个结点的特殊情况。提前创建好结点，因为以后必创建。若只有一个结点，则自己指向自己，返回即可
// 其余情况，设置两个指针a,b，只有两种情况可以插入，一、正常顺位a<=val<=b。二、最大值向最小值跳a>b，且此时比最小值小val<=b，或比最大值大val>=a
// 注意，循环只能遍历链表一次，故b回到head位置就退出。因此，1->2->3案例中，如果插入4时，不能在while循环中处理，一定是break之后，在外单独处理
Node* insert1(Node* head, int insertVal) {
  Node* node = new Node(insertVal);
  if (!head) {
    node->next = node;
    return node;
  }
  Node* cur = head->next;
  Node* pre = head;
  while (cur != head) {
    bool isIn = pre->val <= insertVal && insertVal <= cur->val;
    bool isEnd =
        pre->val > cur->val && (insertVal <= cur->val || insertVal >= pre->val);
    if (isIn || isEnd) {
      break;  // 核心。不能直接处理，一定要在最外，因为末尾插不会到这里
    } else {
      pre = cur;
      cur = cur->next;
    }
  }
  pre->next = node;
  node->next = cur;
  return head;
}

Node* createNode(vector<int>& vec) {
  if (vec.empty())
    return nullptr;
  Node* head = new Node(vec[0]);
  Node* p = head;
  for (int i = 1; i < vec.size(); i++) {
    p->next = new Node(vec[i]);
    p = p->next;
  }
  p->next = head;
  return head;
}
void printNode(Node* head) {
  Node* p = head;
  do {
    cout << p->val << " ";
    p = p->next;
  } while (p != head);
  cout << endl;
}

int main() {
  Node* node1 = new Node(3);
  Node* node2 = new Node(4);
  Node* node3 = new Node(1);
  node1->next = node2;
  node2->next = node3;
  node3->next = node1;
  Node* head = insert(node1, 2);
  vector<int> vec1{3, 4, 1}, vec2{}, vec3{1}, vec4{3, 5, 1};
  Node *p1 = createNode(vec1), *p2 = createNode(vec2), *p3 = createNode(vec3);
  p1 = insert(p1, 2);
  printNode(p1);
  p2 = insert(p2, 1);
  printNode(p2);
  p3 = insert(p3, 0);
  printNode(p3);
  p1 = createNode(vec1), p2 = createNode(vec2), p3 = createNode(vec3);
  p1 = insert1(p1, 2);
  printNode(p1);
  p2 = insert1(p2, 1);
  printNode(p2);
  p3 = insert1(p3, 0);
  printNode(p3);
  return 0;
}