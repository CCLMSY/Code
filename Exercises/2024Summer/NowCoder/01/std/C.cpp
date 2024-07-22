#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=500005;
const int Mod=1000000007;
int a[MAXN];
int main()
{
    int n=0,q;
    scanf("%d",&q);
    ll res=0;
    while(q--)
    {
        int t,v;
        scanf("%d%d",&t,&v);
        while(t--)res=(res-1LL*n*a[n]%Mod+Mod)%Mod,--n;
        a[++n]=v;
        res=(res+1LL*n*a[n]%Mod)%Mod;
        printf("%lld\n",res);
    }
    return 0;
}

