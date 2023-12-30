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
    #define SORT_REV(A) sort(A.rbegin(),A.rend())
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
    #define create_vec(A,n) vector<ll> A(n);for(auto &x:A) cin >> x;
    #define print_vec(A) for(auto i:A) cout << i << ' ';cout << endl;
    #define print_float(value,digit) cout << fixed << setprecision(digit) << value;

    //扩欧返回d=gcd(a,b);x,y对应ax+by=d的解
    ll Exgcd(ll a,ll b,ll &x,ll &y) {if(a==0&&b==0) return -1; if(b==0) {x=1;y=0;return a;} ll d=Exgcd(b,a%b,y,x); y-=a/b*x; return d;}
    ll qcpow(ll x, ll b) {ll ret = 1;x=Get_Mod(x);for(; b; b >>= 1, x = 1ll * x * x % MOD) if(b & 1) ret = Get_Mod(1ll*ret*x); return ret;}

    vector<ll> Fac,Fac_inv;
    void Prepare_Factorium(ll n) {Fac.clear();Fac.resize(n+1);Fac[0]=Fac[1]=1; Fac_inv.clear();Fac_inv.resize(n+1);Fac_inv[0]=Fac_inv[1]=1; FORLL(i,2,n) {Fac[i]=Get_Mod(Fac[i-1]*i);Fac_inv[i]=CCLIB::qcpow(Fac[i],MOD-2);}}void Prepare_Combination(ll n){Prepare_Factorium(n);}
    ll Get_Combination(ll m,ll n) {return Get_Mod(Get_Mod(Fac[m]*Fac_inv[m-n])*Fac_inv[n]);}

    vector<ll> Num;
    void Get_Nums(string s){ Num.clear(); ll n=s.length();ll t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){Num.emplace_back(t);t=0;flag=0;} if(flag){Num.emplace_back(t);t=0;flag=0;}}


}

namespace MOLDULE
{
    inline ll inv(ll x) {return CCLIB::qcpow(x,MOD-2);}
    inline ll add(ll x, ll y) {return Get_Mod(x + y);}
    inline ll addto(ll &x, ll y) {return x = add(x, y);}
    inline ll sub(ll x, ll y) {return Get_Mod(x - y);}
    inline ll subto(ll &x, ll y) {return x = sub(x, y);}
    inline ll mul(ll x, ll y) {return Get_Mod(1ll*x * y);}
    inline ll multo(ll &x, ll y) {return x = mul(x, y);}
    inline ll div(ll x, ll y) {return Get_Mod(1ll*x*inv(y));} 
    inline ll divto(ll &x, ll y) {return x = div(x, y);}
}


#define ONLINE_JUDGE
#define IO_OPTIMIZE
#define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;
using namespace CCLIB;

/*----------Code Area----------*/
#define N 200005
void solve()
{
    ll n;cin >> n;
    vector<ll> a(n+1),b(n+1),c(n+1);
    vector<ll> mxia(3),mxib(3),mxic(3);
    FORLL(i,1,n){
        cin >> a[i];
        if(mxia[2]==0||a[i]>=a[mxia[2]]) mxia[2]=i;
        if(mxia[1]==0||a[mxia[2]]>=a[mxia[1]]) swap(mxia[1],mxia[2]);
        if(mxia[0]==0||a[mxia[1]]>=a[mxia[0]]) swap(mxia[0],mxia[1]);
    }
    FORLL(i,1,n){
        cin >> b[i];
        if(mxib[2]==0||b[i]>=b[mxib[2]]) mxib[2]=i;
        if(mxib[1]==0||b[mxib[2]]>=b[mxib[1]]) swap(mxib[1],mxib[2]);
        if(mxib[0]==0||b[mxib[1]]>=b[mxib[0]]) swap(mxib[0],mxib[1]);
    }
    FORLL(i,1,n){
        cin >> c[i];
        if(mxic[2]==0||c[i]>=c[mxic[2]]) mxic[2]=i;
        if(mxic[1]==0||c[mxic[2]]>=c[mxic[1]]) swap(mxic[1],mxic[2]);
        if(mxic[0]==0||c[mxic[1]]>=c[mxic[0]]) swap(mxic[0],mxic[1]);
    }
    ll re=0;
    FORLL(i,0,2)
        FORLL(j,0,2)
            FORLL(k,0,2)
                if(mxia[i]!=mxib[j]&&mxib[j]!=mxic[k]&&mxic[k]!=mxia[i])
                    re=max(re,a[mxia[i]]+b[mxib[j]]+c[mxic[k]]);
    cout << re << endl;
}
/*----------Code Area----------*/

int main(){
    int clk = clock();

#ifndef ONLINE_JUDGE
    if(freopen("in.txt", "r", stdin)==NULL) {cout << "Fail opening in.txt!" << endl;return 0;}
    if(freopen("out.txt", "w", stdout)==NULL) {cout << "Fail opening out.txt!" << endl;return 0;}
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