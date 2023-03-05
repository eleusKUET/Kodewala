#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

long long add(long long a, long long b)
{	
	long long res = a + b; res %= mod;
	if (res < 0) res += mod;
    return res;
}

long long mul(long long a, long long b)
{
	long long res = (a * b) % mod;
	if (res < 0) res += mod;
	return res;
}

long long modpow(long long a, long long b)
{
	if (b == 0) return 1%mod;
	long long u = modpow(a, b / 2);
	u = mul(u, u);
	if (b & 1) u = mul(u, a);
	return u;
}

struct Combi {
	vector<int> facts;
	vector<int> invs;
	vector<int> finvs;
	int sz;
	Combi(int n) {
		sz = n;
		facts.assign(n + 5, 0);
		invs.assign(n + 5, 0);
		finvs.assign(n + 5, 0);
		facts[0] = finvs[0] = invs[1] = 1;
		for (int i = 2; i <= n; i++) invs[i] = add(mod, -mul(mod / i, invs[mod%i]));
		for (int i = 1; i <= n; i++) {
			facts[i] = mul(facts[i - 1], i);
			finvs[i] = mul(finvs[i - 1], invs[i]);
		}
	}
	inline int fact(int n){return facts[n];}
	inline int inv(int n) {return invs[n];}
	inline int finv(int n){return finvs[n];}
	inline int ncr(int n, int r){return mul(facts[n], mul(finvs[r], finvs[n - r]));}
};

signed main()
{
	
}