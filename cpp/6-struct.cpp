#include <iostream>
#include <string>
using namespace std;

/*1，创建三个老师的数组；
2，通过函数给三个老师赋值，并给老师带的学生赋值；
3，打印所有老师和学生的信息；*/

struct Student {  // 定义结构体时不能省略struct
  string sName;
  int score;
};

struct Teacher {
  string tName;
  Student students[5];
};

void allocateSpace(Teacher teachers[],
                   int len) {  // 传入的是数组名，可以视为地址
  string NameSeed = "ABCDE";
  for (int i = 0; i < len; i++) {
    teachers[i].tName = "Teacher_";
    teachers[i].tName += NameSeed[i];  // 字符串可以直接相加
    for (int j = 0; j < 5; j++) {
      teachers[i].students[j].sName = "Student_";
      teachers[i].students[j].sName += NameSeed[j];
      teachers[i].students[j].score = 60;
    }
  }
}
void printInfo(Teacher teachers[], int len) {
  for (int i = 0; i < len; i++) {
    cout << "T_name " << teachers[i].tName << "\n ";
    for (int j = 0; j < 5; j++) {
      cout << "\t S_name " << teachers[i].students[j].sName << " S_score "
           << teachers[i].students[j].score;
    }
    cout << endl;
  }
}

// 英雄按照年龄冒泡排序
struct Hero {
  string name;
  int age;
  string sex;
};

void bubble_age(Hero heroes[], int len) {
  cout << "before: " << endl;
  for (int i = 0; i < len; i++)
    cout << "name: " << heroes[i].name << "  age:" << heroes[i].age
         << "  sex:" << heroes[i].sex << endl;
  for (int i = 0; i < len - 1; i++) {
    for (int j = 0; j < len - 1 - i; j++) {
      if (heroes[j].age > heroes[j + 1].age) {
        Hero temp = heroes[j];
        heroes[j] = heroes[j + 1];
        heroes[j + 1] = temp;
      }
    }
  }
  cout << "after: " << endl;
  for (int i = 0; i < len; i++)
    cout << "name: " << heroes[i].name << "  age:" << heroes[i].age
         << "  sex:" << heroes[i].sex << endl;
}
int main() {
  Teacher teachers[3];  // 创建变量时可以省略struct
  int len1 = sizeof(teachers) / sizeof(teachers[0]);
  allocateSpace(teachers, len1);
  printInfo(teachers, len1);

  Hero heroes[] = {
      {"关羽", 31, "男"}, {"张飞", 26, "男"}, {"刘备", 40, "男"},
      {"貂蝉", 25, "女"}, {"吕布", 30, "男"},
  };
  heroes[2].sex = "女";  // 直接修改
  Hero* p = &heroes[2];  // 指针指向，对象地址，直接修改参数值
  p->age = 41;
  int len2 = sizeof(heroes) / sizeof(heroes[0]);
  bubble_age(heroes, len2);
  return 0;
}