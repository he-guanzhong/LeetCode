#include "head.h"
/* 621. 任务调度器
给你一个用字符数组 tasks 表示的 CPU 需要执行的任务列表，用字母 A 到 Z
表示，以及一个冷却时间
n。每个周期或时间间隔允许完成一项任务。任务可以按任何顺序完成，但有一个限制：两个
相同种类 的任务之间必须有长度为 n 的冷却时间。
返回完成所有任务所需要的 最短时间间隔 。
示例 1：
输入：tasks = ["A","A","A","B","B","B"], n = 2
输出：8
解释：A -> B -> (待命) -> A -> B -> (待命) -> A -> B
     在本示例中，两个相同类型任务之间必须间隔长度为 n = 2
的冷却时间，而执行一个任务只需要一个单位时间，所以中间出现了（待命）状态。
示例 2：
输入：tasks = ["A","A","A","B","B","B"], n = 0
输出：6
解释：在这种情况下，任何大小为 6 的排列都可以满足要求，因为 n = 0
["A","A","A","B","B","B"]
["A","B","A","B","A","B"]
["B","B","B","A","A","A"]
...
诸如此类
示例 3：
输入：tasks = ["A","A","A","A","A","A","B","C","D","E","F","G"], n = 2
输出：16
解释：一种可能的解决方案是：
     A -> B -> C -> A -> D -> E -> A -> F -> G -> A -> (待命) -> (待命) -> A ->
(待命) -> (待命) -> A */

int leastInterval(vector<char>& tasks, int n) {
  vector<int> map(26, 0);
  int len = tasks.size();
  int maxNum = 0;
  for (int i = 0; i < len; i++) {
    map[tasks[i] - 'A']++;
  }
  int last = 1;
  for (int i = 0; i < 26; i++) {
    if (map[i] > maxNum) {
      maxNum = map[i];
      last = 1;
    } else if (map[i] == maxNum)
      last++;
  }
  return max(len, (maxNum - 1) * (n + 1) + last);
}

// 统计所有任务数量len。由于任务最多26种，建立哈希表保存每种任务数量。我们并不关心任务具体是什么，只关心最多任务量的那个任务，数量为多少
// 排序后首元素即保存了某任务的最大任务数，即为桶数N。最后一个桶的数量cnt，先初始化为1，然后看是否最多数量的任务不止一种，只要相等，就加一
// 若填不满，(N-1)*(n+1)+cnt。若已经填满，则为最大任务数len。最终返回二者最大值
// 时间复杂度O(nlogn)，如果不排序，直接遍历过程中，找到最大值N，及最大值相等的个数cnt。时间复杂度可进一步压缩
int leastInterval1(vector<char>& tasks, int n) {
  int len = tasks.size();
  vector<int> map(26);
  for (char c : tasks)
    map[c - 'A']++;
  sort(map.begin(), map.end(), greater<int>());
  int cnt = 1;
  while (cnt < map.size() && map[cnt] == map[0])
    cnt++;
  return max(len, (map[0] - 1) * (n + 1) + cnt);
}

// C语言版本，不使用排序。
int leastInterval2(char* tasks, int tasksSize, int n) {
  int len = tasksSize;
  int arr[26] = {0};
  for (int i = 0; i < len; i++)
    arr[tasks[i] - 'A']++;
  int N = 0, cnt = 1;
  for (int i = 0; i < 26; i++) {
    if (arr[i] > N) {
      N = arr[i];
      cnt = 1;
    } else if (arr[i] == N) {
      cnt++;
    }
  }
  return fmax(len, (N - 1) * (n + 1) + cnt);
}
int main() {
  vector<char> nums1 = {'A', 'A', 'A', 'B', 'B', 'B'},
               nums3 = {'A', 'A', 'A', 'A', 'A', 'A',
                        'B', 'C', 'D', 'E', 'F', 'G'};
  cout << leastInterval(nums1, 2) << " " << leastInterval(nums1, 0) << " "
       << leastInterval(nums3, 2) << endl;
  cout << leastInterval1(nums1, 2) << " " << leastInterval1(nums1, 0) << " "
       << leastInterval1(nums3, 2) << endl;
  return 0;
}