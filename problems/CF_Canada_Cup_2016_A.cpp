#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <vector>
#include <string>
using namespace std;

char str[200005];
int visited[200005];

bool WillFall(int n, int pos) {
    memset(visited, 0, sizeof(visited));

    while (pos >= 0 && pos < n) {
        // if we have arrived at former position, then return true
        if (visited[pos] == 1) {
            // printf("%d pos Not Fall\n", pos);
            return false;
        }

        visited[pos] = 1;
        pos = (str[pos] == '<' ? pos - 1 : pos + 1);
    }

    // printf("%d pos WillFall\n", pos);
    return true;
}

int main() {
    int n = 0;
    scanf("%d", &n);
    scanf("%s", str);
    // cout << str << endl;
    int res = 0;
    for (int i = 0; i < n; ++i) {
        res = WillFall(n, i) ? res + 1 : res;
    }

    cout << res << endl;
    return 0;
}
