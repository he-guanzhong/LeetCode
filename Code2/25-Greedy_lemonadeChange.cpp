#include "head.h"
/* 860. 柠檬水找零
在柠檬水摊上，每一杯柠檬水的售价为 5 美元。顾客排队购买你的产品，（按账单 bills
支付的顺序）一次购买一杯。每位顾客只买一杯柠檬水，然后向你付 5 美元、10 美元或
20 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 5
美元。注意，一开始你手头没有任何零钱。 给你一个整数数组 bills ，其中 bills[i]
是第i位顾客付的账。如果你能给每位顾客正确找零，返回 true ，否则返回 false 。
示例 1：
  输入：bills = [5,5,5,10,20]
  输出：true
  解释：
    前 3 位顾客那里，我们按顺序收取 3 张 5 美元的钞票。
    第 4 位顾客那里，我们收取一张 10 美元的钞票，并返还 5 美元。
    第 5 位顾客那里，我们找还一张 10 美元的钞票和一张 5 美元的钞票。
    由于所有客户都得到了正确的找零，所以我们输出 true。
示例 2：
  输入：bills = [5,5,10,10,20]
  输出：false
  解释：
    前 2 位顾客那里，我们按顺序收取 2 张 5 美元的钞票。
    对于接下来的 2 位顾客，我们收取一张 10 美元的钞票，然后返还 5 美元。
    对于最后一位顾客，我们无法退回 15 美元，因为我们现在只有两张 10 美元的钞票。
    由于不是每位顾客都得到了正确的找零，所以答案是 false。 */

bool lemonadeChange(vector<int>& bills) {
  int five = 0, ten = 0;
  for (int i = 0; i < bills.size(); i++) {
    if (bills[i] == 5)
      five++;
    else if (bills[i] == 10) {
      if (--five < 0)
        return false;
      ten++;
    } else {
      if (ten) {
        ten--;
        five--;
      } else {
        five -= 3;
      }
      if (five < 0)
        return false;
    }
  }
  return true;
}

// 使用普通整形变量基数，分三种情况讨论即可。注意收到20时，优先判断10和5够不够，再次判断5有没有3个以上。其余情况都是不可行的
// 直接模拟，5、10美元数即可，不必设置20美元数。twenty 这个变量可有可无
bool lemonadeChange1(vector<int>& bills) {
  int five = 0, ten = 0, twenty = 0;
  for (int bill : bills) {
    if (bill == 5)
      five++;
    if (bill == 10) {
      if (five <= 0)
        return false;
      five--;
      ten++;
    }
    if (bill == 20) {
      if (ten > 0 && five > 0) {
        ten--;
        five--;
      } else if (five >= 3) {
        five -= 3;
      } else {
        return false;
      }
    }
  }
  return true;
}

int main() {
  vector<int> nums1 = {5, 5, 5, 10, 20};
  vector<int> nums2 = {5, 5, 10, 10, 20};
  vector<int> nums3 = {1, 3, 2, 2, 1};
  cout << lemonadeChange(nums1) << " " << lemonadeChange(nums2) << " "
       << lemonadeChange(nums3) << endl;
  cout << lemonadeChange1(nums1) << " " << lemonadeChange1(nums2) << " "
       << lemonadeChange1(nums3) << endl;
  return 0;
}