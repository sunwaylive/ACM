#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    fstream in;
    in.open("input.txt");
    cin.rdbuf(in.rdbuf());

    string s;
    int k;
    int w[26];
    cin>>s;
    cin>>k;
    for(int i = 0; i < 26; ++i){
        int tmp;
        cin>>tmp;
        w[i] = tmp;
    }

    int max_w = w[0];
    for(int i = 1; i < 26; ++i)
        if(w[i] > max_w) max_w = w[i];

    int length = s.size();
    int sum = 0;
    for(int i = 0; i < length; ++i){
        sum += (i+1) * w[s[i] - 'a'];
    }

    for(int i = length; i < length + k; ++i){
        sum += (i+1) * max_w;

    }

    cout<<sum;
    return 0;
}
