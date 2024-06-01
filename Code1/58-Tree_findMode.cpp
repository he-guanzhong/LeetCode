#include "head.h"
/* 501. 二叉搜索树中的众数
给你一个含重复值的二叉搜索树（BST）的根节点 root ，找出并返回 BST 中的所有
众数（即，出现频率最高的元素）。
如果树中有不止一个众数，可以按 任意顺序 返回。
假定 BST 满足如下定义：
    结点左子树中所含节点的值 小于等于 当前节点的值
    结点右子树中所含节点的值 大于等于 当前节点的值
    左子树和右子树都是二叉搜索树
示例 1：
输入：root = [1,null,2,2]
输出：[2]
示例 2：
输入：root = [0]
输出：[0]
进阶：你可以不使用额外的空间吗？（假设由递归产生的隐式调用栈的开销不被计算在内）*/

vector<int> findMode(TreeNode* root) {
  vector<int> ans;
  int maxFrq = 0, frq = 0;
  TreeNode* cur = root;
  TreeNode* pre = nullptr;
  stack<TreeNode*> st;
  while (cur || !st.empty()) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();
      if (pre && pre->val == cur->val)
        frq++;
      else
        frq = 1;
      if (frq > maxFrq) {
        ans.clear();
        ans.push_back(cur->val);
        maxFrq = frq;
      } else if (frq == maxFrq)
        ans.push_back(cur->val);
      pre = cur;
      cur = cur->right;
    }
  }
  return ans;
}

// 递归法，记录前一结点数据、计数、最大计数三个量。设置统计计数，如果与前一相等就加1，不等就为1。
// 对计数，如果等于最大计数。则压入，大于最大计数。清除vec，并压入。迭代法，模拟中序遍历
// 任意方法遍历都可以，不考虑二叉搜索树的特殊性质
void traversal1(TreeNode* root, unordered_map<int, int>& map) {
  if (!root)
    return;
  traversal1(root->left, map);
  map[root->val]++;
  traversal1(root->right, map);
}
vector<int> findMode1(TreeNode* root) {
  vector<int> result;
  unordered_map<int, int> map;
  traversal1(root, map);
  vector<pair<int, int>> vec(map.begin(), map.end());
  sort(vec.begin(), vec.end(), [](pair<int, int>& a, pair<int, int>& b) {
    return a.second > b.second;
  });
  result.push_back(vec[0].first);
  for (int i = 1; i < vec.size(); i++) {
    if (vec[0].second == vec[i].second)
      result.push_back(vec[i].first);
    else
      break;
  }
  return result;
}

// 使用二叉搜索树性质，在中序遍历二叉树。外置数量、最大数量、前一个结点、结果。先判断前一结点与当前结点是否相等，计算数量
// 更新前一结点，当数量等于最大数量，就压入结果。当数量大于最大数量，清空结果，并压入最新数量
vector<int> result;
int cnt2 = 0;
int maxCount2 = 0;
TreeNode* pre = nullptr;
void searchBST2(TreeNode* cur) {
  if (!cur)
    return;
  searchBST2(cur->left);
  if (!pre)
    cnt2 = 1;
  else if (pre->val == cur->val)
    cnt2++;
  else
    cnt2 = 1;
  pre = cur;
  if (cnt2 == maxCount2)
    result.push_back(cur->val);
  if (cnt2 > maxCount2) {
    maxCount2 = cnt2;
    result.clear();
    result.push_back(cur->val);
  }
  searchBST2(cur->right);
  return;
}
vector<int> findMode2(TreeNode* root) {
  cnt2 = 0;
  maxCount2 = 0;
  pre = nullptr;
  result.clear();
  searchBST2(root);
  return result;
}
// 迭代法，栈模拟递归，注意不必处理根节点为空的特殊情况
vector<int> findMode3(TreeNode* root) {
  vector<int> result;
  TreeNode* pre = nullptr;
  TreeNode* cur = root;
  int cnt2 = 0, maxCount2 = 0;
  stack<TreeNode*> st;
  while (!st.empty() || cur != nullptr) {
    if (cur) {
      st.push(cur);
      cur = cur->left;
    } else {
      cur = st.top();
      st.pop();

      if (pre == nullptr)
        cnt2 = 1;
      else if (cur->val == pre->val)
        cnt2++;
      else
        cnt2 = 1;
      pre = cur;
      if (cnt2 == maxCount2)
        result.push_back(cur->val);
      if (cnt2 > maxCount2) {
        maxCount2 = cnt2;
        result.clear();
        result.push_back(cur->val);
      }

      cur = cur->right;
    }
  }
  return result;
}

int main() {
  vector<int> vec1 = {1, null, 2, null, null, 2};
  vector<int> vec2 = {0};
  vector<int> vec3 = {5, 4, 7};
  vector<int> vec4 = {1, 0, 1, 0, 0, 1, 1, 0};
  TreeNode* node1 = construct_binary_tree(vec1);
  TreeNode* node2 = construct_binary_tree(vec2);
  TreeNode* node3 = construct_binary_tree(vec3);
  TreeNode* node4 = construct_binary_tree(vec4);

  printVector(findMode(node1));
  printVector(findMode(node2));
  printVector(findMode(node3));
  printVector(findMode(node4));

  printVector(findMode1(node1));
  printVector(findMode1(node2));
  printVector(findMode1(node3));
  printVector(findMode1(node4));
  return 0;
}
