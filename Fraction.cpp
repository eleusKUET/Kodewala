#include <bits/stdc++.h>
using namespace std;

class frac
{
public:
    long long up, down;
    frac() {}
    frac(long long u, long long d = 1) {
        up = u; down = d; long long g = __gcd(abs(u), abs(d));
        up /= g, down /= g; 
        if (up == 0) down = abs(down); 
        if (down < 0) up = -up, down = -down;
    }
    frac &operator=(long long a){frac tmp(a); up = tmp.up, down = tmp.down; return tmp;}
    frac operator+(frac a) {return frac(up * a.down + down * a.up, a.down * down);}
    frac operator-(frac a) {return frac(up * a.down - down * a.up, a.down * down);}
    frac operator*(frac a) {return frac(up * a.up, down * a.down);}
    frac operator/(frac a) {return frac(up * a.down, down * a.up);}
    frac &operator+=(frac &a) {frac res = frac(up * a.down + down * a.up, a.down * down); this->up = res.up; this->down = res.down; return *this;}
    frac &operator-=(frac &a) {frac res = frac(up * a.down - down * a.up, a.down * down); this->up = res.up; this->down = res.down; return *this;}
    frac &operator*=(frac &a) {frac res = frac(up * a.up, down * a.down); this->up = res.up; this->down = res.down; return *this;}
    frac &operator/=(frac &a) {frac res = frac(up * a.down, down * a.up); this->up = res.up; this->down = res.down; return *this;}
    string out() {if (up == 0) return "0"; if (down == 1) return to_string(up); return to_string(up) + "/" + to_string(down);}
    bool operator<(const frac a) const {return up * a.down < down * a.up;}
    bool operator<=(const frac a) const {return up * a.down <= down * a.up;}
    bool operator>(const frac a) const {return up * a.down > down * a.up;}
    bool operator>=(const frac a) const {return up * a.down >= down * a.up;}
    bool operator==(const frac a) const {return up * a.down == down * a.up;}
    bool operator!=(const frac a) const {return !(*this == a);}
    friend frac min(frac a, frac b) {return a <= b ? a : b;}
    friend frac max(frac a, frac b) {return a >= b ? a : b;}
};


signed main(){
    frac a(0, 5), b(1, 2);
    cout << (a + b).out();
}