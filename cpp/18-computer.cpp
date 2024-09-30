#include <cmath>
#include <iostream>
using namespace std;
/* 1，电脑主要部件为CPU，显卡，内存，硬盘，每个部件有其对应的价格；
    2，将每个零件封装出抽象基类，并提供不同厂商生产不同部件；
    3，创建电脑类，提供让电脑工作的函数，并调用每个部件的工作接口；
    4，组装两台不同的电脑进行工作，并显示出总价格； */

class CPU {  // 先设4个抽象类
 public:
  virtual void calculate() = 0;
};
class VideoCard {
 public:
  virtual void display() = 0;
};
class Memory {
 public:
  virtual void storage() = 0;
};
class HardDisk {
 public:
  virtual void massStore() = 0;
};

class IntelCPU : public CPU {
 public:
  void calculate() { cout << "Intel CPU \t"; }
  int m_price = 1;
};
class IntelVideoCard : public VideoCard {
 public:
  void display() { cout << "Intel videocard \t"; }
  int m_price = 2;
};
class IntelMemory : public Memory {
 public:
  void storage() { cout << "Intel memory      \t"; }
  int m_price = 3;
};
class IntelHardDisk : public HardDisk {
 public:
  void massStore() { cout << "Intel HardDisk " << endl; }
  int m_price = 4;
};
class AMDCPU : public CPU {
 public:
  void calculate() { cout << "AMD CPU \t"; }
  int m_price = 10;
};
class NvidiaVideoCard : public VideoCard {
 public:
  void display() { cout << "Nvidia videocard \t"; }
  int m_price = 20;
};
class KingstenMemory : public Memory {
 public:
  void storage() { cout << "Kingsten memory \t"; }
  int m_price = 30;
};
class SanDiskHardDisk : public HardDisk {
 public:
  void massStore() { cout << "SanDisk HardDisk " << endl; }
  int m_price = 40;
};

class Computer {
 public:
  Computer(CPU* cpu, VideoCard* videocard, Memory* memory, HardDisk* harddisk) {
    m_cpu = cpu;
    m_videocard = videocard;
    m_memory = memory;
    m_harddisk = harddisk;
  }
  void execute() {
    m_cpu->calculate();
    m_videocard->display();
    m_memory->storage();
    m_harddisk->massStore();
  }
  ~Computer() {  // 由于内含四个指针，虚构函数需要释放
    if (m_cpu != nullptr) {
      delete m_cpu;
      m_cpu = nullptr;
    }
    if (m_videocard != nullptr) {
      delete m_videocard;
      m_videocard = nullptr;
    }
    if (m_memory != nullptr) {
      delete m_memory;
      m_memory = nullptr;
    }
    if (m_harddisk != nullptr) {
      delete m_harddisk;
      m_harddisk = nullptr;
    }
  }
  void totalPrice(int& cpu_price,
                  int& videocard_price,
                  int& memory_price,
                  int& harddisk_price) {
    m_cpu_price = cpu_price;
    m_videocard_price = videocard_price;
    m_memory_price = memory_price;
    m_harddisk_price = harddisk_price;
    cout << "Price: "
         << m_cpu_price + m_videocard_price + m_memory_price + m_harddisk_price
         << endl;
  }
  int m_cpu_price;
  int m_videocard_price;
  int m_memory_price;
  int m_harddisk_price;
  CPU* m_cpu;
  VideoCard* m_videocard;
  Memory* m_memory;
  HardDisk* m_harddisk;
};

int main() {
  Computer computer1(new IntelCPU, new IntelVideoCard, new IntelMemory,
                     new IntelHardDisk);
  computer1.execute();
  IntelCPU cpu1;
  IntelVideoCard videocard1;
  IntelMemory memory1;
  IntelHardDisk harddisk1;
  computer1.totalPrice(cpu1.m_price, videocard1.m_price, memory1.m_price,
                       harddisk1.m_price);

  Computer* pc2 = new Computer(new AMDCPU, new NvidiaVideoCard,
                               new KingstenMemory, new SanDiskHardDisk);
  AMDCPU cpu2;
  NvidiaVideoCard videocard2;
  KingstenMemory memory2;
  SanDiskHardDisk harddisk2;
  pc2->execute();
  pc2->totalPrice(cpu2.m_price, videocard2.m_price, memory2.m_price,
                  harddisk2.m_price);
  delete pc2;
}