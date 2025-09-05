#include "head.h"

/* 729. 我的日程安排表 I
实现一个 MyCalendar 类来存放你的日程安排。如果要添加的日程安排不会造成 重复预订
，则可以存储这个新的日程安排。
当两个日程安排有一些时间上的交叉时（例如两个日程安排都在同一时间内），就会产生
重复预订 。
日程可以用一对整数 startTime 和 endTime 表示，这里的时间是半开区间，即
[startTime, endTime), 实数 x 的范围为，  startTime <= x < endTime 。
实现 MyCalendar 类：
    MyCalendar() 初始化日历对象。
    boolean book(int startTime, int endTime)
如果可以将日程安排成功添加到日历中而不会导致重复预订，返回 true 。否则，返回
false 并且不要将该日程安排添加到日历中。
示例：
  输入：
    ["MyCalendar", "book", "book", "book"]
    [[], [10, 20], [15, 25], [20, 30]]
  输出：
    [null, true, false, true]
  解释：
    MyCalendar myCalendar = new MyCalendar();
    myCalendar.book(10, 20); // return True
    myCalendar.book(15, 25); // return False
    ，这个日程安排不能添加到日历中，因为时间 15 已经被另一个日程安排预订了。
    myCalendar.book(20, 30); // return True
    ，这个日程安排可以添加到日历中，因为第一个日程安排预订的每个时间都小于 20
    ，且不包含时间 20 。
提示：
    0 <= start < end <= 109
    每个测试用例，调用 book 方法的次数最多不超过 1000 次。 */

class MyCalendar {
 public:
  MyCalendar() {}

  bool book(int start, int end) {
    auto it = umap.lower_bound(start);
    if (it != umap.end() && it->first < end)
      return false;
    if (it != umap.begin() && (--it)->second > start) {
      return false;
    }
    umap.insert({start, end});
    return true;
  }
  map<int, int> umap;
};

// map红黑树经典问题。插入和查询时间复杂度均为logn，自带lower_bound二分查找函数，不得使用通用形式
// lower_bound()返回第一个大于等于元素的下标，upper_bound()返回第一个大于元素的下标
// 即将插入元素[start,end]，首先要根据start查到第一个大于等于其的区间it。若此时end超过了it->left，说明有冲突
// 同理，it区间的前一区间，若start小于it->right，说明亦有冲突。
// 无冲突则将左右区间，作为键值对存入map。并返回真
class MyCalendar1 {
 public:
  MyCalendar1() { events.clear(); }

  bool book(int startTime, int endTime) {
    auto it = events.lower_bound(startTime);
    if (it != events.end() && endTime > it->first)
      return false;
    if (it != events.begin() && startTime < (--it)->second)
      return false;
    events.insert({startTime, endTime});
    return true;
  }
  map<int, int> events;
};

int main() {
  MyCalendar* myCalendar = new MyCalendar();
  cout << myCalendar->book(10, 20) << " " << myCalendar->book(15, 25) << " "
       << myCalendar->book(20, 30) << endl;
  MyCalendar1* myCalendar1 = new MyCalendar1();
  cout << myCalendar1->book(10, 20) << " " << myCalendar1->book(15, 25) << " "
       << myCalendar1->book(20, 30) << endl;
  return 0;
}