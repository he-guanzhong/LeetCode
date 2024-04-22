#include "head.h"
/* LCR 178. 训练计划 VI
教学过程中，教练示范一次，学员跟做三次。该过程被混乱剪辑后，记录于数组
actions，其中 actions[i] 表示做出该动作的人员编号。请返回教练的编号。
示例 1：
输入：actions = [5, 7, 5, 5]
输出：7
示例 2：
输入：actions = [12, 1, 6, 12, 6, 12, 6]
输出：1 */

int trainingPlan(vector<int>& actions) {
  int one = 0, two = 0;
  for (int action : actions) {
    one = one ^ action & ~two;
    two = two ^ action & ~one;
  }
  return one;
}

// 方法一。不易理解。先回顾位运算性质，异或x^0=x,x^1=~x。与x&1=x,x&0=0。
// 由此，统计所有数字某位上1出现次数，如果能被3整除（余数0），说明结果的该位为0，如不能被3整除，说明结果该位为1
// 余数只能为0、1、2，且该题目中不可能为2。设置两位数状态机two/one，三个状态为00->01->10，只要输入的n为1，就不断状态改变
// two为0时，n==1时，one分别0->1,1->0；n==0时0->0,1->1。适配异或one^n。
// two为1时，one必为0。适配two取反后的与操作，~two&one。二者结合one=one^n&~two。
// two位置上的操作，与one同理。最后one代表了的数，其所有位置上余数为1。返回one即可
int trainingPlan1(vector<int>& actions) {
  int one = 0, two = 0;
  for (int action : actions) {
    one = one ^ action & ~two;
    two = two ^ action & ~one;
  }
  return one;
}

// 方法二，易于理解。uint32整形分位统计数量，从低到高分别是0-31位。注意求的是num二进制下每一位是否是1，故使用&1。不是十进制下每位数字，不得使用%10
// 第二次遍历，先初始化返回值为0，从高到低统计cnt。每轮中，先对ans左移1位，再用按位与|，操作每一位余数%3。
// 由于数字出现次数只有1或3两种。所以每位余3后，只可能是4->1,3->0,1->0。得到的结果就是数字
int trainingPlan2(vector<int>& actions) {
  int cnt[32] = {0};
  for (int& num : actions) {
    for (int i = 0; i < 32; i++) {
      cnt[i] += num & 1;
      num >>= 1;
    }
  }
  int ans = 0;
  for (int i = 31; i >= 0; i--) {
    ans <<= 1;
    ans |= cnt[i] % 3;
  }
  return ans;
}

int main() {
  vector<int> actions1 = {5, 7, 5, 5}, actions2 = {12, 1, 6, 12, 6, 12, 6};
  cout << trainingPlan(actions1) << " " << trainingPlan(actions2) << endl;
  cout << trainingPlan1(actions1) << " " << trainingPlan1(actions2) << endl;

  return 0;
}