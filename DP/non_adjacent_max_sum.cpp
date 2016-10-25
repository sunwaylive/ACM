//we are given an array A1, A2, ..., AN; we can't choose adjacent elements and we have to maximise sum of chosen elements.
#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

int NonAdjacentMaxSum(vector<int> &nums) {
    if (nums.empty()) {
        return 0;
    }

    // insert a dummy num, at least 2 elements inside
    nums.insert(nums.begin(), 0);
    const int n = nums.size();
    vector<int> dp(n, 0);
    dp[0] = 0; // dummy num
    dp[1] = max(nums[0], nums[1]);
    for (int i = 2; i < n; ++i) {
        //State: dp[i]: 前i个元素达到的最大sum
        //Fun: dp[i] = {a[i] + dp[i-2], dp[i-1]} // a[i] is chosen or not respectively
        //Init:***
        //Ans: ***
        dp[i] = max(nums[i] + dp[i-2], dp[i-1]);
    }

    return dp[n-1];
}

// 如果上述问题不是在 一个一维数组上，二是在一个Tree上，每一个Tree有一个weight值，选一个树节点的子集出来，保证节点不能相邻，且 和最大
const int N = 100000;
int weight[N];
vector<int> adj[N];
int dp1[N], dp2[N];

void dfs(int v, int parent) {
    int sum1 = 0, sum2 = 0;

    for (auto child : adj[v]) {
        // 虽然用了类似于无向图的邻接表表示法，这句话，过滤掉父节点，就转化成为遍历其所有的孩子节点了
        // 使用邻接表表示树
        if (child == parent) {
            continue;
        }

        dfs(child, v);
        // 选v, 那么我们必须不能选child
        sum1 += dp2[child];
        // 不选v，那么我们可以选择 选或者不选child
        sum2 += max(dp1[child], dp2[child]);
    }

    // 选v, 那么我们不能选择child, 使用sum1
    dp1[v] = weight[v] + sum1;
    // 不选child, 那么我们使用sum2
    dp2[v] = sum2;

    printf("v: %d, dp1[v]: %d, dp2[v]: %d\n", v, dp1[v], dp2[v]);
}

int main() {
    vector<int> arr({1, 15, -3, 4, 2});
    cout << NonAdjacentMaxSum(arr) << endl;

    // for tree dp
    weight[0] = 0;
    weight[1] = 6;
    weight[2] = 3;
    weight[3] = 1;
    weight[4] = 2;
    weight[5] = 4;

    int n = 0, p = 0, c = 0;
    n = 5;
    for (int i = 0; i < n; ++i) {
        cin >> p >> c;
        adj[p].push_back(c);
        adj[c].push_back(p);
    }

    for (int i = 0; i <= n; ++i) {
        for (auto j : adj[i]) {
            cout << j << " ";
        }
        cout << endl;
    }

    dfs(1, 0);
    cout << max(dp1[1], dp2[1]) << endl;
    return 0;
}
