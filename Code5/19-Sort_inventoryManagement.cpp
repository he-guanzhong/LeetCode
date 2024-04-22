#include "head.h"
/* LCR 159. 库存管理 III
仓库管理员以数组 stock 形式记录商品库存表，其中 stock[i]
表示对应商品库存余量。请返回库存余量最少的 cnt 个商品余量，返回 顺序不限。
示例 1：
输入：stock = [2,5,7,4], cnt = 1
输出：[2]
示例 2：
输入：stock = [0,2,3,6], cnt = 2
输出：[0,2] 或 [2,0] */

void quickSort(vector<int>& stock, int cnt, int l, int r) {
  if (l >= r)
    return;
  int i = l, j = r;
  while (i < j) {
    while (i < j && stock[j] >= stock[l])
      j--;
    while (i < j && stock[i] <= stock[l])
      i++;
    swap(stock[i], stock[j]);
  }
  swap(stock[l], stock[i]);
  if (i < cnt)
    quickSort(stock, cnt, i + 1, r);
  else if (i > cnt)
    quickSort(stock, cnt, l, i - 1);
}
vector<int> inventoryManagement(vector<int>& stock, int cnt) {
  quickSort(stock, cnt, 0, stock.size() - 1);
  vector<int> ans(stock.begin(), stock.begin() + cnt);
  return ans;
}

// 考察手写快排。首位哨兵+分治。退出条件是只有一个元素。首元素作为哨兵，从左至右，选第一个大于首元素的，从右至左，选第一个小于首元素的。二者交换
// 退出时，i停在肯定比首元素大的位置。
// 注意，快速排序，一定要先从右侧开始j--
void quickSort1(vector<int>& stock, int l, int r) {
  if (l >= r)
    return;
  int i = l, j = r;
  while (i < j) {
    while (i < j && stock[j] >= stock[l])  // 一定要先从右
      j--;
    while (i < j && stock[i] <= stock[l])
      i++;
    swap(stock[i], stock[j]);
  }
  swap(stock[i], stock[l]);
  quickSort1(stock, l, i - 1);
  quickSort1(stock, i + 1, r);
}
vector<int> inventoryManagement1(vector<int>& stock, int cnt) {
  quickSort1(stock, 0, stock.size() - 1);
  vector<int> ans(stock.begin(), stock.begin() + cnt);
  return ans;
}

// 快速选择。引入cnt,若标志位i>cnt说明，前cnt个数在左区间递归。i<cnt说明前cnt个数在右区间递归
// 时间复杂度为O(n)=N+0.5N+0.25N+0.125N，等比数列求和公式。为2N-1。空间复杂度O(n)=logN
void quickSort2(vector<int>& stock, int cnt, int l, int r) {
  if (l >= r)
    return;
  int i = l, j = r;
  while (i < j) {
    while (i < j && stock[j] >= stock[l])  // 一定要先从右
      j--;
    while (i < j && stock[i] <= stock[l])
      i++;
    swap(stock[i], stock[j]);
  }
  swap(stock[i], stock[l]);
  if (i > cnt)
    quickSort2(stock, cnt, l, i - 1);
  else if (i < cnt)
    quickSort2(stock, cnt, i + 1, r);
}
vector<int> inventoryManagement2(vector<int>& stock, int cnt) {
  quickSort2(stock, cnt, 0, stock.size() - 1);
  vector<int> ans(stock.begin(), stock.begin() + cnt);
  return ans;
}
int main() {
  vector<int> stock1 = {2, 5, 7, 4}, stock2 = {0, 2, 3, 6};
  printVector(inventoryManagement(stock1, 1));
  printVector(inventoryManagement(stock2, 2));
  stock1 = {2, 5, 7, 4}, stock2 = {0, 2, 3, 6};
  printVector(inventoryManagement2(stock1, 1));
  printVector(inventoryManagement2(stock2, 2));
  return 0;
}