#include "head.h"
/* 202. 快乐数
编写一个算法来判断一个数 n 是不是快乐数。
「快乐数」定义为：对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和，然后重复这个过程直到这个数变为
1，也可能是 无限循环 但始终变不到 1。如果 可以变为  1，那么这个数就是快乐数。
如果 n 是快乐数就返回 True ；不是，则返回 False 。
示例：
  输入：19
  输出：true
  解释：
    1^2 + 9^2 = 82
    8^2 + 2^2 = 68
    6^2 + 8^2 = 100
    1^2 + 0^2 + 0^2 = 1
示例 2：
  输入：n = 2
  输出：false */

bool isHappy(int n) {
  unordered_set<int> uset;
  while (n != 1) {
    uset.insert(n);
    int tmp = 0;
    while (n) {
      int digit = n % 10;
      tmp += digit * digit;
      n /= 10;
    }
    if (uset.find(tmp) != uset.end())
      return false;
    n = tmp;
  }
  return true;
}

// 不快乐的数，总和必无限循环，则利用哈希表记录每次的总和，若出现过，则必为假
// 判断快乐数，核心在于两层循环+set集合判断计算结果曾经过，作为退出条件。一、外置计数sum,使用while(n)求每次位置数字平方和。
// 二、无线循环while(1)中，如果出现n==1返回真。使用unordered_set记录每次的n，如果发现曾经出现过，就返回假，否则再插入
// 注意：不得计算出新的n后，直接插入set。必须先判断set中有无现有值，再插入。
bool isHappy1(int num) {
  unordered_set<int> set;
  while (1) {
    int sum = 0;  // 先求总和
    while (num) {
      sum += (num % 10) * (num % 10);
      num /= 10;
    }
    if (sum == 1)  // 结果为1 就返回真
      return true;
    if (set.find(sum) != set.end())  // 找到就返回假
      return false;
    else
      set.insert(sum);
    num = sum;  // 无限循环可以不使用递归
  }
}

int main() {
  int num1 = 19, num2 = 2;
  cout << isHappy(num1) << " " << isHappy(num2) << endl;
  cout << isHappy1(num1) << " " << isHappy1(num2) << endl;

  return 0;
}