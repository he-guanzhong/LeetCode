#include "head.h"

/* 735. 小行星碰撞
给定一个整数数组asteroids，表示在同一行的小行星。数组中小行星的索引表示它们在空间中的相对位置。
对于数组中的每一个元素，其绝对值表示小行星的大小，正负表示小行星的移动方向（正表示向右移动，负表示向左移动）。
每一颗小行星以相同的速度移动。
找出碰撞后剩下的所有小行星。碰撞规则：两个小行星相互碰撞，较小的小行星会爆炸。
如果两颗小行星大小相同，则两颗小行星都会爆炸。两颗移动方向相同的小行星，永远不会发生碰撞。
示例 1：
  输入：asteroids = [5,10,-5]
  输出：[5,10]
  解释：10 和 -5 碰撞后只剩下 10 。 5 和 10 永远不会发生碰撞。
示例 2：
  输入：asteroids = [8,-8]
  输出：[]
  解释：8 和 -8 碰撞后，两者都发生爆炸。
示例 3：
  输入：asteroids = [10,2,-5]
  输出：[10]
  解释：2 和 -5 发生碰撞后剩下 -5 。10 和 -5 发生碰撞后剩下 10 。
示例 4：
  输入：asteroids = [-2,-1,1,2]
  输出：[-2,-1,1,2]
  解释：-2 和 -1 向左移动，而 1 和 2 向右移动。
由于移动方向相同的行星不会发生碰撞，所以最终没有行星发生碰撞。 */

vector<int> asteroidCollision(vector<int>& asteroids) {
  vector<int> ans;
  for (const int& i : asteroids) {
    bool exist = true;
    while (!ans.empty() && i < 0 && ans.back() > 0) {
      if (-i > ans.back())
        ans.pop_back();
      else if (-i < ans.back()) {
        exist = false;
        break;
      } else {
        exist = false;
        ans.pop_back();
        break;
      }
    }
    if (exist)
      ans.push_back(i);
  }
  return ans;
}

// 数组模拟栈。碰撞消除只发生在，栈非空+栈顶为正+新元素为负的情况下。栈顶元素绝对值小于等于新元素，不断弹出。
// 一旦栈顶元素绝对值大于新元素，新元素被销毁，无法入栈，该轮结束。
vector<int> asteroidCollision1(vector<int>& asteroids) {
  vector<int> st;
  for (int i = 0; i < asteroids.size(); i++) {
    bool alive = true;
    while (alive && !st.empty() && asteroids[i] < 0 && st.back() > 0) {
      if (st.back() >= -asteroids[i])
        alive = false;
      if (st.back() <= -asteroids[i])
        st.pop_back();
    }
    if (alive)
      st.push_back(asteroids[i]);
  }
  return st;
}

int main() {
  vector<int> vec1 = {5, 10, -5}, vec2 = {8, -8}, vec3 = {10, 2, -5},
              vec4 = {-2, -1, 1, 2}, vec5 = {1, -2, -2, -2};
  printVector(asteroidCollision(vec1));
  printVector(asteroidCollision(vec2));
  printVector(asteroidCollision(vec3));
  printVector(asteroidCollision(vec4));
  printVector(asteroidCollision(vec5));
  printVector(asteroidCollision1(vec1));
  printVector(asteroidCollision1(vec2));
  printVector(asteroidCollision1(vec3));
  printVector(asteroidCollision1(vec4));
  printVector(asteroidCollision1(vec5));
  return 0;
}