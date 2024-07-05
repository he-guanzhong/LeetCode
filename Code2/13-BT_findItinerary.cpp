#include "head.h"
/* 332. 重新安排行程
给你一份航线列表 tickets ，其中 tickets[i] = [fromi, toi]
表示飞机出发和降落的机场地点。请你对该行程进行重新规划排序。
所有这些机票都属于一个从 JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK
开始。如果存在多种有效的行程，请你按字典排序返回最小的行程组合。

例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前。
假定所有机票至少存在一种合理的行程。且所有的机票 必须都用一次 且 只能用一次。
  输入：tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
  输出：["JFK","MUC","LHR","SFO","SJC"]
  输入：tickets =
    [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
  输出：["JFK","ATL","JFK","SFO","ATL","SFO"]
  解释：另一种有效的行程是 ["JFK","SFO","ATL","JFK","ATL","SFO"]
    ，但是它字典排序更大更靠后。*/

unordered_map<string, map<string, int>> umap;
bool backtracking(vector<vector<string>>& tickets, vector<string>& ans) {
  if (ans.size() == tickets.size() + 1)
    return true;
  string pos = ans.back();
  for (pair<string, int> target : umap[pos]) {
    ans.push_back(target.first);
    umap[pos][target.first]--;
    if (umap[pos][target.first] >= 0) {
      if (backtracking(tickets, ans))
        return true;
    }
    ans.pop_back();
    umap[pos][target.first]++;
  }
  return false;
}
vector<string> findItinerary(vector<vector<string>>& tickets) {
  umap.clear();
  for (vector<string>& ticket : tickets) {
    umap[ticket[0]][ticket[1]]++;
  }
  vector<string> ans;
  ans.push_back("JFK");
  backtracking(tickets, ans);
  return ans;
}

// 考虑两点之间来回机票好几次的情况。故unordered_map记录起始地，由于按字母顺序去终止地，使用map记录终止地及其机票数。
// 题目必存在结果，故返回值设为布尔，第一次寻到结果即可直接返回。传入参数为result和票总数int即可，因为票细节无用，已专用unordered_map
// 广度边度，依据result队尾元素起始地，遍历umap记录的到达地。第一位到达地即压入，并票数减一。如果下一层结果为真，直接返回，无需遍历整个树
// 遍历时由于要操作票数，for循环中一定要使用引用。由于遍历map，不能使用i，只能用it

// unordered_map记录出发点，到达点，和可执行次数。在main函数中遍历整个数据得到map，构造result先将第一个机场压入
// 回溯返回值设计为bool因为只要搜索一条边，到底了即可，返回条件是票数+1=途径地数
// 横向搜索为本出发地能到达的所有目的的，只要找到一条边，就可以返回了
// map<string, int>中string不能改，所以要const，
unordered_map<string, map<string, int>> targets1;
bool backtracking1(int ticketSum, vector<string>& result) {
  if (ticketSum + 1 == result.size())
    return true;
  for (pair<const string, int>& target : targets1[result.back()]) {
    if (target.second > 0) {
      result.push_back(target.first);
      target.second--;
      if (backtracking1(ticketSum, result))
        return true;
      result.pop_back();
      target.second++;
    }
  }
  return false;
}
vector<string> findItinerary1(vector<vector<string>>& tickets) {
  vector<string> result;
  result.push_back("JFK");
  for (const vector<string>& vec : tickets) {
    targets1[vec[0]][vec[1]]++;
  }
  backtracking1(tickets.size(), result);
  return result;
}

int main() {
  vector<vector<string>> tickets1 = {
      {"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
  vector<vector<string>> tickets2 = {{"JFK", "SFO"},
                                     {"JFK", "ATL"},
                                     {"SFO", "ATL"},
                                     {"ATL", "JFK"},
                                     {"ATL", "SFO"}};
  printVector(findItinerary(tickets1));
  printVector(findItinerary(tickets2));
  printVector(findItinerary1(tickets1));
  printVector(findItinerary1(tickets2));
  return 0;
}