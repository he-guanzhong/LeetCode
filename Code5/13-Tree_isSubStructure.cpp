#include "head.h"
#define null -1
/* LCR 143. 子结构判断
给定两棵二叉树 tree1 和 tree2，判断 tree2 是否以 tree1 的某个节点为根的子树具有
相同的结构和节点值 。 注意，空树 不会是以 tree1 的某个节点为根的子树具有
相同的结构和节点值 。
示例 1：
输入：tree1 = [1,7,5], tree2 = [6,1]
输出：false
解释：tree2 与 tree1 的一个子树没有相同的结构和节点值。
示例 2：
输入：tree1 = [3,6,7,1,8], tree2 = [6,1]
输出：true
解释：tree2 与 tree1 的一个子树拥有相同的结构和节点值。即 6 - > 1。  */

// 是否子结构，需要两个函数，一是A前序遍历左、右孩子，B不动，二是专门函数recur，判断该点A起始，B是否是其子结构。
// 函数recur。B无，无论A是否有，必为真。B有A无，或者二者不相等，则必为假。其余情况，则A、B值已相等，则要递归判断其各自的左、右孩子。
// 本体。先排除题目特殊说明的，A、B任意为空，则返回假的特殊情况。其次看当前A\B是否满足关系，或递归左右孩子.
bool recur(TreeNode* A, TreeNode* B) {
  if (!B)
    return true;
  else if (!A || A->val != B->val)
    return false;
  else
    return recur(A->left, B->left) && recur(A->right, B->right);
}
bool isSubStructure(TreeNode* A, TreeNode* B) {
  if (!A || !B)
    return false;
  return recur(A, B) || isSubStructure(A->left, B) ||
         isSubStructure(A->right, B);
}

int main() {
  TreeNode* A1 = construct_binary_tree({1, 7, 5});
  TreeNode* B1 = construct_binary_tree({6, 1});
  cout << isSubStructure(A1, B1) << endl;
  TreeNode* A2 = construct_binary_tree({3, 6, 7, 1, 8});
  TreeNode* B2 = A2->left;
  cout << isSubStructure(A2, B2) << endl;
  return 0;
}