#include "head.h"
/* 455. 分发饼干
假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。
对每个孩子i，都有一个胃口值g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干j，都有一个尺寸s[j]
。如果s[j]>=g[i]，我们可以将这个饼干j分配给孩子i，这个孩子会得到满足。
你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。
示例 1:
  输入: g = [1,2,3], s = [1,1]
  输出: 1
  解释:
    你有三个孩子和两块小饼干，3个孩子的胃口值分别是：1,2,3。
    虽然你有两块小饼干，由于他们的尺寸都是1，你只能让胃口值是1的孩子满足。
    所以你应该输出1。
示例 2:
  输入: g = [1,2], s = [1,2,3]
  输出: 2
  解释:
    你有两个孩子和三块小饼干，2个孩子的胃口值分别是1,2。
    你拥有的饼干数量和尺寸都足以让所有孩子满足。
    所以你应该输出2. */

int findContentChildren(vector<int>& g, vector<int>& s) {
  sort(s.begin(), s.end());
  sort(g.begin(), g.end());
  int ans = 0, j = 0;
  for (int i = 0; i < s.size(); i++) {
    if (j < g.size() && s[i] >= g[j]) {
      j++;
      ans++;
    }
  }
  return ans;
}

// 固定最大的饼干，因为最大的饼干必喂，从大到小遍历孩子。孩子需求满足即饼干退1
// 固定最小的孩子，因为最小的孩子必喂，从小到大遍历饼干，孩子需求满足即孩子加1
// 注意：先排序，默认为从小到大，从大到小需要greater<int>()。
// 固定的index最好外置于for，其即代表最终满足了的孩子数，不必专门result
// 细节：挪动固定index时，必须先做合规性检查，再使用下标取值，否则空集报错。合规性检查如做到for循环内，则必须&&

// 贪心算法，要先排序。最大的饼干必给出，且优先用大饼干喂大孩子
// 先固定饼干index，遍历孩子。给出的饼干数即为结果
// 不能对最大的孩子试饼干。固定孩子，遍历饼干，因为最大饼干不一定满足最大孩子的需求，程序直接退出
int findContentChildren1(vector<int>& g, vector<int>& s) {
  sort(g.begin(), g.end(), greater<int>());
  sort(s.begin(), s.end(), greater<int>());
  int result = 0;
  int index = 0;                                 // 固定饼干
  for (int i = 0; i < g.size(); i++) {           // 遍历孩子
    if (index < s.size() && s[index] >= g[i]) {  // 饼干大于孩子需求
      result++;
      index++;
    }
  }
  return result;
}

// 换思路。小孩子最可能满足，但不一定所有孩子都满足。小饼干喂饱小孩子。
// 因此固定孩子。对着最小的孩子，拿饼干由小到大全部尝试遍历一边，能喂多少喂多少。
// 如此，孩子固定的标志位index即表达了最多孩子数，无需result
int findContentChildren2(vector<int>& g, vector<int>& s) {
  sort(g.begin(), g.end());
  sort(s.begin(), s.end());
  int index = 0;                        // 固定孩子
  for (int i = 0; i < s.size(); i++) {  // 遍历饼干
    if (index < g.size() && s[i] >= g[index]) {
      index++;
    }
  }
  return index;
}

int main() {
  vector<int> g1 = {1, 2, 3}, s1 = {1, 1};
  vector<int> g2 = {1, 2, 3}, s2 = {1, 2};
  vector<int> g3 = {1, 2, 7, 10}, s3 = {1, 3, 5, 9};
  cout << findContentChildren(g1, s1) << " " << findContentChildren(g2, s2)
       << " " << findContentChildren(g3, s3) << endl;
  cout << findContentChildren1(g1, s1) << " " << findContentChildren1(g2, s2)
       << " " << findContentChildren1(g3, s3) << endl;
  return 0;
}