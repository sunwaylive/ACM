#include <iostream>
#include <fstream>
using namespace std;

int A[100005];
int main()
{
    ifstream in;
    in.open("input.txt");
    cin.rdbuf(in.rdbuf());

    int n;
    cin>>n;
    for(int i = 0; i < n; ++i){
        int tmp;
        cin>>tmp;
        A[i] = tmp;
    }

    int max_length = 0;
    bool has_changed = false;
    int i, j;
    for(i = 0; i < n; ++i){
        has_changed = false;
        //cout<<"i: "<<i;
        for(j = i + 1; j < n; ++j){
            if(A[j] > A[j-1]) continue;
            else if(A[j] < A[j-1] && !has_changed){
                //has_changed = true;
                //continue;
                if(j+1 < n && A[j+1] > A[j-1]) { has_changed = true; continue; }
                //else if(j+1 < n && A[j+1] > A[j]) { has_changed = true; continue; }
                else break;
            }else break;//7 2 8 1 5 6
        }
        //cout<<" j: "<<j<<endl;
        max_length = max(max_length, j - i);
    }
    cout<<max_length;
    return 0;
}
