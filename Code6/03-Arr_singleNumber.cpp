#include "head.h"
/* LCR 004. 只出现一次的数字 II
给你一个整数数组 nums ，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次
。请你找出并返回那个只出现了一次的元素。
你必须设计并实现线性时间复杂度的算法且使用常数级空间来解决此问题。
示例 1：
  输入：nums = [2,2,3,2]
  输出：3
示例 2：
  输入：nums = [0,1,0,1,0,1,99]
  输出：99
提示：
  1 <= nums.length <= 3 * 10^4
  -2^31 <= nums[i] <= 2^31 - 1
  nums 中，除某个元素仅出现 一次 外，其余每个元素都恰出现 三次 */

int singleNumber(vector<int>& nums) {
  int ans = 0;
  for (int i = 0; i < 32; i++) {
    int index = (1 << i);
    int cnt = 0;
    for (int& num : nums) {
      cnt += ((num & index) != 0);
    }
    cnt %= 3;
    ans |= (cnt << i);
  }
  return ans;
}

// 依次确定每一个二进制位。注意index实质为2的备注，按位与时得到的结果不是1，不能直接用于计数
// 由于题目中含有负数，故一定要统计全32位。另外，符号优先级，比较大于按位与，因此所有按位运算，一定要加括号，再比较
int singleNumber1(vector<int>& nums) {
  int ans = 0;
  for (int i = 0; i < 32; i++) {
    int index = (1 << i);
    int cnt = 0;
    for (const int& num : nums) {
      cnt += (num & index ? 1 : 0);
    }
    cnt %= 3;
    ans |= (cnt ? index : 0);
  }
  return ans;
}

// 状态机方法，需死记硬背。异或数与反它位。
// 00 - 01 - 10
// one: two为0时，允许异或累加0->1。two为1时，不允许异或累加0->0
// two: one为0时，允许异或累加1->0，one为1时，不允许异或累加
int singleNumber2(vector<int>& nums) {
  int one = 0, two = 0;
  for (const int& num : nums) {
    one ^= num & ~two;
    two ^= num & ~one;
  }
  return one;
}

int main() {
  vector<int> nums1({2, 2, 3, 2}), nums2({0, 1, 0, 1, 0, 1, 99}),
      nums3({-2, -2, 1, 1, 4, 1, 4, 4, -4, -2});
  cout << singleNumber(nums1) << " " << singleNumber(nums2) << " "
       << singleNumber(nums3) << endl;
  cout << singleNumber2(nums1) << " " << singleNumber2(nums2) << " "
       << singleNumber2(nums3) << endl;
  return 0;
}