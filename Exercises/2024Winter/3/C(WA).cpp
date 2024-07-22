#include<bits/stdc++.h>
using namespace std;

/*----------Consts----------*/
const long MOD=1e9+7;
const double eps=1e-80;

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
    #define NO "NO\n"
    #define YES "YES\n"
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
// #define FAST_IO
// #define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;
using namespace CCLIB;

/*----------Code Area----------*/
#define N 200005
void solve()
{
    ll n,m;cin >> n >> m;
    string sa,sb,ts;cin >> sa >> sb;
    reverse(ALL(sb));
    if(n<m){
        swap(n,m);
        swap(sa,sb);
    }
    string osa=sa,osb=sb;

    ll head,tail;head=tail=0;
    while(head<m&&sa[head]==sb[head]) head++;
    while(tail<m&&sa[n-tail-1]==sb[m-tail-1]) tail++;

    if(head==0||tail==0){
        cout << "-1" << endl;
        return ;
    }

    //Manacher
    ts="#"; for(auto c:sa) {ts+=c;ts+='#';} sa=ts;
    ts="#"; for(auto c:sb) {ts+=c;ts+='#';} sb=ts;
    vector<ll> da(n*2+1),db(m*2+1);
    da[0]=db[0]=1;
    ll r=0,p=0;
    FORLL(i,1,n*2){
        if(i<r) da[i]=min(da[2*p-i],r-i);
        else da[i]=1;
        while(i-da[i]>=0&&i+da[i]<=n*2&&sa[i-da[i]]==sa[i+da[i]]) da[i]++;
        if(i+da[i]>r) {r=i+da[i];p=i;}
    }
    
    cout << "sa: "; print_vec(sa);
    cout << "da: "; print_vec(da);

    vector<ll> prea,preb,sufa,sufb;
    for(ll i=1;i<=n;i++){
        if(da[i]==i+1&&i<=head) prea.pb(i-1);
        if(da[n*2-i]==i+1&&i<=tail) sufa.pb(n-i);
    }

    SORT(sufa);

    cout << "osa: " << osa << endl;
    cout << "prea: "; print_vec(prea);
    cout << "sufa: "; print_vec(sufa);

    ll ans=INF;
    vector<ll>::iterator it;
    for(auto &x:prea){
        it=upper_bound(ALL(sufa),x);
        if(it!=sufa.end()) ans=min(ans,(*it)-(x+1));
        else break;
    }
    cout << 2*(n-ans) << endl;
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