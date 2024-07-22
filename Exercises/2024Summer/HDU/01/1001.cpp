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
// using namespace MODULE;

#define ONLINE_JUDGE
#define FAST_IO
#define MUTIPLE_JUDGE

/*----------Code Area----------*/
struct strHash
{ // 字符串哈希
    typedef long long ll;
    typedef pair<ll, ll> pll;
    const ll P1 = 57751, mod1 = 1e9 + 7, P2 = 43331, mod2 = 1e9 + 9;
    size_t length, size;
    vector<ll> hz1, hf1, pz1, pf1, hz2, hf2, pz2, pf2;
    // h:Hash;p:Pow;
    // z:正向;f:反向;
    // 1/2:双Hash;下标从1开始
    strHash(string str)
    {
        length = size = str.length();
        str = ' ' + str;
        hz1.resize(size + 2);
        pz1.resize(size + 2);
        hf1.resize(size + 2);
        pf1.resize(size + 2);
        hz2.resize(size + 2);
        pz2.resize(size + 2);
        hf2.resize(size + 2);
        pf2.resize(size + 2);
        pz1[0] = 1;
        for (int i = 1; i <= size; i++)
        {
            hz1[i] = (hz1[i - 1] * P1 + str[i]) % mod1;
            pz1[i] = pz1[i - 1] * P1 % mod1;
        }
        pf1[size + 1] = 1;
        for (int i = size; i >= 1; i--)
        {
            hf1[i] = (hf1[i + 1] * P1 + str[i]) % mod1;
            pf1[i] = pf1[i + 1] * P1 % mod1;
        }
        pz2[0] = 1;
        for (int i = 1; i <= size; i++)
        {
            hz2[i] = (hz2[i - 1] * P2 + str[i]) % mod2;
            pz2[i] = pz2[i - 1] * P2 % mod2;
        }
        pf2[size + 1] = 1;
        for (int i = size; i >= 1; i--)
        {
            hf2[i] = (hf2[i + 1] * P2 + str[i]) % mod2;
            pf2[i] = pf2[i + 1] * P2 % mod2;
        }
    }
    pll findz(int l, int r)
    { // 返回[l,r]的正向双Hash
        return {((hz1[r] - hz1[l - 1] * pz1[r - l + 1]) % mod1 + mod1) % mod1, ((hz2[r] - hz2[l - 1] * pz2[r - l + 1]) % mod2 + mod2) % mod2};
    }
    pll findf(int l, int r)
    { // 返回[l,r]的反向双Hash
        return {((hf1[l] - hf1[r + 1] * pf1[length - r + l]) % mod1 + mod1) % mod1, ((hf2[l] - hf2[r + 1] * pf2[length - r + l]) % mod2 + mod2) % mod2};
    }
    bool isPalin(ll l, ll r)
    { // 判断[l,r]是否为回文串
        return findz(l, r) == findf(l, r);
    }
};
const ll N = 200005;
void prepare(){
    // Prepare_Combination(5005);
    // MOD = 1e9+7;
}
void solve()
{
    string a,b;
    cin >> a >> b;
    ll n=a.length(),m=b.length();
    set<pll> st;
    strHash sa(a+a);
    FORLL(i,1,n)
        st.insert(sa.findz(i,i+n-1));
    strHash sb(b);
    ll ans = 0 ;
    FORLL(i,1,m-n+1)
        if(st.count(sb.findz(i,i+n-1))) ans++;
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