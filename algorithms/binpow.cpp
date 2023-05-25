//рекурсивно
int bpow(int a, int n){
    if (n == 0) return 1;
    if (n % 2 == 0) return bpow((a*a)%mod,n/2);
    else return (a * bpow(a,n-1))%mod;
}

//нерекурсивно
int bpow(int a, int n){
    int ans = 1;
    while(n){
        if (n % 2) ans = (a * ans)%mod;
        a = (a * a)%mod;
        n/=2;
    }
    return ans;
}
