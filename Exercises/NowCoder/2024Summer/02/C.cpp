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
    #define Get_Mod(a) (((a)-(a)/MOD*MOD+MOD)%MOD)
    #define NO cout << "NO\n"
    #define YES cout << "YES\n"
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
    template<class T>
    void print_vec(const T &A){for(auto &x:A) cout << x << ' ';cout << endl;}
    template<class T>
    void print_float(T value,int digit=10){cout << fixed << setprecision(digit) << value;}

    vector<ll> snums;
    void Get_Nums(string s){ snums.clear(); ll n=s.length();ll t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){snums.emplace_back(t);t=0;flag=0;} if(flag){snums.emplace_back(t);t=0;flag=0;}}

}

namespace MODULE
{
    ll MOD = 1e9+7;
    ll qcpow(ll a,ll b,ll p=MOD){ll ret=1;a=Get_Mod(a);for (;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p;return ret;}
    ll inv(ll a,ll p=MOD){return qcpow(a,p-2,p);}

    ll add(ll a,ll b){return Get_Mod(a+b);}
    ll sub(ll a,ll b){return Get_Mod(a-b);}
    ll mul(ll a,ll b){return Get_Mod(a*b);}
    ll div(ll a,ll b){return Get_Mod(a*inv(b));}

    void addto(ll &a,ll b){a=Get_Mod(a+b);}
    void subto(ll &a,ll b){a=Get_Mod(a-b);}
    void multo(ll &a,ll b){a=Get_Mod(a*b);}
    void divto(ll &a,ll b){a=Get_Mod(a*inv(b));}

    vector<vector<ll>> C;
    void Prepare_Combination(ll n){ C.clear(); C.resize(n+1); C[0].emplace_back(0); FORLL(i,1,n){ C[i].emplace_back(1); FORLL(j,1,i-1) C[i].emplace_back(add(C[i-1][j-1],C[i-1][j])); C[i].emplace_back(1); } }
}


using namespace DEFINITION;
using namespace CCLIB;
using namespace MODULE;

#define ONLINE_JUDGE
#define FAST_IO
// #define MUTIPLE_JUDGE

/*----------Code Area----------*/
const ll N = 200005;
void prepare(){
    // Prepare_Combination(5005);
    // MOD = 1e9+7;
}
array<string, 2> s;
ll n,ans=1;
ll getstat(ll col){
    if(s[0][col]=='W'&&s[1][col]=='W') return 0;
    if(s[0][col]=='W'&&s[1][col]=='R') return 1;
    if(s[0][col]=='R'&&s[1][col]=='W') return 2;
    if(s[0][col]=='R'&&s[1][col]=='R') return 3;
    return -1;
}
ll getcnt(ll col){
    if(s[0][col]=='W'&&s[1][col]=='W') return 0;
    if(s[0][col]=='W'&&s[1][col]=='R') return 1;
    if(s[0][col]=='R'&&s[1][col]=='W') return 1;
    if(s[0][col]=='R'&&s[1][col]=='R') return 2;
    return -1;
}
void preprocess(){
    ll cnt=0,pre=0,cur;
    if(getcnt(0)==1) pre=getstat(0);
    FORLL(i,1,n-1){
        cur = getcnt(i);
        if(cur==1){
            cur=getstat(i);
            if(pre&&cur&&cnt){
                if((cnt%2==0)&&((pre&cur)==0)) s[cur-1][i-1]='W';
                if((cnt%2)&&((pre&cur))) s[cur-1][i-1]='W';
            }
            pre=cur;
            cnt=0;
        }else if(cur==2){
            cnt++;
        }else{
            cnt=0; pre=0;
        }
    }
}
void getans(){
    ll cnt=getcnt(0),pre=getstat(0),cur;
    FORLL(i,1,n-1){
        cur = getstat(i);
        if(cur&pre){
            cnt+=getcnt(i);
        }else{
            chmax(ans,cnt);
            cnt=getcnt(i);
        }pre=cur;
    }
    chmax(ans,cnt);
}
void solve()
{
    cin >> n;
    cin >> s[0] >> s[1];
    ans=1;
    preprocess();
    getans();
    cout << ans-1 << endl;
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