#include "head.h"
/* LCR 189. 设计机械累加器
请设计一个机械累加器，计算从 1、2... 一直累加到目标数值 target
的总和。注意这是一个只能进行加法操作的程序，不具备乘除、if-else、switch-case、for
循环、while 循环，及条件判断语句等高级功能。
示例 1：
输入: target = 5
输出: 15
示例 2：
输入: target = 7
输出: 28
提示：
    1 <= target <= 10000  */

int mechanicalAccumulator(int target) {
  target > 1 && (target += mechanicalAccumulator(target - 1));
  return target;
}

// 要使用逻辑运算符的短路效应。&&第一个为假，第二个即不再执行。||第一个为真，第二个即不再执行。
// 退出条件时target==1，如此应该退出递归，直接返回target。否则应该对target更新下一层返回的总和
// 注意，&&左侧表达式，一般为条件表达式（不是条件判断语句）,返回真假。右侧表达式，允许为赋值表达式。
int mechanicalAccumulator1(int target) {
  target > 1 && (target += mechanicalAccumulator1(target - 1));
  return target;
}

int main() {
  cout << mechanicalAccumulator(5) << " " << mechanicalAccumulator(7) << endl;
  cout << mechanicalAccumulator1(5) << " " << mechanicalAccumulator1(7) << endl;

  return 0;
}