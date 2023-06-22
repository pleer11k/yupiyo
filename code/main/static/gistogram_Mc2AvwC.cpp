#include bitsstdc++.h

using namespace std;

#define int long long
наибольший по площади подпрямоугольник в гистограмме

встречался на муниципе регионов

O(N)

signed main() {
    int n;cinn;
    vectorint a(n);
    for(int i = 0; i  n;++i) cina[i];
    a.push_back(0);

    int total = 0;
    stackint s;
    for(int i = 0; i = n;++i){
        while(!s.empty() && a[s.top()]  a[i]){
            int t = s.top();
            s.pop();
            int w;
            if (!s.empty())
                w=i-s.top()-1;
            else
                w=i;
            total=max(total ,1llwa[t]);
        }
        s.push(i);
    }
    couttotalendl;
    return 0;
}
