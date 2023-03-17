#include <bits/stdc++.h>
using namespace std;

mt19937 myrand(time(NULL));

long long powmod(long long a, long long p, long long m)
{
	long long result = 1;
	a %= m;
	while (p) {
		if (p & 1) result = (__int128) result * a % m;
		a = (__int128) a * a % m;
		p >>= 1;
	}
	return result;
}

bool check_composite(long long n, long long a, long long d, int s)
{
	long long x = powmod(a, d, n);
	if (x == 1 || x == n - 1) return false;
	for (int r = 1; r < s; r++) {
		x = (__int128) x * x % n;
		if (x == n - 1) return false;
	}
	return true;
}

bool millerRabin(long long n) 
{
	if (n < 2) return false;
	int r = 0;
	long long d = n - 1;
	while ((d & 1) == 0) {
		d >>= 1;
		r++;
	}
	for (int a : {2, 3, 5, 7, 11, 13, 19, 23, 29, 31, 37}) {
		if (n == a) return true;
		if (check_composite(n, a, d, r)) return false;
	}
	return true;
}

long long mult(long long a, long long b, long long mod)
{
	return (__int128) a * b % mod;
}

long long f(long long x, long long c, long long mod)
{
	return (mult(x, x, mod) + c)%mod;
}

long long rho(long long n)
{
	if (n%2 == 0) return 2;
	long long x = myrand()%n + 1, y = x, c = myrand()%n + 1, g = 1;
	while (g == 1) {
		x = f(x, c, n);
		y = f(y, c, n);
		y = f(y, c, n);
		g = __gcd(abs(x - y), n);
	}
	return g;
}

vector<long long> primes;

void prime_factorization(long long n)
{
	if (n == 1) return;
	if (millerRabin(n)) {
		primes.push_back(n);
		return;
	}
	long long x = n;
	while (x == n) x = rho(n);
	prime_factorization(x);
	prime_factorization(n / x);
}

void generate_divisor(vector<long long> primes, vector<long long> &divisors)
{
	sort(primes.begin(), primes.end());
	vector<pair<long long, long long>> pfreq;
	for (int i = 0, j; i < primes.size(); i = j) {
		j = i;
		while (j < primes.size() && primes[i] == primes[j]) j++;
		pfreq.push_back({primes[i], j - i});
	}
	divisors.push_back(1);

	for (auto [prime, count] : pfreq) {
		long long result = 1;
		vector<long long> temp;
		for (int i = 1; i <= count; i++) {
			result *= prime;
			for (auto d : divisors) {
				temp.push_back(d * result);
			}
		}
		for (auto d : temp) {
			divisors.push_back(d);
		}
	}
	sort(divisors.begin(), divisors.end());
}	

signed main()
{
	
}
