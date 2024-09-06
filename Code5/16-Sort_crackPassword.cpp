#include "head.h"
/* LCR 164. 破解闯关密码
闯关游戏需要破解一组密码，闯关组给出的有关密码的线索是：
    一个拥有密码所有元素的非负整数数组 password
    密码是 password 中所有元素拼接后得到的最小的一个数
请编写一个程序返回这个密码。
示例 1:
  输入: password = [15, 8, 7]
  输出: "1578"
示例 2:
  输入: password = [0, 3, 30, 34, 5, 9]
  输出: "03033459" */

string crackPassword(vector<int>& password) {
  vector<string> vec(password.size());
  for (int i = 0; i < password.size(); i++) {
    vec[i] = to_string(password[i]);
  }
  sort(vec.begin(), vec.end(),
       [](const string& a, const string& b) { return a + b < b + a; });
  string ans;
  for (int i = 0; i < vec.size(); i++)
    ans += vec[i];
  return ans;
}

// 先将所有int转化为string，然后在新容器中排序。注意字符串可以比较大小，x+y<y+x说明，x的顺序要低于y，应该置前。最后将全部转化为结果
string crackPassword1(vector<int>& password) {
  vector<string> tmp(password.size());
  for (int i = 0; i < password.size(); i++)
    tmp[i] = to_string(password[i]);
  sort(tmp.begin(), tmp.end(),
       [](string& a, string& b) { return a + b < b + a; });
  string ans;
  for (string str : tmp)
    ans += str;
  return ans;
}

int main() {
  vector<int> password1 = {15, 8, 7}, password2 = {0, 3, 30, 34, 5, 9};
  cout << crackPassword(password1) << " " << crackPassword(password2) << endl;
  cout << crackPassword1(password1) << " " << crackPassword1(password2) << endl;

  return 0;
}