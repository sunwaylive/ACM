#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

#define LeftChild(root) ((root << 1) + 1)
#define RightChild(root) ((root << 1) + 2)

const int kMaxN = 100 + 10;

struct ScanLine {
    double x;
    double y1, y2;
    bool is_left;

    bool operator < (const ScanLine &other) const {
        return x < other.x;
    }
};

struct SegTreeNode {
    int start, end;
    double len;
    int cover;
};

double y[kMaxN << 1];               // 记录矩形横边的y轴的实际坐标
ScanLine g_scan_line[kMaxN << 1];   // 记录矩形纵边作为扫描线
SegTreeNode g_seg_tree[kMaxN << 3]; // 预先分配结点
int g_cnt = 0;

/*****************************************************/
void Build(int root, int start, int end) {
    if (start >= end) {
        // 无法形成区间
        return;
    } else if (start + 1 == end) {
        // 至少要形成一个区间
        g_seg_tree[root].start = start;
        g_seg_tree[root].end = end;
        g_seg_tree[root].len = 0;
        g_seg_tree[root].cover = 0;
        return;
    }

    //cout << "start: " << start << " end: " << end << endl;

    int mid = (start + end) >> 1;
    Build(LeftChild(root), start, mid);
    Build(RightChild(root), mid, end);
    g_seg_tree[root].start = start;
    g_seg_tree[root].end = end;
    g_seg_tree[root].len = 0;
    g_seg_tree[root].cover = 0;
}

// interval left inclusive, right outclusive, [,)
void UpdateLen(int root) {
    SegTreeNode *node = &g_seg_tree[root];
    if (node->start >= node->end) {
        // 不能形成区间
        node->len = 0;
    } else if (node->cover > 0) {
        node->len = y[node->end] - y[node->start];
    } else {
        node->len = g_seg_tree[LeftChild(root)].len + g_seg_tree[RightChild(root)].len;
    }
}

// 插入的是数组中的索引,当我们需要计算长度的时候，根据索引取出y坐标就好了
void Insert(int root, int insert_start, int insert_end) {
    SegTreeNode *node = &g_seg_tree[root];
    if (insert_start >= node->end || insert_end <= node->start) {
        return;
    }

    if (insert_start <= node->start && node->end <= insert_end) {
        node->cover++;
        UpdateLen(root);
        return;
    }

    int mid = (node->start + node->end) >> 1;
    Insert(LeftChild(root), insert_start, insert_end);
    Insert(RightChild(root), insert_start, insert_end);
    UpdateLen(root);
}

void Remove(int root, int remove_start, int remove_end) {
    SegTreeNode *node = &g_seg_tree[root];
    if (remove_start >= node->end || remove_end <= node->start) {
        return;
    }

    if (remove_start <= node->start && node->end <= remove_end) {
        node->cover--;
        UpdateLen(root);
        return;
    }

    int mid = (node->start + node->end) >> 1;
    Remove(LeftChild(root), remove_start, remove_end);
    Remove(RightChild(root), remove_start, remove_end);
    UpdateLen(root);
}

// 当调用这个函数的时候，y数组已经去重
// 在已排序数组中，找个 首个大于等于x的迭代器
// 在这里的作用是找到 某个点的y坐标对应在数组中的索引
int GetArrayIdx(double val) {
    return lower_bound(y, y + g_cnt, val) - y;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n = 0, c = 0;
    double x1, y1, x2, y2;
    while (scanf("%d", &n) == 1 && n != 0) {
        for (int i = 0; i < n; ++i) {
            scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
            // 保存矩形的左 右 纵边作为扫描线
            g_scan_line[2*i].x = x1;
            g_scan_line[2*i].y1 = y1;
            g_scan_line[2*i].y2 = y2;
            g_scan_line[2*i].is_left = true;

            g_scan_line[2*i+1].x = x2;
            g_scan_line[2*i+1].y1 = y1;
            g_scan_line[2*i+1].y2 = y2;
            g_scan_line[2*i+1].is_left = false;

            // 保存矩形上下横边的信息
            y[i*2] = y1;
            y[i*2+1] = y2;
        }

        // n个矩形，2n条纵边扫描线
        sort(g_scan_line, g_scan_line + 2*n);

        // y stores 矩形的横边的纵坐标
        sort(y, y+2*n);
        // g_cnt 矩形不重复的横边的数目
        g_cnt = unique(y, y+2*n) - y;
        //cout << "g_cnt: " << g_cnt << endl;

        // 去重 横边数目,线段树维护的是 当前扫描线的有效y轴长度
        Build(0, 0, g_cnt);
        //cout << "Build done!" << endl;

        double area = 0.0f;
        for (int i = 0; i < 2*n - 1; ++i) {
            // 如果是左边，则是插入事件
            if (g_scan_line[i].is_left) {
                // 线段树维护的是，扫描线的y轴长度
                // 离散化思想的体现：插入的是数组中的索引
                //printf("y1 idx: %d, y2 idx: %d\n", GetArrayIdx(g_scan_line[i].y1), GetArrayIdx(g_scan_line[i].y2));
                Insert(0, GetArrayIdx(g_scan_line[i].y1), GetArrayIdx(g_scan_line[i].y2));
                //cout << "after insert: " << g_seg_tree[0].len << endl;
            } else {
                //printf("y1 idx: %d, y2 idx: %d\n", GetArrayIdx(g_scan_line[i].y1), GetArrayIdx(g_scan_line[i].y2));
                Remove(0, GetArrayIdx(g_scan_line[i].y1), GetArrayIdx(g_scan_line[i].y2));
                //cout << "after remove: " << g_seg_tree[0].len << endl;
            }

            // g_seg_tree[0] 存储着当前情况下有效的y轴长度
            area += (g_scan_line[i+1].x - g_scan_line[i].x) * g_seg_tree[0].len;
        }

        printf("Test case #%d\n", ++c);
        printf("Total explored area: %.2f\n\n", area);
    }

    fclose(stdout);
    return 0;
}
