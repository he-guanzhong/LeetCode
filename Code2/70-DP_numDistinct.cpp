#include "head.h"
/* 115. 不同的子序列
给你两个字符串 s 和 t ，统计并返回在 s 的 子序列 中 t 出现的个数，结果需要对
10^9+ 7 取模。
示例 1：
  输入：s = "rabbbit", t = "rabbit"
  输出：3
  解释：
    如下所示, 有 3 种可以从 s 中得到 "rabbit" 的方案。
示例 2：
  输入：s = "babgbag", t = "bag"
  输出：5
  解释：
    如下所示, 有 5 种可以从 s 中得到 "bag" 的方案。 */

int numDistinct(string s, string t) {
  int m = s.size(), n = t.size();
  vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
  for (int i = 0; i <= m; i++)
    dp[i][0] = 1;
  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      if (s[i - 1] == t[j - 1])
        dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % (int)(1e9 + 7);
      else
        dp[i][j] = dp[i - 1][j];
    }
  }
  return dp[m][n];
}

// dp[i][j]表示以t[j-1]结尾子序列，出现在s[i-1]结尾子序列个数（不是长度）。联想bagg和bag二维矩阵例子，看相等的末尾元素，取或不取两种情况
// dp[i][0]为s中删除任意元素，得到空集个数，为1。dp[0][j]为空集中删除任意元素，得到t个数，必为0。
// 递推公式由左上、正上两个方向推出。末尾元素相等，子序列个数为末尾元素都不取，和s末尾元素不取，二者之和。
// 末尾元素不等，子序列个数为dp[i][j]，s末尾元素不取个数。最终返回矩阵右下角值

// dp[i][j]表示以s[i-1]和t[j-1]为结尾的子序列个数（注意不是长度）。由于在s中寻找子集t，则dp[0][j]相当于在空集中找字母，必不可能，为0；
// dp[i][0]相当于在s中寻找空集，必可能，为1。空集中找空集，可能，dp[0][0]=1
// 递推公式，当s[i-1]和t[j-1]元素相等时，将s和t都截取一位，取dp[i-1][j-1]的子集个数；或只截s一位，t不截。取dp[i-1][j]子集个数。
// 二者相加，为dp[i][j]，不能截t且不截s，因为求的是s中t的个数，不是t-1的个数。
// 若s[i-1]和t[j-1]元素不等，则子序列个数为，s元素截1情况下的序列数dp[i-1][j]。
// 注意题目要求取模，可以在每一轮dp[i][j]算出时操作。
int numDistinct1(string s, string t) {
  vector<vector<long long>> dp(s.size() + 1,
                               vector<long long>(t.size() + 1, 0));
  for (int i = 0; i <= s.size(); i++)
    dp[i][0] = 1;
  for (int j = 0; j <= t.size(); j++)
    dp[0][j] = 0;
  dp[0][0] = 1;
  for (int i = 1; i <= s.size(); i++) {
    for (int j = 1; j <= t.size(); j++) {
      if (s[i - 1] == t[j - 1])
        dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]);
      else
        dp[i][j] = dp[i - 1][j];
      dp[i][j] %= ((long long)pow(10, 9) + 7);  // 取模
    }
  }
  return dp[s.size()][t.size()];
}

// 简化写法
int numDistinct2(string s, string t) {
  vector<vector<long long>> dp(s.size() + 1,
                               vector<long long>(t.size() + 1, 0));
  for (int i = 0; i <= s.size(); i++)
    dp[i][0] = 1;
  for (int i = 1; i <= s.size(); i++) {
    for (int j = 1; j <= t.size(); j++) {
      if (s[i - 1] == t[j - 1])
        dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j];
      else
        dp[i][j] = dp[i - 1][j];
    }
  }
  return dp[s.size()][t.size()];
}

int main() {
  string s1 = "rabbbit", t1 = "rabbit";
  string s2 = "babgbag", t2 = "bag";
  string
      s3 = "xslledayhxhadmctrliaxqpokyezcfhzaskeykchkmhpyjipxtsuljkwkovmvelvwxz"
           "wieeuqnjozrfwmzsylcwvsthnxujvrkszqwtglewkycikdaiocglwzukwovsghkhyid"
           "evhbgffoqkpabthmqihcfxxzdejletqjoxmwftlxfcxgxgvpperwbqvhxgsbbkmphyo"
           "mtbjzdjhcrcsggleiczpbfjcgtpycpmrjnckslrwduqlccqmgrdhxolfjafmsrfdghn"
           "atexyanldrdpxvvgujsztuffoymrfteholgonuaqndinadtumnuhkboyzaqguwqijwx"
           "xszngextfcozpetyownmyneehdwqmtpjloztswmzzdzqhuoxrblppqvyvsqhnhryvqs"
           "qogpnlqfulurexdtovqpqkfxxnqykgscxaskmksivoazlducanrqxynxlgvwonalpsy"
           "ddqmaemcrrwvrjmjjnygyebwtqxehrclwsxzylbqexnxjcgspeynlbmetlkacnnbhma"
           "izbadynajpibepbuacggxrqavfnwpcwxbzxfymhjcslghmajrirqzjqxpgtgisfjreq"
           "rqabssobbadmtmdknmakdigjqyqcruujlwmfoagrckdwyiglviyyrekjealvvigiesn"
           "vuumxgsveadrxlpwetioxibtdjblowblqvzpbrmhupyrdophjxvhgzclidzybajuxll"
           "acyhyphssvhcffxonysahvzhzbttyeeyiefhunbokiqrpqfcoxdxvefugapeevdoakx"
           "wzykmhbdytjbhigffkmbqmqxsoaiomgmmgwapzdosorcxxhejvgajyzdmzlcntqbapb"
           "pofdjtulstuzdrffafedufqwsknumcxbschdybosxkrabyfdejgyozwillcxpcaiehl"
           "elczioskqtptzaczobvyojdlyflilvwqgyrqmjaeepydrcchfyftjighntqzoo",
      t3 = "rwmimatmhydhbujebqehjprrwfkoebcxxqfktayaaeheys";
  cout << numDistinct(s1, t1) << " " << numDistinct(s2, t2) << " "
       << numDistinct(s3, t3) << endl;
  cout << numDistinct1(s1, t1) << " " << numDistinct1(s2, t2) << " "
       << numDistinct1(s3, t3) << endl;
  return 0;
}