#include "head.h"
/* 406. 根据身高重建队列
假设有打乱顺序的一群人站成一个队列，数组 people
表示队列中一些人的属性（不一定按顺序）。每个 people{i} = {hi, ki} 表示第 i
个人的身高为 hi ，前面 正好 有 ki 个身高大于或等于 hi 的人。
请你重新构造并返回输入数组 people 所表示的队列。返回的队列应该格式化为数组 queue
，其中 queue{j} = {hj, kj} 是队列中第 j 个人的属性（queue{0}
是排在队列前面的人）。
示例 1：
  输入：people = {{7,0},{4,4},{7,1},{5,0},{6,1},{5,2}}
  输出：{{5,0},{7,0},{5,2},{6,1},{4,4},{7,1}}
  解释：
    编号为 0 的人身高为 5 ，没有身高更高或者相同的人排在他前面。
    编号为 1 的人身高为 7 ，没有身高更高或者相同的人排在他前面。
    编号为 2 的人身高为 5 ，有 2 个身高更高或者相同的人排在他前面，即编号为 0 和
1 的人。 编号为 3 的人身高为 6 ，有 1 个身高更高或者相同的人排在他前面，即编号为
1 的人。 编号为 4 的人身高为 4 ，有 4 个身高更高或者相同的人排在他前面，即编号为
    0、1、2、3 的人。 编号为 5 的人身高为 7 ，有 1
    个身高更高或者相同的人排在他前面，即编号为 1 的人。 因此
    {{5,0},{7,0},{5,2},{6,1},{4,4},{7,1}} 是重新构造后的队列。
示例 2：
  输入：people = {{6,0},{5,0},{4,0},{3,2},{2,2},{1,4}}
  输出：{{4,0},{5,0},{2,2},{3,2},{1,4},{6,0}}*/

vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
  sort(people.begin(), people.end(), [](vector<int> a, vector<int> b) {
    if (a[0] == b[0])
      return a[1] < b[1];
    else
      return a[0] > b[0];
  });
  list<vector<int>> que;
  for (int i = 0; i < people.size(); i++) {
    auto it = que.begin();
    int n = people[i][1];
    while (n--)
      it++;
    que.insert(it, people[i]);
  }
  return vector<vector<int>>(que.begin(), que.end());
}

// 先按照身高从大到小，次序从小到大排序，二次遍历时前面i个身高大于自身数量，即插入的位置。
// vector频繁插入时间复杂度n^2较大。使用list替代，但其不支持迭代器随机访问，必须设定int临时变量挪动步数
// 先按照首数字h从大到小排列，k由小到大排列。然后遍历，找到k代表的前方右几个数合格，就当作下标，插入结果中
// 时间复杂度nlogn + n^2，因为插入需要大量资源
static bool cmp(const vector<int>& a, const vector<int>& b) {
  if (a[0] == b[0])
    return a[1] < b[1];
  return a[0] > b[0];
}
vector<vector<int>> reconstructQueue1(vector<vector<int>>& people) {
  sort(people.begin(), people.end(), cmp);
  vector<vector<int>> que;
  for (int i = 0; i < people.size(); i++) {
    int position = people[i][1];
    que.insert(que.begin() + position, people[i]);
  }
  return que;
}

// 可以使用链表list来存储经常需要频繁插入的情况
vector<vector<int>> reconstructQueue2(vector<vector<int>>& people) {
  sort(people.begin(), people.end(), cmp);
  list<vector<int>> que;
  for (int i = 0; i < people.size(); i++) {
    int position = people[i][1];
    list<vector<int>>::iterator it = que.begin();
    while (position--)
      it++;
    que.insert(it, people[i]);
  }
  return vector<vector<int>>(que.begin(), que.end());
}

// 人为固定vector数组长度，避免capacity调整的时间复杂度影响
vector<vector<int>> reconstructQueue3(vector<vector<int>>& people) {
  sort(people.begin(), people.end(), cmp);
  vector<vector<int>> que(people.size(), vector<int>(2, -1));
  for (int i = 0; i < people.size(); i++) {
    int position = people[i][1];
    if (position >= que.size() - 1)
      que[position] = people[i];
    else {
      for (int j = que.size() - 2; j >= position; j--)
        que[j + 1] = que[j];
      que[position] = people[i];
    }
  }
  return que;
}

int main() {
  vector<vector<int>> people1 = {{5, 0}, {7, 0}, {5, 2},
                                 {6, 1}, {4, 4}, {7, 1}};
  vector<vector<int>> people2 = {{6, 0}, {5, 0}, {4, 0},
                                 {3, 2}, {2, 2}, {1, 4}};
  printMat(reconstructQueue(people1));
  printMat(reconstructQueue(people2));
  printMat(reconstructQueue1(people1));
  printMat(reconstructQueue1(people2));
  return 0;
}