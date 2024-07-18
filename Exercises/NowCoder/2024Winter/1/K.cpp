#include<bits/stdc++.h>
using namespace std;

/*----------Consts----------*/
const long MOD=998244353;
const double eps=1e-6;

const double pi = acos(-1.0);
const long long INF=0x3fffffffffffffff;
/*----------Consts----------*/

typedef long long ll;
typedef long double ld;
typedef pair<ll,ll> pll;

namespace DEFINITION
{
    #define scanfll(a) scanf("%lld",&a)
    #define lowbit(x) ((x)&(-(x)))
    #define ALL(A) (A).begin(),(A).end()
    #define SORT(A) sort(ALL(A))
    #define SORT_REV(A) sort((A).rbegin(),(A).rend())
    #define UNIQUE(A) unique(ALL(A))
    #define Presentation(i,r) " \n"[i==r]
    #define FORLL(i,l,r) for(ll i=l;i<=r;i++)
    #define FORLL_rev(i,r,l) for(ll i=r;i>=l;i--)
    #define Get_Mod(a) (((a)+MOD)%MOD)
    #define pb push_back
    #define NO cout << "NO\n"
    #define YES cout << "YES\n"
    #define EXIT cout << "-1\n"
    #define endl '\n'
}

namespace CCLIB
{
    ostream& operator<<(ostream &out, const pair<ll,ll> &p) {out << '(' << p.first << ',' << p.second << ')';return out;}
    #define create_vec(A,n) vector<ll> A(n);for(auto &x:A) cin >> x;

    //扩欧返回d=gcd(a,b);x,y对应ax+by=d的解
    ll Exgcd(ll a,ll b,ll &x,ll &y) {if(a==0&&b==0) return -1; if(b==0) {x=1;y=0;return a;} ll d=Exgcd(b,a%b,y,x); y-=a/b*x; return d;}

    ll qcpow(ll x, ll b) {ll ret = 1;x=Get_Mod(x);for(; b; b >>= 1, x = 1ll * x * x % MOD) if(b & 1) ret = Get_Mod(1ll*ret*x); return ret;}

    vector<ll> Fac,Fac_inv;
    void Prepare_Factorium(ll n) {Fac.clear();Fac.resize(n+1);Fac[0]=Fac[1]=1; Fac_inv.clear();Fac_inv.resize(n+1);Fac_inv[0]=Fac_inv[1]=1; FORLL(i,2,n) {Fac[i]=Get_Mod(Fac[i-1]*i);Fac_inv[i]=CCLIB::qcpow(Fac[i],MOD-2);}}void Prepare_Combination(ll n){Prepare_Factorium(n);}
    ll Get_Combination(ll m,ll n) {return Get_Mod(Get_Mod(Fac[m]*Fac_inv[m-n])*Fac_inv[n]);}

    vector<ll> snums;
    void Get_Nums(string s){ snums.clear(); ll n=s.length();ll t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){snums.emplace_back(t);t=0;flag=0;} if(flag){snums.emplace_back(t);t=0;flag=0;}}

    template<class T>
    void print_vec(const T &A){for(auto &x:A) cout << x << ' ';cout << endl;}
    template<class T>
    void print_float(T value,int digit=10){cout << fixed << setprecision(digit) << value;}
    
}

#define ONLINE_JUDGE
// #define FAST_IO
// #define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
using namespace CCLIB;

/*----------Code Area----------*/
const ll N = 200005;
template<ll P=0>
class mll{
private:
    constexpr ll norm(ll x) const { return x<0?x+Mod:x; }
    constexpr ll mult(ll x,ll y) const { return norm(x*y-x*y/Mod*Mod); }
    mll qcpow(mll a,ll b) const { mll res = 1; for(;b;b>>=1,a*=a) if(b&1) res*=a; return res; }

public:
    ll val;
    static ll Mod;

    constexpr mll():val(0){if(P>0) Mod = P;}
    constexpr mll(ll x){ if(P>0) Mod = P; val=norm(x%Mod); }
    constexpr static void setMod(ll Mod_){ Mod=Mod_; }

    explicit constexpr operator ll() const { return val; }
    constexpr mll operator-() const { mll res; res.val = norm(Mod-val); return res; }
    constexpr mll inv() const { return qcpow(*this,Mod-2); }
    
    constexpr mll &operator+=(mll rhs) & { val = norm(val+rhs.val); return *this; }
    constexpr mll &operator-=(mll rhs) & { val = norm(val-rhs.val); return *this; }
    constexpr mll &operator*=(mll rhs) & { val = mult(val,rhs.val); return *this; }
    constexpr mll &operator/=(mll rhs) & { val = mult(val,rhs.inv()); return *this; }
    constexpr mll &operator%=(mll rhs) & { val = norm(val%rhs.val); return *this; }
    
    friend constexpr mll operator+(mll lhs, mll rhs) { MLL res = lhs; res += rhs; return res; }
    friend constexpr mll operator-(mll lhs, mll rhs) { MLL res = lhs; res -= rhs; return res; }
    friend constexpr mll operator*(mll lhs, mll rhs) { MLL res = lhs; res *= rhs; return res; }
    friend constexpr mll operator/(mll lhs, mll rhs) { MLL res = lhs; res /= rhs; return res; }
    friend constexpr mll operator%(mll lhs, mll rhs) { MLL res = lhs; res %= rhs; return res; }

    friend ostream &operator<<(ostream &out, const mll &a) { out << a.val; return out; }
    friend istream &operator>>(istream &in, mll &a) { in >> a.val; return in; }

    friend bool operator==(mll a, mll b) { return a.val == b.val; }
    friend bool operator!=(mll a, mll b) { return a.val != b.val; }
    friend bool operator<(mll a, mll b)  { return a.val <  b.val; }
    friend bool operator>(mll a, mll b)  { return a.val >  b.val; }
}; template<> ll mll<>::Mod = MOD;
void solve()
{
    ll n;cin >> n ;
    vector<ll> a(n);
    vector<string> s(n);
    FORLL(i,0,n-1){
        cin >> a[i] >> s[i];
        a[i]--;
    }
    mll ans=1;
    vector<int> vis(n,-1);
    FORLL(i,0,n-1){
        ll j=i;
        while(vis[j]==-1){
            vis[j]=i;
            j=a[j];
        }
        if(vis[j]!=i) continue;
        vector<ll> cycle;//环
        ll k=j;
        do{
            cycle.push_back(k);
            k=a[k];
        }while(k!=j);
        ll res=0,t;
        FORLL(i,0,4){
            t=i;
            for(auto x:cycle) t=s[x][t]-'A';
            if(t==i) res++;
        }
        ans*=res;
    }cout << ans << endl;
}
/*----------Code Area----------*/

signed main(){
    int clk = clock();

#ifndef ONLINE_JUDGE
    if(freopen("in.txt", "r", stdin)==NULL) {cout << "Fail opening in.txt!" << endl;return 0;}
    if(freopen("out.txt", "w", stdout)==NULL) {cout << "Fail opening out.txt!" << endl;return 0;}
#endif

#ifdef FAST_IO
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