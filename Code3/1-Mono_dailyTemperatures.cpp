#include "head.h"
/* 739. 每日温度
给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，其中
answer[i]
是指对于第i天，下一个更高温度出现在几天后。如果气温在这之后都不会升高，请在该位置用
0 来代替。
示例 1:
输入: temperatures = [73,74,75,71,69,72,76,73] 输出:
[1,1,4,2,1,1,0,0]
示例 2:
输入: temperatures = [30,40,50,60] 输出: [1,1,1,0]
示例 3:
输入: temperatures = [30,60,90]
输出: [1,1,0] */

// 单调栈，求下一个最大元素，即保持栈底到栈顶，下标索引的元素从大到小排列，栈内存取下标。结果容器需全部初始化0。因为从大到小排列，返回结果全为0
// 对栈非空且新元素值，大于栈顶下标索引的元素，即栈顶下标找到了下一个最大值的下标，赋值给结果，并弹出栈顶下标。
vector<int> dailyTemperatures(vector<int>& temperatures) {
  stack<int> st;
  st.push(0);
  vector<int> answer(temperatures.size(), 0);
  for (int i = 1; i < temperatures.size(); i++) {
    while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
      answer[st.top()] = i - st.top();
      st.pop();
    }
    st.push(i);
  }
  return answer;
}

// 单调栈，从栈底到栈头，必须从大到小的顺序排列，求出的才是第一个大于该元素的坐标
// 时间复杂度O(n)，空间复杂度O(n)
vector<int> dailyTemperatures1(vector<int>& temperatures) {
  vector<int> answer(temperatures.size(), 0);
  stack<int> st;
  st.push(0);  // 必须先将0压入，否则后续第一个元素无top
  for (int i = 0; i < temperatures.size(); i++) {
    if (temperatures[i] < temperatures[st.top()])
      st.push(i);
    else if (temperatures[i] == temperatures[st.top()])
      st.push(i);
    else {
      while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
        answer[st.top()] = i - st.top();
        st.pop();
      }
      st.push(i);
    }
  }
  return answer;
}

// 简单写法
vector<int> dailyTemperatures2(vector<int>& temperatures) {
  vector<int> answer(temperatures.size(), 0);
  stack<int> st;
  st.push(0);
  for (int i = 0; i < temperatures.size(); i++) {
    while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
      answer[st.top()] = i - st.top();
      st.pop();
    }
    st.push(i);
  }
  return answer;
}

// 暴力解法，时间复杂度O(n^2)
vector<int> dailyTemperatures3(vector<int>& temperatures) {
  vector<int> answer(temperatures.size(), 0);
  for (int i = 0; i < temperatures.size(); i++) {
    int res = 0;
    for (int j = i + 1; j < temperatures.size(); j++) {
      res++;
      if (temperatures[j] > temperatures[i]) {
        answer[i] = res;
        break;
      }
    }
  }
  return answer;
}

int main() {
  vector<int> temp1 = {73, 74, 75, 71, 69, 72, 76, 73},
              temp2 = {30, 40, 50, 60}, temp3 = {30, 60, 90};
  printVector(dailyTemperatures(temp1));
  printVector(dailyTemperatures(temp2));
  printVector(dailyTemperatures(temp3));
  printVector(dailyTemperatures1(temp1));
  printVector(dailyTemperatures1(temp2));
  printVector(dailyTemperatures1(temp3));
}