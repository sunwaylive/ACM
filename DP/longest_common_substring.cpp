#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* 2016 Second Time Just do it */
/*
 * DP
 * S(tate): dp[i][j], 以s1[i], s2[j]结尾的子串形成的LCSubstring的长度。这里跟LIS定义类似，必须是以其结尾的，而不是前i个字符。因为它们有个共同的，substring不能断，longest increasing subsequence必须以其结尾，才能保证状态转换方程的正确递推，否则如果用前i个元素这种定义去计算，会fail，（11，12，13， 1，2）。
 * F(unction): dp[i][j] = if s1[i] == s2[j], dp[i][j] = dp[i-1][j-1] + 1
 *                        else dp[i][j] = 0
 * I(nit):
 * A(nswer):max{dp[0..m-1][0..n-1]}
 * */
int LCSubstring(string &s1, string &s2) {
    if (s1.empty() || s2.empty()) {
        return 0;
    }

   const int m = s1.size();
   const int n = s2.size();
   vector<vector<int> > dp(m, vector<int>(n, 0));
   int res = 0;
   for (int j = 0; j < n; ++j) {
       dp[0][j] = (s1[0] == s2[j] ? 1 : 0);
       res = max(res, dp[0][j]);
   }

   for (int i = 0; i < m; ++i) {
       dp[i][0] = (s1[i] == s2[0] ? 1 : 0);
       res = max(res, dp[i][0]);
   }

   for (int i = 1; i < m; ++i) {
       for (int j = 1; j < n; ++j) {
           dp[i][j] = (s1[i] == s2[j] ? dp[i-1][j-1] + 1 : 0);
           res = max(res, dp[i][j]);
       }
   }

   return res;
}

int main() {
    string s1("asdfasdf");
    string s2("easdfasdf");
    cout << LCSubstring(s1, s2) << endl;
    return 0;
}


