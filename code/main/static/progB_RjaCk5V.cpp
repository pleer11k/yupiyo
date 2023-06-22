#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <cstdio>
#include <map>
#include <set>
#include <queue>
#include <random>
#include <unordered_map>
#include <fstream>
#include <memory.h>
using namespace std;

#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

constexpr long long inf = 1e9;

int n;
vector<int> a;

struct node {
    int val = 0;
    int vl = 0, vr = n;
    node *l = nullptr, *r = nullptr;

    node(int vl, int vr): vl(vl), vr(vr) {}
    node(int val, int vl, int vr, node *l, node *r): val(val), vl(vl), vr(vr), l(l), r(r) {}

    void build() {
        if (vr - vl == 1) {
            val = 0;
            return;
        }
        int vm = (vl + vr) / 2;
        l = new node(vl, vm);
        r = new node(vm, vr);
        l->build();
        r->build();
        val = l->val + r->val;
    }

    int get(int tl, int tr) {
        if (tl >= vr || vl >= tr) return 0;
        if (tl <= vl && vr <= tr) return val;
        return l->get(tl, tr) + r->get(tl, tr);
    }

    void update(int p) {
        if (vr - vl == 1) {
            val = 1;
            return;
        }
        int vm = (vl + vr) / 2;
        if (p < vm) {
            l = new node(l->val, l->vl, l->vr, l->l, l->r);
            l->update(p);
        } else {
            r = new node(r->val, r->vl, r->vr, r->l, r->r);
            r->update(p);
        }
        val = l->val + r->val;
    }

    int down(int k, node *p) {
        if (val < k) return inf;
        if (vr - vl == 1) return vr;
        if (l->val - p->l->val >= k) return l->down(k, p->l);
        else return r->down(k - (l->val - p->l->val), p->r);
    }
};

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n;
    a.resize(n);
    map<int, int> z, b;
    for (int i = 0; i < n; i++) {
        cin >> a[i]; z[a[i]] = 1; // все элементы a - попарно различные
    }
    int cur = 0;
    for (auto& el : z) {
        el.second = cur; b[cur] = el.first;
        cur++;
    }
    for (auto& el : a) el = z[el];
    
    vector<node *> forest = {new node(0, 0, n, nullptr, nullptr)};
    forest[0]->build();
    
    for (int i = 0; i < n; i++) {
        node *p = forest.back();
        node *plant = new node(p->val, p->vl, p->vr, p->l, p->r);
        plant->update(a[i]);
        forest.push_back(plant);
    }

    int q; cin >> q;
    while (q --> 0) {
        int l, r, k; // k-тое по возрастанию число на отрезке [l, r]. l, r = [1, n]
        cin >> l >> r >> k; l--;
        cout << b[forest[r]->down(k, forest[l]) - 1] << endl; // спуск возвращает сжатое значение + 1
    }
}