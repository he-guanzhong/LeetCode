#include "head.h"
/* 26. 删除有序数组中的重复项
给你一个 非严格递增排列 的数组 nums ，请你 原地 删除重复出现的元素，使每个元素
只出现一次 ，返回删除后数组的新长度。元素的 相对顺序 应该保持 一致 。然后返回
nums 中唯一元素的个数。
考虑 nums 的唯一元素的数量为 k ，你需要做以下事情确保你的题解可以被通过：
    更改数组 nums ，使 nums 的前 k 个元素包含唯一元素，并按照它们最初在 nums
中出现的顺序排列。nums 的其余元素与 nums 的大小不重要。 返回 k 。
判题标准:
系统会用下面的代码来测试你的题解:
int[] nums = [...]; // 输入数组
int[] expectedNums = [...]; // 长度正确的期望答案
int k = removeDuplicates(nums); // 调用
assert k == expectedNums.length;
for (int i = 0; i < k; i++) {
    assert nums[i] == expectedNums[i];
}
如果所有断言都通过，那么您的题解将被 通过。
示例 1：
  输入：nums = [1,1,2]
  输出：2, nums = [1,2,_]
  解释：函数应该返回新的长度 2 ，并且原数组 nums 的前两个元素被修改为 1, 2
    。不需要考虑数组中超出新长度后面的元素。
示例 2：
  输入：nums = [0,0,1,1,1,2,2,3,3,4]
  输出：5, nums = [0,1,2,3,4]
  解释：函数应该返回新的长度 5 ， 并且原数组 nums 的前五个元素被修改为 0, 1, 2,
3, 4 。不需要考虑数组中超出新长度后面的元素。 提示： 1 <= nums.length <= 3 * 104
    -104 <= nums[i] <= 104
    nums 已按 非严格递增 排列 */

int removeDuplicates(vector<int>& nums) {
  int j = 0;
  for (int i = 1; i < nums.size(); i++) {
    if (nums[i] != nums[j]) {
      nums[++j] = nums[i];
    }
  }
  return j + 1;
}

// 快慢指针，slow代表最后一个已赋值的位置，0位置必存在，已赋值。快指针fast从1开始。最终返回的数组长度是slow+1
// 非严格递增序列：数组从小到大排列，但允许元素重复
int removeDuplicates1(vector<int>& nums) {
  int slow = 0;
  for (int i = 1; i < nums.size(); i++) {
    if (nums[i] != nums[slow]) {
      nums[++slow] = nums[i];
    }
  }
  slow++;
  nums.resize(slow);
  return slow;
}

int* findPoints(int* nums, int numsSize, int* returnSize) {
  *returnSize = 15;
  int* ans = (int*)malloc(sizeof(int) * 15);
  float ratio = numsSize / 15.0f;
  for (int i = 0; i < 15; ++i) {
    int index = ratio * i;
    ans[i] = nums[index];
  }
  return ans;
}
int main() {
  /*   vector<int> nums1 = {1, 1, 2}, nums2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    cout << removeDuplicates(nums1) << " " << removeDuplicates(nums2) << endl;
    nums1 = {1, 1, 2}, nums2 = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    cout << removeDuplicates1(nums1) << " " << removeDuplicates1(nums2) << endl;
  */

  int nums1[20];
  for (int i = 0; i < 20; i++)
    nums1[i] = i + 1;
  int nums2[25];
  for (int i = 0; i < 25; i++)
    nums2[i] = i + 1;

  int returnSize = 15;
  int* ans1 = findPoints(nums1, 20, &returnSize);
  int* ans2 = findPoints(nums2, 25, &returnSize);

  for (int i = 0; i < returnSize; i++)
    cout << ans1[i] << ", " << endl;
  cout << endl;
  for (int i = 0; i < returnSize; i++)
    cout << ans2[i] << ", " << endl;
  cout << endl;
  return 0;
}