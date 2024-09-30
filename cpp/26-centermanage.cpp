#include "26-centermanage.h"
// 整体菜单

CenterManage::CenterManage() {}
CenterManage::~CenterManage() {}
void CenterManage::showMenu() {
  cout << "================  欢迎来到机房预约系统！  ================" << endl;
  cout << "\t\t------------------------------------------" << endl;
  cout << "\t\t|              1.学生代表                |" << endl;
  cout << "\t\t|              2.老    师                |" << endl;
  cout << "\t\t|              3.管 理 员                |" << endl;
  cout << "\t\t|              0.退    出                |" << endl;
  cout << "\t\t------------------------------------------" << endl;
  cout << "请输入您的身份：" << endl;
  cout << endl;
}
void CenterManage::exitSystem() {
  cout << "是否要退出？" << endl;
  bool select;
  cin >> select;
  if (select) {
    cout << "欢迎下次使用！" << endl;
    system("pause");
    exit(0);
  }
}

void CenterManage::login() {}

// 管理员
Admin::Admin() {}
Admin::Admin(string name, string pw) {
  m_Name = name;
  m_Password = pw;
}
void Admin::showMenu() {
  cout << "============  欢迎管理员 " << this->m_Name
       << " 登录！ ============" << endl;
  cout << endl;
  cout << "\t\t------------------------------------------" << endl;
  cout << "\t\t|              1.添加账号                |" << endl;
  cout << "\t\t|              2.查看账号                |" << endl;
  cout << "\t\t|              3.删除账号（建设中）      |" << endl;
  cout << "\t\t|              4.添加机房                |" << endl;
  cout << "\t\t|              5.查看机房                |" << endl;
  cout << "\t\t|              6.删除机房（建设中）      |" << endl;
  cout << "\t\t|              7.查看所有预约            |" << endl;
  cout << "\t\t|              8.清空预约                |" << endl;
  cout << "\t\t|              9.修改密码（建设中）      |" << endl;
  cout << "\t\t|              0.退出登录                |" << endl;
  cout << "\t\t------------------------------------------" << endl;
  cout << "请输入您的选择：" << endl;
  cout << endl;
}

void Admin::addPerson() {
  string fileName;
  while (1) {
    cout << "请输入添加账号的类型：" << endl;
    cout << "1.添加学生  "
         << "2.添加老师  "
         << "0.返回上一层" << endl;
    int select = 0;
    cin >> select;
    switch (select) {
      case 1:
        cout << "请输入学号：" << endl;
        fileName = STUDENT_FILE;
        break;
      case 2:
        cout << "请输入职工编号：" << endl;
        fileName = TEACHER_FILE;
        break;
      case 0:
        return;
      default:
        cout << "输入有误，请重新输入：" << endl;
        break;
    }
    int id;
    cin >> id;
    string name;
    cout << "请输入姓名：" << endl;
    cin >> name;
    string password;
    cout << "请输入密码：" << endl;
    cin >> password;
    ofstream ofs(fileName, ios::out | ios::app);
    ofs << id << " " << name << " " << password << " " << endl;
    cout << "添加成功！" << endl;
    ofs.close();
    system("pause");
  }
}

void Admin::changePassword() {}
void Admin::showPerson() {}    // 查看账号
void Admin::showComputer() {}  // 查看机房信息
void Admin::showAllOrder() {}  // 查看所有预约
void Admin::cleanFile() {}     // 清空预约记录

void Admin::addRoom() {}       // 添加机房
void Admin::deletePerson() {}  // 删除账号
void Admin::deleteRoom() {}    // 删除机房

// 学生：申请、查看我的、查看所有、取消预约、注销
Student::Student(string name, string pw, int id) {
  m_Name = name;
  m_Password = pw;
  m_Id = id;
}
Student::Student() {}  // 默认构造
void Student::showMenu() {}
void Student::changePassword() {}
void Student::applyOrder() {}    // 申请预约
void Student::showMyOrder() {}   // 查看自身预约
void Student::showAllOrder() {}  // 查看所有预约
void Student::cancelOrder() {}   // 取消预约

// 教师
Teacher::Teacher(string name, string pw, int id) {}
Teacher::Teacher() {}
void Teacher::showMenu() {}
void Teacher::changePassword() {}

int main() {
  CenterManage cm;
  cm.showMenu();
  int select = 0;
  switch (select) {
    case 1:
      break;
    case 2:
      break;
    default:
      break;
  }
  return 0;
}