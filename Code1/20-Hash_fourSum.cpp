#include "head.h"
/* 18. 四数之和
给你一个由 n 个整数组成的数组 nums ，和一个目标值 target
。请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c],
nums[d]] （若两个四元组元素一一对应，则认为两个四元组重复）：
    0 <= a, b, c, d < n
    a、b、c 和 d 互不相同
    nums[a] + nums[b] + nums[c] + nums[d] == target
你可以按 任意顺序 返回答案 。
示例 1：
  输入：nums = [1,0,-1,0,-2,2], target = 0
  输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
示例 2：
  输入：nums = [2,2,2,2,2], target = 8
  输出：[[2,2,2,2]] */

vector<vector<int>> fourSum(vector<int>& nums, int target) {
  vector<vector<int>> ans;
  sort(nums.begin(), nums.end());
  for (int i = 0; i < nums.size(); i++) {
    if (i > 0 && nums[i] == nums[i - 1])
      continue;
    for (int j = i + 1; j < nums.size(); j++) {
      if (j > i + 1 && nums[j] == nums[j - 1])
        continue;
      for (int a = j + 1, b = nums.size() - 1; a < b;) {
        long long sum = (long long)nums[i] + nums[j] + nums[a] + nums[b];
        if (sum > target)
          b--;
        else if (sum < target)
          a++;
        else {
          ans.push_back({nums[i], nums[j], nums[a], nums[b]});
          while (a < b && nums[a] == nums[a + 1])
            a++;
          while (a < b && nums[b] == nums[b - 1])
            b--;
          a++;
          b--;
        }
      }
    }
  }
  return ans;
}

// 排序、剪支、首字符与前比较去重、设定左右窗口，窗口求和分情况调整左右、等于0压入结果并在装口内去重
// 与三数之和问题相比，差异点有二：剪支考虑target正负。二、两个起始点a、b均要先处理、再去重，注意去重起始点要满足j>i+1
// 本体求和是target，剪支时不能单独判断nums[i]>target就break，因为target<0时，可以越加越小，如{-4,-3,-2,-1}目标为-10
// 因此，必须限定nums[i]>0的剪支条件，同理，对于起始点b的剪支，亦如此操作
// 简化为双指针问题，时间复杂度降级为 O(n) = n ^ 3
// 注意先排序，再剪枝处理，然后双指针迭代
vector<vector<int>> fourSum1(vector<int>& nums, int target) {
  vector<vector<int>> result;
  sort(nums.begin(), nums.end());
  for (int k = 0; k < nums.size(); k++) {
    if (nums[k] > target && nums[k] >= 0)  // 注意是不能变小，所以>=
      break;                               // 不必直接return，后续统一处理

    if (k > 0 && nums[k] == nums[k - 1])
      continue;  // 重复数剪枝处理

    for (int i = k + 1; i < nums.size(); i++) {
      if (nums[k] + nums[i] > target && nums[i] + nums[k] >= 0)
        break;
      if (i > k + 1 && nums[i] == nums[i - 1])
        continue;

      int left = i + 1, right = nums.size() - 1;
      while (left < right) {
        // 32位系统，int和long都4字节；64位系统，int4字节，long八字节，long
        // long永远八字节。相加会溢出
        if ((long)nums[k] + nums[i] + nums[left] + nums[right] < target)
          left++;
        else if ((long)nums[k] + nums[i] + nums[left] + nums[right] > target)
          right--;
        else {
          result.push_back({nums[k], nums[i], nums[left], nums[right]});
          while (left < right && nums[left + 1] == nums[left])
            left++;
          while (left < right && nums[right - 1] == nums[right])
            right--;
          left++;
          right--;
        }
      }
    }
  }
  return result;
}

int main() {
  vector<int> nums1 = {1, 0, -1, 0, -2, 2},
              nums2 = {0, 0, 0, 1000000000, 1000000000, 1000000000, 1000000000},
              nums3 = {2, 2, 2, 2, 2},
              nums4 = {-1000000000, -1000000000, -1000000000, -1000000000},
              nums5 = {-4, -3, -2, -1, 0, 0, 1, 2, 3, 4};

  int target1 = 0, target2 = 1000000000, target3 = 8, target4 = -1,
      target5 = -1;

  printMat(fourSum(nums1, target1));
  printMat(fourSum(nums2, target2));
  printMat(fourSum(nums3, target3));
  printMat(fourSum(nums4, target4));
  printMat(fourSum(nums5, target5));

  printMat(fourSum1(nums1, target1));
  printMat(fourSum1(nums2, target2));
  printMat(fourSum1(nums3, target3));
  printMat(fourSum1(nums4, target4));
  printMat(fourSum1(nums5, target5));

  return 0;
}