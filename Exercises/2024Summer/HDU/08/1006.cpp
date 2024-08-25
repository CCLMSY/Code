// #pragma GCC optimize("O3") //调试时关闭

#include<bits/stdc++.h>
using namespace std;

/*----------Consts----------*/
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
    //SORT BEFORE UNIQUE!!
    #define UNIQUE(A) A.erase(unique(ALL(A)),A.end())
    #define Presentation(i,r) " \n"[i==r]
    #define FORLL(i,l,r) for(ll i=l;i<=r;i++)
    #define FORLL_rev(i,r,l) for(ll i=r;i>=l;i--)
    #define NO cout << "No\n"
    #define YES cout << "Yes\n"
    #define x first
    #define y second
    #define endl '\n' //交互题不启用！
}

namespace CCLIB
{
    #define create_vec(v,n) vector<ll> v(n);for(auto &x:v) cin >> x;
    ostream& operator<<(ostream &out, const pair<ll,ll> &p) {out << '(' << p.first << ',' << p.second << ')';return out;}

    //扩欧返回d=gcd(a,b);x,y对应ax+by=d的解;通解为x=x0+k*b/d,y=y0-k*a/d;
    ll Exgcd(ll a,ll b,ll &x,ll &y) {if(a==0&&b==0) return -1; if(b==0) {x=1;y=0;return a;} ll d=Exgcd(b,a%b,y,x); y-=a/b*x; return d;}

    template<typename T>
    void chmax(T &a,T b){if(a<b) a=b;}
    template<typename T>
    void chmin(T &a,T b){if(a>b) a=b;}
    template<class T> //iterable
    void print_vec(const T &A){for(auto &x:A) cout << x << ' ';cout << endl;}
    void print_float(ld value,int digit=10){cout << fixed << setprecision(digit) << value;}

    vector<ll> snums;
    void Get_Nums(string s){ snums.clear(); ll n=s.length();ll t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){snums.emplace_back(t);t=0;flag=0;} if(flag){snums.emplace_back(t);t=0;flag=0;}}

}

namespace MODULE
{
    ll MOD = 1e9+7;
    inline ll Get_Mod(ll x,ll mod=MOD){
        if(x<0) return x-x/mod*mod+mod;
        else return x-x/mod*mod;
    }
    ll qcpow(ll a,ll b,ll p=MOD){ll ret=1;a=Get_Mod(a);for (;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p;return ret;}
    ll inv(ll a,ll p=MOD){return qcpow(a,p-2,p);}

    inline ll add(ll a,ll b){return Get_Mod(a+b);}
    inline ll sub(ll a,ll b){return Get_Mod(a-b);}
    inline ll mul(ll a,ll b){return Get_Mod(a*b);}

    void addto(ll &a,ll b){a=Get_Mod(a+b);}
    void subto(ll &a,ll b){a=Get_Mod(a-b);}
    void multo(ll &a,ll b){a=Get_Mod(a*b);}

    vector<ll> Fac;
    void Prepare_Factorial(ll n){Fac.resize(n+1);Fac[0]=1;FORLL(i,1,n) Fac[i]=mul(Fac[i-1],i);}
    inline ll C(ll n,ll m){return n<m?0:mul(Fac[n],inv(mul(Fac[m],Fac[n-m])));}
}


using namespace DEFINITION;
using namespace CCLIB;
// using namespace MODULE;

#define ONLINE_JUDGE
#define FAST_IO
#define MUTIPLE_JUDGE

/*----------Code Area----------*/
class DSU{
private:
    vector<ll> parents, size;
public:
    explicit DSU(ll n) : parents(n + 1), size(n + 1, 1) { iota(parents.begin(), parents.end(), 0); }
    ll find(ll x) { return (parents[x] == x) ? x : (parents[x] = find(parents[x])); }
    void merge(ll a, ll b)
    { // merge a and b
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (size[a] > size[b]) swap(a, b); //去掉本行：merge a into b
        parents[a] = b;
        size[b] += size[a];
    }
};
const ll N = 200005;
void prepare(){
    // Prepare_Factorial(5005);
    // MOD = 1e9+7;
}
void solve()
{
    ll n,m;cin >> n >> m;
    ll ub=m/(n-1);
    vector<DSU> dsu(ub+2,DSU(n));
    vector<ll> cnt(ub+2,0);
    vector<ll> ans(m+1,0);
    ll u,v;
    FORLL(i,1,m){
        cin >> u >> v;
        ll l=1,r=ub+1;
        while(l<r){
            ll mid=(l+r+1)/2;
            bool fl=(dsu[mid].find(u)==dsu[mid].find(v));
            if(fl) l=mid;
            else r=mid-1;
        }
        ll tar=0;
        FORLL(i,max(1ll,l-3),min(ub+1,l+3)){
            if(dsu[i].find(u)!=dsu[i].find(v)){
                tar=i;
                break;
            }
        }
        if(tar==ub+1) { ans[i]=-1; continue; }
        dsu[tar].merge(u,v);
        cnt[tar]++; ans[i]=tar;
    }
    FORLL(i,1,m){
        if(ans[i]!=-1&&cnt[ans[i]]==n-1) cout << ans[i];
        else cout << "-1";
        cout << Presentation(i,m);
    }
}
/*----------Code Area----------*/

signed main(){

#ifndef ONLINE_JUDGE
    clock_t clk = clock();
    ifstream ifs("1.in");
    ofstream ofs("1.out");
    streambuf *cinbackup;
    cinbackup = cin.rdbuf(ifs.rdbuf());
    streambuf *coutbackup;
    coutbackup = cout.rdbuf(ofs.rdbuf());
#endif

#ifdef FAST_IO
#ifdef ONLINE_JUDGE
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
#endif
#endif

long long T = 1;
#ifdef MUTIPLE_JUDGE
    cin >> T;
#endif
prepare();
while(T--) solve();

#ifndef ONLINE_JUDGE
    cin.rdbuf(cinbackup);
    cout.rdbuf(coutbackup);
    cout << clock() - clk << " ms\n";
#endif
    return 0;
}