#include "head.h"
/* 剑指Offer58-II.左旋转字符串 / LCR 182. 动态口令
字符串的左旋转操作是把字符串前面的若干个字符转移到字符串的尾部。请定义一个函数实现字符串左旋转操作的功能。
比如，输入字符串"abcdefg"和数字2，该函数将返回左旋转两位得到的结果"cdefgab"。
示例 1：
  输入: s = "abcdefg", k = 2
  输出: "cdefgab"
示例 2：
  输入: s = "lrloseumgh", k = 6
  输出: "umghlrlose"
限制：1 <= k < s.length <= 10000 */

string reverseLeftWords(string s, int k) {
  reverse(s.begin(), s.end());
  reverse(s.end() - k, s.end());
  reverse(s.begin(), s.end() - k);
  return s;
}

// 不使用额外空间，通过翻转。方法一、先全部反转，然后对倒数k的元素反转，对剩余0~k个元素反转
// 方法二、先反转前k个元素，再反转剩余k~size个元素。最后反转所有元素
// 划分k位置，先反转0~k,再反转k~end,最后全部反转，即为左旋转
// 不要使用额外空间, 即不要使用substr
string reverseLeftWords1(string s, int k) {
  reverse(s.begin(), s.begin() + k);
  reverse(s.begin() + k, s.end());
  reverse(s.begin(), s.end());
  return s;
}

int main() {
  string s1 = "abcdefg", s2 = "lrloseumgh";
  int k1 = 2, k2 = 6;
  cout << reverseLeftWords(s1, k1) << " " << reverseLeftWords(s2, k2) << endl;
  s1 = "abcdefg", s2 = "lrloseumgh";
  cout << reverseLeftWords1(s1, k1) << " " << reverseLeftWords1(s2, k2) << endl;
  return 0;
}