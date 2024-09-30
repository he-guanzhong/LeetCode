#include <cmath>
#include <iostream>
using namespace std;
// 传统写法
class calculator {
 public:
  double getResult(string oper) {
    if (oper == "+")
      return m_num1 + m_num2;
    else if (oper == "*")
      return m_num1 * m_num2;
    else if (oper == "√")
      return sqrt(m_num1);
    else if (oper == "sin")
      return sin(m_num1);
    else if (oper == "log10")
      return log10(m_num1);
    return 0;
  }
  double m_num1, m_num2;
};

// 多态写法
class BasicCalculator {
 public:
  virtual double getResult() {
    return 0;
  };  // 此处不能写为纯虚函数，否则影响子类为抽象类型
  double m_num1, m_num2;
};
class PlusCalculator : public BasicCalculator {  // 加法计算器类
 public:
  double getResult() { return m_num1 + m_num2; }  // virtual可写可不写
};
class MultiplyCalculator : public BasicCalculator {
 public:
  double getResult() { return m_num1 * m_num2; }
};
class SqrtCalculator : public BasicCalculator {
 public:
  double getResult() { return sqrt(m_num1); }
};
class SinCalculator : public BasicCalculator {
 public:
  double getResult() { return sin(m_num1); }
};
class Log10Calculator : public BasicCalculator {
 public:
  double getResult() { return log10(m_num1); }
};

int main() {
  calculator c;
  c.m_num1 = 2.5, c.m_num2 = 4.7;
  cout << "nums1 + num2 = " << c.getResult("+") << endl;
  cout << "nums1 * num2 = " << c.getResult("*") << endl;
  cout << "nums1 √ = " << c.getResult("√") << endl;
  cout << "sin(nums1) = " << c.getResult("sin") << endl;
  cout << "log10(nums1) = " << c.getResult("log10") << endl;
  cout << endl;

  BasicCalculator* p = new PlusCalculator;  // 堆区数据，手动开辟，手动释放
  p->m_num1 = 2.5, p->m_num2 = 4.7;
  cout << "nums1 + num2 = " << p->getResult() << endl;
  delete p;
  p = new MultiplyCalculator;
  p->m_num1 = 2.5, p->m_num2 = 4.7;
  cout << "nums1 * num2 = " << p->getResult() << endl;
  delete p;
  p = new SqrtCalculator;
  p->m_num1 = 2.5;
  cout << "nums1 √ = " << p->getResult() << endl;
  delete p;
  p = new SinCalculator;
  p->m_num1 = 2.5;
  cout << "sin(nums1) = " << p->getResult() << endl;
  delete p;
  p = new Log10Calculator;
  p->m_num1 = 2.5;
  cout << "log10 = " << p->getResult() << endl;
  delete p;
  return 0;
}