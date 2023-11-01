#include<bits/stdc++.h>
using namespace std;

/*----------Consts----------*/
const long MOD=1e9+7;

const double pi = acos(-1.0);
const double eps=1e-8;
const double goden_radio=1.618033988749895;
const long long INF=0x3fffffffffffffff;
/*----------Consts----------*/

typedef long long ll;
typedef pair<ll,ll> pll;

namespace DEFINITION
{
    #define scanfll(a) scanf("%lld",&a)
    #define lowbit(x) ((x)&(-(x)))
    #define RESET(A) memset(A,0,sizeof(A))
    #define ALL(A) A.begin(),A.end()
    #define SORT(A) sort(ALL(A))
    #define Presentation(i,r) " \n"[i==r]
    #define FORLL(i,l,r) for(ll i=l;i<=r;i++)
    #define FORLL_rev(i,r,l) for(ll i=r;i>=l;i--)
    #define Get_Mod(a) (((a)+MOD)%MOD)
    #define NO "NO\n"
    #define YES "YES\n"
    #define endl '\n'
}

namespace CCLIB
{
    #define create_vec(A,n) vector<ll> A(n);for(auto &x:A) cin >> x
    #define print_vec(A) for(auto i:A) cout << i << ' ';cout << endl
    #define print_float(value,digit) cout << fixed << setprecision(digit) << value

    //扩欧返回d=gcd(a,b);x,y对应ax+by=d的解
    ll Exgcd(ll a,ll b,ll &x,ll &y) {if(a==0&&b==0) return -1; if(b==0) {x=1;y=0;return a;} ll d=Exgcd(b,a%b,y,x); y-=a/b*x; return d;}
    //扩欧求解a在n下的乘法逆元
    ll Get_Inv(ll a,ll n) {ll x,y; ll d=Exgcd(a,n,x,y); if(d==1) return (x%n+n)%n; else return -1;}
    ll qcpow(ll x, ll b) {ll ret = 1;x=Get_Mod(x);for(; b; b >>= 1, x = 1ll * x * x % MOD) if(b & 1) ret = Get_Mod(1ll*ret*x); return ret;}

    vector<ll> Fac,Fac_inv;
    void Prepare_Factorium(ll n) {Fac.clear();Fac.resize(n+1);Fac[0]=Fac[1]=1; Fac_inv.clear();Fac_inv.resize(n+1);Fac_inv[0]=Fac_inv[1]=1; FORLL(i,2,n) {Fac[i]=Get_Mod(Fac[i-1]*i);Fac_inv[i]=Get_Inv(Fac[i],MOD);}}void Prepare_Combination(ll n){Prepare_Factorium(n);}
    ll Get_Combination(ll m,ll n) {return Get_Mod(Get_Mod(Fac[m]*Fac_inv[m-n])*Fac_inv[n]);}

}

namespace MOLDULE
{
    ll inv(ll x) {return CCLIB::Get_Inv(x,MOD);}
    ll add(ll x, ll y) {return Get_Mod(x + y);}
    ll addto(ll &x, ll y) {return x = add(x, y);}
    ll sub(ll x, ll y) {return Get_Mod(x - y);}
    ll subto(ll &x, ll y) {return x = sub(x, y);}
    ll mul(ll x, ll y) {return Get_Mod(1ll*x * y);}
    ll multo(ll &x, ll y) {return x = mul(x, y);}
    ll div(ll x, ll y) {return Get_Mod(1ll*x*inv(y));} 
    ll divto(ll &x, ll y) {return x = div(x, y);}
}


#define ONLINE_JUDGE
#define IO_OPTIMIZE
#define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;
using namespace CCLIB;

/*----------Code Area----------*/
#define N 100005
void solve()
{
    ll m,n,d;cin >> n >> m >> d;
    vector<ll> sell;ll t;sell.emplace_back(1);
    FORLL(i,1,m) {cin >> t;sell.emplace_back(t);}
    vector<ll> dec(m+1,0),eat(m+2,0);
    ll cnt=1;ll i=1;if(sell[1]==1) {eat[1]=1;i=2;}
    for(;i<=m;i++){
        eat[i]=(sell[i]-sell[i-1]-1)/d+1;
        cnt+=eat[i];
    }
    eat[m+1]=(n-sell[m])/d;
    cnt+=eat[m+1];
    //cout << "cnt:" << cnt << endl;
    if(sell[1]==1) {dec[1]=0;i=2;} else i=1;
    for(;i<=m-1;i++){
        dec[i]=(eat[i]+eat[i+1]-((sell[i+1]-sell[i-1]-1)/d+1));
    }dec[m]=(eat[i]+eat[i+1]-((n-sell[i-1])/d));
    SORT(dec);ll mxdec=dec.back();ll cntdec=0;
    //cout << "dec:" ;print_vec(dec);
    FORLL(i,1,m) if(dec[i]==mxdec) cntdec++;
    cout << cnt-mxdec << ' ' << cntdec << endl;
}
/*----------Code Area----------*/

int main(){
    int clk = clock();

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif

#ifdef IO_OPTIMIZE
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
#endif

#ifdef MUTIPLE_JUDGE
    long T; cin >> T;
    while(T--) solve();
#else
    solve();
#endif

#ifdef CHECK_OUT_TIME
    cout << clock() - clk << " ms\n";
#endif
    return 0;
}