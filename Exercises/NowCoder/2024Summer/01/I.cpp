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
    ll qcpow(ll a,ll b,ll p=INF){ll ret=1;a=Get_Mod(a);for (;b;b>>=1,a=a*a%p) if(b&1) ret=ret*a%p;return ret;}
    ll inv(ll a,ll p=MOD){ll x,y,d; d=Exgcd(a,p,x,y);if(d==1) return Get_Mod(x);else return -1;}

    vector<ll> Fac,Fac_inv;
    void Prepare_Factorium(ll n) {Fac.clear();Fac.resize(n+1);Fac[0]=Fac[1]=1; Fac_inv.clear();Fac_inv.resize(n+1);Fac_inv[0]=Fac_inv[1]=1; FORLL(i,2,n) {Fac[i]=Get_Mod(Fac[i-1]*i);Fac_inv[i]=qcpow(Fac[i],MOD-2,MOD);}}void Prepare_Combination(ll n){Prepare_Factorium(n);}
    ll Get_Combination(ll m,ll n) {return Get_Mod(Get_Mod(Fac[m]*Fac_inv[m-n])*Fac_inv[n]);}

    vector<ll> Nums;
    void Get_Nums(string s){ Nums.clear(); ll n=s.length();ll t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){Nums.emplace_back(t);t=0;flag=0;} if(flag){Nums.emplace_back(t);t=0;flag=0;}}

    template<class T>
    void print_vec(const T &A){for(auto &x:A) cout << x << ' ';cout << endl;}
    template<class T>
    void print_float(T value,int digit=10){cout << fixed << setprecision(digit) << value;}
    
}

template<const ll P>
class MODLL{//所有运算皆为右值！！！
private:
    constexpr ll norm(ll x) const { return (x%MOD+MOD)%MOD; }
    constexpr ll mult(ll x,ll y) const { return norm(x*y); }

public:
    ll val; const static ll Mod=P;
    constexpr MODLL():val(0){}
    constexpr MODLL(ll x):val(norm(x)){}
    constexpr static void setMod(ll Mod_){ Mod=Mod_; }
    explicit constexpr operator ll() const { return val; }
    constexpr MODLL operator-() const { MODLL res; res.val = norm(Mod-val); return res; }
    constexpr MODLL inv() const { ll a=val,b=Mod,u=1,v=0;
        while(b!=0){ ll t=a/b; a-=t*b; swap(a,b); u-=t*v; swap(u,v); }
        return MODLL(u);}
    constexpr MODLL pow(ll b) { MODLL res = 1,a = *this; for(;b;b>>=1,a*=a) if(b&1) res*=a; return res; }
    constexpr MODLL &operator+=(MODLL rhs) & { val = norm(val+rhs.val); return *this; }
    constexpr MODLL &operator-=(MODLL rhs) & { val = norm(val-rhs.val); return *this; }
    constexpr MODLL &operator*=(MODLL rhs) & { val = mult(val,rhs.val); return *this; }
    constexpr MODLL &operator/=(MODLL rhs) & { val = mult(val,ll(rhs.inv())); return *this; }
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
// #define MUTIPLE_JUDGE
// #define CHECK_OUT_TIME

typedef MODLL<ll(1e9+7)> mll;

/*----------Code Area----------*/
//                D  U  R  L
const int dx[] = {1, -1, 0, 0};
const int dy[] = {0, 0, 1, -1};
const int c0[] = {1, 0, 2, 3}; // -
const int c1[] = {0, 1, 3, 2}; // |
const int c2[] = {3, 2, 1, 0}; // /
const int c3[] = {2, 3, 0, 1}; // \'

int conv(int d, char c){
    switch(c){
        case '-': return c0[d];
        case '|': return c1[d];
        case '/': return c2[d];
        case '\\': return c3[d];
    }
    return -1;
}

int n,m,q,tms,cnt;
vector<string> mp;
vector<vector<int>> vis;
vector<vector<array<int,4>>> ans,visd;
vector<tuple<int,int,int>> buf;

void dfs_line(int x,int y,int dir){
    buf.push_back({x,y,dir});
    if(x<0||x>=n||y<0||y>=m) return;
    int nd=conv(dir,mp[x][y]); //new direction
    dfs_line(x+dx[nd],y+dy[nd],nd);
}
void f_line(int sx,int sy,int sd){
    buf.clear();
    dfs_line(sx,sy,sd);
    reverse(buf.begin(),buf.end());
    int res=0; tms++;
    for(int i=0;i<buf.size()-1;i++){ //回溯
        auto [x,y,d]=buf[i];
        if(i){
            int fl=1;
            if(mp[x][y]=='-'&&(d&2)||mp[x][y]=='|'&&!(d&2)) fl=0; // 通过
            if(fl){
                if(vis[x][y]!=tms) res+=fl; // 反射
                vis[x][y]=tms;
            }
        }
        visd[x+dx[d^1]][y+dy[d^1]][d]=tms;
        ans [x+dx[d^1]][y+dy[d^1]][d]=res;
    }
}

void dfs_loop(int x,int y,int dir){
    visd[x][y][dir]=tms;
    x += dx[dir];
    y += dy[dir];
    int nd = conv(dir,mp[x][y]);
    if(nd!=dir){
        if(vis[x][y]!=tms) cnt++;
        vis[x][y]=tms;
    }
    if(visd[x][y][nd]!=tms) dfs_loop(x,y,nd);
}
void mk_loop(int x,int y,int dir){
    ans[x][y][dir] = cnt;
    visd[x][y][dir] = tms;
    x+=dx[dir];
    y+=dy[dir];
    int nd=conv(dir,mp[x][y]);
    if(visd[x][y][nd]!=tms) mk_loop(x,y,nd);
}
void f_loop(int sx,int sy,int sd){
    cnt=0; tms++;
    dfs_loop(sx,sy,sd);
    tms++;
    mk_loop(sx,sy,sd);
}

void solve()
{
    cin >> n >> m;
    mp.clear();
    mp.resize(n);
    for(auto& s:mp) cin >> s;
    ans.resize(n,vector<array<int,4>>(m,{0,0,0,0}));
    visd.resize(n,vector<array<int,4>>(m,{0,0,0,0}));
    vis.resize(n,vector<int>(m,0));
    for(int i=0;i<n;i++){
        f_line(i,0,2);
        f_line(i,m-1,3);
    }
    for(int i=0;i<m;i++){
        f_line(0,i,0);
        f_line(n-1,i,1);
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            for(int d=0;d<4;d++){
                if(visd[i][j][d]==0)
                    f_loop(i,j,d);
            }
        }
    }
    cin >> q;
    while(q--){
        int x,y,d;
        string s;
        cin >> x >> y >> s;
        x--,y--;
        if(s[0]=='b') d=0;
        if(s[0]=='a') d=1;
        if(s[0]=='r') d=2;
        if(s[0]=='l') d=3;
        cout << ans[x][y][d] << endl;
    }
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