#include <bits/stdc++.h>
using namespace std;

int egcd(int a, int b, int &x, int &y)
{
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	int x1, y1;
	int g = egcd(b, a % b, x1, y1);
	x = y1;
	y = x1 - y1 * (a / b);
	return g; 
}

pair<int,int> chinese_remainder_theorem(vector<int> a, vector<int> m)
{
	if (a.size() != m.size()) return {-1, -1};
	int a1 = a[0];
	int m1 = m[0];
	for (int i = 1; i < a.size(); i++) {
		int a2 = a[i];
		int m2 = m[i];
		int g = __gcd(m1, m2);
		if(a1%g != a2%g) return {-1, -1};
		int p, q;
		egcd(m1, m2, p, q);
		int mod = m1 / g * m2; 
		int x = (__int128)((__int128)a1 * (m2/g) * q + a2 * (m1/ g) * p)%mod;
		a1 = x;
		if (a1 < 0) a1 += mod;
		m1 = mod;
	}
	return {a1, m1};
}

signed main()
{

}