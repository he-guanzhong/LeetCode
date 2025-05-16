#include <iostream>
using namespace std;

// 1. 虚函数作用和底层实现原理
/*
作用：通过父类指针或引用，访问子类定义的虚函数，实现多态。函数地址可以晚绑定，运行时才绑定
使用：1.父类定义虚函数，函数前加virtual；2.子类重写父类虚函数；
        3.父类指针或引用指向子类对象；4.通过父类指针调用子类虚函数
原理：
*/
#include <iostream>
#include <vector>
using namespace std;
struct Point {
  double x;
  double y;
  double cost;
};
class PathPlanner {
 public:
  PathPlanner(Point start, Point end, vector<Point> obs)
      : start_(start), end_(end), obs_(obs) {}
  virtual ~PathPlanner() = default;

 protected:
  Point start_;
  Point end_;
  vector<Point> obs_;
};

class AStar : public PathPlanner {
 public:
  AStar() = default;
  void Solve() { start_; }
  ~AStar() = default;
};

class Dijkstra : public PathPlanner {
 public:
};