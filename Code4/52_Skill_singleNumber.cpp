#include "head.h"
/* 136. 只出现一次的数字
给你一个 非空 整数数组 nums
，除了某个元素只出现一次以外，其余每个元素均出现两次。找出那个只出现了一次的元素。
你必须设计并实现线性时间复杂度的算法来解决此问题，且该算法只使用常量额外空间。
示例 1 ：
输入：nums = [2,2,1]
输出：1
示例 2 ：
输入：nums = [4,1,2,1,2]
输出：4
示例 3 ：
输入：nums = [1]
输出：1  */

int singleNumber(vector<int>& nums) {
  int ans = 0;
  for (int i : nums)
    ans ^= i;
  return ans;
}

// 异或运算^，对比每一位，相等则为0，不等则为1。三条性质，1.任何一个数和0异或，结果是原数。2.数和自身异或，结果是0。3.异或满足交换律。
// 因此，2m+1个数同时异或，根据交换律，将所有出现两次的数合并为0，即为m个0和最终只出现一次的数n，最终返回n
int singleNumber1(vector<int>& nums) {
  int ans = 0;
  for (int num : nums)
    ans ^= num;
  return ans;
}

// 异或运算还可以用来交换两个数大小
template <class T>
void mySwap(T& a, T& b) {
  a ^= b;
  b ^= a;
  a ^= b;
}

int main() {
  vector<int> nums1 = {2, 2, 1}, nums2 = {4, 1, 2, 1, 2}, nums3 = {1};
  cout << singleNumber(nums1) << " " << singleNumber(nums2) << " "
       << singleNumber(nums3) << endl;
  nums1 = {2, 2, 1}, nums2 = {4, 1, 2, 1, 2}, nums3 = {1};
  cout << singleNumber1(nums1) << " " << singleNumber1(nums2) << " "
       << singleNumber1(nums3) << endl;
  return 0;
}