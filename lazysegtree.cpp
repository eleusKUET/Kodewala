#include <bits/stdc++.h>
using namespace std;

class segTree
{
    vector<int> tree;
    vector<int> lazy;
public:
    segTree(int n)
    {
        tree.assign(n * 4 + 5, 0);
        lazy.assign(n * 4 + 5, 0);
    }
    int rangeQuery(int v, int tl, int tr, int l, int r)
    {
        if (lazy[v] != 0) {
            if (tl != tr) {
                lazy[v * 2] += lazy[v];
                lazy[v * 2 + 1] += lazy[v];
            }
            tree[v] += lazy[v] * (tr - tl + 1);
            lazy[v] = 0;
        }
      
        if (l > tr || tl > r) return 0;
        if (l <= tl && tr <= r) {
            return tree[v];
        }
        int mid = (tl + tr) / 2;
        return rangeQuery(v * 2, tl, mid, l, r) + rangeQuery(v * 2 + 1, mid + 1, tr, l, r);
    }
    void rangeUpdate(int v, int tl, int tr, int l, int r, int x)
    {
        if (lazy[v] != 0) {
            if (tl != tr) {
                lazy[v * 2] += lazy[v];
                lazy[v * 2 + 1] += lazy[v];
            }
            tree[v] += lazy[v] * (tr - tl + 1);
            lazy[v] = 0;
        }
        if (l > tr || tl > r) return;
        if (l <= tl && tr <= r) {
            tree[v] += x * (tr - tl + 1);
            if (tl != tr) {
                lazy[v * 2] += x;
                lazy[v * 2 + 1] += x;
            }
            lazy[v] = 0;
            return;
        }
        int mid = (tl + tr) / 2;
        rangeUpdate(v * 2, tl, mid, l, r, x);
        rangeUpdate(v * 2 + 1, mid + 1, tr, l, r, x);
        tree[v] = tree[v * 2] + tree[v * 2 + 1];
    }
};

int main() {}