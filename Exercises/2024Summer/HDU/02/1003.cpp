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
    ll MOD = INF;
    inline ll Get_Mod(ll x){
        if(x<0) return x-x/MOD*MOD+MOD;
        else return x-x/MOD*MOD;
    }
    ll qcpow(ll a,ll b,ll p=MOD){ll ret=1;a=Get_Mod(a);for (;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p;return ret;}
    ll inv(ll a,ll p=MOD){return qcpow(a,p-2,p);}

    inline ll add(ll a,ll b){return Get_Mod(a+b);}
    inline ll sub(ll a,ll b){return Get_Mod(a-b);}
    inline ll mul(ll a,ll b){return Get_Mod(a*b);}

    void addto(ll &a,ll b){a=Get_Mod(a+b);}
    void subto(ll &a,ll b){a=Get_Mod(a-b);}
    void multo(ll &a,ll b){a=Get_Mod(a*b);}

    vector<vector<ll>> C;
    void Prepare_Combination(ll n){ C.clear(); C.resize(n+1); C[0].emplace_back(1); FORLL(i,1,n){ C[i].emplace_back(1); FORLL(j,1,i-1) C[i].emplace_back(add(C[i-1][j-1],C[i-1][j])); C[i].emplace_back(1); } }
}


using namespace DEFINITION;
using namespace CCLIB;
// using namespace MODULE;

#define ONLINE_JUDGE
#define FAST_IO
#define MUTIPLE_JUDGE

/*----------Code Area----------*/
void prepare(){}
struct cor{
    int a,b,c;
    cor(int _a,int _b,int _c):a(_a),b(_b),c(_c){}
    bool operator==(cor t)const{
        return a==t.a&&b==t.b&&c==t.c;
    }
    void srt(){ //按大小排序
        if(a>b) swap(a,b);
        if(b>c) swap(b,c);
        if(a>b) swap(a,b);
    }
    void mkstd(){ //把三元组化为以1或6开头的形式
        int t;
        while(a!=1&&a!=6){
            t=a; a=b; b=c; c=t;
        }
    }
};
//原始魔方八个角，顺时针
vector<cor> std_cor = {{1,2,3},{1,3,4},{1,4,5},{1,5,2},{6,3,2},{6,4,3},{6,5,4},{6,2,5}};
void solve()
{
    vector<string> mf(9);
    for(auto& s:mf) cin >> s;
    vector<cor> corners={//给定魔方的八个角，顺时针
        {mf[0][3]-'0',mf[3][11]-'0',mf[3][0]-'0'},
        {mf[8][3]-'0',mf[5][0]-'0',mf[5][11]-'0'},
        {mf[3][8]-'0',mf[3][9]-'0',mf[0][5]-'0'},
        {mf[5][8]-'0',mf[8][5]-'0',mf[5][9]-'0'},
        {mf[6][3]-'0',mf[5][3]-'0',mf[5][2]-'0'},
        {mf[3][3]-'0',mf[2][3]-'0',mf[3][2]-'0'},
        {mf[6][5]-'0',mf[5][6]-'0',mf[5][5]-'0'},
        {mf[3][6]-'0',mf[2][5]-'0',mf[3][5]-'0'}};
    for(auto& cor:corners) cor.mkstd();
    for(auto& cor:corners){
        int fl=0;
        for(auto& st:std_cor) if(st==cor) {fl=1;break;}
        if(fl) continue;
        cor.srt();
        cout << cor.a << ' ' << cor.b << ' ' << cor.c << endl;
        return;
    }
    cout << "No problem" << endl;
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