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
    #define create_vec(A,n) vector<ll> A(n);for(auto &x:A) cin >> x
    #define print_vec(A) for(auto i:A) cout << i << ' ';cout << endl
    #define print_float(value,digit) cout << fixed << setprecision(digit) << value

    //扩欧返回d=gcd(a,b);x,y对应ax+by=d的解
    ll Exgcd(ll a,ll b,ll &x,ll &y) {if(a==0&&b==0) return -1; if(b==0) {x=1;y=0;return a;} ll d=Exgcd(b,a%b,y,x); y-=a/b*x; return d;}
    //扩欧求解a在n下的乘法逆元
    ll Get_Inv(ll a,ll n) {ll x,y; ll d=Exgcd(a,n,x,y); if(d==1) return (x%n+n)%n; else return -1;}
    ll qcpow(ll x, ll b) {ll ret = 1;x=Get_Mod(x);for(; b; b >>= 1, x = 1ll * x * x % MOD) if(b & 1) ret = Get_Mod(1ll*ret*x); return ret;}

    vector<ll> Fac,Fac_inv;
    void Prepare_Factorium(ll n) {Fac.clear();Fac.resize(n+1);Fac[0]=Fac[1]=1; Fac_inv.clear();Fac_inv.resize(n+1);Fac_inv[0]=Fac_inv[1]=1; FORLL(i,2,n) {Fac[i]=Get_Mod(Fac[i-1]*i);Fac_inv[i]=Get_Inv(Fac[i],MOD);}}void Prepare_Combination(ll n){Prepare_Factorium(n);}
    ll Get_Combination(ll m,ll n) {return Get_Mod(Get_Mod(Fac[m]*Fac_inv[m-n])*Fac_inv[n]);}

}

namespace MOLDULE
{
    ll inv(ll x) {return CCLIB::Get_Inv(x,MOD);}
    ll add(ll x, ll y) {return Get_Mod(x + y);}
    ll addto(ll &x, ll y) {return x = add(x, y);}
    ll sub(ll x, ll y) {return Get_Mod(x - y);}
    ll subto(ll &x, ll y) {return x = sub(x, y);}
    ll mul(ll x, ll y) {return Get_Mod(1ll*x * y);}
    ll multo(ll &x, ll y) {return x = mul(x, y);}
    ll div(ll x, ll y) {return Get_Mod(1ll*x*inv(y));} 
    ll divto(ll &x, ll y) {return x = div(x, y);}
}


#define ONLINE_JUDGE
//#define IO_OPTIMIZE
#define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;
using namespace CCLIB;

/*----------Code Area----------*/

void solve()
{
    ll n,t;cin >> n;
    string s;cin >> s;

    //n=s.length();

    ll mxlen=0;
    vector<pll> Tpos;

    ll st=0;int flag=0;
    FORLL(i,0,n-1){
        if(s[i]=='T'){
            if(flag==0) {st=i;flag=1;}
            if(i==n-1) {Tpos.emplace_back(st,i);
            flag=0;mxlen=max(mxlen,i-st+1);}
        }else if(flag){
            Tpos.emplace_back(st,i-1);
            flag=0;mxlen=max(mxlen,i-st);
        }
    } if(n<4) {cout << mxlen << endl;return ;}

    vector<ll> BT0(n,0),BT1(n,0),TB0(n,0),TB1(n,0);
    if(s[0]=='B'&&s[1]=='T') BT0[0]++; if(s[0]=='T'&&s[1]=='B') TB0[0]++;
    if(s[1]=='B'&&s[2]=='T') BT1[1]++; if(s[1]=='T'&&s[2]=='B') TB1[1]++;

    FORLL(i,2,n-2){
        BT0[i]=BT0[i-2];BT1[i]=BT1[i-2];TB0[i]=TB0[i-2];TB1[i]=TB1[i-2];
        if(i%2){
            if(s[i]=='B'&&s[i+1]=='T') {BT1[i]++;TB1[i]=0;}
            else if(s[i]=='T'&&s[i+1]=='B') {TB1[i]++;BT1[i]=0;}
            else TB1[i]=BT1[i]=0;
        }else{
            if(s[i]=='B'&&s[i+1]=='T') {BT0[i]++;TB0[i]=0;}
            else if(s[i]=='T'&&s[i+1]=='B') {TB0[i]++;BT0[i]=0;}
            else TB0[i]=BT0[i]=0;
        }
    }

    /*
    cout << "BT0:" ;print_vec(BT0);
    cout << "BT1:" ;print_vec(BT1);
    cout << "TB0:" ;print_vec(TB0);
    cout << "TB1:" ;print_vec(TB1);
    */

    for(auto &tp:Tpos)
        if(tp.first%2){
            if(tp.first-2>=0&&(t=TB1[tp.first-2]))
                if(tp.first-t*2-2>=0&&BT1[tp.first-t*2-2]){
                    tp.first--;
                    mxlen=max(mxlen,tp.second-tp.first+1);
                }
        }else{
            if(tp.first-2>=0&&(t=TB0[tp.first-2]))
                if(tp.first-t*2-2>=0&&BT0[tp.first-t*2-2]){
                    tp.first--;
                    mxlen=max(mxlen,tp.second-tp.first+1);
                }
        }


    FORLL(i,0,n-1) BT0[i]=BT1[i]=TB0[i]=TB1[i]=0;
    if(n%2){
        if(s[n-3]=='B'&&s[n-2]=='T') BT1[n-2]++; if(s[n-3]=='T'&&s[n-2]=='B') TB1[n-2]++;
        if(s[n-2]=='B'&&s[n-1]=='T') BT0[n-1]++; if(s[n-2]=='T'&&s[n-1]=='B') TB0[n-1]++;
    }else{
        if(s[n-3]=='B'&&s[n-2]=='T') BT0[n-2]++; if(s[n-3]=='T'&&s[n-2]=='B') TB0[n-2]++;
        if(s[n-2]=='B'&&s[n-1]=='T') BT1[n-1]++; if(s[n-2]=='T'&&s[n-1]=='B') TB1[n-1]++;
    }

    FORLL_rev(i,n-3,1){
        BT0[i]=BT0[i+2];BT1[i]=BT1[i+2];TB0[i]=TB0[i+2];TB1[i]=TB1[i+2];
        if(i%2){
            if(s[i-1]=='B'&&s[i]=='T') {BT1[i]++;TB1[i]=0;}
            else if(s[i-1]=='T'&&s[i]=='B') {TB1[i]++;BT1[i]=0;}
            else TB1[i]=BT1[i]=0;
        }else{
            if(s[i-1]=='B'&&s[i]=='T') {BT0[i]++;TB0[i]=0;}
            else if(s[i-1]=='T'&&s[i]=='B') {TB0[i]++;BT0[i]=0;}
            else TB0[i]=BT0[i]=0;
        }
    }

    /*
    cout << "BT0:" ;print_vec(BT0);
    cout << "BT1:" ;print_vec(BT1);
    cout << "TB0:" ;print_vec(TB0);
    cout << "TB1:" ;print_vec(TB1);
    */
    
    for(auto &tp:Tpos)
        if(tp.second%2){
            if(tp.second+2<=n-1&&(t=BT1[tp.second+2]))
                if(tp.second+t*2+2<=n-1&&TB1[tp.second+t*2+2]){
                    tp.second++;
                    mxlen=max(mxlen,tp.second-tp.first+1);
                }
        }else{
            if(tp.second+2<=n-1&&(t=BT0[tp.second+2]))
                if(tp.second+t*2+2<=n-1&&TB0[tp.second+t*2+2]){
                    tp.second++;
                    mxlen=max(mxlen,tp.second-tp.first+1);
                }
        }

    cout << mxlen << endl;

}
/*----------Code Area----------*/

int main(){
    int clk = clock();

#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
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