#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    ifstream in;
    in.open("input.txt");
    cin.rdbuf(in.rdbuf());

    int a1, a2, a3;
    int b1, b2, b3;
    int n;
    cin>>a1>>a2>>a3;
    cin>>b1>>b2>>b3;
    cin>>n;

    int totalCups = a1 + a2 + a3;
    int totalMedals = b1 + b2 + b3;
    int i;
    for(i = 0; i < n; ++i){
        if(5 * i >= totalCups && 10 * (n - i) >= totalMedals){
            cout<<"YES";
            break;
        }
        else continue;
    }
    if(i == n)
        cout<<"NO";

    in.close();
    return 0;
}
