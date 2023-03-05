#include <bits/stdc++.h>
using namespace std;

class segTree 
{
public:
    vector<int> tree;
    int n;
    int default_val;
    segTree(int _n, int val) {
        n = _n;
        default_val = val;
        tree.assign(n * 4 + 5, default_val);
    }
    virtual int merge(int u, int v) = 0;
    void update(int v, int tl, int tr, int pos, int val)
    {
        if (tl == tr) {
            tree[v] = val;
            return;
        }
        int mid = (tl + tr) / 2;
        if (pos <= mid) update(v * 2, tl, mid, pos, val);
        else update(v * 2 + 1, mid + 1, tr, pos, val);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }
    int query(int v, int tl, int tr, int l, int r) 
    {
        if (l > r) return default_val;
        if (l == tl && r == tr) {
            return tree[v];
        }
        int mid = (tl + tr) / 2;
        int left = query(v * 2, tl, mid, l, min(r, mid));
        int right = query(v * 2 + 1, mid + 1, tr, max(l, mid + 1), r);
        return merge(left, right);
    }
};

class Min : public segTree
{
public:
    Min(int n) : segTree(n, 1e9){} 
    int merge(int u, int v) {return min(u, v);}
};

class Sum : public segTree
{
public:
    Sum(int n) : segTree(n, 0){} 
    int merge(int u, int v) {return u + v;}
};

struct node {
    int left, right, balance;
    node(){left = right = balance = 0;}
    node(int a, int b, int c) {left = a, right =  b, balance = c;}
};

class CustomSegtree 
{
public:
    int n;
    vector<node> tree;
    CustomSegtree(int _n) : n(_n) {
        tree.assign(n * 4 + 5, node());
    }
    node merge(node u, node v)
    {
        node res;
        res.balance = u.balance + v.balance;
        int mn = min(u.left, v.right);
        res.balance += mn;
        u.left -= mn;
        v.right -= mn;
        res.left = u.left + v.left;
        res.right = u.right + v.right;
        return res;
    }
    node make_data(char val) {
        node res;
        if(val == '(') res.left = 1;
        else if (val == ')') res.right = 1;
        return res;
    }
    void update(int v, int tl, int tr, int pos, char val)
    {
        if (tl == tr) {
            tree[v] = make_data(val);
            return;
        }
        int mid = (tl + tr) / 2;
        if (pos <= mid) update(v * 2, tl, mid, pos, val);
        else update(v * 2 + 1, mid + 1, tr, pos, val);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }
    node query(int v, int tl, int tr, int l, int r) 
    {
        if (l > r) return make_data(' ');
        if (l == tl && r == tr) {
            return tree[v];
        }
        int mid = (tl + tr) / 2;
        node left = query(v * 2, tl, mid, l, min(r, mid));
        node right = query(v * 2 + 1, mid + 1, tr, max(l, mid + 1), r);
        return merge(left, right);
    }
};

signed main()
{
    Min s(5);
    s.update(1, 1, 5, 1, 5);
}