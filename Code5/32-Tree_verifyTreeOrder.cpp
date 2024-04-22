#include "head.h"
/* LCR 152. 验证二叉搜索树的后序遍历序列
请实现一个函数来判断整数数组 postorder 是否为二叉搜索树的后序遍历结果。
示例 1：
输入: postorder = [4,9,6,5,8]
输出: false
解释：从上图可以看出这不是一颗二叉搜索树
示例 2：
输入: postorder = [4,6,5,9,8]
输出: true
解释：可构建的二叉搜索树如上图
提示：
    数组长度 <= 1000
    postorder 中无重复数字 */

// 后序遍历，最后一个结点为根节点。从前到后，找第一个大于根节点的位置m，依次为准切割为[0,m-1]和[m,r-1]两段
// 考虑后段(m, r)中的每个元素，均应大于根节点r，否则就返回错误。分治递归
bool verify(vector<int>& postorder, int l, int r) {
  if (l >= r)
    return true;
  int index = l;
  while (postorder[index] < postorder[r])
    index++;
  for (int i = r - 1; i > index; i--) {
    if (postorder[i] < postorder[r])
      return false;
  }
  return verify(postorder, l, index - 1) && verify(postorder, index, r - 1);
}
bool verifyTreeOrder(vector<int>& postorder) {
  return verify(postorder, 0, postorder.size() - 1);
}

int main() {
  vector<int> postorder1 = {4, 9, 6, 5, 8}, postorder2 = {4, 6, 5, 9, 8};
  cout << verifyTreeOrder(postorder1) << " " << verifyTreeOrder(postorder2)
       << " " << endl;
  float n1 = -2.001f, n2 = -2.01, n3 = -1.99999f;
  float m1 = (int)(n1 / 0.01f) * 0.01f;
  float m2 = (int)(n2 / 0.01f) * 0.01f;
  float m3 = (int)(n3 / 0.01f) * 0.01f;
  printf("m1 = %f, m2 = %f, m3 = %f\n", m1, m2, m3);
  return 0;
}