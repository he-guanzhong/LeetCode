#include "head.h"
/* LCR 156. 序列化与反序列化二叉树
序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，
同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。
请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 /
反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。
提示: 输入输出格式与 LeetCode 目前使用的方式一致，详情请参阅 LeetCode
序列化二叉树的格式。你并非必须采取这种方式，你也可以采用其他的方法解决这个问题。
示例 1：
  输入：root = [1,2,3,null,null,4,5]
  输出：[1,2,3,null,null,4,5]
示例 2：
  输入：root = []
  输出：[]
示例 3：
  输入：root = [1]
  输出：[1]
示例 4：
  输入：root = [1,2]
  输出：[1,2]
提示：
    树中结点数在范围 [0, 104] 内
    -1000 <= Node.val <= 1000 */

class Codec {
 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    string ans;
    queue<TreeNode*> que;
    if (root)
      que.push(root);
    while (!que.empty()) {
      TreeNode* cur = que.front();
      que.pop();
      if (!cur) {
        ans += "null,";
        continue;
      } else {
        ans += to_string(cur->val) + ",";
        que.push(cur->left);
        que.push(cur->right);
      }
    }
    if (!ans.empty())
      ans.pop_back();
    return ans;
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    if (data.empty())
      return nullptr;
    vector<TreeNode*> vec;
    int j = 0;
    for (int i = 0; i <= data.size(); i++) {
      if (i == data.size() || data[i] == ',') {
        string tmp = data.substr(j, i - j);
        j = i + 1;
        TreeNode* node = nullptr;
        if (!tmp.empty() && tmp != "null") {
          int val = stoi(tmp);
          node = new TreeNode(val);
        }
        vec.push_back(node);
      }
    }
    if (vec.empty())
      return nullptr;
    j = 1;
    for (int i = 0; i < vec.size(); i++) {
      if (vec[i]) {
        vec[i]->left = vec[j++];
        vec[i]->right = vec[j++];
      }
    }
    return vec[0];
  }
};

// 序列化二叉树。实质上是利用队列BFS，无论是否空指针，都压队列。如此最后一行全为空指针不可避免。打印函数中没有，是因为故意不打印最后一行
// 反序列化。要先将字符串切割为vector形式，其中可以直接存储TreeNode。注意先排除空字符串情况。否则无法利用stoi()函数
// 若不希望利用辅助队列构造树，也可以直接在vector上双下标，i记录当前结点，j记录孩子结点操作。不得直接使用公式2k+1,2K+2

// 序列化二叉树。队列层序遍历，先排除空字符串，直接返回空结点（不得最后操作）。压队列后，队列首元素如为空指针，直接字符串+null
// 如不为空指针，则添加to_string，并加“,”（注意分号）。并直接压入左右结点，即允许空结点入队列。最终，弹出字符串末尾‘,’，返回
// 反序列化二叉树，先构造分离函数split，将string分解为vector<string>，起始标志位i<n循环，内部j=i+1二层循环，直至遇到','或末尾n，此时字符串正好为[i,j)，并更新i=j+1
// 主函数依旧使用队列辅助，先排除空字符串。然后对vector<string>首元素先置为根节点，入队。队首元素node如果不是null，则要新创结点，并压入队列。
// 队首node若是null，不用做任何操作，因为左右孩子nullptr已默认建立。注意，无论node有数值与否，i++是必须的。
class Codec1 {
 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    string ans;
    queue<TreeNode*> que;
    if (!root)
      return ans;
    que.push(root);
    while (!que.empty()) {
      TreeNode* node = que.front();
      que.pop();
      if (node) {
        ans += to_string(node->val) + ',';
        que.push(node->left);
        que.push(node->right);
      } else {
        ans += "null,";
      }
    }
    ans.pop_back();
    return ans;
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    if (data.empty())
      return nullptr;
    vector<string> s = split(data);
    int i = 0;
    TreeNode* root = new TreeNode(stoi(s[i]));
    i++;
    queue<TreeNode*> que;
    que.push(root);
    while (!que.empty()) {
      TreeNode* node = que.front();
      que.pop();
      if (s[i] != "null") {
        node->left = new TreeNode(stoi(s[i]));
        que.push(node->left);
      }
      i++;

      if (s[i] != "null") {
        node->right = new TreeNode(stoi(s[i]));
        que.push(node->right);
      }
      i++;
    }
    return root;
  }
  vector<string> split(const string data) {
    vector<string> ans;
    int i = 0, n = data.size();
    while (i < n) {
      int j = i + 1;
      while (j < n && data[j] != ',')
        j++;
      ans.push_back(data.substr(i, j - i));
      i = j + 1;
    }
    return ans;
  }
};

int main() {
  Codec codec;
  TreeNode* t = construct_binary_tree({1, 2, 3, null, null, 4, 5});
  string s = codec.serialize(t);
  cout << s << endl;
  print_binary_tree(codec.deserialize(s));
  t = nullptr;
  s = codec.serialize(t);
  cout << s << endl;
  print_binary_tree(codec.deserialize(s));

  Codec1 codec1;
  TreeNode* t1 = construct_binary_tree({1, 2, 3, null, null, 4, 5});
  string s1 = codec1.serialize(t1);
  cout << s1 << endl;
  print_binary_tree(codec1.deserialize(s1));
  t1 = nullptr;
  s1 = codec1.serialize(t1);
  cout << s1 << endl;
  print_binary_tree(codec1.deserialize(s1));
  return 0;
}