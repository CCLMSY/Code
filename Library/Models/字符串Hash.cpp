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
    #define NO "No\n"
    #define YES "Yes\n"
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

    vector<ll> Nums;
    void Get_Nums(string s){ Nums.clear(); ll n=s.length();ll t=0;int flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){Nums.emplace_back(t);t=0;flag=0;} if(flag){Nums.emplace_back(t);t=0;flag=0;}}

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
    inline ll mdiv(ll x, ll y) {return Get_Mod(1ll*x*inv(y));} 
    inline ll mdivto(ll &x, ll y) {return x = mdiv(x, y);}
}


#define ONLINE_JUDGE
#define FAST_IO
#define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;
using namespace CCLIB;

/*----------Code Area----------*/
#define N 200005
struct strHash{//字符串哈希
    // typedef long long ll;
    // typedef pair<ll,ll> pll;
    const ll P1=57751,mod1=1e9+7,P2=43331,mod2=1e9+9;
    size_t length,size;
    vector<ll> hz1,hf1,pz1,pf1,hz2,hf2,pz2,pf2;
    //h:Hash;p:Pow;
    //z:正向;f:反向;
    //1/2:双Hash;下标从1开始
    strHash(string str){
        length=size=str.length();
        str=' '+str;
        hz1.resize(size+2);pz1.resize(size+2);hf1.resize(size+2);pf1.resize(size+2);
        hz2.resize(size+2);pz2.resize(size+2);hf2.resize(size+2);pf2.resize(size+2);
        pz1[0]=1;
        for(int i=1;i<=size;i++){
            hz1[i]=(hz1[i-1]*P1+str[i])%mod1;
            pz1[i]=pz1[i-1]*P1%mod1;
        }
        pf1[size+1]=1;
        for(int i=size;i>=1;i--){
            hf1[i]=(hf1[i+1]*P1+str[i])%mod1;
            pf1[i]=pf1[i+1]*P1%mod1;
        }
        pz2[0]=1;
        for(int i=1;i<=size;i++){
            hz2[i]=(hz2[i-1]*P2+str[i])%mod2;
            pz2[i]=pz2[i-1]*P2%mod2;
        }
        pf2[size+1]=1;
        for(int i=size;i>=1;i--){
            hf2[i]=(hf2[i+1]*P2+str[i])%mod2;
            pf2[i]=pf2[i+1]*P2%mod2;
        }
    }
    pll findz(int l,int r){//返回[l,r]的正向双Hash
        return {((hz1[r]-hz1[l-1]*pz1[r-l+1])%mod1+mod1)%mod1,((hz2[r]-hz2[l-1]*pz2[r-l+1])%mod2+mod2)%mod2};
    }
    pll findf(int l,int r){//返回[l,r]的反向双Hash
        return {((hf1[l]-hf1[r+1]*pf1[length-r+l])%mod1+mod1)%mod1,((hf2[l]-hf2[r+1]*pf2[length-r+l])%mod2+mod2)%mod2};
    }
    bool isPalin(ll l,ll r){//判断[l,r]是否为回文串
        return findz(l,r)==findf(l,r);
    }
};

void solve()
{
    
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