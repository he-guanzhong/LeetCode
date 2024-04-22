#include "head.h"
#define null -1
/* 98. 验证二叉搜索树
给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
有效 二叉搜索树定义如下：
    节点的左子树只包含 小于 当前节点的数。
    节点的右子树只包含 大于 当前节点的数。
    所有左子树和右子树自身必须也是二叉搜索树。
*/

// 二叉搜索树核心性质：中序遍历后，相邻两个结点严格递增的，不得相等。递归法一、可以使用vector作为中序遍历结果。
// 递归法二、中序遍历时就比较该结点值与上一结点值。注意上一结点值要保存为8字节的longlong，因为测试用例中有4字节的最小值
// 迭代法，简化的中序遍历。设置当前、上一双指针，不必提前压入栈。循环中，cur存在就压入，并左移。cur不存在就去栈首，处理后，cur右移

bool isValidBST(TreeNode* root) {
  stack<TreeNode*> stk;
  TreeNode* cur = root;
  TreeNode* pre = nullptr;
  while (!stk.empty() || cur) {
    if (cur) {
      stk.push(cur);
      cur = cur->left;
    } else {
      cur = stk.top();
      stk.pop();
      if (pre && cur->val <= pre->val)
        return false;
      pre = cur;
      cur = cur->right;
    }
  }
  return true;
}

// 注意两个陷阱，一，不能单纯判断左节点小于本结点、右节点大于本结点，因为不能比较孙结点和本结点的大小问题
// 二、结点的值为MIN_INT，注意如何比较。可以使用LONG_MIN，或者记录前一结点的值
// 二叉搜索树中序遍历后，为递增数列，且相邻两数不能相等
void traversal1(TreeNode* root, vector<int>& vec) {
  if (!root)
    return;
  traversal1(root->left, vec);
  vec.push_back(root->val);
  traversal1(root->right, vec);
  return;
}
bool isValidBST1(TreeNode* root) {
  vector<int> vec;
  traversal1(root, vec);
  for (int i = 1; i < vec.size(); i++) {
    if (vec[i] <= vec[i - 1])  // 相等也不行
      return false;
  }
  return true;
}

long long maxValue =
    LONG_LONG_MIN;  // 注意，此处不能写为INT_MIN，否则只有一个结点INT_MIN不会判为真
bool isValidBST2(TreeNode* root) {
  if (!root)
    return true;
  bool left = isValidBST2(root->left);
  if (maxValue < root->val)
    maxValue = root->val;
  else
    return false;
  bool right = isValidBST2(root->right);
  return left && right;
}

// 额外用一个指针记录前一个结点的值，如此不用判断
TreeNode* pre = nullptr;
bool isValidBST3(TreeNode* root) {
  if (!root)
    return true;
  bool left = isValidBST3(root->left);
  if (pre && pre->val >= root->val)
    return false;
  pre = root;
  bool right = isValidBST3(root->right);
  return left && right;
}

// 迭代法模拟中序遍历，迭代法中序遍历与普通不同，设定当前要处理的坐标结点。
// 退出条件为，栈空或者当前结点为空。若当前结点不空，则入栈，然后移动结点坐标。当前结点空，则取头位处理，并坐标右移
bool isValidBST4(TreeNode* root) {
  stack<TreeNode*> st;  // 无需判断头节点
  TreeNode* cur = root;
  TreeNode* pre = nullptr;
  while (!st.empty() || cur) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      if (pre && pre->val >= cur->val)
        return false;
      pre = cur;
      cur = cur->right;
    }
  }
  return true;
}

int main() {
  vector<int> vec1 = {2, 1, 3};
  vector<int> vec2 = {5, 1, 4, null, null, 3, 6};
  vector<int> vec3 = {10, 5, 15, null, null, 6, 20};
  vector<int> vec4 = {-2147483648};

  TreeNode* node1 = construct_binary_tree(vec1);
  TreeNode* node2 = construct_binary_tree(vec2);
  TreeNode* node3 = construct_binary_tree(vec3);
  TreeNode* node4 = construct_binary_tree(vec4);
  cout << isValidBST(node1) << " " << isValidBST(node2) << " "
       << isValidBST(node3) << " " << isValidBST(node4) << endl;
  cout << isValidBST1(node1) << " " << isValidBST1(node2) << " "
       << isValidBST1(node3) << " " << isValidBST1(node4) << endl;
  return 0;
}
