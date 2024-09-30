#include <algorithm>
#include <ctime>
#include <iostream>
#include <numeric>  // accumulate和fill算法需要
#include <vector>
using namespace std;
// 常用STL容器算法

// 遍历
void printNormal(int x) {
  cout << x << " ";
}
class printFunctor {
 public:
  void operator()(int x) { cout << x << " "; }
};
class Transform {
 public:
  int operator()(int x) { return x * 10; }
};
void traverse() {
  // for_each用于遍历，第三个参数为函数或仿函数
  vector<int> v1;
  for (int i = 0; i < 10; i++)
    v1.push_back(i);
  for_each(v1.begin(), v1.end(), printNormal);  // 普通函数，放函数名，不加括号
  cout << endl;
  for_each(v1.begin(), v1.end(), printFunctor());  // 仿函数要构造对象，加括号
  cout << endl;

  // transform函数用于遍历，放原容器起始点，新容器起始点，函数对象，注意新容器大小一定要指定
  vector<int> v2;
  v2.resize(v1.size());  // 必须指定大小
  // vector<int> v2(v1.size());
  transform(v1.begin(), v1.end(), v2.begin(), Transform());
  for_each(v2.begin(), v2.end(), printNormal);  // 仿函数要构造对象，加括号
  cout << endl;
}

// 查找
class GreaterFive {
 public:
  bool operator()(int x) { return x > 5; }
};
void find() {
  vector<int> v1;
  for (int i = 0; i < 10; i++)
    v1.push_back(i);
  vector<int>::iterator it = find(v1.begin(), v1.end(), 5);
  cout << "find value " << (it == v1.end() ? "没找到" : "找到了") << endl;
  it = find_if(v1.begin(), v1.end(), GreaterFive());
  cout << "find value " << (it == v1.end() ? "没找到" : "找到了") << endl;
}
class Person {
 public:
  Person(string name, int age) {
    m_name = name;
    m_age = age;
  }
  bool operator==(const Person& p) {  // 类内重载，否则无法比较
    return this->m_age == p.m_age && this->m_name == p.m_name;
  }
  string m_name;
  int m_age;
};
struct Greater23 {
  bool operator()(const Person& p) { return p.m_age > 23; }
};
void findClass() {
  Person p1 = {"张三", 25};
  Person p2("李四", 21);
  Person p3 = Person("王五", 24);
  Person p4("赵六", 22);
  vector<Person> v;
  v.push_back(p1);
  v.push_back(p2);
  v.push_back(p3);
  v.push_back(p4);
  vector<Person>::iterator it = find(v.begin(), v.end(), Person("赵六", 22));
  cout << "find Class " << (it == v.end() ? "没找到" : "找到了") << endl;

  vector<Person>::iterator ii = find_if(v.begin(), v.end(), Greater23());
  cout << "find Class " << (ii == v.end() ? "没找到" : "找到了") << endl;
}
void findAdjacentBinary() {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(2);
  v.push_back(2);
  v.push_back(3);
  vector<int>::iterator it =
      adjacent_find(v.begin(), v.end());  // 查找相邻重复元素
  if (it == v.end())
    cout << "没找到相邻重复元素" << endl;
  else
    cout << "相邻重复元素" << *it << endl;

  bool result = binary_search(v.begin(), v.end(),
                              3);  // 查找元素是否存在，返回bool,无序序列不可用
  cout << "元素3是否存在" << result << "  元素4是否存在"
       << binary_search(v.begin(), v.end(), 4) << endl;
}

// 统计算法
class GreaterAge23 {
 public:
  bool operator()(Person p) { return p.m_age > 23; }
};
void statistic() {
  vector<int> v;
  for (int i = 1; i < 7; i++) {
    v.push_back(i);
    v.push_back(4);
  }
  int num1 = count(v.begin(), v.end(), 4);
  cout << "等于4元素个数 " << num1 << endl;
  // 大于5的元素个数
  int num2 =
      count_if(v.begin(), v.end(), GreaterFive());  // 统计算法要用count_if
  cout << "大于5元素个数 " << num2 << endl;

  vector<Person> v1;
  Person p1 = {"张三", 25};
  Person p2("李四", 21);
  Person p3 = Person("王五", 24);
  Person p4("赵六", 22);
  Person p5 = p4;
  v1.push_back(p1);
  v1.push_back(p2);
  v1.push_back(p3);
  v1.push_back(p4);
  v1.push_back(p5);
  int num3 = count(v1.begin(), v1.end(), Person("赵六", 22));
  cout << "等于赵六元素个数 " << num3 << endl;
  int num4 = count_if(v1.begin(), v1.end(), GreaterAge23());
  cout << "年龄大于23元素个数 " << num4 << endl;
}

// 排序算法
void sort() {
  // sort(greater<int>())  random_shuffle
  vector<int> v;
  for (int i = 1; i < 5; i++) {
    v.push_back(i);
    v.push_back(10 - i);
  }
  for_each(v.begin(), v.end(), printNormal);
  cout << endl;
  sort(v.begin(), v.end());  // 默认由低到高排序
  for_each(v.begin(), v.end(), printFunctor());
  cout << endl;

  sort(v.begin(), v.end(), greater<int>());  // 可选由高到低排序
  for_each(v.begin(), v.end(), printNormal);
  cout << endl;

  srand((unsigned int)time(NULL));  // 播撒随机数粽子
  random_shuffle(v.begin(), v.end());
  for_each(v.begin(), v.end(), printNormal);
  cout << endl;
}

// 合并 容器合并，两个容器必须都有序，且都升序或者降序
void merge() {
  vector<int> v1, v2, v3;
  for (int i = 1; i <= 10; i += 2) {
    v1.push_back(i);
    v2.push_back(i + 1);
  }
  v3.resize(v1.size() + v2.size());  // merge前必须确定大小，类似transform
  merge(v1.begin(), v1.end(), v2.begin(), v2.end(), v3.begin());
  for_each(v3.begin(), v3.end(), printNormal);
  cout << endl;
  reverse(v3.begin(), v3.end());  // 反转
  for_each(v3.begin(), v3.end(), printNormal);
  cout << endl;
}

// 拷贝、替换和交换
void copyReplaceSwap() {
  vector<int> v1;
  for (int i = 3; i <= 7; i++)
    v1.push_back(i);
  vector<int> v2;
  v2.resize(v1.size());
  copy(v1.begin(), v1.end(), v2.begin());
  // v2 = v1 另一种拷贝用法
  for_each(v2.begin(), v2.end(), printNormal);
  cout << endl;

  replace(v1.begin(), v1.end(), 5, 10);  // 将5替换为10
  for_each(v1.begin(), v1.end(), printNormal);
  cout << endl;
  replace_if(v2.begin(), v2.end(), GreaterFive(), 10);  // 将大于5的替换为10
  for_each(v2.begin(), v2.end(), printNormal);
  cout << endl;

  vector<int> v3;
  for (int i = 1; i < 6; i++)
    v3.push_back(i);
  swap(v1, v3);  // 交换函数
  // v1.swap(v3);
  for_each(v1.begin(), v1.end(), printNormal);
  cout << endl;
}

// 算数生成
void accumulateFill() {
  vector<int> v1;
  for (int i = 1; i <= 10; i++)
    v1.push_back(i);
  int sum =
      accumulate(v1.begin(), v1.end(), 0);  // 需要numeric头文件,0为起始累加点
  cout << "总和 " << sum << endl;
  fill(v1.begin(), v1.end(), 10);
  for_each(v1.begin(), v1.end(), printNormal);
  cout << endl;
}

// 常用集合算法，交集、并集、差集
void intersectionUnionDifference() {
  vector<int> v1, v2;
  for (int i = 0; i < 10; i++) {
    v1.push_back(i);
    v2.push_back(i + 5);
  }
  vector<int> vIntersection;  // 求交集，大小为二者最小的一个
  vIntersection.resize(min(v1.size(), v1.size()));
  vector<int>::iterator it_inter = set_intersection(
      v1.begin(), v1.end(), v2.begin(), v2.end(), vIntersection.begin());
  for_each(vIntersection.begin(), it_inter,
           printNormal);  // 注意交集末尾为it而不是交集的最后值
  cout << endl;

  vector<int> vUnion(v1.size() + v2.size());  // 求并集，大小为二者之和
  vector<int>::iterator it_union =
      set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), vUnion.begin());
  for_each(vUnion.begin(), it_union, printNormal);
  cout << endl;

  vector<int> vDifference(max(v1.size(), v2.size()));  // 求差集，前面的为被减数
  vector<int>::iterator it_diff = set_difference(
      v1.begin(), v1.end(), v2.begin(), v2.end(), vDifference.begin());
  for_each(vDifference.begin(), it_diff, printNormal);
  cout << endl;
  it_diff = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(),
                           vDifference.begin());
  for_each(vDifference.begin(), it_diff, printNormal);
  cout << endl;
}
int main() {
  traverse();
  find();
  findClass();
  findAdjacentBinary();

  statistic();
  sort();
  merge();
  copyReplaceSwap();
  accumulateFill();
  intersectionUnionDifference();
  return 0;
}