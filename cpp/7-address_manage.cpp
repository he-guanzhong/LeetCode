#include <iostream>
#include <string>
#define MAX_SIZE 10  // 宏命令设置最大通讯录内保存数量
using namespace std;
struct Person {
  string m_Name;
  int m_Age;
  int m_Sex;
  string m_Phone;
  string m_Addr;
};

struct AddressBook {
  Person PersonArray[MAX_SIZE];
  int m_size;
};

void showMenu() {
  cout << "***************************" << endl;
  cout << "*****  1，添加联系人  *****" << endl;
  cout << "*****  2，显示联系人  *****" << endl;
  cout << "*****  3，删除联系人  *****" << endl;
  cout << "*****  4，查找联系人  *****" << endl;
  cout << "*****  5，修改联系人  *****" << endl;
  cout << "*****  6，清空联系人  *****" << endl;
  cout << "*****  0，退出通讯录  *****" << endl;
  cout << "***************************" << endl;
}
void addPerson(AddressBook* p) {
  if (p->m_size == MAX_SIZE) {
    cout << "人满，失败" << endl;
    return;
  } else {
    cout << "请输入姓名" << endl;
    string name;
    cin >> name;
    p->PersonArray[p->m_size].m_Name = name;
    cout << "请输入年龄" << endl;
    int age = 0;
    while (1) {
      cin >> age;
      if (age < 120 && age > 0) {
        p->PersonArray[p->m_size].m_Age = age;
        break;
      } else {
        cin.clear();
        cin.ignore();
        cout << "输入有误，重新输入" << endl;
      }
    }
    cout << "请输入性别: 1 男  2 女" << endl;
    int sex = 0;
    while (1) {
      cin >> sex;  // 必须在里面
      if (sex == 1 || sex == 2) {
        p->PersonArray[p->m_size].m_Sex = sex;
        break;
      } else {
        cin.clear();
        cin.ignore();
        cout << "输入有误，重新输入" << endl;
      }
    }
    cout << "请输入电话" << endl;
    string phone;
    cin >> phone;
    p->PersonArray[p->m_size].m_Phone = phone;
    cout << "请输入地址" << endl;
    string addr;
    cin >> addr;
    p->PersonArray[p->m_size].m_Addr = addr;
    p->m_size++;
    cout << "添加成功" << endl;
    system("pause");  // 按任意键继续
    system("cls");    // 清屏
  }
}
void showPerson(AddressBook* p) {
  if (p->m_size == 0) {
    cout << "无联系人" << endl;
    return;
  } else {
    for (int i = 0; i < p->m_size; i++) {
      cout << "Info: " << p->PersonArray[i].m_Name << "\t"
           << p->PersonArray[i].m_Age << "\t"
           << ((p->PersonArray[i].m_Sex == 1) ? "男" : "女")
           << "\t"  // 注意分区必须加括号
           << p->PersonArray[i].m_Phone << "\t" << p->PersonArray[i].m_Addr
           << endl;
    }
  }
  system("pause");  // 按任意键继续
  system("cls");    // 清屏
}
int isExist(AddressBook* p, string name) {
  for (int i = 0; i < p->m_size; i++) {
    if (p->PersonArray[i].m_Name == name)
      return i;
  }
  return -1;
}
void deletePerson(AddressBook* p) {
  cout << "请输入待删除姓名" << endl;
  string input_name;
  cin >> input_name;
  int exist = isExist(p, input_name);
  if (exist != -1) {
    cout << "确定要删除？" << endl;
    bool index;
    cin >> index;
    if (index) {
      for (int i = exist; i < p->m_size; i++)
        p->PersonArray[i] = p->PersonArray[i + 1];
      p->m_size--;
      cout << "删除成功" << endl;
    } else {
      cout << "没有联系人被删除" << endl;
    }
  } else {
    cout << "查无此人，无法删除" << endl;
  }
  system("pause");
  system("cls");
}

void findPerson(AddressBook* p) {
  cout << "请输入查找姓名" << endl;
  string input_name;
  cin >> input_name;
  int exist = isExist(p, input_name);
  if (exist != -1) {
    cout << "联系人已找到:" << p->PersonArray[exist].m_Name << "\t"
         << p->PersonArray[exist].m_Age << "\t" << p->PersonArray[exist].m_Sex
         << "\t" << p->PersonArray[exist].m_Phone << "\t"
         << p->PersonArray[exist].m_Addr << endl;
  } else {
    cout << "查无此人" << endl;
  }
  system("pause");  // 按任意键继续
  system("cls");    // 清屏
}

void modifyPerson(AddressBook* p) {
  cout << "请输入要修改者姓名" << endl;
  string input_name;
  cin >> input_name;
  int exist = isExist(p, input_name);
  if (exist != -1) {
    cout << "请输入要修改内容： 1.名字。2.年龄。3.性别。4.电话。5.住址。0.完毕 "
         << endl;
    while (1) {
      int modifySelect = -1;
      cin >> modifySelect;
      switch (modifySelect) {
        case 1: {
          string name;
          cout << "请输入修改后姓名" << endl;
          cin >> name;
          p->PersonArray[exist].m_Name = name;
          break;
        }
        case 2: {
          cout << "请输入修改后年龄" << endl;
          int age;
          cin >> age;
          p->PersonArray[exist].m_Age = age;
          break;
        }
        case 3: {
          cout << "请输入修改后性别" << endl;
          int sex;
          cin >> sex;
          p->PersonArray[exist].m_Sex = sex;
          break;
        }
        case 4: {
          cout << "请输入修改后电话" << endl;
          string phone;
          cin >> phone;
          p->PersonArray[exist].m_Phone = phone;
          break;
        }
        case 5: {
          cout << "请输入修改后住址" << endl;
          string addr;
          cin >> addr;
          p->PersonArray[exist].m_Addr = addr;
          break;
        }
        case 0:
          cout << "修改完毕" << endl;
          system("pause");
          system("cls");
          return;
          break;
        default:
          cout << "输入有误" << endl;
      }
    }
  } else {
    cout << "查无此人" << endl;
  }
  system("pause");
  system("cls");
}
void cleanPerson(AddressBook* p) {
  cout << "确定要情况么？ 1.是 2.否" << endl;
  bool index = 0;
  cin >> index;
  if (index) {
    p->m_size = 0;
    cout << "已清空" << endl;
  } else {
    cout << "未清空操作" << endl;
  }
  system("pause");
  system("cls");
}

void mainMenu(AddressBook p) {
  while (1) {
    showMenu();
    int input = 0;
    cin >> input;
    switch (input) {
      case 1:
        addPerson(&p);
        break;
      case 2:
        showPerson(&p);
        break;
      case 3:
        deletePerson(&p);
        break;
      case 4:
        findPerson(&p);
        break;
      case 5:
        modifyPerson(&p);
        break;
      case 6:
        cleanPerson(&p);
        break;
      case 0:
        cout << "欢迎下次使用" << endl;
        system("pause");
        exit(0);
        break;
      default:
        break;
    }
  }
}

int main() {
  AddressBook abs;
  abs.m_size = 0;
  mainMenu(abs);
  system("pause");
  return 0;
}