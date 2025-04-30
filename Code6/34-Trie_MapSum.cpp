#include "head.h"

/* 677. 键值映射
设计一个 map ，满足以下几点:
字符串表示键，整数表示值
返回具有前缀等于给定字符串的键的值的总和
实现一个 MapSum 类：
MapSum() 初始化 MapSum 对象
void insert(String key, int val) 插入 key-val 键值对，字符串表示键 key
，整数表示值 val 。如果键 key 已经存在，那么原来的键值对 key-value
将被替代成新的键值对。 int sum(string prefix) 返回所有以该前缀 prefix 开头的键
key 的值的总和。
示例 1：
  输入：
    ["MapSum", "insert", "sum", "insert", "sum"]
    [[], ["apple", 3], ["ap"], ["app", 2], ["ap"]]
  输出：
    [null, null, 3, null, 5]
  解释：
    MapSum mapSum = new MapSum();
    mapSum.insert("apple", 3);
    mapSum.sum("ap");           // 返回 3 (apple = 3)
    mapSum.insert("app", 2);
    mapSum.sum("ap");           // 返回 5 (apple + app = 3 + 2 = 5)
提示：
  1 <= key.length, prefix.length <= 50
  key 和 prefix 仅由小写英文字母组成
  1 <= val <= 1000
  最多调用 50 次 insert 和 sum */

// 前缀树，不仅保存节点，还要保存该节点的数值和。另外，额外的哈希表记录该字符串是否出现过，及其上一次保存值是多少
// insert()新字符串要插入，先看之前是否存在过，如是，则取出该字符串原始值，并更新哈希表。以临时变量delta记录该字符串影响节点值是增加还是减少多少。
// sum()函数直接遍历前缀树找到该节点值，遇到找不到的前缀，直接返回0
// insert()时间复杂度O(n)，n为字符串长度，即前缀树深度。sum()时间复杂度O(n)，n为前缀长度。空间复杂度O(cnm)，C为常数，小于1，n为字符串数量，m为字符串长度
struct Trie {
  vector<Trie*> children;
  int val;
  Trie() {
    children.resize(26, nullptr);
    val = 0;
  }
};

class MapSum {
 public:
  MapSum() { this->root = new Trie(); }

  void insert(string key, int val) {
    Trie* cur = root;
    int delta = val;
    if (umap.find(key) != umap.end())
      delta -= umap[key];
    umap[key] = val;
    for (const char& c : key) {
      if (!cur->children[c - 'a'])
        cur->children[c - 'a'] = new Trie();
      cur = cur->children[c - 'a'];
      cur->val += delta;
    }
  }

  int sum(string prefix) {
    Trie* cur = this->root;
    for (const char& c : prefix) {
      if (cur->children[c - 'a'])
        cur = cur->children[c - 'a'];
      else
        return 0;
    }
    return cur->val;
  }
  Trie* root;
  unordered_map<string, int> umap;
};

int main() {
  MapSum* mapSum = new MapSum();
  mapSum->insert("apple", 3);
  cout << mapSum->sum("ap") << " ";
  mapSum->insert("app", 2);
  cout << mapSum->sum("ap") << " \t";

  mapSum = new MapSum();
  mapSum->insert("a", 3);
  cout << mapSum->sum("ap") << " ";
  mapSum->insert("b", 2);
  cout << mapSum->sum("a") << " \t";

  mapSum = new MapSum();
  mapSum->insert("apple", 3);
  cout << mapSum->sum("ap") << " ";
  mapSum->insert("app", 2);
  mapSum->insert("apple", 2);
  cout << mapSum->sum("ap") << " \t";

  mapSum = new MapSum();
  mapSum->insert("apple", 3);
  cout << mapSum->sum("ap") << " ";
  mapSum->insert("app", 2);
  cout << mapSum->sum("ap") << " ";
  mapSum->insert("apple", 5);
  mapSum->insert("apple", 1);
  cout << mapSum->sum("apple") << endl;

  return 0;
}