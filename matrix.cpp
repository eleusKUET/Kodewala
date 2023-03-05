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

struct Matrix
{
    int sz;
    vector<vector<int>> mat;
    Matrix(int sz_) {
        sz = sz_;
        mat = vector<vector<int>>(sz, vector<int>(sz));
    }
    void toOne() {
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                mat[i][j] = (int)(i == j);
    }
    Matrix multiply(const Matrix &a, const Matrix &b) {
        Matrix res(sz);
        for (int i = 0; i < sz; i++)
            for (int j = 0; j < sz; j++)
                for (int k = 0; k < sz; k++)
                    res.mat[i][k] = add(res.mat[i][k], mul(a.mat[i][j], b.mat[j][k]));
        return res;
    }
    Matrix modpow(Matrix a, int b) {
        if (b == 0) {a.toOne(); return a;}
        Matrix u = modpow(a, b / 2);
        u = multiply(u, u);
        if (b & 1) u = multiply(u, a);
        return u;
    }
};

int main(int argc, char const *argv[])
{
    
    return 0;
}