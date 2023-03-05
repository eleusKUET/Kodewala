#include <bits/stdc++.h>
using namespace std;

class BIT
{
	vector<int> tree;
	int n;
public:
	BIT(int sz, int val = 0) 
	{
		tree.assign(sz + 5, val);
		n = sz;
	}
	void update(int pos, int val)
	{
		while (pos <= n) {
			tree[pos] += val;
			pos += pos & -pos;
		}
	}
	void update(int l, int r, int val)
	{
		update(l, val);
		update(r + 1, -val);
	}
	int query(int l) 
	{
		int sum = 0;
		while (l > 0) {
			sum += tree[l];
			l -= l & -l;
		}
		return sum;
	}
	int query(int l, int r)
	{
		if (l > r) return 0;
		return query(r) - query(l - 1);
	}
};

signed main()
{
	
}