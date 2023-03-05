#include <bits/stdc++.h>
using namespace std;

class SparseTable
{
public:
	int n;
	vector<vector<int>> table;
	int limit;
	vector<int> lg;
	SparseTable(int _n) {
		n = _n;
		limit = __lg(n) + 2;
		lg.assign(n + 5, 0);
		table.assign(n + 5, vector<int>(limit));
		for (int i = 2; i <= n; i++) {
			lg[i] = lg[i / 2] + 1;
		}
	}
	virtual int merge(int u, int v) = 0;
	void build(const vector<int> &a) {
		for (int i = 0; i < n; i++) {
			table[i][0] = a[i];
		}
		for (int j = 1; j < limit; j++) {
			for (int i = 0; i + (1<<j) <= n; i++) {
				table[i][j] = merge(table[i][j - 1], table[i + (1<<(j - 1))][j - 1]);
			}
		}
	}
	int query(int l, int r) {
		int len = lg[r - l + 1];
		int ans = merge(table[l][len], table[r - (1<<len) + 1][len]);
		return ans;
	}
};

class Min : public SparseTable
{
public:
	Min(int n) : SparseTable(n) {};
	int merge(int u, int v) {return min(u, v);}
};

class Max : public SparseTable
{
public:
	Max(int n) : SparseTable(n){}
	int merge(int u, int v) {return max(u, v);}
};

signed main()
{

}