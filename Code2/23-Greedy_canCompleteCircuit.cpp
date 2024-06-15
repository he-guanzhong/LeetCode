#include "head.h"
/* 134. 加油站
在一条环路上有 n 个加油站，其中第 i 个加油站有汽油 gas[i] 升。
你有一辆油箱容量无限的的汽车，从第 i 个加油站开往第 i+1
个加油站需要消耗汽油cost[i] 升。你从其中的一个加油站出发，开始时油箱为空。
给定两个整数数组gas和cost，如果你可以按顺序绕环路行驶一周，则返回出发时加油站的编号，否则返回-1。如果存在解，则
保证 它是 唯一 的。
示例 1: 输入: gas = [1,2,3,4,5], cost = [3,4,5,1,2] 输出: 3
解释:
从 3 号加油站(索引为 3 处)出发，可获得 4 升汽油。此时油箱有 = 0 + 4 = 4 升汽油
开往 4 号加油站，此时油箱有 4 - 1 + 5 = 8 升汽油
开往 0 号加油站，此时油箱有 8 - 2 + 1 = 7 升汽油
开往 1 号加油站，此时油箱有 7 - 3 + 2 = 6 升汽油
开往 2 号加油站，此时油箱有 6 - 4 + 3 = 5 升汽油
开往 3 号加油站，你需要消耗 5 升汽油，正好足够你返回到 3 号加油站。
因此，3 可为起始索引。
示例 2:
输入: gas = [2,3,4], cost = [3,4,3]
输出: -1
解释:
你不能从 0 号或 1 号加油站出发，因为没有足够的汽油可以让你行驶到下一个加油站。
我们从 2 号加油站出发，可以获得 4 升汽油。 此时油箱有 = 0 + 4 = 4 升汽油
开往 0 号加油站，此时油箱有 4 - 3 + 2 = 3 升汽油
开往 1 号加油站，此时油箱有 3 - 3 + 3 = 3 升汽油
你无法返回 2 号加油站，因为返程需要消耗 4 升汽油，但是你的油箱只有 3 升汽油。
因此，无论怎样，你都不可能绕环路行驶一周。 */

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
  int curSum = 0, start = 0, totalSum = 0;
  for (int i = 0; i < gas.size(); i++) {
    int gap = gas[i] - cost[i];
    totalSum += gap;
    curSum += gap;
    if (curSum < 0) {
      curSum = 0;
      start = i + 1;
    }
  }
  return totalSum < 0 ? -1 : start;
}

// 贪心，计算全局油量和当前油量。到达i时当前剩油小于0，说明[0,i]区间任意一结点出发，必到不了。当前剩油归零，并start设置为i+1。
// 判断全局油量是否小于0，如小则不可行。如大于0，则返回start

// 全局思路，记录当前剩余油量总和，和历史出现最低油量。情况一、如果剩余油量总和小于0，不可行。
// 情况二，历史最低油量大于0，说明首元素为出发点（题目规定只有唯一解）
// 情况三、历史最低值小于0，说明起始点不是首元素，则从后向前，寻找可以填平谷底结点，即为起点
int canCompleteCircuit1(vector<int>& gas, vector<int>& cost) {
  int curSum = 0, min = INT_MAX;
  for (int i = 0; i < gas.size(); i++) {
    curSum += gas[i] - cost[i];
    if (min > curSum)
      min = curSum;
  }
  if (curSum < 0)
    return -1;
  if (min >= 0)
    return 0;
  for (int i = gas.size() - 1; i >= 0; i--) {
    min += gas[i] - cost[i];
    if (min >= 0)
      return i;
  }
  return -1;
}

// 从0开始遍历，记录剩余油量当前总和，和全局总和，若当前总和<0，则start必从i+1开始。最后判断全局总和<0则不可行。
int canCompleteCircuit2(vector<int>& gas, vector<int>& cost) {
  int start = 0;
  int curSum = 0, totalSum = 0;
  for (int i = 0; i < gas.size(); i++) {
    curSum += gas[i] - cost[i];
    totalSum += gas[i] - cost[i];
    if (curSum < 0) {
      start = i + 1;
      curSum = 0;
    }
  }
  if (totalSum < 0)
    return -1;
  return start;
}

int main() {
  vector<int> gas1 = {1, 2, 3, 4, 5};
  vector<int> cost1 = {3, 4, 5, 1, 2};
  vector<int> gas2 = {2, 3, 4};
  vector<int> cost2 = {3, 4, 3};
  vector<int> gas3 = {5, 8, 2, 8};
  vector<int> cost3 = {6, 5, 6, 6};
  cout << canCompleteCircuit(gas1, cost1) << " "
       << canCompleteCircuit(gas2, cost2) << " "
       << canCompleteCircuit(gas3, cost3) << " " << endl;
  gas1 = {1, 2, 3, 4, 5};
  cost1 = {3, 4, 5, 1, 2};
  gas2 = {2, 3, 4};
  cost2 = {3, 4, 3};
  gas3 = {5, 8, 2, 8};
  cost3 = {6, 5, 6, 6};
  cout << canCompleteCircuit2(gas1, cost1) << " "
       << canCompleteCircuit2(gas2, cost2) << " "
       << canCompleteCircuit2(gas3, cost3) << " " << endl;
  return 0;
}