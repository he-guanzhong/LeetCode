#include <algorithm>
#include <iostream>
#include <list>
#include <map>  // map multimap均包含
#include <queue>
#include <set>  // set multiset均包含
#include <stack>
#include <string>
using namespace std;
// stack容器，栈，先进后出，只有栈顶元素才可以访问，不允许遍历
// size判断个数，top访问栈顶元素，empty判空

void stackConstruct() {
  stack<int> s;
  s.push(1);
  s.push(2);
  s.push(3);
  s.push(4);
  cout << "stack size: " << s.size() << endl;
  while (!s.empty()) {
    cout << "stack top: " << s.top() << " ";
    s.pop();
  }
  cout << endl;
}

// queue容器，队列，先进先出，只有队头队尾元素才能访问，不能遍历
// size判断个数，push/pop压入弹出，front/back访问元素
struct Animal {
  Animal(string name, int age) {
    m_name = name;
    m_age = age;
  }
  string m_name;
  int m_age;
};

void queueConstruct() {
  queue<Animal> q;
  Animal a1("Lion", 10);
  Animal a2("Tiger", 8);
  Animal a3("Cat", 5);
  q.push(a1);
  q.push(a2);
  q.push(a3);
  cout << "queue size: " << q.size() << endl;
  while (!q.empty()) {
    cout << "q front: " << q.front().m_name << " " << q.front().m_age << "  ";
    q.pop();
  }
  cout << endl;
  cout << "queue size: " << q.size() << endl;
}

// List链表，非连续存储，通过数据元素根据指针域连接。其结点包括数据域和指针域
// list内部为双向循环链表：前指针指向前一元素、后指针指向后一元素。末元素后指针指向首元素，首元素前指针指向末元素
// 相比vector优势：插入删除速度快，不会浪费或溢出内存，迭代器不会失效
// 相比vector劣势：占用空间大，遍历访问速度慢
// list链表不连续，迭代器为双向迭代器，只能前后移动，不支持随机访问、跳跃
void printList(list<int>& l) {
  for (list<int>::iterator it = l.begin(); it != l.end(); it++)
    cout << *it << " ";
  cout << endl;
}
void listConstruct() {
  list<int> l1;  // 默认构造
  l1.push_back(1);
  l1.push_back(2);
  l1.push_back(3);
  list<int> l2(l1);  // 拷贝构造
  printList(l2);
  list<int> l3(l1.begin(), l1.end());  // 迭代器构造
  printList(l3);
  list<int> l4(3, 40);  // 参数构造,3个40
  printList(l4);
}
void listAssign() {
  list<int> l1;
  l1.push_back(1);
  l1.push_back(2);
  l1.push_back(3);
  list<int> l2 = l1;  // =赋值
  printList(l2);
  list<int> l3;
  l3.assign(l1.begin(), l1.end());  // assign赋值
  printList(l3);
  list<int> l4;
  l4.assign(3, 50);  // 参数赋值
  printList(l4);
  l1.swap(l4);  // 交换操作
}
void listSize() {
  list<int> l1;
  l1.push_back(1);
  l1.push_back(2);
  l1.push_back(3);
  cout << "list is empty = " << l1.empty() << " , size = " << l1.size() << endl;
  l1.resize(5);
  printList(l1);
  l1.resize(8, 10);
  printList(l1);
  l1.resize(3);
  printList(l1);
}
void listInsertDelete() {  // 相比顺序存储的vector，多一个移除remove函数
  list<int> l1;
  for (int i = 1; i <= 3; i++) {
    l1.push_back(i);
    l1.push_front(10 * i);
  }
  printList(l1);
  l1.pop_back();
  l1.pop_front();
  printList(l1);
  list<int>::iterator it = l1.begin();
  l1.insert(++ ++it, 99);  // 删除第三位元素，此时it已经指向第四元素
  printList(l1);
  l1.erase(-- --it);  // 删除第二元素
  printList(l1);
  l1.push_back(1000);
  l1.push_back(1000);
  l1.push_back(1000);
  printList(l1);
  l1.remove(1000);  // 移除所有值为1000元素
  printList(l1);
  l1.clear();  // 清空
}
void listAcccess() {  // 存取，不支持[]和at，因为不是连续空间，迭代器不支持跳跃访问
  list<int> l1;
  for (int i = 1; i <= 5; i++)
    l1.push_back(i);
  cout << "list first: " << l1.front() << ", last: " << l1.back() << endl;
  list<int>::iterator it = l1.begin();
  // it = it + 3;  // 不能跳跃访问
  // it++ ++ ++;  // 重载i++时 self operator++(int) 返回的是值，不能连续(it++)++
  ++ ++ ++it;  // 移到第四个元素, 重载++i,self&
               // operator++(),返回的是引用，可以++++i
  cout << "access node: " << *it << endl;
}
void listReverseSort() {
  list<int> l1;
  for (int i = 1; i <= 5; i++) {
    l1.push_back(i);
    l1.push_front(i * 3);
  }
  printList(l1);
  l1.reverse();  // 反转，无参数
  printList(l1);
  // sort(l1.begin(), l1.end()); // 不支持随机访问的容器，不能用标准算法排序方式
  l1.sort();  // 内部提供成员函数算法
  printList(l1);
  l1.sort([](int val1, int val2) { return val1 > val2; });
  printList(l1);
}
// 案例，Person定义成员，姓名、年龄、身高
// 规则：按照年龄升序排序，年龄相同按身高降序
class Person {
 public:
  Person(string name, int age, int height) {
    m_name = name;
    m_age = age;
    m_height = height;
  }
  string m_name;
  int m_age;
  int m_height;
};
void casePersonSort() {
  Person p1("张三", 25, 180);
  Person p2("李四", 24, 180);
  Person p3("王五", 26, 180);
  Person p4("赵六", 25, 190);
  Person p5("陈七", 25, 170);
  list<Person> l;
  l.push_back(p1);
  l.push_back(p2);
  l.push_back(p3);
  l.push_back(p4);
  l.push_back(p5);
  l.sort([](Person& p1, Person& p2) {
    return p1.m_age == p2.m_age ? p1.m_height > p2.m_height
                                : p1.m_age < p2.m_age;
  });
  for (list<Person>::iterator it = l.begin(); it != l.end(); ++it)
    cout << it->m_name << " age:" << it->m_age << " height:" << (*it).m_height
         << endl;  // 两种访问方式
}

// set multiset容器，集合。关联式容器，插入项会自动排序
// 底层结构二叉树，set不能重复，multiset可以重复
void printSet(const set<int>& s) {
  for (set<int>::const_iterator it = s.begin(); it != s.end(); it++)
    cout << *it << " ";
  cout << endl;
}
void printMultiset(const multiset<int>& s) {
  for (multiset<int>::const_iterator it = s.begin(); it != s.end(); it++)
    cout << *it << " ";
  cout << endl;
}
void setEmpty(const set<int>& s) {
  if (s.empty())
    cout << "空容器" << endl;
  else
    cout << "容器大小：" << s.size() << endl;
}
void findSet(const set<int>& s, int x) {
  set<int>::iterator it = s.find(x);
  cout << (it == s.end() ? "没找到" : "找到元素") << *it << endl;
}
void findMultiset(const multiset<int>& s, int x) {
  set<int>::iterator it = s.find(x);
  cout << (it == s.end() ? "没找到" : "找到元素") << *it << endl;
}
void setConstruct() {
  set<int> s1;
  s1.insert(1);  // 排序容器只能insert不能push
  s1.insert(2);
  s1.insert(3);
  s1.insert(3);  // 重复数字只能插入一个
  s1.insert(4);
  printSet(s1);
  set<int> s2(s1);  // 拷贝构造
  printSet(s2);
  set<int> s3;  // =赋值
  s3 = s1;
  printSet(s3);

  multiset<int> s4;
  s4.insert(1);  // 排序容器只能insert不能push
  s4.insert(2);
  s4.insert(3);
  s4.insert(3);  // 重复数字只能插入一个
  s4.insert(4);
  multiset<int> s5(s4);  // 拷贝构造
  printMultiset(s4);
  /*   multiset<int> s6(s1);  // multiset\set不能相互拷贝和赋值
    multiset<int> s6;
    s6 = s1; */
  // set没有resize的概念
  s3.insert(9);
  s3.insert(8);
  s3.swap(s1);  // set可以互换
  printSet(s1);
  printSet(s3);
}
void setDeleteFind() {
  set<int> s1;
  multiset<int> s2;
  for (int i = 9; i > 0; i -= 2) {
    s1.insert(i);
    s2.insert(i * 10);
  }
  s2.insert(30);
  s2.insert(30);
  printSet(s1);
  printMultiset(s2);

  s1.erase(3);  // erase可以两种方式，直接值，或者是位置，类似List的remove
  s2.erase(30);
  printSet(s1);
  printMultiset(s2);
  s1.erase(s1.begin());
  s2.erase(s2.begin());
  printSet(s1);
  printMultiset(s2);
  findSet(s1, 5);
  findMultiset(s2, 50);

  s2.insert(70);
  s2.insert(70);
  cout << s1.count(7) << endl;  // 统计7元素的个数
  cout << s2.count(70) << endl;
  s1.clear();
  s2.clear();
}

void setPair() {
  set<int> s1;
  // s.insert()函数会返回一个pair "对组" 值，一为迭代器，二位成功与否
  pair<set<int>::iterator, bool> p1 = s1.insert(1);
  cout << "set容器 " << (p1.second ? "插入成功" : "插入失败") << endl;
  p1 = s1.insert(1);
  cout << "set容器 " << (p1.second ? "插入成功" : "插入失败") << endl;

  // multiset 的insert函数返回的直接是迭代器值，因为其插入必成功
  multiset<int> s2;
  multiset<int>::iterator p2 = s2.insert(1);
  cout << "multiset容器 " << (*p2) << endl;
  p2 = s2.insert(1);
  cout << "multiset容器 " << (*p2) << endl;
  // pair 对组练功构造方法
  pair<string, int> p3("Tom", 20);
  pair<string, int> p4 = make_pair("Jerry", 10);
  cout << p3.first << " " << p3.second << endl;
  cout << p4.first << " " << p4.second << endl;
}

// set排序自定义大小
class MyCompare {
 public:
  bool operator()(int a, int b) { return a > b; }  // 仿函数，重载大小
};
void setSort() {
  set<int> s1;
  for (int i = 5; i > 0; i--)
    s1.insert(i);
  printSet(s1);

  set<int, MyCompare> s2;
  for (int i = 1; i < 6; i++)
    s2.insert(i);
  // 仿函数放置set第二位，即可重新定义排序顺序
  for (set<int, MyCompare>::iterator it = s2.begin(); it != s2.end(); it++)
    cout << *it << " ";
  cout << endl;
}

class Person1 {
 public:
  Person1(string name, int age) {
    m_name = name;
    m_age = age;
  }
  string m_name;
  int m_age;
};
class MyComparePerson {  // 仿函数，按照年龄降序
 public:
  bool operator()(Person1 a, Person1 b) { return a.m_age > b.m_age; }
};
void setSortClass() {
  set<Person1, MyComparePerson> s;  // 自定义数据类型比较，必须定义仿函数
  Person1 p1("小明", 20);
  Person1 p2("小刚", 24);
  Person1 p3("小李", 21);
  Person1 p4("小张", 27);
  Person1 p5("小军", 23);
  s.insert(p1);
  s.insert(p2);
  s.insert(p3);
  s.insert(p4);
  s.insert(p5);
  for (set<Person1, MyComparePerson>::iterator it = s.begin(); it != s.end();
       it++)
    cout << it->m_name << " " << (*it).m_age << endl;
}

// map multimap容器，内部为pair,第一位为键值key,第二位为实值value
// 高性能、高效率可以快速查询key值和其唯一对应的value, 所有元素按照key排序
// 均为关联式容器，底层使用平衡二叉树实现
// map 不允许有重复key, multimap允许重复key
void printMap(map<int, int>& m) {
  for (map<int, int>::iterator it = m.begin(); it != m.end(); it++)
    cout << "(key:" << it->first << ", value:" << (*it).second << ")  ";
  cout << endl;
}
void mapConstructFind() {
  map<int, int> m1;
  m1.insert(pair<int, int>(1, 10));
  m1.insert(pair<int, int>(4, 40));
  m1.insert(pair<int, int>(3, 30));
  m1.insert(pair<int, int>(2, 20));

  map<int, int> m2(m1);  // 构造
  printMap(m2);
  map<int, int> m3;
  m3 = m1;  // = 赋值
  printMap(m3);
  cout << "size: " << m1.size() << endl;

  map<int, int> m4;
  m4.insert(pair<int, int>(9, 90));
  m4.insert(pair<int, int>(8, 80));
  m4.swap(m1);
  printMap(m1);
  printMap(m4);

  map<int, int>::iterator it = m1.find(9);
  if (it == m1.end())
    cout << "没有找到" << endl;
  else
    cout << "找到key " << it->first << "  value " << it->second << endl;
  cout << "找到元素数量 " << m1.count(8) << endl;  // map要么是0要么是1
}

void mapInsertDelete() {
  map<int, int> m;  // 四种插入方法
  m.insert(pair<int, int>(1, 11));
  m.insert(make_pair(2, 22));
  m.insert(map<int, int>::value_type(3, 33));  // 不常用
  m[4] = 44;  // 不建议用于插入，因为不写value,会自动默认创建为0
  cout << "key 3's value " << m[3] << endl;  //[] 可以用来通过key访问value
  printMap(m);

  m.erase(m.begin());  // erase可以删除key值或位置
  m.erase(3);
  printMap(m);
  m.clear();
}

void mapSort() {
  map<int, int, MyCompare> m;
  m.insert(pair<int, int>(1, 10));
  m.insert(make_pair(2, 20));
  m.insert(map<int, int>::value_type(3, 30));
  m[4] = 40;
  // printMap(m); 原函数接收的不能直接打印，需要重写打印函数
  for (map<int, int, MyCompare>::iterator it = m.begin(); it != m.end(); it++)
    cout << "(key:" << it->first << ", value:" << (*it).second << ")  ";
  cout << endl;
}
void mapSortClass() {
  map<Person1, int, MyComparePerson> m;  // 自定义数据类型比较，必须定义仿函数
  Person1 m1("小明", 20);
  Person1 m2("小刚", 24);
  Person1 m3("小李", 21);
  Person1 m4("小张", 27);
  Person1 m5("小军", 23);
  m.insert(pair<Person1, int>(m1, 100));
  m.insert(pair<Person1, int>(m2, 200));
  m.insert(pair<Person1, int>(m3, 300));
  m.insert(pair<Person1, int>(m4, 400));
  m.insert(pair<Person1, int>(m5, 500));
  for (map<Person1, int, MyComparePerson>::iterator it = m.begin();
       it != m.end(); it++)
    cout << it->first.m_name << " " << it->first.m_age
         << " score:" << (*it).second << endl;
}

// 案例：员工分组，创建十个员工，根据三个部分将其分组，然后展示
#define PLAN 0
#define ART 1
#define RND 2
class Worker {
 public:
  Worker(string name, int salary) {
    m_name = name;
    m_salary = salary;
  }
  string m_name;
  int m_salary;
};
void createWorkers(vector<Worker>& workers) {
  string nameSeed = "ABCDEFGHIJ";
  for (int i = 0; i < nameSeed.size(); i++) {
    string name = "员工";
    name += nameSeed[i];
    int salary = 1000 + 100 * i;
    Worker w(name, salary);
    workers.push_back(w);
    cout << workers[i].m_name << " " << workers[i].m_salary << endl;
  }
  cout << endl;
}
void setGroup(vector<Worker>& v, multimap<int, Worker>& m) {
  for (vector<Worker>::iterator it = v.begin(); it != v.end(); it++) {
    int groupId = rand() % 3;  // 0 1 2 代表三个部门
    m.insert(make_pair(groupId, *it));
  }
}
void showResult(multimap<int, Worker>& m) {
  // 分三段打印员工，因为key的顺序不一定从0开始。引入index为数量，但定义必须在for循环外
  cout << "RnD:\t";
  int index = m.count(RND);
  for (multimap<int, Worker>::iterator it = m.find(RND);
       it != m.end() && index > 0; it++, index--) {
    cout << it->second.m_name << " " << it->second.m_salary << "  ";
  }
  cout << endl;
  cout << "Art:\t";
  index = m.count(ART);
  for (multimap<int, Worker>::iterator it = m.find(ART);
       it != m.end() && index > 0; it++, index--) {
    cout << it->second.m_name << " " << it->second.m_salary << "  ";
  }
  cout << endl;
  cout << "Plan:\t";
  index = m.count(PLAN);
  for (multimap<int, Worker>::iterator it = m.find(PLAN);
       it != m.end() && index > 0; it++, index--) {
    cout << it->second.m_name << " " << it->second.m_salary << "  ";
  }
  cout << endl;
}
void caseWorkerGroup() {
  vector<Worker> v;
  multimap<int, Worker> m;
  createWorkers(v);
  setGroup(v, m);
  showResult(m);
}
int main() {
  stackConstruct();
  queueConstruct();

  listConstruct();
  listAssign();
  listSize();
  listInsertDelete();
  listAcccess();
  listReverseSort();
  casePersonSort();

  setConstruct();
  setDeleteFind();
  setPair();
  setSort();
  setSortClass();

  mapConstructFind();
  mapInsertDelete();
  mapSort();
  mapSortClass();
  caseWorkerGroup();
  return 0;
}