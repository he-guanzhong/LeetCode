#include "head.h"
#define null -1
/* 968. 监控二叉树
给定一个二叉树，我们在树的节点上安装摄像头。
节点上的每个摄影头都可以监视其父对象、自身及其直接子对象。
计算监控树的所有节点所需的最小摄像头数量。
示例 1：
输入：[0,0,null,0,0]
输出：1
解释：如图所示，一台摄像头足以监控所有节点
示例 2：
输入：[0,0,null,0,null,0,null,null,0]
输出：2
解释：需要至少两个摄像头来监视树的所有节点。
上图显示了摄像头放置的有效位置之一。*/

// 后序遍历递归，回溯。摄像头数量额外设置传参，返回值表述前结点状态。0-未覆盖，1-摄像头，2-覆盖。空结点必为2-覆盖
// 提取左右结点递归返回值状态。情况一，左右均覆盖，返回未覆盖；情况二、左右任一没覆盖，返回摄像头，数量加1。情况三、左右任一摄像头，返回覆盖。
// 根节状态未处理，如果为未覆盖，则摄像头数+1.
int traversal(TreeNode* root, int& result) {
  if (!root)
    return 2;
  int left = traversal(root->left, result);
  int right = traversal(root->right, result);
  if (left == 2 && right == 2)
    return 0;
  else if (left == 0 || right == 0) {
    result++;
    return 1;
  } else if (left == 1 || right == 1)
    return 2;
  return -1;
}
int minCameraCover(TreeNode* root) {
  int result = 0;
  if (traversal(root, result) == 0)
    result++;
  return result;
}

// 核心是从叶子节点的父节点开始布置摄像头，由下至上回溯，后序遍历。返回值设置为状态，0为无覆盖。1为摄像头，2为有覆盖
// 返回条件是遇到空结点，只能认为其有覆盖2。提取左右返回状态。
// 情况一，左右均有覆盖，返回无覆盖。情况二，左右任何出现无覆盖，均布置摄像头。情况三，左右任何出现摄像头，返回有覆盖
// 时间复杂度: O(n)，空间复杂度: O(n)
int result1;
int traversal1(TreeNode* cur) {
  if (!cur)
    return 2;
  int left = traversal1(cur->left);
  int right = traversal1(cur->right);
  if (left == 2 && right == 2)  // 叶子结点一般状态
    return 0;
  if (left == 0 || right == 0) {  // 叶子结点父节点
    result1++;
    return 1;
  }
  if (left == 1 || right == 1)  // 叶子结点爷结点
    return 2;
  return -1;  // 此处不会出现
}
int minCameraCover1(TreeNode* root) {
  result1 = 0;
  if (traversal1(root) == 0)  // 最后根节点未覆盖，结果加一
    result1++;
  return result1;
}
// 不可以使用层序遍历，分别统计单双层结点数量的办法。

int main() {
  TreeNode* t1 = construct_binary_tree({0, 0, null, 0, 0});
  TreeNode* t2 = construct_binary_tree({0, 0, null, 0, null, 0, null, null, 0});
  TreeNode* t3 = construct_binary_tree({0});
  TreeNode* t4 =
      construct_binary_tree({0, 0, null, null, 0, 0, null, null, 0, 0});
  cout << minCameraCover(t1) << " " << minCameraCover(t2) << " "
       << minCameraCover(t3) << " " << minCameraCover(t4) << endl;
  cout << minCameraCover1(t1) << " " << minCameraCover1(t2) << " "
       << minCameraCover1(t3) << " " << minCameraCover1(t4) << endl;
  return 0;
}