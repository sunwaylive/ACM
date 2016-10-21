/*
 * Given a list of N coins, their values (V1, V2, … , VN), and the total sum S.
 * Find the minimum number of coins the sum of which is S (we can use as many coins of one type as we want),
 * or report that it’s not possible to select coins in such a way that they sum up to S.
 * */
#include <iostream>
#include <cstdio>
using namespace std;

#define INF 0x3f3f3f3f
const int kMaxCoinNum = 1000000;
int coin_val[kMaxCoinNum];
int dp[kMaxCoinNum];

int main() {
    int coin_num = 0, sum = 0;
    cin >> coin_num >> sum;
    for (int i = 0; i < coin_num; ++i) {
        cin >> coin_val[i];
    }

    for (int i = 0; i <= sum; ++i) {
        dp[i] = INF;
    }

    dp[0] = 0;
    for (int i = 1; i <= sum; ++i) {
        for (int j = 0; j < coin_num; ++j) {
            if (coin_val[j] <= i && dp[i-coin_val[j]] + 1 < dp[i]) {
                dp[i] = dp[i-coin_val[j]] + 1;
            }
        }
    }

    cout << dp[sum] << endl;
    return 0;
}
