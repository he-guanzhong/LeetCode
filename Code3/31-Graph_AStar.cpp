#include <string.h>
#include "head.h"
/*  A * 算法精讲 （A star算法）
题目描述：
  在象棋中，马和象的移动规则分别是“马走日”和“象走田”。现给定骑士的起始坐标和目标坐标，
  要求根据骑士的移动规则，计算从起点到达目标点所需的最短步数。
  棋盘大小 1000 x 1000（棋盘的 x 和 y 坐标均在 [1, 1000] 区间内，包含边界）
输入描述：
  第一行包含一个整数n，表示测试用例的数量。接下来的n行，每行包含四个整数a1,a2,b1,b2，
  分别表示骑士的起始位置(a1,a2)和目标位置 (b1, b2)。
输出描述：
  输出共 n 行，每行输出一个整数，表示骑士从起点到目标点的最短路径长度。
输入示例：
  6
  5 2 5 4
  1 1 2 2
  1 1 8 8
  1 1 8 7
  2 1 3 3
  4 6 4 6
输出示例：
  2
  4
  6
  5
  1
  0 */

int moveStep[1001][1001];
int dir[8][2] = {-2, -1, -1, -2, 2, -1, 1, -2, 1, 2, 2, 1, -2, 1, -1, 2};
// 总代价F = 距离起点代价G + 到终点代价H
struct Knight {
  int x, y;
  int f, g, h;
  // 重载小于符号，按从小到大排
  bool operator<(const Knight& k) const { return k.f < f; }
};

// 启发函数，求当前点距离终点的代价，欧式距离，但不开方，以提高精度
int heuristic(const Knight& k, int endx, int endy) {
  return (k.x - endx) * (k.x - endx) + (k.y - endy) * (k.y - endy);
}
int astar(const Knight& start, int endx, int endy) {
  memset(moveStep, 0, sizeof(moveStep));
  Knight cur, next;            // 提前申请内存
  priority_queue<Knight> que;  // 默认小顶堆
  que.push(start);
  while (que.size()) {
    cur = que.top();
    que.pop();
    if (cur.x == endx && cur.y == endy)  // 必须是取的时候处理
      break;
    for (int i = 0; i < 8; i++) {
      next.x = cur.x + dir[i][0];
      next.y = cur.y + dir[i][1];

      if (next.x < 1 || next.x > 1000 || next.y < 1 || next.y > 1000)
        continue;
      if (moveStep[next.x][next.y])  // 只走没走过的地方
        continue;
      moveStep[next.x][next.y] = moveStep[cur.x][cur.y] + 1;
      next.g = cur.g + 5;  // 日字形，距离加1*1+2*2
      next.h = heuristic(next, endx, endy);
      next.f = next.g + next.h;
      que.push(next);
    }
  }
  return moveStep[endx][endy];
}

int main() {
  vector<vector<int>> test = {{5, 2, 5, 4}, {1, 1, 2, 2}, {1, 1, 8, 8},
                              {1, 1, 8, 7}, {2, 1, 3, 3}, {4, 6, 4, 6}};
  for (int i = 0; i < test.size(); i++) {
    int startx = test[i][0], starty = test[i][1], endx = test[i][2],
        endy = test[i][3];
    Knight start;
    start.x = startx, start.y = starty;
    start.g = 0, start.h = heuristic(start, endx, endy);
    start.f = start.g + start.h;
    cout << astar(start, endx, endy) << endl;
  }

  return 0;
}