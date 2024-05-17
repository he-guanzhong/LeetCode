#include "head.h"
/* 150. 逆波兰表达式求值
给你一个字符串数组 tokens ，表示一个根据 逆波兰表示法 表示的算术表达式。
请你计算该表达式。返回一个表示表达式值的整数。
注意：
    有效的算符为 '+'、'-'、'*' 和 '/' 。
    每个操作数（运算对象）都可以是一个整数或者另一个表达式。
    两个整数之间的除法总是 向零截断 。
    表达式中不含除零运算。
    输入是一个根据逆波兰表示法表示的算术表达式。
    答案及所有中间计算结果可以用 32 位 整数表示。
    示例 1：
输入：tokens = ["2","1","+","3","*"]
输出：9
解释：该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
示例 2：
输入：tokens = ["4","13","5","/","+"]
输出：6
解释：该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
示例 3：
输入：tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
输出：22
解释：该算式转化为常见的中缀算术表达式为：
  ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22 */

int evalRPN(vector<string>& tokens) {
  stack<int> st;
  int num1 = 0, num2 = 0;
  for (string str : tokens) {
    int ans = 0;
    if (str == "+" || str == "-" || str == "*" || str == "/") {
      num2 = st.top();
      st.pop();
      num1 = st.top();
      st.pop();
      if (str == "+")
        ans = num1 + num2;
      else if (str == "-")
        ans = num1 - num2;
      else if (str == "*")
        ans = num1 * num2;
      else if (str == "/")
        ans = num1 / num2;
    } else {
      ans = stoi(str);
    }
    st.push(ans);
  }
  return st.top();
}

// 逆波兰表达式，利用栈，变量类型longlong，而非int因为题目限定了整型大小。
// 碰到运算符，由于四种符号均需处理前两位数字，故双层if，并将结果压回栈内。碰到数字，就stoll转化为longlong，压入栈。
// 最终的结果必是栈内唯一元素，由于返回值已经限定了int，故可以使用int
// Reverse Polish Notation 逆波兰（后缀）表达式。利用栈，注意整形为long long,
// 字符串转整形，C语言头文件stdlib.h后，可使用atoi,atol,atoll，仅接收一个参数char*。若为string类，则需转化为str.c_str()输入
// 若使用strtoi,strtol,strtoll，包含三个参数char*,char* endptr, int base
// endptr为第一个不能转化的位置endptr(不需要可以输入NULL)，base为允许指定的基数，如10、16等
// C++语言包含头文件string.h后，使用stoi,stol,stoll，仅接收一个参数string，如果
int evalRPN1(vector<string>& tokens) {
  stack<long long> st;
  for (string s : tokens) {
    if (s == "+" || s == "-" || s == "*" || s == "/") {
      long long num1 = st.top();
      st.pop();
      long long num2 = st.top();
      st.pop();
      if (s == "+")
        st.push(num2 + num1);
      if (s == "-")
        st.push(num2 - num1);
      if (s == "*")
        st.push(num2 * num1);
      if (s == "/")
        st.push(num2 / num1);
    } else {
      st.push(stoll(s));
    }
  }
  int result = st.top();  // 返回值已经确定了是int, 没必要long long
  st.pop();
  return result;
}

int main() {
  vector<string> tokens1 = {"2", "1", "+", "3", "*"};
  vector<string> tokens2 = {"4", "13", "5", "/", "+"};
  vector<string> tokens3 = {"10", "6", "9",  "3", "+", "-11", "*",
                            "/",  "*", "17", "+", "5", "+"};
  cout << evalRPN(tokens1) << " " << evalRPN(tokens2) << " " << evalRPN(tokens3)
       << " " << endl;
  cout << evalRPN1(tokens1) << " " << evalRPN1(tokens2) << " "
       << evalRPN1(tokens3) << " " << endl;
  return 0;
}
