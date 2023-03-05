#include <bits/stdc++.h>
using namespace std;

class LCA 
{
public:
	vector<int> depth;
	vector<int> wdist;
	vector<vector<pair<int,int>>> graph;
	vector<int> sub;
	vector<vector<int>> up;
	int N;
	int LOG;
	LCA(int n) : N(n) {
		depth.assign(N + 5, 0);
		graph.assign(N + 5, vector<pair<int,int>>());
		sub.assign(N + 5, 0);
		wdist.assign(N + 5, 0);
		LOG = __lg(N) + 2;
		up.assign(N + 5, vector<int>(LOG));
	}
	void addEdge(int u, int v, int w = 1) {
		graph[u].push_back({v, w});
		graph[v].push_back({u, w});
	}
	void dfs(int u, int p = 0, int cost = 0) {
		sub[u] = 1;
		up[u][0] = p;
		depth[u] = depth[p] + 1;
		wdist[u] = cost;
		for (int i = 1; i < LOG; i++) {
			up[u][i] = up[up[u][i - 1]][i - 1];
		}
		for (auto [v, w] : graph[u]) {
			if (v != p) {
				dfs(v, u, cost + w);
				sub[u] += sub[v];
			}
		}
	}
	int lca(int u, int v) {
		if (depth[u] > depth[v]) swap(u, v);
		int dif = depth[v] - depth[u];
		for (int i = LOG - 1; i >= 0; i--) {
			if ((dif >> i) & 1) {
				v = up[v][i];
			}
		}
		if (u == v) return u;
		for (int i = LOG - 1; i >= 0; i--) {
			if (up[u][i] != up[v][i]) {
				u = up[u][i];
				v = up[v][i];
			}
		}
		return up[u][0];
	}
	int distance(int u, int v)
	{
		return depth[u] + depth[v] - 2 * depth[lca(u, v)];
	}
	int kth(int u, int k)
	{
		for (int i = LOG - 1; i >= 0; i--) {
			if ((k >> i) & 1) {
				u = up[u][i];
			}
		}
		return u;
	}
};

int main()
{

}