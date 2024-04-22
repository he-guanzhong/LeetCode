#include "head.h"
/* 146. LRU 缓存
请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：
    LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
    int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1
。 void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value
；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过
capacity ，则应该 逐出 最久未使用的关键字。
函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
示例：
输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]
解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4  */

struct DLinkedList {
  int key;
  int value;
  DLinkedList* prev;
  DLinkedList* next;
  DLinkedList() {
    key = 0;
    value = 0;
    prev = nullptr;
    next = nullptr;
  }
  DLinkedList(int _key, int _value)
      : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
 public:
  LRUCache(int capacity) {
    head = new DLinkedList();
    tail = new DLinkedList();
    head->next = tail;
    tail->prev = head;
    this->capacity_ = capacity;
  }

  int get(int key) {
    if (umap.count(key)) {
      MoveToHead(umap[key]);
      return umap[key]->value;
    }
    return -1;
  }

  void put(int key, int value) {
    if (umap.count(key)) {
      DLinkedList* node = umap[key];
      node->value = value;
      MoveToHead(node);
    } else {
      DLinkedList* p = new DLinkedList(key, value);
      umap[key] = p;
      AddToHead(p);
      if (umap.size() > capacity_) {
        DLinkedList* node = tail->prev;
        umap.erase(node->key);
        DeleteNode(node);
        delete node;
        node = nullptr;
      }
    }
  }

  void MoveToHead(DLinkedList* p) {
    DeleteNode(p);
    AddToHead(p);
  }
  void DeleteNode(DLinkedList* p) {
    p->prev->next = p->next;
    p->next->prev = p->prev;
  }
  void AddToHead(DLinkedList* p) {
    p->prev = head;
    p->next = head->next;
    head->next->prev = p;
    head->next = p;
  }

  unordered_map<int, DLinkedList*> umap;
  DLinkedList* tail;
  DLinkedList* head;
  int capacity_;
};

// 哈希表+双向链表。双向链表记录访问优先级，访问过就置首，内部要同时记录key和value，以便四个辅助函数删除结点、新增结点到头部，移动结点到头部。删除末尾结点
// 删除末尾结点需要返回值，其key用于哈希表删除。构造函数初始化，要初始化虚拟头、尾结点，并将其链接。同时更新容量capacity

class LRUCache1 {
 public:
  LRUCache1(int _capacity) {
    capacity = _capacity;
    head = new DLinkedList();
    tail = new DLinkedList();
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) {
    if (cache.count(key) == 0)
      return -1;
    DLinkedList* node = cache[key];
    moveToHead(node);
    return node->value;
  }

  void put(int key, int value) {
    if (cache.count(key) != 0) {
      DLinkedList* node = cache[key];
      node->value = value;
      moveToHead(node);
    } else {
      DLinkedList* node = new DLinkedList(key, value);
      cache[key] = node;
      addToHead(node);
      if (cache.size() > capacity) {
        node = removeTail();
        cache.erase(node->key);
        delete node;
        node = nullptr;
      }
    }
  }
  void moveToHead(DLinkedList* node) {
    removeNode(node);
    addToHead(node);
  }
  void removeNode(DLinkedList* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }
  void addToHead(DLinkedList* node) {
    node->prev = head;
    node->next = head->next;
    head->next->prev = node;
    head->next = node;
  }
  DLinkedList* removeTail() {
    DLinkedList* node = tail->prev;
    removeNode(node);
    return node;
  }

 private:
  unordered_map<int, DLinkedList*> cache;
  DLinkedList* head;
  DLinkedList* tail;
  int capacity;
};

int main() {
  LRUCache lRUCache(2);
  lRUCache.put(1, 1);              // 缓存是 {1=1}
  lRUCache.put(2, 2);              // 缓存是 {1=1, 2=2}
  cout << lRUCache.get(1) << " ";  // 返回 1
  lRUCache.put(3, 3);  // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
  cout << lRUCache.get(2) << " ";  // 返回 -1 (未找到)
  lRUCache.put(4, 4);  // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
  cout << lRUCache.get(1) << " ";   // 返回 -1 (未找到)
  cout << lRUCache.get(3) << " ";   // 返回 3
  cout << lRUCache.get(4) << endl;  // 返回 4  */
  LRUCache1 lRUCache1(2);
  lRUCache1.put(1, 1);              // 缓存是 {1=1}
  lRUCache1.put(2, 2);              // 缓存是 {1=1, 2=2}
  cout << lRUCache1.get(1) << " ";  // 返回 1
  lRUCache1.put(3, 3);  // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
  cout << lRUCache1.get(2) << " ";  // 返回 -1 (未找到)
  lRUCache1.put(4, 4);  // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
  cout << lRUCache1.get(1) << " ";   // 返回 -1 (未找到)
  cout << lRUCache1.get(3) << " ";   // 返回 3
  cout << lRUCache1.get(4) << endl;  // 返回 4  */
  return 0;
}