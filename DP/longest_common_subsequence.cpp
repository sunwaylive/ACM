#include <iostream>
#include <string>
#include <vector>

using namespace std;

/* 2016 Second Time Just do it */
/*
 * DP
 * S(tate): dp[i][j]:表示s1前i个字符和s2前j个字符的LCS
 * F(unction): dp[i][j] = {if s[i] == s[j], dp[i-1][j-1] + 1;
 *                         else, 反正s1[i] != s2[j], dp[i][j]的值肯定是dp[i-1][j] dp[i][j-1]中较大的一个}
 * I(init): 见L23 - L31
 * A(nswer): dp[m-1][n-1]
 * */
int LCSequence(string &s1, string &s2) {
    if (s1.empty() || s2.empty()) {
        return 0;
    }

    const int m = s1.size();
    const int n = s2.size();
    vector<vector<int> > dp(m, vector<int>(n, 0));
    dp[0][0] = (s1[0] == s2[0] ? 1 : 0);

    for (int j = 1; j < n; ++j) {
        dp[0][j] = (s1[0] == s2[j] ? 1 : dp[0][j-1]);
    }

    for (int i = 1; i < m; ++i) {
        dp[i][0] = (s1[i] == s2[0] ? 1 : dp[i-1][0]);
    }

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            if (s1[i] == s2[j]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i][j-1], dp[i-1][j]);
            }
        }
    }

    return dp[m-1][n-1];
}

int main() {
    string s1("abc");
    string s2("a:wwewebc");
    cout << LCSequence(s1, s2) << endl;
    return 0;
}
