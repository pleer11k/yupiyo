#include "bits/stdc++.h"

using namespace std;

#define int long long

//O(N)

signed main() {
    int n; cin >> n;
    vector<int> a(n);
    for(int i = 0; i < n; ++i) cin >> a[i];
    a.push_back(0);
    
    int total = 0;
    stack<int> s;
    for(int i = 0; i <= n; ++i){
        while(!s.empty() && a[s.top()] > a[i]){
            int t = s.top();
            s.pop();
            int w;
            if (!s.empty()) w = i - s.top() - 1;
            else w=i;
            total = max(total ,1LL * w * a[t]);
        }
        s.push(i);
    }
    cout << total << endl;
    return 0;
}
