#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

bool ordered(vector<int> &A){
    int size = A.size();
    for(int i = 1; i < size; ++i){
        if(A[i] <= A[i - 1])
            return false;
    }
    return true;
}

void reverse(vector<int> &A, int start, int end)
{
    while(start < end){
        swap(A[start], A[end]);
        ++start, --end;
    }
}

void printVector(const vector<int> &A){
    for(int i = 0; i < A.size(); ++i)
        cout<<A[i]<<" ";
    cout<<endl;
}

int main()
{
    //fstream in;
    //in.open("input.txt");
    //cin.rdbuf(in.rdbuf());

    int n;
    vector<int> array;
    cin>>n;
    int tmp = n;
    while(tmp--){
        int temp;
        cin>>temp;
        array.push_back(temp);
    }

    int start, end;
    for(int i = 0; i < array.size()-1; ++i){
        if(array[i] > array[i+1]){
            start = i;
            break;
        }
    }

    for(int i = array.size() - 1; i >= 1; --i){
        if(array[i] < array[i-1]) {
            end = i;
            break;
        }
    }

    //cout<<start<<" "<<end<<endl;
    reverse(array, start, end);
    if(ordered(array)) cout<<"yes"<<endl << start+1 <<" "<<end+1<<endl;
    else cout<<"no"<<endl;
    //in.close();
    return 0;
}
