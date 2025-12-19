#include "head.h"

/* LCR 115. 序列重建
给定一个长度为 n 的整数数组 nums ，其中 nums 是范围为 [1，n]
的整数的排列。还提供了一个 2D 整数数组 sequences ，其中 sequences[i] 是 nums
的子序列。 检查 nums 是否是唯一的最短 超序列 。最短 超序列 是 长度最短
的序列，并且所有序列 sequences[i] 都是它的子序列。对于给定的数组 sequences
，可能存在多个有效的 超序列 。
例如，对于 sequences = [[1,2],[1,3]] ，有两个最短的 超序列 ，[1,2,3] 和 [1,3,2]
。 而对于 sequences = [[1,2],[1,3],[1,2,3]] ，唯一可能的最短 超序列 是 [1,2,3]
。[1,2,3,4] 是可能的超序列，但不是最短的。 如果 nums 是序列的唯一最短 超序列
，则返回 true ，否则返回 false 。 子序列
是一个可以通过从另一个序列中删除一些元素或不删除任何元素，而不改变其余元素的顺序的序列。
示例 1：
  输入：nums = [1,2,3], sequences = [[1,2],[1,3]]
  输出：false
  解释：有两种可能的超序列：[1,2,3]和[1,3,2]。
    序列 [1,2] 是[1,2,3]和[1,3,2]的子序列。
    序列 [1,3] 是[1,2,3]和[1,3,2]的子序列。
    因为 nums 不是唯一最短的超序列，所以返回false。
示例 2：
  输入：nums = [1,2,3], sequences = [[1,2]]
  输出：false
  解释：最短可能的超序列为 [1,2]。
    序列 [1,2] 是它的子序列：[1,2]。
    因为 nums 不是最短的超序列，所以返回false。
示例 3：
  输入：nums = [1,2,3], sequences = [[1,2],[1,3],[2,3]]
  输出：true
  解释：最短可能的超序列为[1,2,3]。
    序列 [1,2] 是它的一个子序列：[1,2,3]。
    序列 [1,3] 是它的一个子序列：[1,2,3]。
    序列 [2,3] 是它的一个子序列：[1,2,3]。
    因为 nums 是唯一最短的超序列，所以返回true。
提示：
  n == nums.length
  1 <= n <= 104
  nums 是 [1, n] 范围内所有整数的排列
  1 <= sequences.length <= 104
  1 <= sequences[i].length <= 104
  1 <= sum(sequences[i].length) <= 105
  1 <= sequences[i][j] <= n
  sequences 的所有数组都是 唯一 的
  sequences[i] 是 nums 的一个子序列 */

bool sequenceReconstruction(vector<int>& nums, vector<vector<int>>& sequences) {
  int n = nums.size();
  vector<int> inDeg(n + 1, 0);
  vector<vector<int>> graph(n + 1);
  for (const auto& seq : sequences) {
    for (int i = 1; i < seq.size(); i++) {
      int from = seq[i - 1], to = seq[i];
      inDeg[to]++;
      graph[from].push_back(to);
    }
  }
  queue<int> que;
  for (int i = 1; i < inDeg.size(); i++) {
    if (inDeg[i] == 0)
      que.push(i);
  }
  int j = 0;
  while (!que.empty()) {
    int m = que.size();
    if (m > 1)
      return false;
    int cur = que.front();
    que.pop();
    if (cur != nums[j++])
      return false;
    for (int i = 0; i < graph[cur].size(); i++) {
      int to = graph[cur][i];
      if (--inDeg[to] == 0)
        que.push(to);
    }
  }
  return true;
}

// 拓扑排序，由于每一个sequence都确定是nums的子序列，故必可能出现两个sequence意指元素顺序不同的情况，即不存在环
// 每一个sequence均代表一条有向路径，由起点指向终点，故起点的入度必为0。总计n个结点，为方便，设置n+1大小的容器
// 入度容器，初始化即可对所有结点设置为0，题目已经说明结点范围[1,n]，故可以直接用vector建图，而非unordered_map后天建图
// 对每个sequence相邻两个字符，以邻接表的形式记录a->b。统计入度时注意，可能多个sequence同时记录了a->b这一指向，故首次更新邻接表时才统计入度
// 设置队列，将所有入度为0的结点作为起点压入。每一轮遍历时，若该轮节点数大于1，说明有两种路径可选，违背了nums时唯一最短超序列这一原则，返回假
// 对该轮结点cur所指向的各next结点，入度减1，入度为0的。继续压入队列下一轮操作，直至结束
// 鉴于题目提示中最后一条：sequences[i]必是nums子序列。因此，不存在nums和sequences无关的特殊情况。
// 只要能求出最短唯一路径，其必然和nums完全一致。故结尾处，直接返回真，无需额外判断path和nums的相等性
bool sequenceReconstruction1(vector<int>& nums,
                             vector<vector<int>>& sequences) {
  vector<int> inDeg(nums.size() + 1, 0);
  vector<unordered_set<int>> graph(nums.size() + 1);
  for (int i = 0; i < sequences.size(); i++) {
    for (int j = 1; j < sequences[i].size(); j++) {
      int from = sequences[i][j - 1], to = sequences[i][j];
      if (!graph[from].count(to)) {
        inDeg[to]++;
        graph[from].insert(to);
      }
    }
  }
  queue<int> que;
  for (int i = 1; i < inDeg.size(); i++) {
    if (inDeg[i] == 0)
      que.push(i);
  }
  while (!que.empty()) {
    if (que.size() > 1)
      return false;
    int cur = que.front();
    que.pop();
    for (const int& next : graph[cur]) {
      if (--inDeg[next] == 0)
        que.push(next);
    }
  }

  return true;
}

int main() {
  vector<int> nums1 = {1, 2, 3}, nums2 = {1, 2, 3}, nums3 = {1, 2, 3},
              nums4 = {4, 1, 5, 2, 6, 3}, nums5 = {1};
  vector<vector<int>> sequences1 = {{1, 2}, {1, 3}}, sequences2 = {{1, 2}},
                      sequences3 = {{1, 2}, {1, 3}, {2, 3}},
                      sequences4 = {{5, 2, 6, 3}, {4, 1, 5, 2}},
                      sequences5 = {{1}};
  cout << sequenceReconstruction(nums1, sequences1) << " "
       << sequenceReconstruction(nums2, sequences2) << " "
       << sequenceReconstruction(nums3, sequences3) << " "
       << sequenceReconstruction(nums4, sequences4) << " "
       << sequenceReconstruction(nums4, sequences5) << endl;
  cout << sequenceReconstruction1(nums1, sequences1) << " "
       << sequenceReconstruction1(nums2, sequences2) << " "
       << sequenceReconstruction1(nums3, sequences3) << " "
       << sequenceReconstruction1(nums4, sequences4) << " "
       << sequenceReconstruction1(nums4, sequences5) << endl;
  return 0;
}