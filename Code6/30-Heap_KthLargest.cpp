#include "head.h"

/* 703. 数据流中的第 K 大元素
设计一个找到数据流中第 k
大元素的类（class）。注意是排序后的第 k 大元素，不是第 k 个不同的元素。
请实现 KthLargest 类：
KthLargest(int k, int[] nums) 使用整数 k 和整数流 nums 初始化对象。
int add(int val) 将 val 插入数据流 nums 后，返回当前数据流中第 k 大的元素。
示例 1：
  输入：
    ["KthLargest", "add", "add", "add", "add", "add"]
    [[3, [4, 5, 8, 2]], [3], [5], [10], [9], [4]]
  输出：[null, 4, 5, 5, 8, 8]
  解释：
    KthLargest kthLargest = new KthLargest(3, [4, 5, 8, 2]);
    kthLargest.add(3); // 返回 4
    kthLargest.add(5); // 返回 5
    kthLargest.add(10); // 返回 5
    kthLargest.add(9); // 返回 8
    kthLargest.add(4); // 返回 8
示例 2：
  输入：
    ["KthLargest", "add", "add", "add", "add"]
    [[4, [7, 7, 7, 7, 8, 3]], [2], [10], [9], [9]]
  输出：[null, 7, 7, 7, 8]
  解释：
    KthLargest kthLargest = new KthLargest(4, [7, 7, 7, 7, 8, 3]);
    kthLargest.add(2); // 返回 7
    kthLargest.add(10); // 返回 7
    kthLargest.add(9); // 返回 7
    kthLargest.add(9); // 返回 8
提示：
  0 <= nums.length <= 104
  1 <= k <= nums.length + 1
  -104 <= nums[i] <= 104
  -104 <= val <= 104
  最多调用 add 方法 104 次 */

class KthLargest {
 public:
  KthLargest(int k, vector<int>& nums) {
    size = k;
    for (int& num : nums) {
      add(num);
    }
  }

  int add(int val) {
    pq.push(val);
    while (pq.size() > size) {
      pq.pop();
    }
    return pq.top();
  }
  priority_queue<int, vector<int>, greater<>> pq;
  int size;
};

// 优先队列。最小堆，先压k个。如此对堆顶为最小元素。再压入其余元素。如果队列长度大于k，弹出队首
// 注意，构造函数中，可以调用成员函数。成员变量n，不得与局部变量同名
// 最小堆priority_queue模板要求修改第三个参数为greater<>，所以前两个参数不能省略，一定要传
// C++对象构造函数中，可以调用普通成员函数，但在此之前，成员变量必须完成初始化
class KthLargest1 {
 public:
  KthLargest1(int k, vector<int>& nums) {
    n = k;
    for (int i = 0; i < nums.size(); i++) {
      add(nums[i]);
    }
  }

  int add(int val) {
    que.push(val);
    while (que.size() > n)
      que.pop();
    return que.top();
  }
  priority_queue<int, vector<int>, greater<>> que;
  int n;
};

int main() {
  vector<int> nums1({4, 5, 8, 2}), nums2({7, 7, 7, 7, 8, 3});
  KthLargest* kthLargest1 = new KthLargest(3, nums1);
  cout << kthLargest1->add(3) << " " << kthLargest1->add(5) << " "
       << kthLargest1->add(10) << " " << kthLargest1->add(9) << " "
       << kthLargest1->add(4) << endl;
  KthLargest* kthLargest2 = new KthLargest(4, nums2);
  cout << kthLargest2->add(2) << " " << kthLargest2->add(10) << " "
       << kthLargest2->add(9) << " " << kthLargest2->add(9) << endl;

  KthLargest1* kthLargest3 = new KthLargest1(3, nums1);
  cout << kthLargest3->add(3) << " " << kthLargest3->add(5) << " "
       << kthLargest3->add(10) << " " << kthLargest3->add(9) << " "
       << kthLargest3->add(4) << endl;
  KthLargest1* kthLargest4 = new KthLargest1(4, nums2);
  cout << kthLargest4->add(2) << " " << kthLargest4->add(10) << " "
       << kthLargest4->add(9) << " " << kthLargest4->add(9) << endl;
  return 0;
}