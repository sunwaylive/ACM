#include <iostream>
#include <vector>
#include <deque>
#include <cmath>
using namespace std;

void getDivisors(int x, vector<int> &result)
{
    int upper = sqrt(x);
    vector<int> later;
    result.push_back(1);
    later.push_back(x);
    for(int i = 2; i <= upper; ++i)
        if(x % i == 0){
            result.push_back(i);
            later.push_back(x / i);
        }

    if(upper * upper == x)
        result.pop_back();

    for(int i = later.size() - 1; i >= 0; --i){
        result.push_back(later[i]);
    }
}

void printKth(int x, int k)
{
    vector<int> cur;
    vector<int> next;
    cur.push_back(x);
    for(int i = 0; i < k; ++i){
        next.clear();
        for(size_t j = 0; j < cur.size(); ++j)
            getDivisors(cur[j], next);
        //copy next to cur
        cur.clear();
        for(size_t k = 0; k < next.size(); ++k)
            cur.push_back(next[k]);
    }

     for(size_t i = 0; i < cur.size() && i < 100000; ++i)
         cout<<cur[i]<<" ";
}

int main()
{
    int x, k;
    cin>>x>>k;
    vector<int> ret;
    printKth(x, k);
    return 0;
}
