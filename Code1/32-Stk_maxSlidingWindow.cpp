#include "head.h"
/* 239. 滑动窗口最大值
给你一个整数数组 nums，有一个大小为 k
的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k
个数字。滑动窗口每次只向右移动一位。
返回 滑动窗口中的最大值 。
示例 1：
  输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
  输出：[3,3,5,5,6,7]
  解释：
滑动窗口的位置                最大值
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
示例 2：
  输入：nums = [1], k = 1
  输出：[1] */

vector<int> maxSlidingWindow(vector<int>& nums, int k) {
  deque<int> que;
  vector<int> ans;
  for (int i = 0; i < k; i++) {
    while (!que.empty() && nums[i] > que.back())
      que.pop_back();
    que.push_back(nums[i]);
  }
  ans.push_back(que.front());
  for (int i = k; i < nums.size(); i++) {
    if (nums[i - k] == que.front())
      que.pop_front();
    while (!que.empty() && nums[i] > que.back())
      que.pop_back();
    que.push_back(nums[i]);
    ans.push_back(que.front());
  }
  return ans;
}

// 单调队列，底层可选deque，因为两端都要弹。保持滑动窗口内，队列元素递减。但不必维护所有元素，只保存以最大元素起始的元素即可。
// push函数，若元素比队尾元素大，不断弹出pop_back()队尾，直至队列内保持递减。
// pop函数，有传入参数，只有要弹出的元素等于队首元素，才弹出pop_front()
// front函数，取值直接取队首元素。对主函数，先对前k个元素压入单调队列，然后result压入第一个最大值，之后遍历处理
// 单调栈，从栈底到栈头递减，求的是第一个比该元素大的位置。单调队列，从队头到队尾递减，求的是滑动窗口内最大元素
// 自设递减单调栈，使用deque封装，弹出pop时，判断要弹出元素是否为队首最大值元素，如是则弹出，不是则不处理
// 压入push时，若队尾元素比压入元素小，则将队尾元素弹出。再压入，如此保证整个栈单调递减
// 实际运行时，先将k个元素全部压入，然后从k+1个元素开始，弹出队首，压入队尾，取最大值输出
class MyQueue1 {
 public:
  void pop(int val) {
    if (!que.empty() && val == que.front())
      que.pop_front();
  }
  void push(int val) {
    while (!que.empty() && val > que.back())
      que.pop_back();
    que.push_back(val);
  }
  int front() { return que.front(); }
  deque<int> que;
};
vector<int> maxSlidingWindow1(vector<int>& nums, int k) {
  MyQueue1 que;
  vector<int> res;
  for (int i = 0; i < k; i++)
    que.push(nums[i]);
  res.push_back(que.front());
  for (int i = k; i < nums.size(); i++) {
    que.pop(nums[i - k]);
    que.push(nums[i]);
    res.push_back(que.front());
  }
  return res;
}

int main() {
  vector<int> nums1 = {1, 3, -1, -3, 5, 3, 6, 7};
  vector<int> nums2 = {1};
  int k1 = 3, k2 = 1;
  printVector(maxSlidingWindow(nums1, k1));
  printVector(maxSlidingWindow(nums2, k2));
  printVector(maxSlidingWindow1(nums1, k1));
  printVector(maxSlidingWindow1(nums2, k2));
  return 0;
}