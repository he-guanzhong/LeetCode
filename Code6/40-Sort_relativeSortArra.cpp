#include "head.h"
/* 1122. 数组的相对排序
给你两个数组，arr1 和 arr2，arr2 中的元素各不相同，arr2 中的每个元素都出现在
arr1 中。
对 arr1 中的元素进行排序，使 arr1 中项的相对顺序和 arr2 中的相对顺序相同。未在
arr2 中出现过的元素需要按照升序放在 arr1 的末尾。
示例 1：
  输入：arr1 = [2,3,1,3,2,4,6,7,9,2,19], arr2 = [2,1,4,3,9,6]
  输出：[2,2,2,1,4,3,3,9,6,7,19]
示例  2:
  输入：arr1 = [28,6,22,8,44,17], arr2 = [22,28,8,6]
  输出：[22,28,8,6,17,44]
提示：
  1 <= arr1.length, arr2.length <= 1000
  0 <= arr1[i], arr2[i] <= 1000
  arr2 中的元素 arr2[i]  各不相同
  arr2 中的每个元素 arr2[i] 都出现在 arr1 中*/

// 自定义排序。利用arr2构造哈希表，键是元素，值为其下表，供对比使用。sort()函数中比较函数x,y为真时x在前，为假时y在前
// 若x、y均存在，则对比其下标。若x、y仅一方存在，则返回存在的一方靠前，若都不存在，则直接比较其值
vector<int> relativeSortArray1(vector<int>& arr1, vector<int>& arr2) {
  unordered_map<int, int> umap;
  for (int i = 0; i < arr2.size(); i++) umap[arr2[i]] = i;
  sort(arr1.begin(), arr1.end(), [&](int x, int y) {
    if (umap.count(x)) {
      return umap.count(y) ? umap[x] < umap[y] : true;
    } else {
      return umap.count(y) ? false : x < y;
    }
  });
  return arr1;
}

// 计数排序，鉴于arr1中最大数字才1000，设置每个数字出现的频率数组freq。遍历第一遍，得到该freq数组所需大小
// 二次遍历，统计所有arr1中元素出现次数。三次遍历，遍历arr2，对其中每个元素x，分别对答案压入freq[x]次
// 四次遍历，此时freq中仍有一些元素未清零，再次遍历，对所有元素压入
vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
  int upper = 0;
  for (int i = 0; i < arr1.size(); i++) upper = max(upper, arr1[i]);
  vector<int> freq(upper + 1, 0);
  for (int i = 0; i < arr1.size(); i++) freq[arr1[i]]++;
  vector<int> ans(arr1.size(), 0);
  int j = 0;
  for (int i = 0; i < arr2.size(); i++) {
    int x = arr2[i];
    while (freq[x]) {
      ans[j++] = x;
      freq[x]--;
    }
  }
  for (int i = 0; i < freq.size(); i++) {
    while (freq[i]) {
      ans[j++] = i;
      freq[i]--;
    }
  }
  return ans;
}

int main() {
  vector<int> vec1 = {2, 3, 1, 3, 2, 4, 6, 7, 9, 2, 19},
              vec2 = {2, 1, 4, 3, 9, 6}, vec3 = {28, 6, 22, 8, 44, 17},
              vec4 = {22, 28, 8, 6};
  printVector(relativeSortArray(vec1, vec2));
  printVector(relativeSortArray(vec3, vec4));
  return 0;
}