#include <iostream>
#include <memory>
using namespace std;

// C++中三种智能指针，unique_ptr, shared_ptr, weak_ptr
// 定义在头文件<memory>，可对动态资源管理，构造对象销毁时析构函数被调用

// unique_ptr，是一个模板创建的对象，不用加*。生命周期从指针创建开始，到离开作用域结束
// 通过禁止拷贝语义，只有移动语义实线同一时刻只有一个unique_ptr绑定对象
class UniquePtrObj {
 public:
  ~UniquePtrObj() { cout << "deconstruct" << endl; }
};
void unique_ptr_test() {
  unique_ptr<int> up1(new int(11));  // 指向堆区空间
  cout << "*up1: " << *up1 << "\t";
  // unique_ptr<int> up2 = up1; // 自动禁止拷贝构造
  unique_ptr<int> up3 = move(up1);  // 允许移动构造，但up1变为野指针不能再使用
  // cout << "*up1 after: " << *up1 << "\t";
  cout << "*up3: " << *up3 << "\n";

  unique_ptr<UniquePtrObj> up4(new UniquePtrObj);  // 无需手动释放
  up4 = nullptr;                                   // 手动释放，指向空指针
  up4.reset();  // 手动释放，可执行多次，但只析构一次，堆内存只释放一次
                // 离开作用域，析构函数自动调用

  unique_ptr<int> up5(new int(11));
  up5.reset();             // 无参，显示释放堆内存
  up5.reset(new int(22));  // 有参。释放原内存后，重新绑定新堆区
  cout << "*up5: " << *up5 << "\t";
  int* p = up5.release();  // 释放控制权给普通指针，但不释放堆内存
  // cout << "*up5 release: " << *up5 << "\n"; // up5变为野指针，不得再次使用
  cout << "*p: " << *p << endl;
  delete p;  // 普通指针，必须手动释放
}

// 共享指针，允许多个智能指针对象共同管理一块堆内存，使用引用计数机制。
// 若最后一个共享指针销毁，计数器为0，才自动删除对象
void shared_ptr_test() {
  shared_ptr<int> sp1(new int(5));
  shared_ptr<int> sp2 = sp1;  // 允许拷贝构造
  cout << "sp1 cnt: " << sp1.use_count() << ", sp2 cnt: " << sp2.use_count()
       << ". sp1 val: " << *sp1 << ", sp2 val: " << *sp2 << endl;
  // 2 2 5 5
  sp1.reset();  // 只释放sp1，堆内存仍然存在
  cout << "sp1 cnt: " << sp1.use_count() << ", sp2 cnt: " << sp2.use_count()
       << ". sp2 val: " << *sp2 << endl;
  // 0 1 5
  sp2.reset();
  cout << "sp1 cnt: " << sp1.use_count() << ", sp2 cnt: " << sp2.use_count()
       << endl;
  // 0 0
}

// weak_ptr弱指针。由shared_ptr或weak_ptr对象构造，不能单独管理堆内存。构造析构补不影响引用计数变化
// 没有重载*和->符号，其虽然指向shared_ptr的内存空间，但不拥有改内存
// 使用lock()可返回一个可用的shared_ptr。若指向的内存已经无效，则返回nullptr

void weak_ptr_test() {
  shared_ptr<int> sp1(new int(8));
  shared_ptr<int> sp2 = sp1;  // 两个指针绑定同一块堆内存
  weak_ptr<int> wp = sp1;     // 三个指针绑定内存，弱指针不影响引用计数
  cout << "sp1 cnt: " << sp1.use_count() << ", sp2 cnt: " << sp2.use_count()
       << ". wp cnt: " << wp.use_count() << endl;  // 2 2 2
  // cout << "wp val: " << *wp << endl;               //
  // wp没有和堆内存绑定，不能使用wp操作符
  shared_ptr<int> sp3 = wp.lock();  // lock返回一个可用的share_ptr对象
  cout << "sp1 cnt: " << sp1.use_count() << ", sp2 cnt: " << sp2.use_count()
       << ". wp cnt: " << wp.use_count() << ". sp3 cnt: " << sp3.use_count()
       << endl;  // 3 3 3 3
  sp1.reset();
  cout << "sp1 cnt: " << sp1.use_count() << ", sp2 cnt: " << sp2.use_count()
       << ". wp cnt: " << wp.use_count() << ". sp3 cnt: " << sp3.use_count()
       << endl;  // 0 2 2 2
  sp2.reset();
  cout << "sp1 cnt: " << sp1.use_count() << ", sp2 cnt: " << sp2.use_count()
       << ". wp cnt: " << wp.use_count() << ". sp3 cnt: " << sp3.use_count()
       << endl;  // 0 0 1 1
  sp3.reset();
  cout << "sp1 cnt: " << sp1.use_count() << ", sp2 cnt: " << sp2.use_count()
       << ". wp cnt: " << wp.use_count() << ". sp3 cnt: " << sp3.use_count()
       << endl;                     // 0 0 0 0
  wp.reset();                       // 上述操作已经释放堆内存，该操作可加可不加
  shared_ptr<int> tmp = wp.lock();  // 此时堆内存已被释放，返回空指针
  if (tmp == nullptr) {
    cout << "heap memory has been released" << endl;
  }
  return;
}

int main() {
  unique_ptr_test();
  shared_ptr_test();
  weak_ptr_test();
  return 0;
}