#include <bits/stdc++.h>

using namespace std;

#define int long long

vector<int> a;
vector<int> t, op;

void build(int v, int tl, int tr) {
    if (tl + 1 == tr) {
        t[v] = a[tl];
        return;
    }
    int tm = (tl + tr) / 2;
    build(2 * v + 1, tl, tm);
    build(2 * v + 2, tm, tr);
    t[v] = t[2 * v + 1] + t[2 * v + 2];
}

void push(int v, int tl, int tr) {
    if (op[v] == 0)
        return;
    t[v] += (tr - tl) * op[v];
    if (tl + 1 != tr) {
        op[2 * v + 1] += op[v];
        op[2 * v + 2] += op[v];
    }
    op[v] = 0;
}

void update(int v, int tl, int tr, int l, int r, int x) {
    if (r <= tl || l >= tr) {
        push(v, tl, tr);
        return;
    }
    if (l <= tl && tr <= r) {
        op[v] += x;
        push(v, tl, tr);
        return;
    }
    push(v, tl, tr);
    int tm = (tl + tr) / 2;
    update(2 * v + 1, tl, tm, l, r, x);
    update(2 * v + 2, tm, tr, l, r, x);
    t[v] = t[2 * v + 1] + t[2 * v + 2];
}

int get(int v, int tl, int tr, int l, int r) {
    if (tr <= l || tl >= r)
        return 0;
    push(v, tl, tr);
    if (l <= tl && tr <= r)
        return t[v];
    int tm = (tl + tr) / 2;
    return get(2 * v + 1, tl, tm, l, r) + get(2 * v + 2, tm, tr, l, r);
}

signed main() {
    cin.tie(NULL); cout.tie(NULL); ios::sync_with_stdio(false);
    int n;
    cin >> n;
    a.resize(n);
    for (auto& x : a) {
        cin >> x;
    }
    t.resize(4 * n);
    op.resize(4 * n);
    build(0, 0, n);
    //update(0, 0, n, l - 1, r, x);
    //get(0, 0, n, i - 1, i);
    return 0;
}
