/*
 * Given a sequence of N numbers – A[1] , A[2] , …, A[N] .
 * Find the length of the longest non-decreasing sequence.
 */

#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

const int kMax = 1000000;

int main() {
    /*
     * DP, 定义的时候 dp[i]必须定义为以nums[i] 为结尾 的LIS的长度
     *
     * State:  dp[i]: 表示以第i个元素结尾的LIS的长度，只有这样才能保证下面的Func能够正确递推
     *         错误的dp[i]的定义：前i个元素中最长的LIS的长度，Wrong!
     * Func: dp[i] = max{dp[j]+1, 其中：0<=j<i && nums[i] > nums[j]}
     * Init: dp[0] = 1;
     * Ans: max{dp[0...n-1]}
     * */
    vector<int> nums({11, 12, 13, 1, 2, 3});
    int n = nums.size();
    vector<int> dp(n, 1);
    int res = 1;
    // dp[0] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            dp[i] = max(dp[i], nums[i] >= nums[j] ? dp[j] + 1 : 1);
        }
        res = max(res, dp[i]);
    }
    cout << res << endl;
    return 0;
}

/*
 * 另一个相似的问题是：给定一个带权重的无向图，求从起点到终点的最短距离
 * w[i][j]: 表示点i到点j的距离, INF if not reachable
 *state: dp[i]:从起点到达i点的最短距离
 *function: dp[i] = min(dp[j] + w[j][i]), 0 <=j < i,
 *init: dp[0] = 0
 *ans: dp[n]

 for (int i = 0; i < n; ++i) {
    dp[i]  = INF;
 }

 int dp[0] = 0;
 for (int i = 1; i < n; ++i) {
    for (int j = 0; j < i; ++j) {
        if(w[i][j] != INF) dp[i] = min(dp[i], dp[j] + w[j][i] )
    }
 }
 return dp[n-1];
 * */
