#include "head.h"
/* 347. 前 K 个高频元素
给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按
任意顺序 返回答案。
示例 1:
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]
示例 2:
输入: nums = [1], k = 1
输出: [1]
提示：1 <= nums.length <= 105
    k 的取值范围是 [1, 数组中不相同的元素的个数]
    题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的
进阶：你所设计算法的时间复杂度 必须 优于 O(n log n) ，其中 n 是数组大小。 */

vector<int> topKFrequent(vector<int>& nums, int k) {
  unordered_map<int, int> umap;
  for (int i : nums)
    umap[i]++;
  auto cmp = [](pair<int, int> a, pair<int, int> b) {
    return a.second > b.second;
  };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> que(
      cmp);
  for (auto i : umap) {
    que.push(i);
    if (que.size() > k)
      que.pop();
  }
  vector<int> ans(k, 0);
  for (int i = k - 1; i >= 0; i--) {
    ans[i] = que.top().first;
    que.pop();
  }
  return ans;
}

// 传统方法：unordered_map统计各元素出现次数，转化为vector<pair>按照出现频率从大到小排序，最后result数组取前k个元素
// 时间复杂度在于排序，O(n)=nlogn，空间复杂度O(n)
// 推荐方法：得到umap后，优先级队列，使用小顶堆，堆内只维护k个元素，如果size大于k就弹出小的元素。如此时间复杂度可优化为O(n)=nlog(k)
// 注意，优先级队列priority_queue默认大顶堆，其比较函数cmp是反的，a>b表示小顶堆。
vector<int> topKFrequent2(vector<int>& nums, int k) {
  unordered_map<int, int> umap;
  for (int i : nums)
    umap[i]++;
  auto cmp = [](pair<int, int> lhs, pair<int, int> rhs) {
    return lhs.second > rhs.second;
  };
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pri_que(
      cmp);
  for (auto it = umap.begin(); it != umap.end(); it++) {
    pri_que.push(make_pair(it->first, it->second));
    if (pri_que.size() > k)
      pri_que.pop();
  }
  vector<int> result(k, 0);
  for (int i = k - 1; i >= 0; i--) {
    result[i] = pri_que.top().first;
    pri_que.pop();
  }
  return result;
}

// 优先级队列（小顶堆），仿函数与正常的比较函数，大小是相反的，即做大于右是小顶堆
// 首先使用map将每个元素频率记录。其次以元素频率为准，建立小顶堆，当容器大于k时，要弹出队首较小值
// 最后，小顶堆内仅有k个元素，将其倒叙放入输出vector中。时间复杂度nlog(k)
class MyComparison {
 public:
  bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return lhs.second > rhs.second;
  }
};  // 小顶堆比较

vector<int> topKFrequent1(vector<int>& nums, int k) {
  unordered_map<int, int> map;
  for (int i : nums)
    map[i]++;
  auto cmp = [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
    return lhs.second > rhs.second;
  };

  // 仿函数方法
  // priority_queue<pair<int, int>, vector<pair<int, int>>, MyComparison>
  // pri_que;

  // lamda表达式方法
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pri_que(
      cmp);

  for (unordered_map<int, int>::iterator it = map.begin(); it != map.end();
       it++) {
    pri_que.push(*it);
    if (pri_que.size() > k)
      pri_que.pop();
  }
  vector<int> result(k, 0);
  for (int i = k - 1; i >= 0; i--) {
    result[i] = (pri_que.top().first);  // 先弹最小的，倒序
    pri_que.pop();
  }
  return result;
  // return pri_que.top().first; //直接返回，就是第k的元素的值
}

// priority_queue练习。lamda表达式实现小顶堆函数。若使用static，则后方必须传入的是一个地址decltype(&cmp)
static bool cmp(pair<int, int>& a, pair<int, int>& b) {
  return a.first > b.first;
}
// 仿函数实现大顶堆
class MyCompare {
 public:
  bool operator()(const pair<int, int>& a, const pair<int, int>& b) {
    return a.first < b.first;
  }
};

void priorityQue() {
  priority_queue<int, vector<int>, less<int>> queBigInt;
  priority_queue<double, vector<double>> queBigDou;
  priority_queue<string, vector<string>, greater<string>> queMinStr;
  priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)>
      queMinStruct(cmp);
  priority_queue<pair<int, int>, vector<pair<int, int>>, MyCompare>
      queMaxStruct;
  queBigInt.push(1);
  queBigInt.push(2);
  queBigInt.push(3);
  cout << "大顶堆整型：" << queBigInt.top() << " \t" << " 大小："
       << queBigInt.size() << "\t";
  queBigInt.pop();
  queBigInt.pop();
  queBigInt.pop();
  cout << " 为空：" << queBigInt.empty() << endl;
  queBigDou.push(1.1);
  queBigDou.push(2.2);
  queBigDou.push(3.3);
  cout << "默认大顶堆浮点：" << queBigDou.top() << endl;
  queMinStr.push("c");
  queMinStr.push("b");
  queMinStr.push("a");
  cout << "小顶堆字符串：" << queMinStr.top() << endl;
  queMinStruct.push(make_pair(3, 10));
  queMinStruct.push(make_pair(2, 10));
  queMinStruct.push(make_pair(1, 10));
  cout << "小顶堆结构体：" << queMinStruct.top().first << " "
       << queMinStruct.top().second << endl;
  queMaxStruct.push(make_pair(1, 10));
  queMaxStruct.push(make_pair(2, 10));
  queMaxStruct.push(make_pair(3, 10));
  cout << "大顶堆结构体：" << queMaxStruct.top().first << " "
       << queMaxStruct.top().second << endl;
}

int main() {
  vector<int> nums1 = {1, 1, 1, 2, 2, 3};
  vector<int> nums2 = {1};
  int k1 = 2, k2 = 1;
  printVector(topKFrequent(nums1, k1));
  printVector(topKFrequent(nums2, k2));
  printVector(topKFrequent1(nums1, k1));
  printVector(topKFrequent1(nums2, k2));
  // priorityQue();
  return 0;
}