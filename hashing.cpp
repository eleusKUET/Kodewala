#include <bits/stdc++.h>
using namespace std;

struct simpleHash {
	long long base, mod, invbase;
	vector<long long> hval, rhval, power, invpow;
	simpleHash(){}
	simpleHash(long long b, long long m) {
		base = b; mod = m;
		power.push_back(1);
		invpow.push_back(1);
		invbase = modpow(base, mod - 2);
	}
	inline long long add(long long a, long long b) {return (a + b + mod)%mod;}
	inline long long mul(long long a, long long b) {return (a * b)%mod;}
	inline long long modpow(long long a, long long b) {
		 if (b == 0) return 1%mod;
		 long long u = modpow(a, b / 2);
		 u = mul(u, u);
		 return (b & 1) ? mul(u, a) : u;
	}
	void add(char ch) {
		long long item = (long long) ch;
        if (hval.empty()) hval.push_back(item);
        else hval.push_back(add(hval.back(), mul(item, power[hval.size()])));
        power.push_back(mul(power.back(), base));
        invpow.push_back(mul(invpow.back(), invbase));
        if (rhval.empty()) rhval.push_back(item);
        else rhval.push_back(add(item, mul(base, rhval.back())));
	}
	void compute(const string &s) {
		for (auto item : s) {
			add(item);
		}
	}
	long long rangehash(int l, int r) {
		l--; r--;
		if (l == 0) return hval[r];
		return mul(add(hval[r], - hval[l - 1]), invpow[l]);
	}
	long long rrangehash(int l, int r) {
		l--; r--;
		if (l == 0) return rhval[r];
		return add(rhval[r], - mul(rhval[l - 1], power[l - 1]));
	}
};

struct doubleHash {
	simpleHash sh1, sh2;
	doubleHash() {
		sh1 = simpleHash(151, 1e9 + 9);
		sh2 = simpleHash(197, 1e9 + 7);
	}
	void add(char ch) {
		sh1.add(ch);
		sh2.add(ch);
	}
	void compute(const string &s) {
		sh1.compute(s);
		sh2.compute(s);
	}
	long long rangehash(int l, int r) {
		long long res = sh1.rangehash(l, r);
		res <<= 32;
		res ^= sh2.rangehash(l, r);
		return res;
	}
	long long rrangehash(int l, int r) {
		long long res = sh1.rrangehash(l, r);
		res <<= 32;
		res ^= sh2.rrangehash(l, r);
		return res;
	}
};

class hashing 
{
public:
	vector<long long> t[2], pw[2], ipw[2];
	const long long base1 = 151, mod1 = 1e9 + 9, base2 = 197, mod2 = 1e9 + 7;
	int n;
	inline long long add(long long a, long long b, long long mod) {return (a + b + mod)%mod;}
	inline long long mul(long long a, long long b, long long mod) {return (a * b)%mod;}
	inline long long modpow(long long a, long long b, long long mod) {
		 if (b == 0) return 1%mod;
		 long long u = modpow(a, b / 2, mod);
		 u = mul(u, u, mod);
		 return (b & 1) ? mul(u, a, mod) : u;
	}
	hashing(int _n) : n(_n) {
		t[0].assign(n * 4 + 5, 0LL);
		t[1].assign(n * 4 + 5, 0LL);
		pw[0].assign(n + 5, 0LL);
		ipw[0].assign(n + 5, 0LL);
		pw[1].assign(n + 5, 0LL);
		ipw[1].assign(n + 5, 0LL);
		pw[0][0] = pw[1][0] = 1;
		ipw[0][0] = ipw[1][0] = 1;
		long long invbase1, invbase2;
		invbase1 = modpow(base1, mod1 - 2, mod1);
		invbase2 = modpow(base2, mod2 - 2, mod2);
		for (int i = 1; i <= n; i++) {
			pw[0][i] = mul(pw[0][i - 1], base1, mod1);
			pw[1][i] = mul(pw[1][i - 1], base2, mod2);
			ipw[0][i] = mul(ipw[0][i - 1], invbase1, mod1);
			ipw[1][i] = mul(ipw[1][i - 1], invbase2, mod2);
		}
	}
	void build(int v, int tl, int tr, const vector<int> &a)
	{
		if (tl == tr) {
			t[0][v] = mul(pw[0][tl], a[tl], mod1);
			t[1][v] = mul(pw[1][tl], a[tl], mod2);
			return;
		}
		int mid = (tl + tr) / 2;
		build(v * 2, tl, mid, a);
		build(v * 2 + 1, mid + 1, tr, a);
		t[0][v] = add(t[0][v * 2], t[0][v * 2 + 1], mod1);
		t[1][v] = add(t[1][v * 2], t[1][v * 2 + 1], mod2);
	}
	void update(int v, int tl, int tr, int pos, int val)
	{
		if (tl == tr) {
			t[0][v] = mul(pw[0][tl], val, mod1);
			t[1][v] = mul(pw[1][tl], val, mod2);
			return;
		}
		int mid = (tl + tr) / 2;
		if (mid >= pos) {
			update(v * 2, tl, mid, pos, val);
		}
		else {
			update(v * 2 + 1, mid + 1, tr, pos, val);
		}
		t[0][v] = add(t[0][v * 2], t[0][v * 2 + 1], mod1);
		t[1][v] = add(t[1][v * 2], t[1][v * 2 + 1], mod2);
	}
	pair<int,int> query(int v, int tl, int tr, int l, int r)
	{
		if (l > r) return {0,0};
		if (tl == l && r == tr) {
			return {t[0][v], t[1][v]};
		}
		int mid = (tl + tr) / 2;
		auto left = query(v * 2, tl, mid, l, min(r, mid));
		auto right = query(v * 2 + 1, mid + 1, tr, max(l, mid + 1), r);
		return {add(left.first, right.first, mod1), add(left.second, right.second, mod2)};
	}
	int get_hash(int l, int r) {
		auto ask = query(1, 1, n, l, r);
		ask.first = mul(ask.first, ipw[0][l - 1], mod1);
		ask.second = mul(ask.second, ipw[1][n - r], mod2);
		return (ask.first << 32) | ask.second;
	}
};

const int mod1 = 1e9 + 7;
const int base1 = 151;
const int base2 = 197;
int mod2 = 1e9 + 9;
int add(int a, int b, int mod) 
{
  return ((a + b)%mod + mod)%mod;
}
int mul(int a, int b, int mod)
{
  return ((a * b)%mod + mod)%mod;
}
int modpow(int a, int b, int mod)
{
  if (b == 0) return 1%mod;
  int u = modpow(a, b / 2, mod);
  u = mul(u, u, mod);
  if (b & 1) u = mul(u, a, mod);
  return u;
}

signed main()
{

}