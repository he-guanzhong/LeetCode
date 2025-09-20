#include "head.h"

/* 873. 最长的斐波那契子序列的长度
如果序列 X_1, X_2, ..., X_n 满足下列条件，就说它是 斐波那契式 的：
n >= 3
对于所有 i + 2 <= n，都有 X_i + X_{i+1} = X_{i+2}
给定一个严格递增的正整数数组形成序列 arr ，找到 arr
中最长的斐波那契式的子序列的长度。如果一个不存在，返回  0 。
（回想一下，子序列是从原序列 arr 中派生出来的，它从 arr
中删掉任意数量的元素（也可以不删），而不改变其余元素的顺序。例如， [3, 5, 8] 是
[3, 4, 5, 6, 7, 8] 的一个子序列）
示例 1：
  输入: arr = [1,2,3,4,5,6,7,8]
  输出: 5
  解释: 最长的斐波那契式子序列为 [1,2,3,5,8] 。
示例 2：
  输入: arr = [1,3,7,11,12,14,18]
  输出: 3
  解释: 最长的斐波那契式子序列有 [1,11,12]、[3,11,14] 以及 [7,11,18] 。
提示：
  3 <= arr.length <= 1000
  1 <= arr[i] < arr[i + 1] <= 10^9 */

int lenLongestFibSubseq(vector<int>& arr) {
  int n = arr.size();
  int ans = 0;
  vector<vector<int>> dp(n, vector<int>(n, 2));
  for (int i = 2; i < n; i++) {
    for (int j = 0, k = i - 1; j < k;) {
      if (arr[j] + arr[k] == arr[i]) {
        dp[k][i] = max(dp[k][i], dp[j][k] + 1);
        ans = max(ans, dp[k][i]);
        j++, k--;
      } else if (arr[j] + arr[k] < arr[i])
        j++;
      else
        k--;
    }
  }
  return ans == 2 ? 0 : ans;
}

// 动态规划+双指针。斐波那契数列特征是，至少三个元素。下标j<k<i，起值arr[j]+arr[k]==arr[i]
// dp[k][i]含义是，以arr[k]和arr[i]为末尾两个元素的数列长度。因此，第一轮遍历[0,i]范围内
// 双指针(j,k)切割这个区间，若发现符合斐波那契列特征，则需要更新最大长度，在原dp[k][i]和dp[j][k]+1中取大
// 鉴于最长斐波那契列不一定是以整个数列末尾元素为结束，故要单独设置答案变量并随时更新
// dp[][]数组可全部初始化为2，省去判断首次成数列时，初始化长度为3的特殊处理。但在返回答案不能为2的特殊情况
int lenLongestFibSubseq1(vector<int>& arr) {
  int ans = 0;
  vector<vector<int>> dp(arr.size(), vector<int>(arr.size(), 2));
  for (int i = 2; i < arr.size(); i++) {
    for (int j = 0, k = i - 1; j < k;) {
      if (arr[j] + arr[k] == arr[i]) {
        dp[k][i] = max(dp[k][i], dp[j][k] + 1);
        ans = max(ans, dp[k][i]);
        j++, k--;
      } else if (arr[j] + arr[k] < arr[i]) {
        j++;
      } else {
        k--;
      }
    }
  }
  return ans == 2 ? 0 : ans;
}

// 哈希表做法。利用哈希表记录每个元素值及其下标。若能在[0,j]中找到下标k，其值tmp可以满足数列和关系，即成立
int lenLongestFibSubseq2(vector<int>& arr) {
  unordered_map<int, int> umap;
  int n = arr.size();
  for (int i = 0; i < n; i++) {
    umap[arr[i]] = i;
  }
  vector<vector<int>> dp(n, vector<int>(n, 2));
  int ans = 0;
  for (int i = 2; i < n; i++) {
    for (int j = 1; j < i; j++) {
      int tmp = arr[i] - arr[j];
      if (umap.count(tmp) && umap[tmp] < j) {
        dp[j][i] = max(dp[j][i], dp[umap[tmp]][j] + 1);
        ans = max(ans, dp[j][i]);
      }
    }
  }
  return ans;
}

int main() {
  vector<int> arr1 = {1, 2, 3, 4, 5, 6, 7, 8}, arr2 = {1, 3, 7, 11, 12, 14, 18},
              arr3{2, 4, 7, 8, 9, 10, 14, 15, 18, 23, 32, 50};
  cout << lenLongestFibSubseq(arr1) << " " << lenLongestFibSubseq(arr2) << " "
       << lenLongestFibSubseq(arr3) << endl;
  cout << lenLongestFibSubseq1(arr1) << " " << lenLongestFibSubseq1(arr2) << " "
       << lenLongestFibSubseq1(arr3) << endl;
  return 0;
}