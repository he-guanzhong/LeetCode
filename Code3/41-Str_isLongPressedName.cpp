#include "head.h"
/* 925. 长按键入
你的朋友正在使用键盘输入他的名字 name。偶尔，在键入字符 c
时，按键可能会被长按，而字符可能被输入 1 次或多次。
你将会检查键盘输入的字符typed。如果它对应的可能是你的朋友的名字（其中一些字符可能被长按），那么就返回
True。
示例 1：
  输入：name = "alex", typed = "aaleex"
  输出：true
  解释：'alex' 中的 'a' 和 'e' 被长按。
示例 2：
  输入：name = "saeed", typed = "ssaaedd"
  输出：false
  解释：'e' 一定需要被键入两次，但在 typed 的输出中不是这样。
提示：
    1 <= name.length, typed.length <= 1000
    name 和 typed 的字符都是小写字母 */

bool isLongPressedName(string name, string typed) {
  int i = 0, j = 0;
  while (j < typed.size()) {
    if (i < name.size() && name[i] == typed[j]) {
      i++;
      j++;
    } else if (j > 0 && typed[j] == typed[j - 1]) {
      j++;
    } else {
      return false;
    }
  }
  return i == name.size();
}

// 要求顺序匹配，双指针。如果双方字母匹配上，i,j位置各加1，若匹配不上，且不是首位，单移动j，保证去重
// 返回假三种情况：1.i已先于j耗尽。2.首位就匹配不上，例如b和xxb，无需去重。3.直接匹配不上，且不符合去重条件
// j到末端后，观察i位置，及name是否所有元素都被匹配，如果是，则返回真，否
bool isLongPressedName1(string name, string typed) {
  int i = 0, j = 0;
  while (j < typed.size()) {
    if (i < name.size() && name[i] == typed[j]) {
      i++;
      j++;
    } else if (j > 0 && typed[j - 1] == typed[j]) {
      j++;
    } else {
      return false;
    }
  }
  return i == name.size();
}

int main() {
  string name1 = "alex", typed1 = "aaleex";
  string name2 = "saeed", typed2 = "ssaaedd";
  string name3 = "rick", typed3 = "kric";
  string name4 = "leelee", typed4 = "lleeelee";
  string name5 = "alex", typed5 = "aaleexa";
  cout << isLongPressedName(name1, typed1) << " "
       << isLongPressedName(name2, typed2) << " "
       << isLongPressedName(name3, typed3) << " "
       << isLongPressedName(name4, typed4) << " "
       << isLongPressedName(name5, typed5) << endl;
  cout << isLongPressedName1(name1, typed1) << " "
       << isLongPressedName1(name2, typed2) << " "
       << isLongPressedName1(name3, typed3) << " "
       << isLongPressedName1(name4, typed4) << " "
       << isLongPressedName1(name5, typed5) << endl;
  return 0;
}