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
    #define point_dist(x1,y1,x2,y2) (sqrt(((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2))))

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

/*----------Code Area----------*/
const ll N = 2e2+7; // 线段树节点数的最大值
ll n; // 元素个数
ll a[N]; // 原数组
ll stree[N << 2]; // 线段树节点

//建线段树
void build(ll p, ll l, ll r) {
    //p 表示当前节点在线段树数组中的下标。
    //对于根节点来说，它的下标为 1，对于任意一个节点 i，它的左子节点下标为 i << 1，右子节点下标为 i << 1 | 1。
    if (l == r) { // 叶子节点
        stree[p] = a[l];
    } else {
        ll mid = (l + r) >> 1;
        ll lc = p << 1, rc = p << 1 | 1;
        build(lc, l, mid); // 左子节点
        build(rc, mid + 1, r); // 右子节点
        stree[p] = stree[lc] & stree[rc]; // 合并左右子树的结果
    }
}

//查询区间
ll query(ll p, ll l, ll r, ll ql, ll qr) {
    if (ql <= l && qr >= r) { // 当前区间被查询区间包含
        return stree[p];
    }
    ll mid = (l + r) >> 1;
    ll lc = p << 1, rc = p << 1 | 1;
    ll sum = 0;bool flag=0;
    if (ql <= mid) {sum = query(lc, l, mid, ql, qr);flag=1;} // 查询左子树
    if (qr > mid)
        if(flag) sum &= query(rc, mid + 1, r, ql, qr);
        else sum=query(rc, mid + 1, r, ql, qr); // 查询右子树
    return sum;
}

void solve()
{
    ll n;cin >> n;
    FORLL(i,1,n) cin >> a[i];
    build(1,1,n);
    ll q;cin >> q;
    vector<ll> re;
    while(q--){
        ll l,k;cin >> l >> k;
        if(a[l]<k) {re.emplace_back(-1);continue;}
        ll il=l,ir=n,im,t;
        while(il<ir){
            im=(il+ir)/2;
            if(query(1,1,n,l,im)>=k) il=im+1;
            else ir=im-1;
        }
        ll qwq=query(1,1,n,l,ir);
        if(qwq>=k) re.emplace_back(qwq);
        else re.emplace_back(query(1,1,n,l,il));
    }
    ll t=re.size();
    FORLL(i,0,t-1) cout << re[i] << Presentation(i,t-1);
}
/*----------Code Area----------*/

int main(){
    int clk = clock();

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