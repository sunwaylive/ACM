#include <iostream>
using namespace std;

int main()
{
    int n, m;
    cin>>n>>m;
    int total = n * m;
    int count = 0;
    while(n > 0 && m > 0 && total > 0){
        total -= (n + m - 1);
        ++count;
        --n, --m;
    }
    if(count & 0x1) cout<<"Akshat"<<endl;
    else cout<<"Malvika"<<endl;
    return 0;
}
