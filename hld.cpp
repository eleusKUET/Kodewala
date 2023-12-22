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

class HLD : public segTree
{
public:
    vector<vector<int>> graph;
    vector<int> parent;
    vector<int> depth;
    vector<int> heavy;
    vector<int> head;
    vector<int> pos;
    int cur_pos;
    int N;
    HLD(int _size) : segTree(_size, 0) {
        N = _size;
        parent.assign(N + 2, 0);
        depth.assign(N + 2, 0);
        heavy.assign(N + 2, -1);
        head.assign(N + 2, 0);
        pos.assign(N + 2, 0);
        graph.assign(N + 2, vector<int>());
        cur_pos = 0;
    }
    int merge(int u, int v) {return max(u, v);} // segment tree merge
    void addEdge(int u, int v) {
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int dfs(int v = 1) {
        int size = 1;
        int max_c_size = 0;
        for (auto c : graph[v]) {
            if (c != parent[v]) {
                parent[c] = v;
                depth[c] = depth[v] + 1;
                int c_size = dfs(c);
                size += c_size;
                if (c_size > max_c_size) {
                    max_c_size = c_size, heavy[v] = c;
                }
            }
        }
        return size;
    }
    void decompose(int v = 1, int h = 1) {
        head[v] = h;
        pos[v] = ++cur_pos;
        if (heavy[v] != -1) {
            decompose(heavy[v], h);
        }
        for (auto c : graph[v]) {
            if (c != parent[v] && c != heavy[v]) {
                decompose(c, c);
            }
        }
    }
    int query(int a, int b) {
        int res = 0;
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] > depth[head[b]]) {
                swap(a, b);
            }
            int cur_heavy_path_max = segTree::query(1, 1, N, pos[head[b]], pos[b]);
            res = merge(res, cur_heavy_path_max);
        }
        if (depth[a] > depth[b])
            swap(a, b);
        int last_heavy_path_max = segTree::query(1, 1, N, pos[a], pos[b]);
        return merge(res, last_heavy_path_max);
    }
    void update(int u, int val) {
        segTree::update(1, 1, N, pos[u], val);
    }
    int lca(int a, int b) {
        for (; head[a] != head[b]; b = parent[head[b]]) {
            if (depth[head[a]] > depth[head[b]]) {
                swap(a, b);
            }
        }
        if (depth[a] > depth[b])
            swap(a, b);
        return a;
    }
};

signed main()
{
    
}