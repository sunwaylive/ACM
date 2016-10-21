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

int main() {
    int k = 0, r = 0;
    cin >> k >> r;
    int cnt = 1;
    for(cnt = 1; k*cnt%10 != 0 && k*cnt%10 != r; cnt++);
    cout << cnt;
    return 0;
}
