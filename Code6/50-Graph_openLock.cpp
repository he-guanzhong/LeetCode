#include "head.h"
/* 752. 打开转盘锁
你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： '0', '1', '2', '3',
'4', '5', '6', '7', '8', '9' 。每个拨轮可以自由旋转：例如把 '9' 变为 '0'，'0'
变为 '9' 。每次旋转都只能旋转一个拨轮的一位数字。
锁的初始数字为 '0000' ，一个代表四个拨轮的数字的字符串。
列表 deadends
包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。
字符串
target代表可以解锁的数字，你需要给出解锁需要的最小旋转次数，如果无论如何不能解锁，返回
-1 。
示例 1:
  输入：deadends = ["0201","0101","0102","1212","2002"], target = "0202"
  输出：6
解释：
  可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" ->
  "0202"。 注意 "0000" -> "0001" -> "0002" -> "0102" -> "0202"
  这样的序列是不能解锁的， 因为当拨动到 "0102" 时这个锁就会被锁定。
示例 2:
  输入: deadends = ["8888"], target = "0009"
  输出：1
  解释：把最后一位反向旋转一次即可 "0000" -> "0009"。
示例 3:
  输入: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"],
      target = "8888"
  输出：-1
  解释：无法旋转到目标数字且不被锁定。
提示：
  1 <= deadends.length <= 500
  deadends[i].length == 4
  target.length == 4
  target 不在 deadends 之中
  target 和 deadends[i] 仅由若干位数字组成 */

int openLock(vector<string>& deadends, string target) {
  unordered_set<string> uset(deadends.begin(), deadends.end());
  unordered_map<string, int> visit;
  if (target == "0000")
    return 0;
  if (uset.count("0000") || uset.count(target))
    return -1;
  struct AStar {
    string str;
    int f, g, h;
    int heuristic(const string& s, const string& target) {
      int ans = 0;
      for (int i = 0; i < 4; i++) {
        int dis = abs(s[i] - target[i]);
        ans += min(dis, 10 - dis);
      }
      return ans;
    }
    AStar(const string& s, const string& target, int _g)
        : str(s), g(_g), h(heuristic(s, target)) {
      f = g + h;
    }
    bool operator>(const AStar& other) const { return f > other.f; }
  };
  priority_queue<AStar, vector<AStar>, greater<>> que;
  AStar cur("0000", target, 0);
  que.push(cur);
  visit["0000"] = 0;
  while (!que.empty()) {
    cur = que.top();
    que.pop();
    if (cur.str == target)
      return cur.g;
    for (int i = 0; i < 4; i++) {
      string tmp = cur.str;
      tmp[i] = (tmp[i] == '9' ? '0' : tmp[i] + 1);
      if (uset.count(tmp) == 0 &&
          (visit.count(tmp) == 0 || visit[tmp] > cur.g + 1)) {
        que.push(AStar(tmp, target, cur.g + 1));
        visit[tmp] = cur.g + 1;
      }
      tmp = cur.str;
      tmp[i] = (tmp[i] == '0' ? '9' : tmp[i] - 1);
      if (uset.count(tmp) == 0 &&
          (visit.count(tmp) == 0 || visit[tmp] > cur.g + 1)) {
        que.push(AStar(tmp, target, cur.g + 1));
        visit[tmp] = cur.g + 1;
      }
    }
  }
  return -1;
}

// A星算法典例。成员变量不仅要包括此结点的字符串status_，总代价f_，距离起点代价g_，距离终点代价h_
// 启发函数heuristic对应代价h_，含义为两个字符串，4位中每一位的相距距离。其必不可能大于5，故距离为四个min(dis,10-dis)之和
// 另外优先队列默认调用less<>，生成最大堆。故重载小于号<，本类代价大于其他代价。可生成最小堆
// 主函数中，首先排除目标就是起点，和终点或起点不可达的情况。注意设置哈希集合visit，保存所有访问过的结点，以防被后续重复访问

// 注意，C++构造函数，f=g+h，可以在构造函数体内赋值，也可以初始化列表中初始化成员。
// 但是，初始化顺序由变量在类中声明的顺序决定，而不是初始化列表的顺序，所以声明f，不能再g和h之后。要么就直接早构造函数体内赋值
struct AStar1 {
  AStar1(const string& status, const string& target, int g)
      : status_(status), h_(Heuristic(status, target)), g_(g) {
    f_ = g_ + h_;  // 注意！这里不能写在初始化列表里
  }
  int Heuristic(const string& status, const string& target) {
    int ans = 0;
    for (int i = 0; i < 4; i++) {
      int dis = abs(status[i] - '0' - target[i] + '0');
      dis = min(dis, 10 - dis);
      ans += dis;
    }
    return ans;
  }
  // 比较函数必须加const
  bool operator<(const AStar1& other) const { return this->f_ > other.f_; }
  string status_;
  int f_, g_, h_;
};

int openLock1(vector<string>& deadends, string target) {
  if (target == "0000")
    return 0;
  unordered_set<string> uset(deadends.begin(), deadends.end());
  if (uset.count(target) || uset.count("0000"))
    return -1;
  unordered_map<string, int> visit;
  visit["0000"] = 0;
  AStar1 start("0000", target, 0);
  priority_queue<AStar1> pri_que;
  pri_que.push(start);
  while (!pri_que.empty()) {
    AStar1 cur = pri_que.top();
    pri_que.pop();
    if (cur.status_ == target)
      return cur.g_;

    for (int i = 0; i < 4; i++) {
      string add = cur.status_;
      add[i] = (add[i] == '9' ? '0' : add[i] + 1);
      if (!uset.count(add) && (!visit.count(add) || cur.g_ + 1 < visit[add])) {
        pri_que.push(AStar1(add, target, cur.g_ + 1));
        visit[add] = cur.g_ + 1;
      }
      string minus = cur.status_;
      minus[i] = (minus[i] == '0' ? '9' : minus[i] - 1);
      if (!uset.count(minus) &&
          (!visit.count(minus) || cur.g_ + 1 < visit[minus])) {
        pri_que.push(AStar1(minus, target, cur.g_ + 1));
        visit[minus] = cur.g_ + 1;
      }
    }
  }
  return -1;
}

// BFS解法，时间和空间复杂度均容易超时。故要做特殊处理，target就是起点，直接返回步数0。target或者起点不可达，直接返回-1
// 对string的4位中每一位分别+1和-1，注意设置哈希集合，避免上一周期判断过的元素，第二次被压入栈中
// 返回的步数就是BFS搜索圈数
int openLock2(vector<string>& deadends, string target) {
  if (target == "0000")
    return 0;
  unordered_set<string> uset(deadends.begin(), deadends.end());
  if (uset.count(target) || uset.count("0000"))
    return -1;
  unordered_set<string> visit;
  int ans = -1;
  queue<string> que;
  que.push("0000");
  visit.insert("0000");
  while (!que.empty()) {
    int size = que.size();
    ans++;
    while (size--) {
      string cur = que.front();
      que.pop();
      if (target == cur)
        return ans;
      for (int i = 0; i < 4; i++) {
        string add = cur;
        add[i] = add[i] == '9' ? '0' : add[i] + 1;
        if (add == target)
          return ans + 1;
        if (uset.count(add) == 0 && visit.count(add) == 0) {
          que.push(add);
          visit.insert(add);
        }
        string minus = cur;
        minus[i] = minus[i] == '0' ? '9' : minus[i] - 1;
        if (minus == target)
          return ans + 1;
        if (uset.count(minus) == 0 && visit.count(minus) == 0) {
          que.push(minus);
          visit.insert(minus);
        }
      }
    }
  }
  return -1;
}

int main() {
  vector<string> deadends1 = {"0201", "0101", "0102", "1212", "2002"},
                 deadends2 = {"8888"},
                 deadends3 = {"8887", "8889", "8878", "8898",
                              "8788", "8988", "7888", "9888"},
                 deadends4 = {"2321", "1231", "2011", "2333", "0300",
                              "3331", "3111", "3021", "0100", "1333"},
                 deadends5 = {"2022", "0230", "1330", "2033", "2113",
                              "2113", "2102", "3013", "0120", "3021"},
                 deadends6 = {"2321", "1231", "2011", "2333", "0300",
                              "3331", "3111", "3021", "0100", "1333"};

  string target1 = "0202", target2 = "0009", target3 = "8888", target4 = "2022",
         target5 = "3102", target6 = "2022";
  cout << openLock(deadends1, target1) << " " << openLock(deadends2, target2)
       << " " << openLock(deadends3, target3) << " "
       << openLock(deadends4, target4) << " " << openLock(deadends5, target5)
       << " " << openLock(deadends6, target6) << endl;
  cout << openLock1(deadends1, target1) << " " << openLock1(deadends2, target2)
       << " " << openLock1(deadends3, target3) << " "
       << openLock1(deadends4, target4) << " " << openLock1(deadends5, target5)
       << " " << openLock1(deadends6, target6) << endl;
  return 0;
}