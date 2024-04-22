#pragma once

#include <algorithm>
#include <cmath>
#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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

class Node1 {  // 二叉搜索树和双向循环链表
 public:
  int val;
  Node1* left;
  Node1* right;
  Node1(){};
  Node1(int value) : val(value), left(NULL), right(NULL) {}
  Node1(int value, Node1* l, Node1* r) : val(value), left(l), right(r) {}
};

void printVector(vector<int> vec);
void printVector(vector<string> vec);

void printVector2(vector<int> vec);

void printDeque(deque<int> deq);

void printDeque2(deque<int> deq);

ListNode* createList(vector<int> vec);

void printList(ListNode* list);

void inorder(TreeNode* root, vector<int>& res);

TreeNode* sortedArray2BST(vector<int> num);

TreeNode* construct_binary_tree(const vector<int>& vec);

void print_binary_tree(TreeNode* root);

void printMat(vector<vector<int>> nums);
void printMat(vector<vector<char>> nums);
void printMat(vector<vector<string>> nums);
