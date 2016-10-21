#include<string>
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string.h>
#include<memory.h>
#include<math.h>
#include<vector>
#include<algorithm>
#include<map>
#include<numeric>
#include<deque>
#include<set>
#include<functional>
#include<queue>

#define REP(i,s,n) for(int (i)=s; (i)<(int)(n);(i)++)
#define RIT(it,c) for(__typeof(c.begin()) it = c.begin();it!=c.end();it++)
#define RITT(it,v,c) for(__typeof(c.begin()) it = v;it!=c.end();it++)
#define ALL(x) x.begin(), x.end()
#define SZ(x) (int)(x).size()
#define MSET(m,v) memset(m,v,sizeof(m))
#define auto(c) __typeof(c.begin())

using namespace std;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef vector<pair<int,int> >vp;
typedef long long llint;

const int kMaxN = 550;
int planned[kMaxN];
int add[kMaxN];
int f[kMaxN];

int main() {
    int n = 0, k = 0;
    scanf("%d %d", &n, &k);

    for(int i = 0; i < n; ++i) {
        scanf("%d", &planned[i]);
        add[i] = 0;
    }

    int ret = 10000000;
    for (int i = 0; i < n - 1; ++i) {
        for (add[i] = 0; true; add[i]++) {
            if (i == 0 && add[i] + planned[i] > k)
                break;
            else if (i >= 1 && add[i-1] + planned[i-1] + add[i] + planned[i] > k)
                break;

            for (int j = i + 1; j < n; ++j) {
                add[j] = max((k- add[j-1] - planned[j-1] - planned[j]), 0);
            }

            //printf("add[%d]: ", i);

            int more = 0;
            for (int t = 0; t < n; ++t) {
                //cout << add[t] << " ";
                more += add[t];
            }
            //cout << endl << more << endl;

            if (more < ret) {
                for (int t = 0; t < n; ++t) {
                    f[t] = planned[t] + add[t];
                }
                ret = more;
            }
        }
    }

    cout << ret << endl;
    for (int t = 0; t < n - 1; ++t) {
        cout << f[t] << " ";
    }
    cout << f[n - 1];
    return 0;
}
