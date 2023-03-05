#include <bits/stdc++.h>
using namespace std;

class Dsu
{
public:
	vector<int> sz;
	vector<int> parent;
	Dsu(int n)
	{
		sz.assign(n + 5, 1);
		parent.assign(n + 5, 0);
		for (int i = 0; i <= n; i++) {
			parent[i] = i;
		}
	}
	int Find(int u)
	{
		return parent[u] == u? u : parent[u] = Find(parent[u]);
	}
	bool Union(int u, int v)
	{
		int a = Find(u), b = Find(v);
		if (a == b) return false;
		if (sz[a] < sz[b]) swap(a, b);
		sz[a] += sz[b];
		parent[b] = a; 
		return true;
	}
	int size_of(int u) 
	{
		return sz[Find(u)];
	}
};

int main()
{}