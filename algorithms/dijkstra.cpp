#include <bits/stdc++.h>

using namespace std;

#define int long long
#define inf ((int) 1e9 + 7)

signed main() {
    cin.tie(NULL); cout.tie(NULL); ios::sync_with_stdio(false);
    int n,m;
    cin>>n>>m;
    vector<vector<pair<int,int> > > g(n);
    for(int i = 0; i < m; ++i){
        int a,b,w; cin>>a>>b>>w; --a;--b;
        g[a].emplace_back(w,b);
        g[b].emplace_back(w,a);
    }
    int s,e;
    cin>>s>>e;
    vector<int> d(n, inf);
    d[s] = 0;
    set<pair<int,int> > q;
    q.insert({d[s],s});
    while(!q.empty()){
        int cur = (*(q.begin())).second;
        q.erase(q.begin());
        for(auto u:g[cur]){
            int to = u.second, len = u.first;
            if (d[cur] + len < d[to]){
                q.erase({d[to],to});
                d[to] = d[cur]+len;
                q.insert({d[to],to});
            }
        }
    }
    return 0;
}
