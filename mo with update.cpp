#include <bits/stdc++.h>
// #include "debug.h"
using namespace std;

//1 indexed
//Complexity:$O(S\times Q+Q\times \frac{N^2}{S^2})$
//S = (2*n^2)^(1/3)
const int block_size = 2720;  // 4310 for 2e5
const int mx = 1e5 + 5;

int a[mx], n, cnt[2 * mx];
int ans[mx];

const int buck = 320;
int tab[buck + 5];
int mark[buck * buck + 5];

int getAns()
{
    int id = -1;
    for (int i = 0; i < buck; i++) {
        if (tab[i] == buck) continue;
        id = i;
        break;
    }
    assert(id != -1);
    // debug(id);
    // for (int i = 0; i < n; i++) {
        // debug(i, mark[i]);
    // }
    for (int i = id * buck; i < (id + 1) * buck; i++) {
        if (mark[i]) continue;
        // debug(i);
        return i;
    }
    assert(false);
}

struct Query {
  int L, R, T, id;
  Query() {}
  Query(int _L, int _R, int _T, int _id) : L(_L), R(_R), T(_T), id(_id) {}
  bool operator<(const Query &x) const {
    if (L / block_size == x.L / block_size) {
      if (R / block_size == x.R / block_size) return T < x.T;
      return R / block_size < x.R / block_size;
    }
    return L / block_size < x.L / block_size;
  }
} Q[mx];
struct Update {
  int pos;
  int old, cur;
  Update(){};
  Update(int _p, int _o, int _c) : pos(_p), old(_o), cur(_c){};
} U[mx];

inline void add(int id) {
    int prv = cnt[a[id]];
    // debug(id, a[id], prv);
    if (prv) {
        mark[prv]--;
        if (mark[prv] == 0) tab[prv / buck]--;
    }
    cnt[a[id]]++;
    int now = cnt[a[id]];
    mark[now]++;
    if (mark[now] == 1) {
        tab[now / buck]++;
    }
}
inline void remove(int id) {
    int prv = cnt[a[id]];
    if (prv) {
        mark[prv]--;
        if (mark[prv] == 0) tab[prv / buck]--;
    }
    cnt[a[id]]--;
    if (cnt[a[id]] > 0) {
        int now = cnt[a[id]];
        mark[now]++;
        if (mark[now] == 1) {
            tab[now / buck]++;
        }
    }
}
inline void update(int id, int L, int R) {
    if(U[id].pos >= L && U[id].pos <= R){
        int prv = cnt[U[id].old];
        if (prv) {
            mark[prv]--;
            if (mark[prv] == 0) tab[prv / buck]--;
        }
        cnt[U[id].old]--;
        if (cnt[U[id].old]) {
            int now = cnt[U[id].old];
            mark[now]++;
            if (mark[now] == 1) {
                tab[now / buck]++;
            }
        }
        prv = cnt[U[id].cur];
        if (prv) {
            mark[prv]--;
            if (mark[prv] == 0) tab[prv / buck]--;
        }
        cnt[U[id].cur]++;
        int now = cnt[U[id].cur];
        mark[now]++;
        if (mark[now] == 1) {
            tab[now / buck]++;
        }
    }
    a[U[id].pos] = U[id].cur;
}
inline void undo(int id, int L, int R) {
    if(U[id].pos >= L && U[id].pos <= R){
        int prv = cnt[U[id].cur];
        if (prv) {
            mark[prv]--;
            if (mark[prv] == 0) tab[prv / buck]--;
        }
        cnt[U[id].cur]--;
        if (cnt[U[id].cur] > 0) {
            int now = cnt[U[id].cur];
            mark[now]++;
            if (mark[now] == 1) {
                tab[now / buck]++;
            }
        }
        prv = cnt[U[id].old];
        if (prv) {
            mark[prv]--;
            if (mark[prv] == 0) tab[prv / buck]--;
        }
        cnt[U[id].old]++;
        int now = cnt[U[id].old];
        mark[now]++;
        if (mark[now] == 1) {
            tab[now / buck]++;
        }
    }
    a[U[id].pos] = U[id].old;
}


void MO(int nq, int nu) {
  sort(Q + 1, Q + nq + 1);
  int L = 1, R = 0, T = nu;
  for (int i = 1; i <= nq; i++) {
    Query q = Q[i];
    while (T < q.T) update(++T, L, R);
    while (T > q.T) undo(T--, L, R);
    while (L > q.L) add(--L);
    while (R < q.R) add(++R);
    while (L < q.L) remove(L++);
    while (R > q.R) remove(R--);
    ans[q.id] = getAns();
  }
}


int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int m;
    cin >> n >> m;

    // vector<int> a(n + 1);
    unordered_map<int,int> compress;
    int now = 0;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (compress[a[i]] == 0) compress[a[i]] = ++now;
        a[i] = compress[a[i]];
    }
    // debug(a);
    int nu = 0;
    int nq = 0;
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            Q[++nq] = Query(l, r, nu, nq);
        }
        else {
            int p, x;
            cin >> p >> x;
            if (compress[x] == 0) compress[x] = ++now;
            x = compress[x];
            U[++nu] = Update(p, a[p], x);
            a[p] = x;
        }
    }

    mark[0]++;
    tab[0]++;

    MO(nq, nu);

    for (int i = 0; i < nq; i++) {
        cout << ans[i] << "\n";
    }
}