#include <algorithm>  // 标准算法头文件
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
/*  数据结构与算法的一般标准，STL（标准模板库），目的是提升易用性
  STL广义上分为：容器、算法、迭代器。容器和算法通过迭代器连接
  STL几乎所有代码都利用了类模板、函数模板
  STL主要分为六大部分：
  1. 容器。如vector deque list set map
  2. 算法。如sort, find, copy, for_each
  3. 迭代器。容器与算法间桥梁
  4. 仿函数。运算符重载，算法某种策略
  5. 适配器（配机器）。修饰容器、仿函数、迭代器接口
  6. 空间配置器。空间配置与管理
*/
/*
  容器：用途最广泛的数据结构。如数组、链表、树、栈、集合、映射表
  序列式容器：强调值排序，每个元素有固定位置
  关联式容器：二叉树结构，元素间无物理上顺序关联

  算法：优先步骤，解决逻辑或数学上问题，
  质变算法：运算中修改区间元素内容。拷贝、替换、删除
  非质变算法：运算中不改变元素内容。如查找、计数、寻找极值

  迭代器：容器与算法间桥梁
  类似指针，算法需要依赖迭代器访问容器中元素，无需暴露容器内部表示方式
  输入迭代器：数据只读。支持运算++, ==, !, =
  输出迭代器：数据只写。支持运算++
  前向迭代器：读写操作，向前推进。支持运算++, ==, !, =
  双向迭代器：读写操作，向前向后操作。支持运算++, --
  随机访问迭代器：读写操作，向前向后跳跃访问任意数据。支持运算++，--, [n], <, <=
  双向和随机访问最常用
  */
// vector容器，相当于数组类模板，存放普通整型
void myPrint(int val) {
  cout << val << " ";
}
void vectorInt() {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  // 通过迭代器遍历数据，方法一
  vector<int>::iterator it_begin = v.begin();  // 指向容器第一个元素
  vector<int>::iterator it_end = v.end();  // 指向最后一个元素下一个位置
  while (it_begin != it_end) {
    cout << *it_begin << " ";
    it_begin++;
  }
  cout << endl;
  // 遍历方法二
  for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    cout << *it << " ";
  cout << endl;
  // 遍历方法三，利用STL提供的遍历算法，回调函数
  for_each(v.begin(), v.end(), myPrint);  // algorithm中包含了for_each 和sort
  cout << endl;
}
class Person {
 public:
  Person(string name, int age) : m_name(name), m_age(age) {}
  string m_name;
  int m_age;
};

void vectorClass() {
  vector<Person> v1;
  Person p1("Max", 24);
  Person p2("Lewis", 36);
  Person p3("Schumacher", 52);
  v1.push_back(p1);
  v1.push_back(p2);
  v1.push_back(p3);
  for (vector<Person>::iterator it = v1.begin(); it != v1.end(); it++) {
    cout << (*it).m_name << " " << (*it).m_age
         << ", ";  // *it时解引用后的数据类型，与<>内相同
    cout << it->m_name << " " << it->m_age << ", ";
  }
  cout << endl;
}
void vectorPointer() {
  vector<Person*> v2;
  Person p1("Max", 24);
  Person p2("Lewis", 36);
  Person p3("Schumacher", 52);
  v2.push_back(&p1);
  v2.push_back(&p2);
  v2.push_back(&p3);
  for (vector<Person*>::iterator it = v2.begin(); it != v2.end(); it++) {
    cout << (*it)->m_name << " " << (*it)->m_age
         << ", ";  // （*it）解引用后为指针
  }
  cout << endl;
}
void vectorNested() {
  vector<vector<int>> v;
  vector<int> v1, v2, v3, v4;  // 四个小容器
  for (int i = 0; i < 5; i++) {
    v1.push_back(i);
    v2.push_back(i + 10);
    v3.push_back(i + 20);
    v4.push_back(i + 30);
  }
  v.push_back(v1);
  v.push_back(v2);
  v.push_back(v3);
  v.push_back(v4);
  for (vector<vector<int>>::iterator it = v.begin(); it != v.end(); it++) {
    for (vector<int>::iterator jt = it->begin(); jt != it->end();
         jt++)  // (*jt)就是一个容器类型
      cout << (*jt) << " ";
    cout << endl;
  }
}

// string 容器
// string 本质是C++封装的一个类，封装了char*指针,是char*型容器
// string 封装了很多方法，管理char*分配的内存，不用担心月结
void stringConstruct() {  // 四种构造方式
  string s1;              // 默认构造
  const char* str = "char construct";
  string s2(str);      // 有参构造
  string s3(s2);       // 拷贝构造
  string s4(10, 'a');  // 参数化构造
  cout << "s1 = " << s1 << ", s2 = " << s2 << ", s3 = " << s3 << ", s4 = " << s4
       << endl;
}
void stringAssign() {
  // 使用 = 赋值
  string s1;
  s1 = "assign with =";
  string s2 = s1;
  string s3;
  s3 = 'a';  // 只赋值一个字符
  // 使用assign赋值
  string s4;
  s4.assign("assign with assigh");
  string s5;
  s5.assign(s4);
  string s6;
  s6.assign("assign with assigh", 6);  // 取前6个字符
  string s7;
  s7.assign(10, 'b');  // 10个b
  cout << "s1 = " << s1 << ", s2 = " << s2 << ", s3 = " << s3 << endl;
  cout << "s4 = " << s4 << ", s5 = " << s5 << ", s6 = " << s6 << ", s7 = " << s7
       << endl;
}
void stringConcatenation() {
  // 使用+= 拼接
  string s1 = "string";
  s1 += " can be";
  string s3 = " concatenated with +=";
  s1 += s3;
  cout << "s1 = " << s1 << endl;
  // 使用append 拼接
  string s4 = "string";
  s4.append(" can");
  s4.append(" be , xxxyyy", 3);  // 只截取前三位数
  string s5 = " concatenated";
  s4.append(s5);
  string s6 = "x by append xxxx";
  s4.append(s6, 1, 10);  // 从第1位开始，截取9位
  cout << "s4 = " << s4 << endl;
}
void stringFindReplace() {
  string s1 = "abcdefgde";
  int pos1 = s1.find("de");   // 返回以0开始的下标
  int pos2 = s1.find("df");   // 找不到返回-1
  int pos3 = s1.rfind("de");  // 从右开始找，返回首次找到的下标
  cout << "left find pos = " << pos1 << ", cannot find pos = " << pos2
       << ", right find pos = " << pos3 << endl;
  s1.replace(1, 3, "1111");  // 从下标1开始，连续3个字符，替换为1111
  cout << "after replace = " << s1 << endl;
}
void stringCompare() {
  string s1 = "ab";  // 比较ASCII码的大小，<返回-1，>返回1，=返回0
  string s2("abc");
  string s3("ab");
  cout << "compare smaller = " << s1.compare(s2)
       << ", bigger = " << s2.compare(s1) << ", equal = " << s3.compare(s1)
       << endl;
}
void stringAccess() {
  string s1 = "abcde";
  for (int i = 0; i < s1.size(); i++) {  // 通过[]访问
    cout << s1[i] << " ";
  }
  cout << endl;
  for (int i = 0; i < s1.size(); i++) {  // 通过at访问
    cout << s1.at(i) << " ";
  }
  cout << endl;
  s1[0] = 'x';
  s1.at(1) = 'y';
  cout << s1 << endl;
}
void stringInsertDelete() {
  string s = "hello";
  s.insert(2, "abc");  // 从下标为2个位置，插入abc
  cout << s << endl;
  s.erase(2, 3);  // 从下标为2个位置，删除3个字符
  cout << s << endl;
}
void stringSubstr() {
  string s = "supermarket";
  cout << s.substr(5, 6) << endl;  // 从下标为1截取三个字符
  string str = "vettel@foxmail.com";
  int pos = str.find('@');
  cout << str.substr(0, pos) << endl;
}

// Vector容器,类似数组，但是单端数组，只能从尾部差值
// 普通数组为静态空间，vector空间可以动态拓展。拓展时是找到更大的内存空间，将元素组拷贝到新空间，释放原空间
// 常用迭代器 begin() end() insert(),尾插push_back() ,pop_back()
// 迭代器支持随机访问
void printVector(vector<int>& v) {  // 迭代器打印
  for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
    cout << (*it) << " ";
  cout << endl;
}
void printVector1(vector<int>& v) {
  for (int i = 0; i < v.size(); i++)  // [] 访问打印
    cout << v[i] << " ";
  cout << endl;
}
void printVector2(vector<int>& v) {
  for (int i = 0; i < v.size(); i++)
    cout << v.at(i) << " ";
  cout << endl;
}
// vector和string都有默认、拷贝、参数构造；vector独有迭代器构造
void vectorConstruct() {
  vector<int> v1;  // 默认构造
  for (int i = 1; i < 5; i++)
    v1.push_back(i);
  vector<int> v2(v1);                    // 拷贝构造
  vector<int> v3(v1.begin(), v1.end());  // 迭代器构造
  vector<int> v4(4, 10);                 // 参数构造， 4个10
  printVector(v1);
  printVector(v2);
  printVector(v3);
  printVector(v4);
}
// vector和string都有=赋值、assign参数赋值；vector独有assign迭代器赋值,string独有截取某长度
void vectorAssign() {
  vector<int> v1;
  for (int i = 1; i < 5; i++)
    v1.push_back(i);
  vector<int> v2 = v1;  // =赋值
  vector<int> v3;
  v3.assign(v1.begin(), v1.end());  // assign 赋值
  vector<int> v4;
  v4.assign(4, 11);  // assign参数赋值， 4个11
  printVector(v2);
  printVector(v3);
  printVector(v4);
}
void vectorSize() {
  vector<int> v1;
  for (int i = 1; i < 5; i++)
    v1.push_back(i);
  if (v1.empty())
    cout << "vector为空" << endl;
  else
    cout << "vector.size = " << v1.size()
         << ", vector.capacity = " << v1.capacity() << endl;
  v1.resize(10);  // 重新指定大小，比原来长就填充0
  printVector(v1);
  v1.resize(15, 100);  // 重新指定大小，比原来长的部分填充100
  printVector(v1);
  v1.resize(8);  // 比原来短，其余被删除
  printVector(v1);
}
void vectorInsertDelete() {
  vector<int> v1;
  for (int i = 1; i < 5; i++)
    v1.push_back(i);
  printVector(v1);
  v1.insert(v1.begin(), 10);  // 首位值插入10
  printVector(v1);
  v1.insert(v1.begin(), 3, 20);  // 首位置插2个20
  v1.insert(v1.begin(), v1.begin() + 1, v1.begin() + 2);
  printVector(v1);
  v1.erase(v1.begin());  // 首位删除一个元素
  printVector(v1);
  v1.erase(v1.begin(), v1.begin() + 3);  // 首位置处删除指定区间内元素
  printVector(v1);
  v1.clear();  // 全部清除
  printVector(v1);
}
void vectorAccess() {
  vector<int> v1;
  for (int i = 1; i <= 5; i++)
    v1.push_back(i);
  printVector(v1);   // 迭代器访问
  printVector1(v1);  //[]访问
  printVector2(v1);  // at访问
  cout << "First Element:" << v1.front() << ", Last Element:" << v1.back()
       << endl;
}
void vectorSwap() {
  vector<int> v1;
  for (int i = 1; i <= 5; i++)
    v1.push_back(i);
  vector<int> v2;
  for (int i = 10; i > 5; i--)
    v2.push_back(i);
  cout << "Before swap: ";
  printVector(v1);
  printVector(v2);
  v1.swap(v2);
  cout << "After swap: ";
  printVector(v1);
  printVector(v2);
}
// swap函数可以收缩内存空间
void vectorMemoryOpti() {
  vector<int> v;
  for (int i = 1; i <= 1000; i++)
    v.push_back(i);
  cout << "Before size = " << v.size() << ", capacity = " << v.capacity()
       << endl;
  v.resize(3);
  cout << "After size = " << v.size() << ", capacity = " << v.capacity()
       << endl;
  // vector<int> v_tmp(v); // 利用拷贝构造创建临时对象，新对象容量和大小都为小值
  // v_tmp.swap(v); // 可以化简为以下匿名对象表达式
  // 匿名对象调用拷贝构造新对象，有新容量，然后与现在的v交换。
  // 匿名对象执行完就会被系统回收，不占用内存
  vector<int>(v).swap(v);
  cout << "tmp size = " << v.size() << ", capacity = " << v.capacity() << endl;
}
void vectorCapacity() {
  vector<int> v;
  // 预留空间，可以减少动态扩容的次数。否则动态扩容以2^n的方式扩容
  v.reserve(2000);
  int num = 0;
  int* p = nullptr;
  for (int i = 1; i <= 1000; i++) {
    v.push_back(i);
    if (p != &v[0]) {  // 每开辟一次，就要重新指向首地址
      num++;
      p = &v[0];
      // cout << "Add: " << p << " capacity: " << v.capacity() << endl;
    }
  }
  cout << "Reserve nums = " << num << endl;
}

// deque容器，双端数组，头尾都可以插入删除。
// 相比vector, deque头部操作快，vector访问元素速度快
// vector是连续内存空间，deque内部有中控器，记录每个缓冲区地址，数据记录在缓冲区内
// deque迭代器也支持随机访问
void printDeque(const deque<int>& d) {  // 迭代器
  for (deque<int>::const_iterator it = d.begin(); it != d.end(); it++)
    cout << (*it) << " ";  // 注意为了防止写操作，要const_iterator
  cout << endl;
}
void printDeque1(deque<int>& d) {
  for (int i = 0; i < d.size(); i++)  // [] 访问打印
    cout << d[i] << " ";
  cout << endl;
}
void printDeque2(deque<int>& d) {
  for (int i = 0; i < d.size(); i++)
    cout << d.at(i) << " ";
  cout << endl;
}
void dequeConstruct() {
  deque<int> d1;  // 默认构造
  for (int i = 1; i < 5; i++) {
    d1.push_back(i);   // 头插
    d1.push_front(i);  // 尾插
  }
  deque<int> d2(d1);                    // 拷贝构造
  deque<int> d3(d1.begin(), d1.end());  // 迭代器构造
  deque<int> d4(4, 10);                 // 参数构造， 4个10
  printDeque(d1);
  printDeque(d2);
  printDeque(d3);
  printDeque(d4);
}
void dequeAssign() {
  deque<int> d1;
  for (int i = 1; i < 5; i++)
    d1.push_front(i);
  deque<int> d2 = d1;  // = 赋值
  deque<int> d3;
  d3.assign(d2.begin(), d2.end());  // 迭代器赋值
  deque<int> d4;
  d4.assign(3, 111);  // 参数赋值， 3个111
  printDeque(d2);
  printDeque(d3);
  printDeque(d4);
}
void dequeSize() {  // 没有容量的概念，只有size
  deque<int> d1;
  for (int i = 1; i < 5; i++)
    d1.push_front(i);
  d1.resize(8);
  printDeque(d1);
  d1.resize(10, 2);
  printDeque(d1);
  d1.resize(3);
  printDeque(d1);
}
void dequeInsertDelete() {
  deque<int> d1;  // 传统从前从后push 和 pop
  d1.push_back(10);
  d1.push_back(20);
  d1.push_front(100);
  d1.push_front(200);
  deque<int> d2;
  d2.push_back(98);
  d2.push_back(99);
  printDeque(d1);
  d1.pop_back();
  d1.pop_front();
  d1.insert(d1.begin(), 1);  // 插入可以单点，参数，迭代器插入
  d1.insert(d1.begin(), 3, 333);  // 首位置插入两个111
  d1.insert(d1.begin(), d2.begin(), d2.end());
  printDeque(d1);
  d1.erase(d1.begin());    // erase可以单点、区间、迭代器删除
  d1.erase(++d1.begin());  // 删除第二个元素可以直接++
  d1.erase(d1.begin() + 2, d1.begin() + 3);
  printDeque(d1);
  d1.clear();
}
void dequeAccess() {
  deque<int> d;
  d.push_back(1);
  d.push_back(2);
  d.push_front(10);
  d.push_front(20);
  printDeque1(d);  // 利用[]
  printDeque2(d);  // 利用at
  printDeque(d);   // 利用迭代器
  cout << "deque frist = " << d.front() << ", last = " << d.back() << endl;
  sort(d.begin(), d.end());  // 所有支持随机访问的容器，都可以使用sort算法排序
  printDeque(d);
}

// 案例1，评委打分。5位选手，10个评委打分，去掉最低分、最高分，得到平均分
class Player {
 public:
  Player(string name, int score) {
    m_name = name;
    m_score = score;
  }
  string m_name;
  int m_score;
};
void setPlayers(vector<Player>& v) {
  string nameSeed = "ABCDE";
  for (int i = 0; i < 5; i++) {
    string name = "Player ";
    name += nameSeed[i];  // string 可以 + char
    Player p(name, 0);    // 姓名赋值后，初始赋值设为0
    v.push_back(p);
  }
}
void setScores(vector<Player>& v) {
  for (vector<Player>::iterator it = v.begin(); it != v.end();
       it++) {  // 使用迭代器
    deque<int> scores;
    for (int j = 0; j < 10; j++) {
      int score = rand() % 41 + 60;  // 产生 60 - 100 之间随机数
      scores.push_back(score);
    }
    sort(scores.begin(), scores.end());
    scores.pop_back();
    scores.pop_front();

    int sum = 0;
    cout << it->m_name << " 's scores: ";
    for (deque<int>::iterator ii = scores.begin(); ii != scores.end(); ii++) {
      cout << (*ii) << " ";
      sum += *ii;
    }
    cout << endl;
    int ave = sum / scores.size();  // 注意这里可以用size
    it->m_score = ave;
  }

  sort(v.begin(), v.end(),
       [&](Player p1, Player p2) { return p1.m_score > p2.m_score; });
  cout << "Final result: " << endl;
  for (auto i : v)
    cout << i.m_name << " " << i.m_score << endl;
}

int main() {
  vectorInt();
  vectorClass();
  vectorPointer();
  vectorNested();

  stringConstruct();
  stringAssign();
  stringConcatenation();
  stringFindReplace();
  stringCompare();
  stringAccess();
  stringInsertDelete();
  stringSubstr();

  vectorConstruct();
  vectorAssign();
  vectorSize();
  vectorInsertDelete();
  vectorAccess();
  vectorSwap();
  vectorMemoryOpti();
  vectorCapacity();

  dequeConstruct();
  dequeAssign();
  dequeSize();
  dequeInsertDelete();
  dequeAccess();

  vector<Player> v;
  setPlayers(v);
  setScores(v);
  return 0;
}