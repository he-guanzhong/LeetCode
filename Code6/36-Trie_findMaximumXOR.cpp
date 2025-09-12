#include "head.h"
/* 421. 数组中两个数的最大异或值
给你一个整数数组 nums ，返回 nums[i] XOR nums[j] 的最大运算结果，其中 0 ≤ i ≤ j
< n 。
示例 1：
  输入：nums = [3,10,5,25,2,8]
  输出：28
  解释：最大运算结果是 5 XOR 25 = 28.
示例 2：
  输入：nums = [14,70,53,83,49,91,36,80,92,51,66,70]
  输出：127
提示：
  1 <= nums.length <= 2 * 105
  0 <= nums[i] <= 231 - 1 */

struct Trie {
  Trie *left, *right;
};

void addElem(int x, Trie* root) {
  Trie* node = root;
  for (int i = 30; i >= 0; i--) {
    if (x >> i & 1) {
      if (!node->right)
        node->right = new Trie();
      node = node->right;
    } else {
      if (!node->left)
        node->left = new Trie();
      node = node->left;
    }
  }
}

int check(int num, Trie* root) {
  Trie* node = root;
  int x = 0;
  for (int i = 30; i >= 0; i--) {
    if (num >> i & 1) {
      if (node->left) {
        x = 2 * x + 1;
        node = node->left;
      } else {
        x = 2 * x;
        node = node->right;
      }
    } else {
      if (node->right) {
        x = 2 * x + 1;
        node = node->right;
      } else {
        x = 2 * x;
        node = node->left;
      }
    }
  }
  return x;
}
int findMaximumXOR(vector<int>& nums) {
  Trie* root = new Trie();
  int ans = 0;
  for (int i = 1; i < nums.size(); i++) {
    addElem(nums[i - 1], root);
    ans = max(ans, check(nums[i], root));
  }
  return ans;
}

// 前缀树，31位正整数可以看作一棵深度31的二叉树，左、右节点分别代表从高到底其每一位为0或1
// 将数字，从高位(移动30次)，到低位（移动0）次，看末位上是否为1。
// 先将num[i-1]存入树中，然后以nums[i]对树进行比较。如此相当于执行了数组中，两两元素的比较
// addElem辅助函数将数组每一位分别加入树中。checkElem辅助函数，将待求元素x
struct Trie1 {
  Trie1* left;
  Trie1* right;
};

void addElem1(int num, Trie1* root) {
  Trie1* cur = root;
  for (int k = 30; k >= 0; k--) {
    if (num >> k & 1) {
      if (!cur->right)
        cur->right = new Trie1();
      cur = cur->right;
    } else {
      if (!cur->left)
        cur->left = new Trie1();
      cur = cur->left;
    }
  }
}
int checkElem1(int num, Trie1* root) {
  Trie1* cur = root;
  int x = 0;
  for (int k = 30; k >= 0; k--) {
    if (num >> k & 1) {
      // 元素是1。节点要左移，争取这一位是0
      if (cur->left) {
        cur = cur->left;
        x = 2 * x + 1;
      } else {
        cur = cur->right;
        x = 2 * x;
      }
    } else {
      // 元素是0。节点要右移，争取这一位是1
      if (cur->right) {
        cur = cur->right;
        x = 2 * x + 1;
      } else {
        cur = cur->left;
        x = 2 * x;
      }
    }
  }
  return x;
}
int findMaximumXOR2(vector<int>& nums) {
  Trie1* root = new Trie1();
  int x = 0;
  for (int i = 1; i < nums.size(); i++) {
    // 此时[0,i-1]均在树内
    addElem1(nums[i - 1], root);
    x = max(x, checkElem1(nums[i], root));
  }
  return x;
}

// 传统做法，哈希表。时间复杂度O(nlogC)。C是常数31。对于一个31位正整数，从高到底，依次检阅每一位k，是否可以取1
// 具体地，假定上一轮是否可以取的结果是x。那么本轮先假定其可以取，x_next=x<<1+1
// 对于ai和aj两个元素的前缀，其结果前缀pre_x=pre_ai^pre_aj。那么必定有pre_aj=pre_x^pre_ai
// 利用哈希表，提前存储该轮所有的pre_ai，若发现pre_x^pre_aj成立，则该位可以取1，x=x_next
// 若该条件不成立，说明该位只能取0，则x =x_next - 1
int findMaximumXOR1(vector<int>& nums) {
  int x = 0;
  for (int k = 30; k >= 0; k--) {
    unordered_set<int> uset;
    for (int i = 0; i < nums.size(); i++) {
      uset.insert(nums[i] >> k);
    }
    int x_next = 2 * x + 1;
    bool found = false;
    for (int i = 0; i < nums.size(); i++) {
      if (uset.count(x_next ^ (nums[i] >> k))) {
        x = x_next;
        found = true;
        break;
      }
    }
    if (!found)
      x = x_next - 1;
  }
  return x;
}

int main() {
  vector<int> nums1{3, 10, 5, 25, 2, 8},
      nums2{14, 70, 53, 83, 49, 91, 36, 80, 92, 51, 66, 70};
  cout << findMaximumXOR(nums1) << " " << findMaximumXOR(nums2) << endl;
  cout << findMaximumXOR1(nums1) << " " << findMaximumXOR1(nums2) << endl;

  return 0;
}