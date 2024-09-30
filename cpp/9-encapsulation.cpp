#include <cmath>
#include <iostream>
using namespace std;

// C++面向对象特性：封装、继承、多态
// 对象可抽象为类，具有成员属性（变量），成员函数（方法）
// 语法 class 类名 { 访问权限： 属性/ 行为}；
// 访问权限
// public:    公共。类内可访问，类外可访问
// protected: 保护。类内可访问，类外不能访问，可继承
// private:   私有。类内可访问，类外不能访问，不可继承
// struct 和 class 区别
// 默认访问权限，struct公共，class私有。class可用于template，struct不行
class Circle {
 public:
  double m_r;  // 属性：半径，m_代表成员变量
  double perimeter() { return 2 * M_PI * m_r; }  // 行为：周长函数卸载声明里
};

class Student {
 public:
  string m_name;
  int m_number;
  void showInfo() { cout << m_name << " " << m_number << endl; }
  void setName(string name) { m_name = name; }
  void setNumber(int number) { m_number = number; }
};

class Person {
 public:
  string m_name;
  void setAge(int age) { m_age = age; }  // 私有属性公开化，权限为可写
  void getAge() { cout << "age = " << m_age << endl; }
  void setPassword(int password) { m_password = password; }      // 权限可写
  void getPassword() { cout << "PW = " << m_password << endl; }  // 权限可读
  void showInfo() {
    cout << m_name << " " << m_age << " " << m_password << endl;
  }

 protected:
  string m_car;

 private:
  int m_age;
  int m_password;
};
class Cube {
 public:
  Cube(double L, double W, double H) : m_L(L), m_W(W), m_H(H) {}
  double getL() { return m_L; }
  double getW() { return m_W; }
  double getH() { return m_H; }
  double getSurface() { return 2 * (m_L * m_W + m_W * m_H + m_H * m_L); }
  double getVolume() { return m_L * m_W * m_H; }
  bool isEqual_Class(Cube& C) {  // 成员函数判断是否相等，只需一个参数
    return C.getL() == m_L && C.getW() == m_W && C.getH() == m_H;
  }

 private:
  double m_L;
  double m_W;
  double m_H;
};
bool isEqual_All(Cube& C1, Cube& C2) {  // 全局函数判断，需要两个参数
  return C1.getH() == C2.getH() && C1.getL() == C2.getL() &&
         C1.getW() == C2.getW();
}

// 封装案例2：点和圆的关系
class Point {
 public:
  void setX(double X) { m_X = X; }
  void setY(double Y) { m_Y = Y; }
  double getX() { return m_X; }
  double getY() { return m_Y; }

 private:
  double m_X;
  double m_Y;
};
class Circle1 {
 public:
  void setCentre(Point centre) { m_centre = centre; }
  Point getCentre() { return m_centre; }
  void setR(double r) { m_r = r; }
  double getR() { return m_r; }

 private:
  double m_r;
  Point m_centre;
};
void createCircle(Circle1& circle, double r, Point& centre) {
  circle.setCentre(centre);
  circle.setR(r);
}
void isInCircle(Circle1& circle, Point& point) {
  /*   double dis = sqrt(pow(circle.getCentre().getX() - point.getX(), 2) +
                      pow(circle.getCentre().getY() - point.getY(), 2)); */
  // hypotenuse 三角形斜边，求两点距离
  double dis = hypot(circle.getCentre().getX() - point.getX(),
                     circle.getCentre().getY() - point.getY());
  if (dis > circle.getR())
    cout << "point is out of circle.\n";
  else if (dis == circle.getR())
    cout << "point is at edge of circle.\n";
  else
    cout << "point is in circle." << endl;
}
int main() {
  Circle C1;
  C1.m_r = 10;
  cout << "圆周长：" << C1.perimeter() << endl;

  Student Stu1;
  Stu1.setName("张三");
  Stu1.setNumber(123456);
  Stu1.m_name = "张四";
  Stu1.m_number = 654321;
  Stu1.showInfo();

  Person Per1;
  Per1.m_name = "李四";
  // Per1.m_age = 50; 类外不可访问
  // Per1.m_password = (13124);
  Per1.setAge(50);
  Per1.setPassword(13124);  // 仅可写
  Per1.showInfo();          // 仅可读

  Cube Cube1(1, 2, 3);
  Cube Cube2(2, 3, 4);
  cout << "cube1 surface: " << Cube1.getSurface()
       << " volume: " << Cube1.getVolume() << endl;
  cout << "isEqual ?  local-" << Cube1.isEqual_Class(Cube2) << "  All-"
       << isEqual_All(Cube1, Cube2) << endl;
  Circle1 C2;
  Point centre;
  Point point;
  centre.setX(0.0);
  centre.setY(0.0);
  point.setX(3.0);
  point.setY(-3.0);
  createCircle(C2, 5, centre);
  isInCircle(C2, point);
}