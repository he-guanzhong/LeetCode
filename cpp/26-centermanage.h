#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#define ADMIN_FILE "26-cm_admin.txt"            // 管理员文件
#define STUDENT_FILE "26-cm_student.txt"        // 学生文件
#define TEACHER_FILE "26-cm_teacher.txt"        // 老师文件
#define COMPUTER_FILE "26-cm_computerRoom.txt"  // 机房信息文件
#define ORDER_FILE "26-cm_order.txt"            // 预约订单文件

using namespace std;
class CenterManage {
 public:
  CenterManage();
  ~CenterManage();
  void showMenu();
  void exitSystem();
  void login();
};
class ComputerRoom {
 public:
  int m_ComId;   // 机房号
  int m_MaxNum;  // 最大电脑数量
};

// 身份抽象基类。不同名字、密码，现实不同菜单，修改密码
class Identity {
 public:
  virtual void showMenu() = 0;
  virtual void changePassword() = 0;
  string m_Name;
  string m_Password;
};

// 学生：申请、查看我的、查看所有、取消预约、注销
class Student : public Identity {
 public:
  Student(string name, string pw, int id);
  Student();  // 默认构造
  virtual void showMenu() override;
  virtual void changePassword() override;
  void applyOrder();    // 申请预约
  void showMyOrder();   // 查看自身预约
  void showAllOrder();  // 查看所有预约
  void cancelOrder();   // 取消预约
  int m_Id;
};

class Teacher : public Identity {
 public:
  Teacher(string name, string pw, int id);
  Teacher();  // 默认构造
  virtual void showMenu() override;
  virtual void changePassword() override;
};

// 管理员
class Admin : public Identity {
 public:
  Admin();
  Admin(string name, string pw);
  virtual void showMenu() override;
  virtual void changePassword() override;
  void addPerson();     // 添加账号
  void showPerson();    // 查看账号
  void showComputer();  // 查看机房信息
  void showAllOrder();  // 查看所有预约
  void cleanFile();     // 清空预约记录

  void addRoom();       // 添加机房
  void deletePerson();  // 删除账号
  void deleteRoom();    // 删除机房
  vector<Student> vStu;
};
