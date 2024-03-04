#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FORLL(i,l,r) for(ll i=l;i<=r;i++)

namespace MOLDULE
{
    const long long MOD=1e9+7;
    #define Get_Mod(a) (((a)+MOD)%MOD)
    ll qcpow(ll x, ll b)
    {
        ll ret = 1;
        x = Get_Mod(x);
        for (; b; b >>= 1, x = 1ll * x * x % MOD)
            if (b & 1)
                ret = Get_Mod(1ll * ret * x);
        return ret;
    }
    inline ll inv(ll x) {return qcpow(x,MOD-2);}
    inline ll add(ll x, ll y) {return Get_Mod(x + y);}
    inline ll addto(ll &x, ll y) {return x = add(x, y);}
    inline ll sub(ll x, ll y) {return Get_Mod(x - y);}
    inline ll subto(ll &x, ll y) {return x = sub(x, y);}
    inline ll mul(ll x, ll y) {return Get_Mod(1ll*x * y);}
    inline ll multo(ll &x, ll y) {return x = mul(x, y);}
    inline ll mdiv(ll x, ll y) {return Get_Mod(1ll*x*inv(y));} 
    inline ll mdivto(ll &x, ll y) {return x = mdiv(x, y);}
}using namespace MOLDULE;

vector<ll> Fac, Fac_inv;
void Prepare_Factorium(ll n)
{
    Fac.clear();
    Fac.resize(n + 1);
    Fac[0] = Fac[1] = 1;
    Fac_inv.clear();
    Fac_inv.resize(n + 1);
    Fac_inv[0] = Fac_inv[1] = 1;
    FORLL(i,2,n)
    {
        Fac[i] = Get_Mod(Fac[i - 1] * i);
        Fac_inv[i] = qcpow(Fac[i], MOD - 2);
    }
}
void Prepare_Combination(ll n) { Prepare_Factorium(n); }
ll Get_Combination(ll m, ll n) { return Get_Mod(Get_Mod(Fac[m] * Fac_inv[m - n]) * Fac_inv[n]); }

//第二类Stirling数，n个不同球放入m个不同盒子的方案数 复杂度O(mlogn)
ll Get_Stirling(ll n,ll m){
    ll ans=0;
    if(n<m) return 0;
    FORLL(i,0,m){
        ll t=mul(Get_Combination(m,i),qcpow(m-i,n));
        if((m-i)&1) t=MOD-t;
        addto(ans,t);
    }return ans;
}