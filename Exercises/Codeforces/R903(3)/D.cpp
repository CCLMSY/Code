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
    #define create_vec(A,n) vector<ll> A(n);for(auto &x:A) cin >> x;
    #define print_vec(A) for(auto i:A) cout << i << ' ';cout << endl;
    #define print_float(value,digit) cout << fixed << setprecision(digit) << value;

    //扩欧返回d=gcd(a,b);x,y对应ax+by=d的解
    ll Exgcd(ll a,ll b,ll &x,ll &y) {if(a==0&&b==0) return -1; if(b==0) {x=1;y=0;return a;} ll d=Exgcd(b,a%b,y,x); y-=a/b*x; return d;}
    ll qcpow(ll x, ll b) {ll ret = 1;x=Get_Mod(x);for(; b; b >>= 1, x = 1ll * x * x % MOD) if(b & 1) ret = Get_Mod(1ll*ret*x); return ret;}

    vector<ll> Fac,Fac_inv;
    void Prepare_Factorium(ll n) {Fac.clear();Fac.resize(n+1);Fac[0]=Fac[1]=1; Fac_inv.clear();Fac_inv.resize(n+1);Fac_inv[0]=Fac_inv[1]=1; FORLL(i,2,n) {Fac[i]=Get_Mod(Fac[i-1]*i);Fac_inv[i]=CCLIB::qcpow(Fac[i],MOD-2);}}void Prepare_Combination(ll n){Prepare_Factorium(n);}
    ll Get_Combination(ll m,ll n) {return Get_Mod(Get_Mod(Fac[m]*Fac_inv[m-n])*Fac_inv[n]);}

    vector<ll> snums;
    void Get_Nums(string s){ snums.clear(); ll n=s.length();ll t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){snums.emplace_back(t);t=0;flag=0;} if(flag){snums.emplace_back(t);t=0;flag=0;}}


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

const ll N = 1000005;
bool check[N+10];//check=1表示合数，被筛除
ll phi[N+10];
ll prime[N+10];
ll tot;//素数的个数
void Phi_and_Prime_Table(ll N=N){
    memset(check,false,sizeof(check)); phi[1] = 1; tot = 0;
    for(ll i = 2; i <= N; i++) {if( !check[i] ) {prime[tot++] = i; phi[i] = i-1; }
        for(ll j = 0; j < tot; j++) {if(i * prime[j] > N)break; check[i * prime[j]] = true;
            if( i % prime[j] == 0) {phi[i * prime[j]] = phi[i] * prime[j]; break; }
            else {phi[i * prime[j]] = phi[i] * (prime[j] - 1);}}}}

ll qcpow_p(ll a,ll b,ll p){
	ll ret=1;
	for(;b;b>>=1,a=(__int128)a*a%p)
		if(b&1)ret=(__int128)ret*a%p;
	return ret;
}
bool Miller_Rabin(ll p){
	if(p<2)return 0;
	if(p==2||p==3)return 1;
	ll d=p-1,r=0;
	while(!(d&1))++r,d>>=1;
	for(ll k=0;k<10;++k){
		ll a=rand()%(p-2)+2;
		ll x=qcpow_p(a,d,p);
		if(x==1||x==p-1)continue;
		for(int i=0;i<r-1;++i){
			x=(__int128)x*x%p;
			if(x==p-1)break;
		}
		if(x!=p-1)return 0;
	}
	return 1;
}
/*----------Code Area----------*/
#define N 100005
void solve()
{
    ll n;cin >> n;
    create_vec(a,n);
    map<ll,ll> mp;
    for(auto x:a){
        FORLL(j,0,tot-1){
            if(x<prime[j]) break;
            if(Miller_Rabin(x)) {mp[x]++;break;}
            while(x%prime[j]==0){
                mp[prime[j]]++;
                x/=prime[j];
            }
        }
    }
    for(auto x:mp) if(x.second%n) {cout << NO;return ;}
    cout << YES;
}
/*----------Code Area----------*/

int main(){
    int clk = clock();
    Phi_and_Prime_Table();

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