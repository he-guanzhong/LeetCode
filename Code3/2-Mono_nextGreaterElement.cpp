#include "head.h"
/* 496. 下一个更大元素 I
nums1 中数字 x 的 下一个更大元素 是指 x 在 nums2 中对应位置 右侧 的 第一个 比 x
大的元素。 给你两个 没有重复元素 的数组 nums1 和 nums2 ，下标从 0
开始计数，其中nums1 是 nums2 的子集。 对于每个 0 <= i < nums1.length ，找出满足
nums1[i] == nums2[j] 的下标 j ，并且在 nums2 确定 nums2[j] 的 下一个更大元素
。如果不存在下一个更大元素，那么本次查询的答案是 -1 。 返回一个长度为
nums1.length 的数组 ans 作为答案，满足 ans[i] 是如上所述的 下一个更大元素 。
示例 1：
输入：nums1 = [4,1,2], nums2 = [1,3,4,2].
输出：[-1,3,-1]
解释：nums1 中每个值的下一个更大元素如下所述：
- 4 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。
- 1 ，用加粗斜体标识，nums2 = [1,3,4,2]。下一个更大元素是 3 。
- 2 ，用加粗斜体标识，nums2 = [1,3,4,2]。不存在下一个更大元素，所以答案是 -1 。
示例 2：
输入：nums1 = [2,4], nums2 = [1,2,3,4].
输出：[3,-1]
解释：nums1 中每个值的下一个更大元素如下所述：
- 2 ，用加粗斜体标识，nums2 = [1,2,3,4]。下一个更大元素是 3 。
- 4 ，用加粗斜体标识，nums2 = [1,2,3,4]。不存在下一个更大元素，所以答案是 -1 。
*/

// 单调栈方法一，umap记录nums2每一个弹出nums2[i]，和下一个大于其的值。遍历nums1，只要在该元素曾弹出过（umap的key相等），将value赋值给结果
// 方法二，umap的记录nums1每一个值，及其下标。遍历nums2，弹出时只要发现元素存在于nums1，即取出nums1对应下标，并对结果赋值
// unordered_map 寻找key，可以使用find函数，或者count函数
vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
  vector<int> result(nums1.size(), -1);
  unordered_map<int, int> umap;
  stack<int> st;
  st.push(0);
  for (int i = 0; i < nums1.size(); i++) {
    umap[nums1[i]] = i;
  }
  for (int i = 1; i < nums2.size(); i++) {
    while (!st.empty() && nums2[i] > nums2[st.top()]) {
      if (umap.count(nums2[st.top()]) > 0) {
        int index = umap[nums2[st.top()]];
        result[index] = nums2[i];
      }
      st.pop();
    }
    st.push(i);
  }
  return result;
}

// 单调栈，先使用unordered_map记录nums1，key是元素内容，value是元素下标，并新建answer数组，由于找不到元素返回-1，故所有元素初始化为-1
// 对于nums2进行从栈底到栈顶的从大到小排列，可求第一个大于该元素的值。如果新元素小于等于栈顶元素，直接入栈nums2[i]<=nums2[st.top()]
// 如果新元素大于栈顶元素，则必须将栈顶元素弹出，直至栈顶元素为小于栈内元素。弹出过程中，如果发现即将弹出的是nums1中的元素，使用count.
// 获取nums1元素中的下标index，然后在结果数组中，使用下标记录该处nums2[i]，即为下一个更大的元素
vector<int> nextGreaterElement1(vector<int>& nums1, vector<int>& nums2) {
  vector<int> answer(nums1.size(), -1);
  unordered_map<int, int> umap;
  stack<int> st;
  st.push(0);
  for (int i = 0; i < nums1.size(); i++)
    umap[nums1[i]] = i;
  for (int i = 1; i < nums2.size(); i++) {
    if (nums2[i] <= nums2[st.top()])
      st.push(i);
    else {
      while (!st.empty() && nums2[i] > nums2[st.top()]) {
        if (umap.count(nums2[st.top()]) > 0) {
          int index = umap[nums2[st.top()]];
          answer[index] = nums2[i];
        }
        st.pop();
      }
      st.push(i);
    }
  }
  return answer;
}
// 方法二、
vector<int> nextGreaterElement2(vector<int>& nums1, vector<int>& nums2) {
  vector<int> result(nums1.size(), -1);
  unordered_map<int, int> umap;
  stack<int> st;
  st.push(0);
  for (int i = 1; i < nums2.size(); i++) {
    while (!st.empty() && nums2[i] > nums2[st.top()]) {
      umap[nums2[st.top()]] = nums2[i];
      st.pop();
    }
    st.push(i);
  }
  for (int i = 0; i < result.size(); i++) {
    if (umap.find(nums1[i]) != umap.end())
      result[i] = umap[nums1[i]];
  }
  return result;
}
// 暴力解法，时间复杂度O(n^2)
vector<int> nextGreaterElement3(vector<int>& nums1, vector<int>& nums2) {
  vector<int> answer(nums1.size(), -1);
  for (int i = 0; i < nums1.size(); i++) {
    int start = 0;
    for (int j = 0; j < nums2.size(); j++) {
      if (nums1[i] == nums2[j]) {
        start = j;
        break;
      }
    }
    for (int j = start; j < nums2.size(); j++) {
      if (nums2[j] > nums2[start]) {
        answer[i] = nums2[j];
        break;
      }
    }
  }
  return answer;
}

int main() {
  vector<int> num1 = {4, 1, 2}, num2 = {1, 3, 4, 2}, num3 = {2, 4},
              num4 = {1, 2, 3, 4};
  printVector(nextGreaterElement(num1, num2));
  printVector(nextGreaterElement(num3, num4));
  printVector(nextGreaterElement1(num1, num2));
  printVector(nextGreaterElement1(num3, num4));
  return 0;
}