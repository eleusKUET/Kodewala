#include <bits/stdc++.h>
using namespace std;

struct EdmondKarp
{
	const int INF = 1e9 + 7;
	vector<vector<int>> graph;
	int N; // size of the graph, source = 0, sink = N + 1;
	vector<vector<int>> capacity;
	EdmondKarp(int n) : N(n) {
		graph.assign(N + 5, vector<int>());
		capacity.assign(N + 5, vector<int>(N + 5));
	}
	void addEdge(int u, int v, int cap) {
		graph[u].push_back(v);
		graph[v].push_back(u);
		capacity[u][v] = cap;
	};
	int bfs(int s, int t, vector<int> &parent) {
		fill(parent.begin(), parent.end(), -1);
		parent[s] = -2;
		queue<pair<int,int>> q;
		q.push({s, INF});
		while (q.size()) {
			auto [cur, flow] = q.front();
			q.pop();
			for (auto next : graph[cur]) {
				if (parent[next] == -1 && capacity[cur][next] > 0) {
					parent[next] = cur;
					int newflow = min(flow, capacity[cur][next]);
					if (next == t) return newflow;
					q.push({next, newflow});
				}
			}
		}
		return 0;
	}
	int maxflow(int s, int t) {
		int flow = 0;
		vector<int> parent(N + 5);
		int newflow;
		while(newflow = bfs(s, t, parent)) {
			flow += newflow;
			int cur = t;
			while (cur != s){
				int prev = parent[cur];
				capacity[prev][cur] -= newflow;
				capacity[cur][prev] += newflow;
				cur = prev;
			}
		}
		return flow;
	}
};

signed main()
{

}