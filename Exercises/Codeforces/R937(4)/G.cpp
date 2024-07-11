#include<bits/stdc++.h>
using namespace std;

/*----------Consts----------*/
const long long MOD=1e9+7;
const double eps=1e-6;

const double pi = acos(-1.0);
const long long INF=0x3fffffffffffffff;
/*----------Consts----------*/

typedef long long ll;
typedef long double ld;
typedef pair<int,int> pll;

namespace DEFINITION
{
    #define scanfll(a) scanf("%lld",&a)
    #define lowbit(x) ((x)&(-(x)))
    #define ALL(A) (A).begin(),(A).end()
    #define SORT(A) sort(ALL(A))
    #define SORT_REV(A) sort((A).rbegin(),(A).rend())
    #define UNIQUE(A) (A).erase(unique(ALL(A)),(A).end())
    #define Presentation(i,r) " \n"[i==r]
    #define FORLL(i,l,r) for(int i=l;i<=r;i++)
    #define FORLL_rev(i,r,l) for(int i=r;i>=l;i--)
    #define Get_Mod(a) (((a)-(a)/MOD*MOD+MOD)%MOD)
    #define NO cout << "NO\n"
    #define YES cout << "YES\n"
    #define endl '\n'
}

namespace CCLIB
{
    #define create_vec(v,n) vector<int> v(n);for(auto &x:v) cin >> x;
    ostream& operator<<(ostream &out, const pair<int,int> &p) {out << '(' << p.first << ',' << p.second << ')';return out;}

    //扩欧返回d=gcd(a,b);x,y对应ax+by=d的解;通解为x=x0+k*b/d,y=y0-k*a/d;
    int Exgcd(int a,int b,int &x,int &y) {if(a==0&&b==0) return -1; if(b==0) {x=1;y=0;return a;} int d=Exgcd(b,a%b,y,x); y-=a/b*x; return d;}
    int qcpow(int a,int b,int p){int ret=1;a=Get_Mod(a);for (;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p;return ret;}

    vector<int> Fac,Fac_inv;
    void Prepare_Factorium(int n) {Fac.clear();Fac.resize(n+1);Fac[0]=Fac[1]=1; Fac_inv.clear();Fac_inv.resize(n+1);Fac_inv[0]=Fac_inv[1]=1; FORLL(i,2,n) {Fac[i]=Get_Mod(Fac[i-1]*i);Fac_inv[i]=qcpow(Fac[i],MOD-2,MOD);}}void Prepare_Combination(int n){Prepare_Factorium(n);}
    int Get_Combination(int m,int n) {return Get_Mod(Get_Mod(Fac[m]*Fac_inv[m-n])*Fac_inv[n]);}

    vector<int> Nums;
    void Get_Nums(string s){ Nums.clear(); int n=s.length();int t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){Nums.emplace_back(t);t=0;flag=0;} if(flag){Nums.emplace_back(t);t=0;flag=0;}}

    template<class T>
    void print_vec(const T &A){for(auto &x:A) cout << x << ' ';cout << endl;}
    template<class T>
    void print_float(T value,int digit=10){cout << fixed << setprecision(digit) << value;}
    
}

template<const int P>
class MODLL{//所有运算皆为右值！！！
private:
    constexpr int norm(int x) const { return (x%MOD+MOD)%MOD; }
    constexpr int mult(int x,int y) const { return norm(x*y); }

public:
    int val; const static int Mod=P;
    constexpr MODLL():val(0){}
    constexpr MODLL(int x):val(norm(x)){}
    constexpr static void setMod(int Mod_){ Mod=Mod_; }
    explicit constexpr operator int() const { return val; }
    constexpr MODLL operator-() const { MODLL res; res.val = norm(Mod-val); return res; }
    constexpr MODLL inv() const { int a=val,b=Mod,u=1,v=0;
        while(b!=0){ int t=a/b; a-=t*b; swap(a,b); u-=t*v; swap(u,v); }
        return MODLL(u);}
    constexpr MODLL pow(int b) { MODLL res = 1,a = *this; for(;b;b>>=1,a*=a) if(b&1) res*=a; return res; }
    constexpr MODLL &operator+=(MODLL rhs) & { val = norm(val+rhs.val); return *this; }
    constexpr MODLL &operator-=(MODLL rhs) & { val = norm(val-rhs.val); return *this; }
    constexpr MODLL &operator*=(MODLL rhs) & { val = mult(val,rhs.val); return *this; }
    constexpr MODLL &operator/=(MODLL rhs) & { val = mult(val,int(rhs.inv())); return *this; }
    constexpr MODLL &operator%=(MODLL rhs) & { val = norm(val%rhs.val); return *this; }
    friend constexpr MODLL operator+(MODLL lhs, MODLL rhs) { MODLL res = lhs; res += rhs; return res; }
    friend constexpr MODLL operator-(MODLL lhs, MODLL rhs) { MODLL res = lhs; res -= rhs; return res; }
    friend constexpr MODLL operator*(MODLL lhs, MODLL rhs) { MODLL res = lhs; res *= rhs; return res; }
    friend constexpr MODLL operator/(MODLL lhs, MODLL rhs) { MODLL res = lhs; res /= rhs; return res; }
    friend constexpr MODLL operator%(MODLL lhs, MODLL rhs) { MODLL res = lhs; res %= rhs; return res; }
    friend ostream &operator<<(ostream &out, const MODLL &a) { out << a.val; return out; }
    friend istream &operator>>(istream &in, MODLL &a) { in >> a.val; return in; }
    friend bool operator==(MODLL a, MODLL b) { return a.val == b.val; }
    friend bool operator!=(MODLL a, MODLL b) { return a.val != b.val; }
    friend bool operator<(MODLL a, MODLL b)  { return a.val <  b.val; }
    friend bool operator>(MODLL a, MODLL b)  { return a.val >  b.val; }
};

using namespace DEFINITION;
using namespace CCLIB;

#define ONLINE_JUDGE
#define FAST_IO
#define MUTIPLE_JUDGE
// #define CHECK_OUT_TIME

typedef MODLL<int(1e9+7)> mll;

/*----------Code Area----------*/
const int N = 200005;
void solve()
{
    int n;cin >> n;
    vector<string> g(n),w(n),vals;
    vector<int> gi(n),wi(n);
    FORLL(i,0,n-1){
        cin >> g[i] >> w[i];
        vals.push_back(g[i]);
        vals.push_back(w[i]);
    }
    SORT(vals);
    UNIQUE(vals);
    FORLL(i,0,n-1){
        gi[i] = lower_bound(ALL(vals),g[i])-vals.begin();
        wi[i] = lower_bound(ALL(vals),w[i])-vals.begin();
    }
    vector<vector<int>> dp(1<<n,vector<int>(n,0)); //dp[mask][lst]表示mask状态下，以lst结尾的方案是否合法
    FORLL(i,0,n-1) dp[1<<i][i] = 1;
    FORLL(mask,0,(1<<n)-1){
        FORLL(lst,0,n-1){
            if(!dp[mask][lst]) continue; //当前状态无法达到
            FORLL(nxt,0,n-1){
                if((mask>>nxt)&1) continue; //当前状态已经包含了nxt
                if(gi[lst]==gi[nxt] || wi[lst]==wi[nxt]){  //可以转移
                    dp[mask|(1<<nxt)][nxt] |= dp[mask][lst]; //实际是置1
                }
            }
        }
    }
    int ans = 0;
    FORLL(mask,0,(1<<n)-1){
        FORLL(lst,0,n-1){
            if(dp[mask][lst])
                ans = max(ans,__builtin_popcount(mask));
        }
    }
    cout << n-ans << endl;
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