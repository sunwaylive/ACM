#include <iostream>
#include <cstdio>
using namespace std;

#define MAX 350
int main()
{
    int p, n;
    int x;
    int count[MAX];
    for(int i = 0; i < MAX; ++i)
        count[i] = 0;
    cin>>p>>n;
    for(int i = 1; i <= n; ++i){
        cin>>x;
        if(count[x % p] > 0) {
            cout<<i;
            return 0;
        }
        else count[x % p]++;
    }
    cout<<-1;
    return 0;
}
