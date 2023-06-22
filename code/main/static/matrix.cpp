#include <bits/stdc++.h>

using namespace std;

#define int long long

//O(N*M)

//5 6
//1 0 0 0 1 0
//0 0 0 0 1 0
//0 0 1 0 0 0
//0 0 0 0 0 0
//0 0 1 0 0 0
//ans = 9

signed main() {
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    vector<vector<int> > a(n,vector<int>(m)), dp(n,vector<int>(m));

    for (int i = 0; i < n; ++i) for(int j = 0; j < m;++j) cin >> a[i][j];

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j]) dp[i][j] = i;
            else if (!a[i][j] && !i) dp[i][j] = -1;
            else dp[i][j] = dp[i - 1][j];
        }
    }

    int mx = 0;
    vector<vector<int> > lm(n, vector<int>(m)), rm(n,vector<int>(m));
    for (int i = 0; i < n; ++i) {
        stack<int> s;
        for(int j = 0; j < m;++j){
            while(!s.empty() && dp[i][s.top()] <= dp[i][j]) s.pop();
            if (!s.empty()) lm[i][j] = s.top();
            else lm[i][j] = -1;
            s.push(j);
        }
        while(!s.empty()) s.pop();
        for(int j = m - 1; j >= 0;--j){
            while(!s.empty() && dp[i][s.top()] <= dp[i][j]) s.pop();
            if (!s.empty()) rm[i][j] = s.top();
            else rm[i][j] = m;
            s.push(j);
        }
        for(int j = 0; j < m;++j){
            int l = lm[i][j];
            int r = rm[i][j];
            mx = max(mx, (i-dp[i][j]) * (r-l-1));
        }
    }
    cout << mx << endl;
    return 0;
}
