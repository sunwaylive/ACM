#include <iostream>
#include <string>
#include <stack>
#include <cstdio>
using namespace std;

// straightforward
int func(string str, int l, int r) {
    l = l - 1;
    r = r - 1;

    stack<char> stk;
    int length = 0;
    for (int i = l; i <= r; ++i) {
        if (str[i] == '(') {
            stk.push(str[i]);
        } else if (str[i] == ')') {
            if (stk.empty() || stk.top() == ')') {
                stk.push(str[i]);
            } else if (stk.top() == '('){
                stk.pop();
                length += 2;
            }
        }
    }

    return length;
}

// segment tree solution
// open[i]: 剩下的未使用的左括号数目
// close[i]:剩下的未使用的右边括号数目
// match_num[i]: 该区间匹配成功的括号的对数
const int kSegTreeNodeMax = 100000;
int open[kSegTreeNodeMax];
int close[kSegTreeNodeMax];
int match_num[kSegTreeNodeMax];

void Build(string str, int root, int start, int end) {
    // base cases
    if (start >= end) {
        return;
    }

    if (start + 1 == end) {
        if (str[start] == '(') {
            open[root] = 1;
        } else if (str[start] == ')') {
            close[root] = 1;
        }

        // Never miss it!
        return;
    }

    // recursive case
    int mid = start + (end - start) / 2;
    Build(str, 2*root+1, start, mid);
    Build(str, 2*root+2, mid, end);

    int new_match = min(open[2*root+1], close[2*root+2]);
    open[root] = open[2*root+1] + open[2*root+2] - new_match;
    close[root] = close[2*root+1] + close[2*root+2] - new_match;
    match_num[root] = match_num[2*root+1] + match_num[2*root+2] + new_match;
}

typedef pair<int, int> pii;
typedef pair<int, pii> node;
// {match_num, {open, close}}

node Query(int root, int start, int end, int query_start, int query_end) {
    // no intersection
    if (query_start >= end || query_end <= start) {
        return {0, {0, 0}};
    }

    // current interval is in query interval
    // all current interval info is saved at root position
    if (query_start <= start && query_end >= end) {
        return {match_num[root], {open[root], close[root]}};
    }

    int mid = start + (end - start) / 2;
    node left = Query(2*root+1, start, mid, query_start, query_end);
    node right = Query(2*root+2, mid, end, query_start, query_end);

    // MUST you query return data, NOT origin data in SegTree
    int new_match = min(left.second.first, right.second.second);
    node ret;
    ret.first = left.first + right.first + new_match;
    ret.second.first = left.second.first + right.second.first - new_match;
    ret.second.second = left.second.second + right.second.second - new_match;
    return ret;
}

int main() {
    string str = "())(())(())(";
    //cout << func(str, 1, 1) << endl;
    //cout << func(str, 2, 3) << endl;
    //cout << func(str, 1, 2) << endl;
    //cout << func(str, 1, 12) << endl;
    //cout << func(str, 8, 12) << endl;
    //cout << func(str, 5, 11) << endl;
    //cout << func(str, 2, 10) << endl;

    Build(str, 0, 0, str.length());
    cout << Query(0, 0, str.length(), 1-1, 1).first * 2 << endl;
    cout << Query(0, 0, str.length(), 2-1, 3).first * 2 << endl;
    cout << Query(0, 0, str.length(), 1-1, 2).first * 2 << endl;
    cout << Query(0, 0, str.length(), 1-1, 12).first * 2 << endl;
    cout << Query(0, 0, str.length(), 8-1, 12).first * 2 << endl;
    cout << Query(0, 0, str.length(), 5-1, 11).first * 2 << endl;
    cout << Query(0, 0, str.length(), 2-1, 10).first * 2 << endl;

    return 0;
}
