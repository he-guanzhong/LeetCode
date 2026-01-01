#include "head.h"
/* 15. 三数之和
给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]] 满足
i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。
请你返回所有和为 0 且不重复的三元组。
注意：答案中不可以包含重复的三元组。
示例 1：
  输入：nums = [-1,0,1,2,-1,-4]
  输出：[[-1,-1,2],[-1,0,1]]
  解释：
    nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
    nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
    nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
    不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
    注意，输出的顺序和三元组的顺序并不重要。
示例 2：
  输入：nums = [0,1,1]
  输出：[]
  解释：唯一可能的三元组和不为 0 。 */

vector<vector<int>> threeSum(vector<int>& nums) {
  vector<vector<int>> ans;
  sort(nums.begin(), nums.end());
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] > 0)
      break;
    if (i > 0 && nums[i] == nums[i - 1])
      continue;
    for (int j = i + 1, k = nums.size() - 1; j < k;) {
      int sum = nums[i] + nums[j] + nums[k];
      if (sum > 0)
        k--;
      else if (sum < 0)
        j++;
      else {
        ans.push_back({nums[i], nums[j], nums[k]});
        j++;
        k--;
        while (j < k && nums[j] == nums[j - 1])
          j++;
        while (j < k && nums[k] == nums[k + 1])
          k--;
      }
    }
  }
  return ans;
}

// 三数之和，一、不求下标，而求元素数值，故可以排序。二、要求不重复数组，故需要入result时去重。
// 优选双指针方法，先从小到大排序。剪支，若首元素小于0，则必不可能后序总和为0
// 步骤一、遍历确定起始点a，去重，注意要先处理该元素，如果于上一元素相等再跳过，不能预先判断该元素于下一元素相等就掉过
// 步骤二、设定b=a+1,c=nums.size()-1。三者求和，根据和大小，分别挪动b\c，如=0，先压入结果，再在b<c空间内去重，共同向中间收敛。
// 去重，核心在于先处理，再去重，因为组内允许相等元素出现。若先去重、在处理，相当于不允许组内相等元素
// 排序、剪支、遍历起始点、起始点与上一元素比较去重、设定左右指针窗口、计算窗口和，分情况挪动左右步、如相等先压入再去重
vector<vector<int>> threeSum1(vector<int>& nums) {
  vector<vector<int>> result;
  sort(nums.begin(), nums.end());
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] > 0)  // 排序后第一个元素大于0，必不可能
      break;
    if (i > 0 && nums[i] == nums[i - 1])  // a元素去重
      continue;

    unordered_set<int> set;
    for (int j = i + 1; j < nums.size(); j++) {
      if (j > i + 2 && nums[j] == nums[j - 1] && nums[j - 1] == nums[j - 2])
        continue;

      int c = 0 - nums[i] - nums[j];
      if (set.find(c) != set.end()) {
        result.push_back({nums[i], nums[j], c});
        set.erase(c);
      } else
        set.insert(nums[j]);
    }
  }
  return result;
}

// 双指针法，先排序，a作为i节点移动，bc设置为left和right
vector<vector<int>> threeSum2(vector<int>& nums) {
  vector<vector<int>> result;
  sort(nums.begin(), nums.end());
  for (int i = 0; i < nums.size(); i++) {
    if (nums[i] > 0)
      break;
    // 不能nums[i]==nums[i+1]否则会漏掉{-1，-1，2}，组内元素可以重复，故一定要先处理，如果遇到上一次相等的数再跳过
    if (i > 0 && nums[i] == nums[i - 1])
      continue;
    int left = i + 1;
    int right = nums.size() - 1;
    while (left < right) {
      if (nums[i] + nums[left] + nums[right] > 0)
        right--;
      else if (nums[i] + nums[left] + nums[right] < 0)
        left++;
      else {
        result.push_back({nums[i], nums[left], nums[right]});
        // push后去重，避免0，0，0情况。去重一定要加left<right条件，否则right=-1时，nums[-1]无法访问
        while (left < right && nums[left + 1] == nums[left])
          left++;
        while (left < right && nums[right - 1] == nums[right])
          right--;
        left++;
        right--;
      }
    }
  }
  return result;
}

int main() {
  vector<int> nums1 = {-1, 0, 1, 2, -1, -4};
  vector<int> nums2 = {-4, -1, -1, 0, 1, 2};
  vector<int> nums3 = {-2, 0, 0, 2, 2};
  printMat(threeSum(nums1));
  printMat(threeSum(nums2));
  printMat(threeSum(nums3));
  printMat(threeSum2(nums1));
  printMat(threeSum2(nums2));
  printMat(threeSum2(nums3));
  return 0;
}