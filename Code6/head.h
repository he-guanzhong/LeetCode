#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

constexpr int null = -1;

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int val) : val(val), next(nullptr) {}
  ListNode(int val, ListNode* next) : val(val), next(next) {}
};

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
  TreeNode(int value, TreeNode* left, TreeNode* right)
      : val(value), left(left), right(right) {}
};

class Node {  // complex linklist
 public:
  int val;
  Node* next;
  Node* random;
  Node(int value) {
    val = value;
    next = NULL;
    random = NULL;
  }
};

class Node1 {  // binary search tree / double linked circular list
 public:
  int val;
  Node1* left;
  Node1* right;
  Node1(){};
  Node1(int value) : val(value), left(NULL), right(NULL) {}
  Node1(int value, Node1* l, Node1* r) : val(value), left(l), right(r) {}
};

template <typename T>
void printVector(const vector<T>& vec) {
  for_each(vec.begin(), vec.end(), [](const auto& val) { cout << val << ","; });
  cout << endl;
}

template <typename T>
void printDeque(const deque<T>& deq) {
  for_each(deq.begin(), deq.end(), [](const auto& val) { cout << val << " "; });
  cout << endl;
}

template <typename T>
void printMat(const vector<vector<T>>& nums) {
  for (const auto& row : nums) {
    for (const auto& elem : row)
      cout << elem << ",";
    cout << "\t";
  }
  cout << endl;
}

ListNode* createList(const vector<int>& vec);

void printList(ListNode* list);

TreeNode* sortedArray2BST(vector<int> num);

TreeNode* construct_binary_tree(const vector<int>& vec);

void print_binary_tree(TreeNode* root);
