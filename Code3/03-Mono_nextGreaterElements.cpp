#include "head.h"
/* 503. 下一个更大元素 II
给定一个循环数组 nums （ nums[nums.length - 1] 的下一个元素是 nums[0] ），返回
nums 中每个元素的 下一个更大元素 。数字 x 的 下一个更大的元素
是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应该循环地搜索它的下一个更大的数。如果不存在，则输出-1。
示例 1:
  输入: nums = [1,2,1]
  输出: [2,-1,2]
  解释: 第一个 1 的下一个更大的数是2； 数字 2 找不到下一个更大的数； 第二个 1
    的下一个最大的数需要循环搜索，结果也是 2。
示例 2:
  输入: nums = [1,2,3,4,3]
  输出: [2,3,4,-1,4] */

vector<int> nextGreaterElements(vector<int>& nums) {
  int n = nums.size();
  vector<int> ans(n, -1);
  stack<int> st;
  st.push(0);
  for (int i = 1; i < 2 * n; i++) {
    while (!st.empty() && nums[i % n] > nums[st.top()]) {
      ans[st.top()] = nums[i % n];
      st.pop();
    }
    st.push(i % n);
  }
  return ans;
}

// 两个数组收尾拼接，即模拟成环。实际可利用i%n操作下标，模拟两次遍历。
// 可以不使用insert扩容，多了O(n)操作。直接模拟两边遍历，取值i%nums.size()即可
vector<int> nextGreaterElements1(vector<int>& nums) {
  vector<int> answer(nums.size(), -1);
  stack<int> st;
  st.push(0);
  for (int i = 1; i < nums.size() * 2; i++) {
    while (!st.empty() && nums[i % nums.size()] > nums[st.top()]) {
      answer[st.top()] = nums[i % nums.size()];
      st.pop();
    }
    st.push(i % nums.size());
  }
  return answer;
}
// 循环数组，初步想法是将两个数组拼接一起，然后最终结果只取前半部分
vector<int> nextGreaterElements2(vector<int>& nums) {
  vector<int> nums1(nums.begin(), nums.end());
  nums.insert(nums.end(), nums1.begin(), nums1.end());
  vector<int> answer(nums.size(), -1);
  stack<int> st;
  st.push(0);
  for (int i = 1; i < nums.size(); i++) {
    while (!st.empty() && nums[i] > nums[st.top()]) {
      answer[st.top()] = nums[i];
      st.pop();
    }
    st.push(i);
  }
  answer.resize(nums.size() / 2);
  return answer;
}

int main() {
  vector<int> num1 = {1, 2, 1}, num2 = {1, 2, 3, 4, 3}, num3 = {2, 4},
              num4 = {1, 2, 3, 4};
  printVector(nextGreaterElements(num1));
  printVector(nextGreaterElements(num2));
  printVector(nextGreaterElements1(num1));
  printVector(nextGreaterElements1(num2));
  return 0;
}