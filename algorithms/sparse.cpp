#include <bits/stdc++.h>

using namespace std;

#define int long long

int n;

vector<int> a;
vector<vector<int> > s;

void build(){
    for(int i = 0; i < n;++i){
        s[0][i] = a[i];
    }
    for(int k = 1; (1ll<<k) <= n;++k){
        int len = (1ll<<k);
        for(int i = 0; i + len <= n;++i){
            s[k][i] = min(s[k-1][i],s[k-1][i+(1<<(k-1))]);
        }
    }
}

int get_min(int l, int r){
    int t = (int)log2(r-l+1);
    return min(s[t][l],s[t][r-(1<<t)+1]);
}

signed main() {
    cin.tie(NULL); cout.tie(NULL); ios::sync_with_stdio(false);
    cin>>n;
    a.resize(n);
    s.resize((int)log2(n) + 1);
    for(auto &x:s){
        x.resize(n);
    }
    for(auto &x:a){
        cin>>x;
    }
    build();
    //get_min(--l,--r)
    return 0;
}
