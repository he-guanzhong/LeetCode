#include "head.h"

void printVector(vector<int> vec) {
  for (int val : vec)
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

template <class T>
void printMat(T& matrix) {
  for (auto row : matrix) {
    for (auto i : row)
      cout << i << " ";
    cout << endl;
  }
}