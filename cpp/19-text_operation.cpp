
#include <fstream>  // 读写文件头文件
#include <iostream>
using namespace std;

/// ofstream 写文件。 ifstream 读文件。 fstream 读写文件
void writeFiles() {
  ofstream ofs;                    // 创建写文件流对象
  ofs.open("test.txt", ios::out);  // 打开方式
  // ios::out 写数据
  // ios::in  读数据
  // ios::trunc 文件存在，先删再创建
  // ios::binary 二进制方式，可以 ios::binary | ios::out
  ofs << "张三" << endl;
  ofs << "男" << endl;
  ofs << "50岁" << endl;
  ofs.close();  // 关闭文件
}
void readFiles() {
  ifstream ifs;                   // 读文件流对象
  ifs.open("test.txt", ios::in);  // 读文件打开方式
  if (!ifs.is_open()) {
    cout << "打开失败" << endl;  // 判断是否打开成功
    return;
  }
  // 读数据方法一
  /*   char buf[1024] = {0};
    while (ifs >> buf)
      cout << buf << endl;
  // 读数据方法二
    char buf[1024] = {0};
    while (ifs.getline(buf, sizeof(buf)))
      cout << buf << endl; */
  // 读数据方法三
  string buf;
  while (getline(ifs, buf))
    cout << buf << endl;
  ifs.close();
}

// 二进制操作
class Person {
 public:
  char m_Name[64];
  int m_age;
};
void writeFilesBinary() {
  fstream ofs("person.txt", ios::out | ios::binary);
  // ofs.open("person.txt", ios::out | ios::binary);
  Person p = {"李四", 25};
  ofs.write((const char*)&p, sizeof(p));
  ofs.close();
}
void readFilesBinary() {
  fstream ifs;
  ifs.open("person.txt", ios::in | ios::binary);
  if (!ifs.is_open())
    cout << "打开失败" << endl;
  Person p;
  ifs.read((char*)&p, sizeof(p));
  cout << p.m_Name << " " << p.m_age << endl;
  ifs.close();
}
int main() {
  writeFiles();
  readFiles();
  writeFilesBinary();
  readFilesBinary();
  return 0;
}
