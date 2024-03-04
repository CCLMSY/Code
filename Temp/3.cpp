#include<bits/stdc++.h>
using namespace std;
namespace CCLIB
{
    #define create_vec(A,n) vector<ll> A(n);for(auto &x:A) cin >> x;

    // 扩欧返回d=gcd(a,b);x,y对应ax+by=d的解
    ll Exgcd(ll a, ll b, ll &x, ll &y)
    {
        if (a == 0 && b == 0)
            return -1;
        if (b == 0)
        {
            x = 1;
            y = 0;
            return a;
        }
        ll d = Exgcd(b, a % b, y, x);
        y -= a / b * x;
        return d;
    }

    ll qcpow(ll x, ll b)
    {
        ll ret = 1;
        x = Get_Mod(x);
        for (; b; b >>= 1, x = 1ll * x * x % MOD)
            if (b & 1)
                ret = Get_Mod(1ll * ret * x);
        return ret;
    }

    vector<ll> Fac, Fac_inv;
    void Prepare_Factorium(ll n)
    {
        Fac.clear();
        Fac.resize(n + 1);
        Fac[0] = Fac[1] = 1;
        Fac_inv.clear();
        Fac_inv.resize(n + 1);
        Fac_inv[0] = Fac_inv[1] = 1;
        FORLL(i, 2, n)
        {
            Fac[i] = Get_Mod(Fac[i - 1] * i);
            Fac_inv[i] = CCLIB::qcpow(Fac[i], MOD - 2);
        }
    }
    void Prepare_Combination(ll n) { Prepare_Factorium(n); }
    ll Get_Combination(ll m, ll n) { return Get_Mod(Get_Mod(Fac[m] * Fac_inv[m - n]) * Fac_inv[n]); }

    vector<ll> Nums;
    void Get_Nums(string s){ Nums.clear(); ll n=s.length();ll t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){Nums.emplace_back(t);t=0;flag=0;} if(flag){Nums.emplace_back(t);t=0;flag=0;}}

    template<class T>
    void print_vec(const T &A){for(auto &x:A) cout << x << ' ';cout << endl;}
    template<class T>
    void print_float(T value,int digit=10){cout << fixed << setprecision(digit) << value;}
    
}