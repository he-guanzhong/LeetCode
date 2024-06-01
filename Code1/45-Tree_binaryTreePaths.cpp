#include "head.h"
/* 257. 二叉树的所有路径
给你一个二叉树的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。
叶子节点是指没有子节点的节点。
输入：root = [ 1, 2, 3, null, 5 ] 输出：["1->2->5", "1->3"]
输入：root = [1] 输出：["1"] */

vector<string> binaryTreePaths(TreeNode* root) {
  vector<string> result;
  vector<int> path;
  stack<TreeNode*> stk;
  if (root)
    stk.push(root);
  while (!stk.empty()) {
    TreeNode* cur = stk.top();
    stk.pop();
    path.push_back(cur->val);
    if (!cur->left && !cur->right) {
      string tmp;
      for (int i : path) {
        tmp += to_string(i);
        tmp += "->";
      }
      tmp.resize(tmp.size() - 2);
      result.push_back(tmp);
    }
    if (cur->right)
      stk.push(cur->right);
    if (cur->left)
      stk.push(cur->left);
    path.pop_back();
  }
  return result;
}

// 前序遍历，递归法。不加引用的string作为path，退出条件为空结点，进入递归先压值，若叶子结点，就收集result。->的压入和弹出，放在递归语句前后
// 前序遍历，递归法。使用vector<int>作为path，所有值压入，遇到叶子结点，统一转化string，收集result。如此可不必考虑->。
// 递归函数流程：1、先判空，压入本结点，判断是否合规，分别处理左右孩子。统一弹出本结点。如果传入path没有引用，可以不弹出
// 细节：整型int，只能通过to_string，使用+=压入string。不得使用push_back，因为如果是两位数，不能转化位字符型char
// 细节：同理，回溯时，也不得使用-=和pop_back，因为不知道要弹出多少位。核心方案在于传入的string不加引用，如此自动回溯了值

// 中序遍历，使用vector<int>作为暂存结果，因为pop_back时好处理，注意压入的量全部有值，才处理
void traversal1(TreeNode* cur, vector<int>& path, vector<string>& result) {
  path.push_back(cur->val);
  if (cur->left == nullptr && cur->right == nullptr) {  // 中，叶子结点
    string sPath;
    for (int i = 0; i < path.size() - 1; i++) {
      sPath += to_string(path[i]);
      sPath += "->";
    }
    sPath += to_string(path[path.size() - 1]);
    result.push_back(sPath);
    return;
  }
  if (cur->left) {
    traversal1(cur->left, path, result);
    path.pop_back();  // pop_back回溯必须紧跟递归
  }
  if (cur->right) {
    traversal1(cur->right, path, result);
    path.pop_back();
  }
}
vector<string> binaryTreePaths1(TreeNode* root) {
  vector<string> result;
  vector<int> path;
  if (!root)
    return result;
  traversal1(root, path, result);
  return result;
}

// 递归，只有有值结点才递归，path直接使用string，且不引用，如此不用回溯值，注意回溯的简写法
void traversal2(TreeNode* cur, string path, vector<string>& result) {
  path += to_string(cur->val);
  if (cur->left == nullptr && cur->right == nullptr) {
    result.push_back(path);
    return;
  }
  if (cur->left)
    traversal2(cur->left, path + "->", result);
  if (cur->right)
    traversal2(cur->right, path + "->", result);
  /*   if (cur->right) { // 完整版表达式
      path += "->";
      traversal(cur->right, path, result);
      path.pop_back(); // 弹出-
      path.pop_back(); // 弹出>
    } */
}
vector<string> binaryTreePaths2(TreeNode* root) {
  vector<string> result;
  string path;
  if (!root)
    return result;
  traversal2(root, path, result);
  return result;
}
// 递归，简写法。多一层递归，在内部处理push和pop。
void traversal3(TreeNode* root, vector<int> path, vector<string>& result) {
  if (!root)
    return;
  path.push_back(root->val);
  if (!root->left && !root->right) {
    string tmp;
    for (auto i : path) {
      tmp += to_string(i);
      tmp += "->";
    }
    tmp.resize(tmp.size() - 2);
    result.push_back(tmp);
  }
  traversal3(root->left, path, result);
  traversal3(root->right, path, result);
}

vector<string> binaryTreePaths3(TreeNode* root) {
  vector<string> result;
  vector<int> path;
  traversal3(root, path, result);
  return result;
}

// 迭代法，前序遍历，利用栈顺序 右左中
vector<string> binaryTreePaths4(TreeNode* root) {
  vector<string> result;
  stack<string> pathSt;     // 保存遍历路径的结点
  stack<TreeNode*> treeSt;  // 保存树的结点
  if (!root)
    return result;
  treeSt.push(root);
  pathSt.push(to_string(root->val));
  while (!treeSt.empty()) {
    TreeNode* node = treeSt.top();
    treeSt.pop();
    string path = pathSt.top();
    pathSt.pop();
    if (node->left == nullptr && node->right == nullptr) {
      result.push_back(path);
    }
    if (node->right) {
      treeSt.push(node->right);
      pathSt.push(path + "->" +
                  to_string(node->right->val));  // 注意，此处压入的是右节点的值
    }
    if (node->left) {
      treeSt.push(node->left);
      pathSt.push(path + "->" + to_string(node->left->val));
    }
  }
  return result;
}

void printMatrix(const vector<string>& mat) {
  for (auto row : mat)
    cout << row << ", ";
  cout << endl;
}
int main() {
  vector<int> vec1 = {1, 2, 3, null, 5};
  TreeNode* node1 = construct_binary_tree(vec1);
  vector<int> vec2 = {1};
  TreeNode* node2 = construct_binary_tree(vec2);
  printMatrix(binaryTreePaths(node1));
  printMatrix(binaryTreePaths(node2));
  printMatrix(binaryTreePaths1(node1));
  printMatrix(binaryTreePaths1(node2));
  return 0;
}
