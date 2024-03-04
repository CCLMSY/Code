#include<bits/stdc++.h>
using namespace std;

/*----------Consts----------*/
const long MOD=1e9+7;
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
    #define RESET(A) memset(A,0,sizeof(A))
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

    vector<ll> Nums;
    void Get_Nums(string s){ Nums.clear(); ll n=s.length();ll t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){Nums.emplace_back(t);t=0;flag=0;} if(flag){Nums.emplace_back(t);t=0;flag=0;}}

    template<class T>
    void print_vec(const T &A){for(auto &x:A) cout << x << ' ';cout << endl;}
    template<class T>
    void print_float(T value,int digit=10){cout << fixed << setprecision(digit) << value;}
    
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
    inline ll mdiv(ll x, ll y) {return Get_Mod(1ll*x*inv(y));} 
    inline ll mdivto(ll &x, ll y) {return x = mdiv(x, y);}
}


#define ONLINE_JUDGE
// #define FAST_IO
#define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;
using namespace CCLIB;

/*----------Code Area----------*/
const ll N = 1000006;
bool check[N+10];//check=1表示合数，被筛除
ll phi[N+10];
ll prime[N+10];
ll tot;//素数的个数
void Phi_and_Prime_Table(ll N){
    memset(check,false,sizeof(check)); phi[1] = 1; tot = 0;
    for(ll i = 2; i <= N; i++) {if( !check[i] ) {prime[tot++] = i; phi[i] = i-1; }
        for(ll j = 0; j < tot; j++) {if(i * prime[j] > N)break; check[i * prime[j]] = true;
            if( i % prime[j] == 0) {phi[i * prime[j]] = phi[i] * prime[j]; break; }
            else {phi[i * prime[j]] = phi[i] * (prime[j] - 1);}}}}

vector<ll> GetFac(ll x){//返回x的质因数集合
    vector<ll> ret;
    ll i=0;
    while(x>1){
        if(check[x]){//check[i]==1表示i是合数
            if(x%prime[i]==0){//prime是质数表
                ret.pb(prime[i]);
                while(x%prime[i]==0) x/=prime[i];
            }
        }else{ ret.pb(x); return ret; }
        i++;
    }return ret;
}

void solve()
{
    ll n,t;cin >> n;
    vector<vector<ll>> vFac;
    vector<ll> v;
    FORLL(i,1,n){
        cin >> t;
        v.push_back(t);
        vFac.push_back(GetFac(t));
    }
    set<ll> st;
    vector<int> sa(n,0);//放入集合a
    sa[0]=1; t=1;
    for(auto &x:vFac[0]) st.insert(x);//将第一个数的质因数放入集合
    while(t){
        t=0;//t表示本轮是否有数放入集合a
        FORLL(i,0,n-1) if(sa[i]==0){
            for(auto &x:vFac[i]) if(st.count(x)){
                sa[i]=1; t++;
                for(auto &y:vFac[i]) st.insert(y);
                break;
            }
        }
    }
    vector<ll> a,b;
    FORLL(i,0,n-1) if(sa[i]) a.pb(v[i]); else b.pb(v[i]);
    if(b.size()==0) {cout << "-1 -1" << endl;return;}
    ll na=a.size(),nb=b.size();
    cout << na << ' ' << nb << endl;
    FORLL(i,0,na-1) cout << a[i] << Presentation(i,na-1);
    FORLL(i,0,nb-1) cout << b[i] << Presentation(i,nb-1);
}
/*----------Code Area----------*/

int main(){
    int clk = clock();

#ifndef ONLINE_JUDGE
    if(freopen("in.txt", "r", stdin)==NULL) {cout << "Fail opening in.txt!" << endl;return 0;}
    if(freopen("out.txt", "w", stdout)==NULL) {cout << "Fail opening out.txt!" << endl;return 0;}
#endif

#ifdef FAST_IO
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
#endif

    Phi_and_Prime_Table(N);

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