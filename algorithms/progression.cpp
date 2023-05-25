//здесь нет деления, как в обычной формуле => работает для любого модуля

const int mod = 1'000'000'007;

int getsum(int a, int q, int n){
    if (n == 0) return 0;
    if (n == 1) return a%mod;
    if (n % 2 == 0)
        return (((pow(q,n/2)%mod + 1)%mod)*(getsum(a,q,n/2))%mod)%mod;
    else
        return (a*pow(q,n-1) + getsum(a,q,n-1)%mod)%mod;
}
