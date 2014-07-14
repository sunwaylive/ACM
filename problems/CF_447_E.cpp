#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int fb(int x){
    if(x == 1 || x == 2) return 1;
    return fb(x - 1) + fb(x - 2);
}

int main()
{
    ifstream in;
    in.open("input.txt");
    cin.rdbuf(in.rdbuf());

    int n, m;
    cin>>n>>m;
    vector<int> a;
    for(int i = 0; i < n; ++i){
        int tmp;
        cin>>tmp;
        a.push_back(tmp);
    }

    for(int i = 0; i < m; ++i){
        int op, start, end;
        cin>>op>>start>>end;
        if(op == 1){
            for(int j = start; j <= end; ++j){
                a[j-1] += fb(j - start + 1);
            }
        }
        if(op == 2){
            int sum = 0;
            for(int j = start; j <= end; ++j){
                sum += a[j-1] % 1000000009;
            }
            cout<<sum;
        }
    }
    return 0;
}
