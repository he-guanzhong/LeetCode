#include "head.h"
/* LCR 180. 文件组合
待传输文件被切分成多个部分，按照原排列顺序，每部分文件编号均为一个
正整数（至少含有两个文件）。传输要求为：连续文件编号总和为接收方指定数字 target
的所有文件。请返回所有符合该要求的文件传输组合列表。
注意，返回时需遵循以下规则：
    每种组合按照文件编号 升序 排列；
    不同组合按照第一个文件编号 升序 排列。
示例 1：
  输入：target = 12
  输出：[[3, 4, 5]]
  解释：在上述示例中，存在一个连续正整数序列的和为 12，为 [3, 4, 5]。
示例 2：
  输入：target = 18
  输出：[[3,4,5,6],[5,6,7]]
  解释：在上述示例中，存在两个连续正整数序列的和分别为 18，分别为 [3, 4, 5, 6]
和 [5, 6, 7]。 */

vector<vector<int>> fileCombination(int target) {
  vector<vector<int>> ans;
  deque<int> path;
  int sum = 0;
  int j = 1;
  for (int i = 1; i < target / 2 + 1; i++) {
    sum += i;
    path.push_back(i);
    while (sum >= target) {
      if (sum == target)
        ans.push_back(vector<int>(path.begin(), path.end()));
      path.pop_front();
      sum -= j;
      j++;
    }
  }
  return ans;
}

// 数学法，求和公式，已知[i,j]范围内和为平均数*项数。target=(i+j)/2*(j-i+1)/2，故已知起点i和总和target，可以根据一元二次方程求根公式反推右边界j。
// 注意，i*i可能会超过int上线，要用long，如果右界j是整数，且i<j，即满足最小两个元素。即将[i,j]内所有元素，作为一组解，压入最终结果。时间复杂度O(n)。
// 整数判断方法，一般使用fracPart=modf(j,&intPart)，判断fracPart==0.0的方式来进行。j==(int)j只有在直接赋值和精确计算的前提下，才可以使用。
vector<vector<int>> fileCombination2(int target) {
  vector<vector<int>> ans;
  int i = 1;
  double j = 2.0;
  while (i < j) {  // 不是小于target
    j = (-1 + sqrt(1 + 4 * ((long)i * i - i + 2 * target))) / 2;
    if (j > i && j == (int)j) {
      vector<int> path;
      for (int k = i; k <= (int)j; k++)
        path.push_back(k);
      ans.push_back(path);
    }
    i++;
  }
  return ans;
}

// 优选滑动窗口。初始化窗口左右边界为[1,2]其总和为3。保证i<j循环，即维持了窗口内至少有两个元素。每一轮先验sum是否等于target，如果是就收集结果
// 另外，当sum>=target，窗口左边界要右移，使窗口内sum变小。先减i，再移动。若sum<target，窗口右边界右移，使窗口sum变大。先移动j，再加j。注意次序
vector<vector<int>> fileCombination1(int target) {
  vector<vector<int>> ans;
  int sum = 3, i = 1, j = 2;
  while (i < j) {
    if (sum == target) {
      vector<int> path;
      for (int k = i; k <= j; k++)
        path.push_back(k);
      ans.push_back(path);
    }
    if (sum >= target) {
      sum -= i;
      i++;
    } else {
      j++;
      sum += j;
    }
  }
  return ans;
}

int main() {
  printMat(fileCombination(10));
  printMat(fileCombination(12));
  printMat(fileCombination(18));
  printMat(fileCombination(9));
  printMat(fileCombination(50252));
  printMat(fileCombination(10));
  printMat(fileCombination1(12));
  printMat(fileCombination1(18));
  printMat(fileCombination1(9));
  printMat(fileCombination1(50252));
  return 0;
}