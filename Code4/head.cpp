#include "head.h"
void printVector(vector<int> vec) {
  for (int val : vec)
    cout << val << ",";
  cout << endl;
}
void printVector(vector<string> vec) {
  for (string val : vec)
    cout << val << ",";
  cout << endl;
}

void printVector2(vector<int> vec) {
  for_each(vec.begin(), vec.end(), [](const auto& val) { cout << val << ","; });
  cout << endl;
}

void printDeque(deque<int> deq) {
  for (auto i : deq)
    cout << i << ' ';
  cout << endl;
}

void printDeque2(deque<int> deq) {
  for_each(deq.begin(), deq.end(), [](const auto& val) { cout << val << " "; });
  cout << endl;
}

ListNode* createList(vector<int> vec) {
  ListNode* head = new ListNode();
  ListNode* p = head;

  for (int i = 0; i < vec.size(); i++) {
    ListNode* n = new ListNode(vec[i]);
    p->next = n;
    p = n;
  }
  return head->next;  // here why ?
}

void printList(ListNode* list) {
  if (list == nullptr) {
    cout << "empty" << endl;
    return;
  }
  ListNode* p = list;
  while (p != nullptr) {
    cout << p->val << " ";
    p = p->next;
  }
  cout << "NULLPTR" << endl;
}

void inorder(TreeNode* root, vector<int>& res) {
  if (!root)
    return;
  inorder(root->left, res);
  res.push_back(root->val);
  inorder(root->right, res);
}

TreeNode* helper(vector<int> nums, int left, int right) {
  if (left > right)
    return nullptr;
  int mid = (left + right) / 2;
  TreeNode* root = new TreeNode(nums[mid]);
  root->left = helper(nums, left, mid - 1);
  root->right = helper(nums, mid + 1, right);
  return root;
}

TreeNode* sortedArray2BST(vector<int> nums) {
  if (nums.empty())
    return nullptr;
  return helper(nums, 0, nums.size() - 1);
}

TreeNode* construct_binary_tree(const vector<int>& vec) {
  vector<TreeNode*> vecTree(vec.size(), nullptr);
  TreeNode* root = nullptr;
  for (int i = 0; i < vec.size(); i++) {
    TreeNode* node = nullptr;
    if (vec[i] != -1)
      node = new TreeNode(vec[i]);
    vecTree[i] = node;
    if (i == 0)
      root = node;
  }
  for (int i = 0; 2 * i + 1 < vec.size(); i++) {
    if (vecTree[i] != nullptr) {
      vecTree[i]->left = vecTree[2 * i + 1];
      if (2 * i + 2 < vec.size())
        vecTree[i]->right = vecTree[2 * i + 2];
    }
  }
  return root;
}

void print_binary_tree(TreeNode* root) {
  vector<vector<int>> result;
  queue<TreeNode*> que;
  if (root)
    que.push(root);
  while (!que.empty()) {
    int size = que.size();
    vector<int> level;
    while (size--) {
      TreeNode* node = que.front();
      que.pop();
      if (node) {
        level.push_back(node->val);
        que.push(node->left);
        que.push(node->right);
      } else {
        level.push_back(-1);
      }
    }
    result.push_back(level);
  }
  if (result.size() == 0) {
    cout << -1;
    return;
  } else if (result.size() == 1) {
    cout << result[0][0];
    return;
  }
  for (int i = 0; i < result.size() - 1; i++) {
    for (int j = 0; j < result[i].size(); j++)
      cout << result[i][j] << " ";
    cout << endl;
  }
  cout << endl;
}

void printMat(vector<vector<int>> nums) {
  for (auto row : nums) {
    for (auto i : row)
      cout << i << ",";
    cout << "\t";
  }
  cout << endl;
}
void printMat(vector<vector<string>> nums) {
  for (auto row : nums) {
    for (auto i : row)
      cout << i << " , ";
    cout << "\t";
  }
  cout << endl;
}
void printMat(vector<vector<char>> nums) {
  for (auto row : nums) {
    for (auto i : row)
      cout << i << " ";
    cout << "\n";
  }
  cout << endl;
}
