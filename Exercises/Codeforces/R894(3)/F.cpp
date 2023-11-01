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

    vector<ll> Num;
    void Get_Nums(string s){ Num.clear(); ll n=s.length();ll t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){Num.emplace_back(t);t=0;flag=0;} if(flag){Num.emplace_back(t);t=0;flag=0;}}


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
#define N 105
#define W 1000000
int dp[W+5];
void solve()
{
    ll w,f;cin >> w >> f;
    ll n;cin >> n;
    create_vec(v,n);
    ll sum=0;
    FORLL(i,0,n-1) sum+=v[i];

    FORLL(j,0,sum+1) dp[j]=0;
    dp[0]=1;

    FORLL(i,0,n-1)
        FORLL_rev(j,sum,v[i])
            if(dp[j-v[i]]) dp[j]=1;

    ll re=INF;
    FORLL(i,0,sum) if(dp[i]){
        re=min({re,max((i-1)/f+1,(sum-i-1)/w+1),max((i-1)/w+1,(sum-i-1)/f+1)});
    }cout << re << endl;
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