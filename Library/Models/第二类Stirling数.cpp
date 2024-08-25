#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace MODULE{
    ll MOD = 167772161;
    inline ll Get_Mod(ll x,ll mod=MOD){
        if(x<0) return x-x/mod*mod+mod;
        else return x-x/mod*mod;
    }
    ll qcpow(ll a,ll b,ll p=MOD){ll ret=1;a=Get_Mod(a);for (;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p;return ret;}
    ll inv(ll a,ll p=MOD){return qcpow(a,p-2,p);}

    inline ll add(ll a,ll b){return Get_Mod(a+b);}
    inline ll sub(ll a,ll b){return Get_Mod(a-b);}
    inline ll mul(ll a,ll b){return Get_Mod(a*b);}

    void addto(ll &a,ll b){a=Get_Mod(a+b);}
    void subto(ll &a,ll b){a=Get_Mod(a-b);}
    void multo(ll &a,ll b){a=Get_Mod(a*b);}

    vector<ll> Fac;
    void Prepare_Factorial(ll n){Fac.resize(n+1);Fac[0]=1;for(ll i=1;i<=n;i++) Fac[i]=mul(Fac[i-1],i);}
    inline ll C(ll n,ll m){return n<m?0:mul(Fac[n],inv(mul(Fac[m],Fac[n-m])));}
} using namespace MODULE;

//第二类Stirling数，表示表示把n个不同元素划分成m个集合（不能有空集）复杂度O(mlogn)
ll Get_Stirling(ll n,ll m){
    ll ans=0;
    if(n<m) return 0;
    for(ll i=0;i<=m;i++){
        ll t=mul(C(m,i),qcpow(m-i,n));
        if((m-i)&1) t=MOD-t;
        addto(ans,t);
    }return ans;
}