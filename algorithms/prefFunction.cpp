#include <bits/stdc++.h>

using namespace std;

#define int long long

signed main() {
    cin.tie(NULL); cout.tie(NULL); ios::sync_with_stdio(false);
    string s;
    cin>>s;
    int n = s.size();
    vector<int> p(n,0);
    for(int i = 1; i < n;++i){
        int prev = p[i-1];
        while (prev > 0 && s[i] != s[prev]){
            prev = p[prev-1];
        }
        if (s[i] == s[prev]){
            prev++;
        }
        p[i] = prev;
    }
    return 0;
}
