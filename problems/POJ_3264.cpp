#include <algorithm>
#include <cstdio>

using namespace std;

const int kInf = 1e7;
const int kMaxN = 1e6;

struct SegTreeNode {
    SegTreeNode() : max(-kInf), min(kInf) {
    }

    int max, min;
};

int g_height[kMaxN];
SegTreeNode g_seg_tree[3 * kMaxN];

void Build(int root, int l, int r) {
    if (l >= r) return;

    if (l + 1 == r) {
        g_seg_tree[root].max = g_height[l];
        g_seg_tree[root].min = g_height[l];
        //printf("g_seg_tree[%d].max: %d, min: %d\n", root, g_seg_tree[root].max, g_seg_tree[root].min);
        return;
    }

    int mid = l + ((r - l) >> 1);
    Build(2*root+1, l, mid);
    Build(2*root+2, mid, r);
    g_seg_tree[root].max = max(g_seg_tree[2*root+1].max, g_seg_tree[2*root+2].max);
    g_seg_tree[root].min = min(g_seg_tree[2*root+1].min, g_seg_tree[2*root+2].min);
    //printf("g_seg_tree[%d].max: %d, min: %d\n", root, g_seg_tree[root].max, g_seg_tree[root].min);
}

void  Query(int root, int l, int r, int query_l, int query_r, int &max_val, int &min_val) {
    if (query_l >= r || query_r <= l) {
        return;
    } else if (query_l <= l && query_r >= r) {
        // 查询范围包含当前区间
        max_val = max(g_seg_tree[root].max, max_val);
        min_val = min(g_seg_tree[root].min, min_val);
        //printf("root: %d, l: %d, r: %d, max_val:%d, min_val:%d\n", root, l, r, max_val, min_val);
    } else {
        int mid = l + (r - l) / 2;
        // 查询区间在右边
        Query(2*root+1, l, mid, query_l, query_r, max_val, min_val);
        Query(2*root+2, mid, r, query_l, query_r, max_val, min_val);
    }
}

// min
/* int QueryMin(int root, int l, int r, int query_l, int query_r) {
    if (query_l >= r || query_r <= l) {
        return kInf;
    } else if (query_l <= l && query_r >= r) {
        // 查询范围包含当前区间
        return g_seg_tree[root].min;
    } else {
        int mid = l + (r - l) / 2;
        return min(QueryMin(2*root+1, l, mid, query_l, query_r),
                   QueryMin(2*root+2, mid, r, query_l, query_r));
    }
}
*/

int main() {
    //ifstream in("input.txt");
    //cin.rdbuf(in.rdbuf());
    freopen("input.txt", "r", stdin);
    int N = 0, Q = 0;
    while(scanf("%d %d", &N, &Q) != EOF) {
        for (int i = 0; i < N; ++i) {
            scanf("%d", &g_height[i]);
        }

        Build(0, 0, N);

        int ql = 0, qr = 0;
        for (int i = 0; i < Q; ++i) {
            scanf("%d %d", &ql, &qr);
            ql = ql - 1; // match interval
            int max_val = -kInf, min_val = kInf;
            Query(0, 0, N, ql, qr, max_val, min_val);

            printf("%d\n", max_val - min_val);
        }

        //in.close();
        return 0;
    }
}
