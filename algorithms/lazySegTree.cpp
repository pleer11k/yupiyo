#include<bits/stdc++.h>

using namespace std;

#define int long long

constexpr int inf = 1e18;
constexpr int maxN = 2e14 + 2;

//прибавление и колво минимумов на отрезке

struct node {
    int v = 0, vl = 0, vr = maxN;
    int val = 0, add = 0, cnt = maxN;
    node *l = nullptr, *r = nullptr;

    node(int _v = 0, int _vl = 0, int _vr = maxN, int _val = 0) {
        v = _v; vl = _vl; vr = _vr; val = _val; cnt = vr - vl; add = 0;
    }

    void make() {
        if (l != nullptr || vr - vl == 1) return;
        int vm = (vl + vr) / 2;
        l = new node(v * 2 + 1, vl, vm, 0);
        r = new node(v * 2 + 2, vm, vr, 0);
    }

    void push() {
        if (add == 0) return;
        if (vr - vl == 1) {
            val += add;
            add = 0;
        } else {
            l->add += add;
            r->add += add;
            val += add;
            add = 0;
        }
    }

    void update(int ql, int qr, int d) {
        make();
        if (ql >= vr || vl >= qr) return;
        if (ql <= vl && vr <= qr) {
            add += d;
            push();
            return;
        }
        push();
        l->update(ql, qr, d);
        r->update(ql, qr, d);
        if (l->val + l->add < r->val + r->add) {
            val = l->val + l->add; cnt = l->cnt;
        } else if (l->val + l->add > r->val + r->add) {
            val = r->val + r->add; cnt = r->cnt;
        } else {
            val = l->val + l->add; cnt = l->cnt + r->cnt;
        }
    }

    pair<int, int> get(int ql, int qr) {
        make();
        if (ql >= vr || vl >= qr) return {inf, 0};
        push();
        if (ql <= vl && vr <= qr) return {val, cnt};
        auto lans = l->get(ql, qr);
        auto rans = r->get(ql, qr);
        if (lans.first < rans.first) return lans;
        if (lans.first > rans.first) return rans;
        return {lans.first, lans.second + rans.second};
    }
};

void print(node *t) {
    if (t == nullptr) return;
    cout << t->v << " ";
    print(t->l); print(t->r);
}

node *root = new node();

signed main() {
    cin.tie(NULL); cout.tie(NULL); ios::sync_with_stdio(false);
    //root->get(--l, r);
    //root->update(--l, r, x);
    return 0;
}
