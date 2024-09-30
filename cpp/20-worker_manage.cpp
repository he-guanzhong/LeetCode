#include <fstream>
#include <iostream>
#include <string>
#define FILENAME "20-worker_manager.txt"
using namespace std;
class Worker {
 public:
  virtual void showInfo() = 0;
  virtual string getDeptName() = 0;
  virtual string jobDescrip() = 0;
  string m_Name;
  int m_ID;
  int m_DepartID;
};
class Boss : public Worker {
 public:
  Boss(string name, int id, int departId) {
    m_Name = name;
    m_ID = id;
    m_DepartID = departId;
  }
  void showInfo() {
    cout << "编号：" << m_ID << "\t 姓名：" << m_Name << " \t 岗位："
         << this->getDeptName() << "\t 岗位职责：" << this->jobDescrip()
         << endl;
  }
  string getDeptName() { return string("老板"); }  // 强制类型转换
  string jobDescrip() { return "管理所有事务"; }
};
class Employee : public Worker {
 public:
  Employee(string name, int id, int departId) {
    m_Name = name;
    m_ID = id;
    m_DepartID = departId;
  }
  void showInfo() {
    cout << "编号：" << m_ID << "\t 姓名：" << m_Name << " \t 岗位："
         << this->getDeptName() << "\t 岗位职责：" << this->jobDescrip()
         << endl;
  }
  string getDeptName() { return string("员工"); }  // 强制类型转换
  string jobDescrip() { return "完成普通事务"; }
};
class Manager : public Worker {
 public:
  Manager(string name, int id, int departId) {
    m_Name = name;
    m_ID = id;
    m_DepartID = departId;
  }
  void showInfo() {
    cout << "编号：" << m_ID << "\t 姓名：" << m_Name << " \t 岗位："
         << this->getDeptName() << "\t 岗位职责：" << this->jobDescrip()
         << endl;
  }
  string getDeptName() { return string("经理"); }
  string jobDescrip() { return "完成领导事务"; }
};

class WorkerManager {
 public:
  WorkerManager() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    // 1. 假定文件不存在
    if (!ifs.is_open()) {
      this->m_EmpNum = 0;
      this->m_EmpArray = nullptr;
      this->m_FileEmpty = -1;
      ifs.close();  // 直接关闭
      return;
    }
    // 2. 文件存在，但无数据
    char ch;
    ifs >> ch;
    if (ifs.eof()) {  // 读一个字符之后，直接到结尾，eof()为真，文件内容为空
      this->m_EmpNum = 0;
      this->m_EmpArray = nullptr;
      this->m_FileEmpty = 0;
      ifs.close();
      return;
    }
    // 3. 文件存在，有数据
    this->m_EmpNum = this->get_EmpNum();
    this->m_FileEmpty = 1;
    this->m_EmpArray = new Worker*[this->m_EmpNum];  // 开辟空间创建数组
    this->init_Emp();  // 文件中的数据保存在数组中
  }

  void ShowMenu() {
    cout << "*****************************************" << endl;
    cout << "********   欢迎使用职工管理系统！  ********" << endl;
    cout << "************  0.退出管理程序  ************" << endl;
    cout << "************  1.增加职工信息  ************" << endl;
    cout << "************  2.显示职工信息  ************" << endl;
    cout << "************  3.删除职工信息  ************" << endl;
    cout << "************  4.修改职工信息  ************" << endl;
    cout << "************  5.查找职工信息  ************" << endl;
    cout << "************  6.按照编号排序  ************" << endl;
    cout << "************  7.清空所有信息  ************" << endl;
    cout << "*****************************************" << endl;
  }
  void ExitSystem() {
    cout << "欢迎下次再使用！" << endl;
    system("pause");
    exit(0);
  }
  /* void AddEmp()  // 添加职工
  {
  input:
    cout << "请输入要添加的职工的数量：" << endl;
    cout << "（返回主菜单请输入0）" << endl;
    int addnum = 0;  // 记录用户输入的数量
  numinput:
    cin >> addnum;
    if (addnum == 0) {
      system("cls");
      return;
    }

    else if (addnum > 0) {
      // 计算空间大小
      int newsize =
          this->m_EmpNum + addnum;  // 新的数量=现有数量+用户输入的数量；

      // 开辟新空间
      Worker** newSpace =
          new Worker*[newsize];  // 只有用指针才能在同一数组里放不同的数据信息
      // Worker
      // *[newsize]是指针列表，**newSpace是二级指针，指向这个列表的首地址；

      // 将原来空间下的数据拷贝到新空间里
      if (this->m_EmpArray != NULL) {
        for (int i = 0; i < this->m_EmpNum; i++) {
          newSpace[i] = this->m_EmpArray[i];
        }
      }

      // 批量添加新数据
      for (int i = 0; i < addnum; i++) {
        int id;
        string name;
        int dSelect;
        cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
        cout << "（返回主菜单请输入0）" << endl;
      id_input:
        cin >> id;
        if (id == 0) {
          system("cls");
          return;
        }

        for (int j = 0; j < this->m_EmpNum; j++)  // 防止职工编号重复
        {
          if (id == this->m_EmpArray[j]
                        ->m_ID)  // 说明输入的id和现有的id重复了，让用户重新输入
          {
            cout << "您输入的职工编号" << id << "已经存在，请重新输入："
                 << endl;
            goto id_input;
          }
        }

        cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
        cout << "（返回主菜单请输入0）" << endl;
        cin >> name;
        if (name == "0") {
          system("cls");
          return;
        }

        cout << "请选择该职工的岗位：" << endl;
        cout << "（返回主菜单请输入0）" << endl;
        cout << "1.普通职工" << endl;
        cout << "2.经理" << endl;
        cout << "3.老板" << endl;

      dSelect:
        cin >> dSelect;
        if (dSelect == 0) {
          system("cls");
          return;
        } else if (dSelect < 0 || dSelect > 3) {
          cout << "无此岗位，请重新输入：" << endl;
          goto dSelect;
        }

        Worker* w = NULL;  // 创建父类指针；
        switch (dSelect) {
          case 1:
            w = new Employee(name, id, dSelect);  // 父类指针指向子类对象
            break;
          case 2:
            w = new Manager(name, id, dSelect);
            break;
          case 3:
            w = new Boss(name, id, dSelect);
            break;

          default:
            break;
        }

        // 将职工保存到数组中；
        newSpace[this->m_EmpNum + i] = w;
      }

      // 释放原有的空间
      delete[] this->m_EmpArray;  // 释放数组要加[]

      // 更改新空间的指向
      this->m_EmpArray = newSpace;

      // 更新新职工的人数；
      this->m_EmpNum = newsize;

      // 加了人，文件就不为空了；
      this->m_FileEmpty = 1;

      // 保存到本地文件中
      this->save();
      cout << "成功添加" << addnum << "名新职工！" << endl;
      cout << "继续添加请输入1，返回主菜单请输入0：" << endl;
      int goon_add;
      cin >> goon_add;
      if (goon_add == 1) {
        goto input;
      } else {
        system("cls");
        return;
      }
    } else {
      cout << "输入有误，请重新输入：" << endl;
      goto numinput;
    }

    system("pause");
    system("cls");
  } */

  void AddEmp() {
  input:
    cout << "请输入要添加的职工的数量：" << endl;
    cout << "（返回主菜单请输入0）" << endl;
    int addNum = 0;
  num_input:
    cin >> addNum;
    if (addNum == 0) {
      return;
    } else if (addNum < 0) {
      cout << "输入有误，请重新输入：" << endl;
      goto num_input;
    } else {
      int newSize = this->m_EmpNum + addNum;
      Worker** newSpace = new Worker*[newSize];
      if (this->m_EmpArray != nullptr) {  // 原数据拷贝到新空间
        for (int i = 0; i < this->m_EmpNum; i++)
          newSpace[i] = this->m_EmpArray[i];
      }
      for (int i = 0; i < addNum; i++) {
        int input_id;
        string input_name;
        int input_select;
        cout << "请输入第" << i + 1 << "个新职工编号：" << endl;
        cout << "（返回主菜单请输入0）" << endl;
      id_input_flag:
        cin >> input_id;
        if (input_id == 0)
          return;
        for (int j = 0; j < this->m_EmpNum; j++) {  // 防止编号重复
          if (input_id == m_EmpArray[j]->m_ID) {
            cout << "您输入的职工编号" << input_id << "已经存在，请重新输入："
                 << endl;
            goto id_input_flag;
          }
        }
        cout << "请输入第" << i + 1 << "个新职工姓名：" << endl;
        cout << "（返回主菜单请输入0）" << endl;
        cin >> input_name;
        if (input_name == "0")
          return;
        cout << "请选择该职工的岗位："
             << " 1.普通职工 "
             << " 2.经理 "
             << " 3.老板 " << endl;
        cout << "（返回主菜单请输入0）" << endl;
      select_input_flag:
        cin >> input_select;
        if (input_select == 0)
          return;
        else if (input_select > 3 || input_select < 0) {
          cout << "无此岗位，请重新输入：" << endl;
          goto select_input_flag;
        }
        Worker* w = nullptr;  // 创建父类指针
        switch (input_select) {
          case 1:
            w = new Employee(input_name, input_id, input_select);
            break;
          case 2:
            w = new Manager(input_name, input_id, input_select);
            break;
          case 3:
            w = new Boss(input_name, input_id, input_select);
            break;
          default:
            break;
        }
        newSpace[this->m_EmpNum + i] = w;
      }
      delete[] this->m_EmpArray;  // 释放原有数组空间[]
      this->m_EmpArray = newSpace;
      this->m_EmpNum = newSize;
      this->m_FileEmpty = 1;
      this->save();
      cout << "成功添加" << addNum << "名新职工！" << endl;
      cout << "继续添加请输入1，返回主菜单请输入0：" << endl;
      int go_on;
      cin >> go_on;
      if (go_on == 1)
        goto input;
      else
        return;
    }
    system("pause");
  }
  void save() {
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (int i = 0; i < m_EmpNum; i++)
      ofs << this->m_EmpArray[i]->m_ID << "\t" << this->m_EmpArray[i]->m_Name
          << "\t" << this->m_EmpArray[i]->m_DepartID << endl;
    ofs.close();
  }

  int get_EmpNum() {  // 获取人数
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id;
    string name;
    int departId;
    int num = 0;
    while (ifs >> id && ifs >> name && ifs >> departId)  // 读取每一行数据
      num++;
    return num;
  }
  void init_Emp() {
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    int id, departId, index = 0;
    string name;
    while (ifs >> id && ifs >> name && ifs >> departId) {  // while 而不是for
      Worker* w = nullptr;
      if (departId == 1)
        w = new Employee(name, id, departId);  // 不能在if内定义
      else if (departId == 2)
        w = new Manager(name, id, departId);
      else if (departId == 3)
        w = new Boss(name, id, departId);
      this->m_EmpArray[index++] = w;
    }
    ifs.close();
  }
  void Show_Emp() {
    if (this->m_FileEmpty == -1)
      cout << "文件不存在！" << endl;
    else if (this->m_FileEmpty == 0)
      cout << "文件为空！" << endl;
    else {
      cout << "共找到人数 " << this->m_EmpNum << endl;
      for (int i = 0; i < m_EmpNum; i++)
        m_EmpArray[i]->showInfo();  // 多态
    }
    system("pause");
  }
  int isExist(int id) {  // 判断职工是否存在，返回位置
    int index = -1;
    while (index < this->m_EmpNum) {
      if (m_EmpArray[++index]->m_ID == id)
        break;
    }
    return index;
  }

  void Delete_Emp() {
  input:
    if (this->m_FileEmpty == -1)
      cout << "文件不存在！" << endl;
    else if (this->m_FileEmpty == 0)
      cout << "文件为空！" << endl;
    else {
      cout << "请输入想要删除的职工编号：" << endl;
      cout << "（返回主菜单请输入0）" << endl;
      int id = 0;
      cin >> id;
      if (id == 0)
        return;
      int index_delete = isExist(id);
      if (index_delete != -1) {
        cout << "确认要删除该职工吗？确认请输入1，否则请输入0：" << endl;
        bool comfirm;
        cin >> comfirm;
        if (comfirm) {
          for (int i = index_delete; i < this->m_EmpNum - 1;
               i++)  // 删除本质是数据前移
            m_EmpArray[i] = m_EmpArray[i + 1];
          m_EmpNum--;
          this->save();  // 注意实施保存文件中
          cout << "成功删除编号为" << id << "的职工 "
               << this->m_EmpArray[index_delete]->m_Name << "!" << endl;
          cout << "继续删除请输入1，返回主菜单请输入0：" << endl;
          int go_on;
          cin >> go_on;
          if (go_on)
            goto input;
          else
            return;
        } else {
          cout << "没有人被删除！" << endl;
          goto input;
        }
      } else {
        cout << "未找到该职工，删除失败！" << endl;
        goto input;
      }
    }
    system("pause");
  }
  void Mod_Emp() {
  input:
    if (this->m_FileEmpty == -1)
      cout << "文件不存在！" << endl;
    else if (this->m_FileEmpty == 0)
      cout << "文件为空！" << endl;
    else {
      cout << "请输入想要修改的职工编号：" << endl;
      cout << "（返回主菜单请输入0）" << endl;
      int id = 0;
      cin >> id;
      if (id == 0)
        return;
      int index_mod = isExist(id);
      if (index_mod != -1) {
        int newId, newSelect;
        string newName;
        cout << "查找到编号为" << id << "的职工"
             << this->m_EmpArray[index_mod]->m_Name
             << "，请输入职工编号，若不修改此项，请输入0跳过：" << endl;
        cin >> newId;
        if (newId == 0)
          newId = this->m_EmpArray[index_mod]->m_ID;
        cout << "请输入姓名，若不修改此项，请输入0跳过：" << endl;
        cin >> newName;
        if (newName == "0")
          newName = this->m_EmpArray[index_mod]->m_Name;
        cout << "请选择该职工的岗位，若不修改此项，请输入0跳过： 1.普通职工  "
                "2.经理  3.老板"
             << endl;
        cin >> newSelect;
        if (newSelect == 0)
          newSelect = this->m_EmpArray[index_mod]->m_DepartID;
        if (newId == this->m_EmpArray[index_mod]->m_ID &&
            newName == this->m_EmpArray[index_mod]->m_Name &&
            newSelect == this->m_EmpArray[index_mod]->m_DepartID) {
          cout << "该职工信息没有被修改！" << endl;
          cout << "继续修改请输入1，返回主菜单请输入0：" << endl;
          bool go_on;
          cin >> go_on;
          if (go_on)
            goto input;
          else
            return;
        } else {
          cout << "确认要修改该职工吗？确认请输入1，否则请输入0：" << endl;
          bool comfirm;
          cin >> comfirm;
          if (comfirm) {
            delete this->m_EmpArray[index_mod];
            Worker* w = nullptr;
            if (newSelect == 1)
              w = new Employee(newName, newId, newSelect);  // 不能在if内定义
            else if (newSelect == 2)
              w = new Manager(newName, newId, newSelect);
            else if (newSelect == 3)
              w = new Boss(newName, newId, newSelect);
            this->m_EmpArray[index_mod] = w;
            cout << "修改成功！" << endl;
            this->save();  // 保存到本地文件中
            cout << "继续修改请输入1，返回主菜单请输入0：" << endl;
            bool go_on;
            cin >> go_on;
            if (go_on)
              goto input;
            else
              return;
          } else {
            cout << "该职工信息没有被修改！" << endl;
            goto input;
          }
        }
      } else {
        cout << "未找到该职工，修改失败！" << endl;
        goto input;
      }
    }
    system("pause");
  }

  int isExistByName(string name) {
    int index = -1;
    while (index < m_EmpNum) {
      if (m_EmpArray[++index]->m_Name == name)
        break;
    }
    return index;
  }
  void Find_Emp() {
  input:
    if (this->m_FileEmpty == -1)
      cout << "文件不存在！" << endl;
    else if (this->m_FileEmpty == 0)
      cout << "文件为空！" << endl;
    else {
      cout << "请输入查找方式：\t1.按职工编号查找 \t2.按职工姓名查找 "
              "\t（返回主菜单请输入0）"
           << endl;
    select:
      int select;
      cin >> select;
      if (select == 0)
        return;
      else if (select == 1) {
        cout << "请输入要查找的职工的编号：" << endl;
        cout << "（返回主菜单请输入0）" << endl;
        int id;
        cin >> id;
        if (isExist(id) == -1) {
          cout << "已找到，继续查找请输入1，返回主菜单请输入0：" << endl;
          int go_on;
          cin >> go_on;
          if (go_on)
            goto input;
          else
            return;
        } else {
          cout << "查找失败，查无此人！" << endl;
          goto input;
        }
      } else if (select == 2) {
        cout << "请输入要查找的职工的姓名：" << endl;
        cout << "（返回主菜单请输入0）" << endl;
        string name;
        cin >> name;
        if (name == "0")
          return;
        int index_FindByName = isExistByName(name);
        if (index_FindByName != -1) {
          for (int i = 0; i < this->m_EmpNum; i++) {
            if (this->m_EmpArray[i]->m_Name == name)
              this->m_EmpArray[i]->showInfo();
          }
          cout << "已找到，继续查找请输入1，返回主菜单请输入0：" << endl;
          int go_on;
          cin >> go_on;
          if (go_on)
            goto input;
          else
            return;
        } else {
          cout << "查找失败，查无此人！" << endl;
          goto input;
        }
      } else {
        cout << "输入无效，请重新输入：" << endl;
        goto select;
      }
    }
    system("pause");
  }

  void Clean_Emp() {
    cout << "确认要清空吗？确认请输入1，否则请输入0：" << endl;
    int confirm = 0;
    cin >> confirm;
    if (confirm) {
      ofstream ofs;
      ofs.open(FILENAME, ios::trunc);  // 对于文件，删除后重新创建
      ofs.close();
      if (m_EmpArray != nullptr) {  // 对于堆区文件，要注意判断原有数据存在
        for (int i = 0; i < m_EmpNum; i++) {  // 清空每个元素
          delete m_EmpArray[i];
          m_EmpArray[i] = nullptr;
        }
        delete[] this->m_EmpArray;  // 清空数组
        m_EmpArray = nullptr;
        m_EmpNum = 0;
        m_FileEmpty = 0;  // 文件存在但无数据
      }
      cout << "清空成功！" << endl;
    } else {
      cout << "没有被清空。" << endl;
    }
    system("pause");
  }
  ~WorkerManager() {
    if (m_EmpArray != nullptr) {
      for (int i = 0; i < m_EmpNum; i++) {  // 清空每个元素
        delete m_EmpArray[i];
        m_EmpArray[i] = nullptr;
      }
      delete[] this->m_EmpArray;  // 清空数组
      m_EmpArray = nullptr;
    }
  }
  int m_EmpNum;  // 总人数
  Worker** m_EmpArray;
  int m_FileEmpty;  // -1无文件，0有文件为空，1有文件
};

int main() {
  WorkerManager wm;
  int choice;
  while (true) {
    wm.ShowMenu();
    cin >> choice;
    switch (choice) {
      case 0:  // 退出
        wm.ExitSystem();
        break;
      case 1:  // 增加
        wm.AddEmp();
        break;
      case 2:  // 显示
        wm.Show_Emp();
        break;
      case 3:  // 删除
        wm.Delete_Emp();
        break;
      case 4:  // 修改
        wm.Mod_Emp();
        break;
      case 5:  // 查找
        wm.Find_Emp();
        break;
        /*       case 6:  // 排序
                wm.Sort_Emp();
                break; */
      case 7:  // 清空
        wm.Clean_Emp();
        break;
      default:
        system("cls");  // 清屏
        break;
    }
    return 0;
  }
}