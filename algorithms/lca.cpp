#include <bits/stdc++.h>

using namespace std;

#define int long long

constexpr int t = 29;
int n;
vector<vector<int>> gr, bins;
vector<int> d;

void dfs(int v, int p) {
    for (int to : gr[v]) {
        if (to != p) {
            d[to] = d[v] + 1;
            bins[0][to] = v;
            dfs(to, v);
        }
    }
}

int lca(int a, int b) {
    if (d[a] != d[b]) {
        if (d[b] > d[a]) swap(a, b);
        int dif = d[a] - d[b];
        for (int i = 0; i < t; i++) {
            if (dif & (1 << i)) a = bins[i][a];
        }
    }
    if (a == b) return a;
    for (int lt = t - 1; lt >= 0; lt--) {
        if (bins[lt][a] != bins[lt][b]) {
            a = bins[lt][a];
            b = bins[lt][b];
        }
    }
    return bins[0][a];
}

signed main() {
    cin.tie(NULL); cout.tie(NULL); ios::sync_with_stdio(false);
    cin >> n;
    gr.assign(n, vector<int> ());
    bins.assign(t, vector<int> (n, -1));

    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        gr[--u].push_back(--v);
        gr[v].push_back(u);
    }
    d.assign(n, 0);
    dfs(0, -1);

    for (int i = 1; i < t; i++) {
        for (int j = 0; j < n; j++) {
            if (bins[i - 1][j] == -1) bins[i][j] = -1;
            else bins[i][j] = bins[i - 1][bins[i - 1][j]];
        }
    }
    return 0;
}
