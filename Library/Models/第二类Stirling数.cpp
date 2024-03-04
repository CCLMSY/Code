#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define FORLL(i,l,r) for(ll i=l;i<=r;i++)
using namespace MOLDULE;

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