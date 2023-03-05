#include <bits/stdc++.h>
using namespace std;

class mergeSortTree
{
    vector<vector<int>> t;
public:
    mergeSortTree(int n)
    {
        t.assign(n * 4 + 5, vector<int>());
    }
    void build(int v, int tl, int tr, vector<int> &a) 
    {
        if(tl == tr) {
            t[v] = {a[tl]};
            return;
        }
        int mid = (tl + tr) / 2;
        build(v * 2, tl, mid, a);
        build(v * 2 + 1, mid + 1, tr, a);
        
        merge(all(t[v * 2]), all(t[v * 2 + 1]), back_inserter(t[v]));
    }

    int ask(int v, int tl, int tr, int l, int r, int k)
    { 
        if (l > r) return 0;
        if (tl == l && r == tr) {
            return ub(all(t[v]), k) - t[v].begin();
        }
        int mid = (tl + tr) / 2;
        
        int left = ask(v * 2, tl, mid, l, min(mid, r), k);
        int right = ask(v * 2 + 1, mid + 1, tr, max(l, mid + 1), r, k);
        return left + right;
    }
};

int main(){}