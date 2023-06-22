#include <iostream>
#include <vector>

typedef long long ll;
std::vector<ll> prev, s;

void init(ll n) {
    prev.resize(n);
    for (ll i = 0; i < n; i++) prev[i] = i;
    s.resize(n, 1);
}

ll root(ll a) {
    return (a == prev[a] ? a : prev[a] = root(prev[a]));
}

void unite(ll a, ll b) {
    a = root(a); b = root(b);
    if (s[a] > s[b]) std::swap(a, b);
    s[b] += s[a];
    prev[a] = b;
}

int main() {
}
