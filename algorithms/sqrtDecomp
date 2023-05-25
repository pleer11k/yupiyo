#include <bits/stdc++.h>

using namespace std;

#define int long long

int n,k;

vector<int> a,b,op;

void upd(int l, int r, int x){
    int i = l;
    while(i <= r){
        if (i % k == 0 && i + k - 1 <= r){
            op[i/k]+=x;
            b[i/k]+=(k*x);
            i+=k;
        }
        else{
            a[i]+=x;
            b[i/k]+=x;
            ++i;
        }
    }
}

int get(int l, int r){
    int i = l;
    int ans = 0;
    while(i <= r){
        if (i % k == 0 && i + k - 1 <= r){
            ans+=b[i/k];
            i+=k;
        }
        else{
            ans+=a[i]+op[i/k];
            ++i;
        }
    }
    return ans;
}

signed main() {
    cin.tie(NULL); cout.tie(NULL); ios::sync_with_stdio(false); 
    cin>>n;
    a.resize(n);
    for(int i = 0; i < n;++i){
        cin>>a[i];
    }
    k = sqrt(n + .0f);
    b.resize(n/k); op.resize(n/k);
    for(int i = 0; i < n;++i){
        b[i/k]+=a[i];
    }
    //upd(--l,--r,x);
    //get(--l,--r);
    return 0;
}
