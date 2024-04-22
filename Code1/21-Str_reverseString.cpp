#include "head.h"
/* 344. 反转字符串
编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 s
的形式给出。
不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用 O(1)
的额外空间解决这一问题。
示例 1：
输入：s = ["h","e","l","l","o"]
输出：["o","l","l","e","h"]
示例 2：
输入：s = ["H","a","n","n","a","h"]
输出：["h","a","n","n","a","H"]*/

// 尽量不要使用Reverse，而是从头到中央一半，swap函数调换位置。注意任何一个只遍历一半的操作，下标可以使用i<size()/2
// 对于偶数，其正好是一半，对于奇数，其是小一半。
void reverseString(vector<char>& s) {
  // reverse(s.begin(), s.end());
  for (int i = 0; i < s.size() / 2; i++)
    swap(s[i], s[s.size() - 1 - i]);
}

// for循环内可以定义双变量，奇偶数都可以使用 size() / 2来判断。
// 可以直接reverse()库函数，利用栈，定义左右点swap。官方推荐for 循环内的swap方法
void reverseString1(vector<char>& s) {
  for (int i = 0, j = s.size() - 1; i < s.size() / 2; i++, j--)
    swap(s[i], s[j]);
}

int main() {
  vector<char> s = {'a', 'b', 'c', 'd', 'e'};
  reverseString(s);
  printVector(s);
  s = {'a', 'b', 'c', 'd', 'e'};
  reverseString1(s);
  printVector(s);
  return 0;
}