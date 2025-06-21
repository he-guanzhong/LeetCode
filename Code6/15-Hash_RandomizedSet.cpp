#include <ctime>
#include "head.h"
/* 380. O(1) 时间插入、删除和获取随机元素
实现RandomizedSet 类：
  RandomizedSet() 初始化 RandomizedSet 对象
  bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true
      ；否则，返回 false 。
  bool remove(int val) 当元素 val   存在时，从集合中移除该项，并返回 true
      ；否则，返回 false 。
  int getRandom() 随机返回现有集合中的一项
    （测试用例保证调用此方法时集合中至少存在一个元素）
    。每个元素应该有相同的概率 被返回。
你必须实现类的所有函数，并满足每个函数的 平均 时间复杂度为 O(1) 。
示例：
  输入
    ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove",
"insert", "getRandom"]
    [[], [1], [2], [2], [], [1], [2], []]
  输出
    [null, true, false, true, 2, true, false, 2]
  解释
    RandomizedSet randomizedSet = new RandomizedSet();
    randomizedSet.insert(1); // 向集合中插入 1 。返回 true 表示 1 被成功地插入。
    randomizedSet.remove(2); // 返回 false ，表示集合中不存在 2 。
    randomizedSet.insert(2); // 向集合中插入 2 。返回 true 。集合现在包含 [1,2]
    randomizedSet.getRandom(); // getRandom 应随机返回 1 或 2 。
    randomizedSet.remove(1); // 从集合中移除 1 ，返回 true 。集合现在包含 [2] 。
    randomizedSet.insert(2); // 2 已在集合中，所以返回 false 。
    randomizedSet.getRandom(); // 由于 2 是集合中唯一的数字，getRandom 总是返回
2 。 提示： -231 <= val <= 231 - 1 最多调用 insert、remove 和 getRandom 函数 2 *
105 次 在调用 getRandom 方法时，数据结构中 至少存在一个 元素。*/

class RandomizedSet {
 public:
  RandomizedSet() { srand(time(nullptr)); }

  bool insert(int val) {
    if (umap.count(val) > 0)
      return false;
    umap[val] = vec.size();
    vec.push_back(val);
    return true;
  }

  bool remove(int val) {
    if (umap.count(val) == 0)
      return false;
    int oriIndex = umap[val];
    vec[oriIndex] = vec.back();
    umap[vec.back()] = oriIndex;
    vec.pop_back();
    umap.erase(val);
    return true;
  }

  int getRandom() {
    int index = rand() % vec.size();
    return vec[index];
  }
  unordered_map<int, int> umap;
  vector<int> vec;
};

// 哈希表支持O(1)新增删除，数组支持O(1)随机访问，需要二者结合。
// 数组中保存的是下标和对应压入的值。哈希表反之，以值为key，下标为val
// insert,哈希表首先判断是否存在。不存在则在数组最末端压入，并更新哈希表下标
// remove,保存目标元素下标。哈希表，更新数组末端值，改为即将移除元素下标，并删除移除元素（重要）。数组，即将移除元素下标改存末端值。并弹出末端元素
// 随机访问，只需构造函数中撒点srand()，并在数组中随机选取一个下标返回即可
class RandomizedSet1 {
 public:
  RandomizedSet1() {
    indices.clear();
    srand(time(nullptr));
  }

  bool insert(int val) {
    if (umap.count(val))
      return false;
    umap[val] = indices.size();
    indices.push_back(val);
    return true;
  }

  bool remove(int val) {
    if (umap.count(val) == 0)
      return false;
    int index = umap[val];
    int lastVal = indices.back();
    umap[lastVal] = index;
    umap.erase(val);
    indices[index] = lastVal;
    indices.pop_back();
    return true;
  }

  int getRandom() { return indices[rand() % indices.size()]; }

 private:
  unordered_map<int, int> umap;
  vector<int> indices;
};

int main() {
  RandomizedSet* randomizedSet1 = new RandomizedSet();
  cout << randomizedSet1->insert(1) << " " << randomizedSet1->remove(2) << " "
       << randomizedSet1->insert(2) << " " << randomizedSet1->getRandom() << " "
       << randomizedSet1->remove(1) << " " << randomizedSet1->insert(2) << " "
       << randomizedSet1->getRandom() << endl;
  RandomizedSet* randomizedSet2 = new RandomizedSet();
  cout << randomizedSet2->remove(0) << " " << randomizedSet2->remove(0) << " "
       << randomizedSet2->insert(0) << " " << randomizedSet2->getRandom() << " "
       << randomizedSet2->remove(0) << " " << randomizedSet2->insert(0) << endl;
  RandomizedSet1* randomizedSet3 = new RandomizedSet1();
  cout << randomizedSet3->insert(1) << " " << randomizedSet3->remove(2) << " "
       << randomizedSet3->insert(2) << " " << randomizedSet3->getRandom() << " "
       << randomizedSet3->remove(1) << " " << randomizedSet3->insert(2) << " "
       << randomizedSet3->getRandom() << endl;
  RandomizedSet1* randomizedSet4 = new RandomizedSet1();
  cout << randomizedSet4->remove(0) << " " << randomizedSet4->remove(0) << " "
       << randomizedSet4->insert(0) << " " << randomizedSet4->getRandom() << " "
       << randomizedSet4->remove(0) << " " << randomizedSet4->insert(0) << endl;
  return 0;
}