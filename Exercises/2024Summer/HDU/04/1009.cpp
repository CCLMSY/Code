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

    vector<vector<ll>> C;
    void Prepare_Combination(ll n){ C.clear(); C.resize(n+1); C[0].emplace_back(1); for(ll i=1;i<=n;i++) { C[i].emplace_back(1); for(ll j=1;j<=n-1;j++) C[i].emplace_back(add(C[i-1][j-1],C[i-1][j])); C[i].emplace_back(1); } }
}


using namespace DEFINITION;
using namespace CCLIB;
// using namespace MODULE;

#define ONLINE_JUDGE
#define FAST_IO
#define MUTIPLE_JUDGE

/*----------Code Area----------*/
const ll N = 200005;
void prepare(){
    // Prepare_Combination(5005);
    // MOD = 1e9+7;
}
vector<int> days = {0,31,29,31,30,31,30,31,31,30,31,30,31};
inline int toint(char c1,char c2){
    return (c1-'0')*10+c2-'0';
}
void solve()
{
    ll n,m;cin >> n >> m;
    vector<string> names;
    string s,t;
    cin >> s;
    FORLL(i,1,n){
        cin >> t;
        names.emplace_back(t);
    }
    map<char,vector<ll>> posc,posint;
    FORLL(i,0,m-1){
        if(s[i]>='a'&&s[i]<='z') posc[s[i]].emplace_back(i);
        else posint[s[i]].emplace_back(i);
    }
    vector<ll> date(m+1,0);
    for(auto d2='0';d2<='9';d2++){
        if(posint[d2].empty()) continue; //没有这个数字
        auto posd2 = posint[d2].back(); //最后一个位置
        for(auto d1='0';d1<='3';d1++){
            auto day=toint(d1,d2);
            if(day>31||day<1) continue; //不可能的天数
            if(posint[d1].empty()) continue; //没有这个数字
            auto itposd1 = lower_bound(ALL(posint[d1]),posd2); //找比posd2小的最大的位置
            if(itposd1==posint[d1].begin()) continue; //没有比posd2小的
            auto posd1 = *(--itposd1);
            for(auto m2='0';m2<='9';m2++){
                if(posint[m2].empty()) continue; //没有这个数字
                auto itposm2 = lower_bound(ALL(posint[m2]),posd1); //找比posd1小的最大的位置
                if(itposm2==posint[m2].begin()) continue; //没有比posd1小的
                auto posm2 = *(--itposm2);
                for(auto m1='0';m1<='1';m1++){
                    auto month=toint(m1,m2);
                    if(month>12||month<1) continue;; //不可能的月份
                    if(day>days[month]) continue;; //不可能的日期
                    if(posint[m1].empty()) continue; //没有这个数字
                    auto itposm1 = lower_bound(ALL(posint[m1]),posm2); //找比posm2小的最大的位置
                    if(itposm1==posint[m1].begin()) continue; //没有比posm2小的
                    auto posm1 = *(--itposm1);
                    date[posm1]++;
                    // cout << month << ' ' << day << endl;
                }
            }
        }
    }
    FORLL_rev(i,m-1,0) date[i]+=date[i+1];
    // print_vec(date);
    ll ans=0;
    for(auto &name:names){
        ll curi=-1,len=name.length();
        FORLL(i,0,len-1){
            auto c=name[i];
            auto it=upper_bound(ALL(posc[c]),curi);
            if(it==posc[c].end()) break;
            curi=*it;
            if(i==len-1) ans+=date[curi+1];
        }
    }
    cout << ans << endl;
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