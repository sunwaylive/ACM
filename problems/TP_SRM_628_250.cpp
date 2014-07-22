#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


class BishopMove {
public:
    int howManyMoves(int r1, int c1, int r2, int c2) {
        if(r1 == r2 && c1 == c2) return 0;

        int sum = abs(r2 - r1) + abs(c2 - c1);
        if((sum & 0x01) == 1){
            return -1;
	}else if(abs(r2 - r1) == abs(c2 - c1)){
            return 1;
	}else{
            return 2;
	}
    }
};


<%:testing-code%>
   //Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
