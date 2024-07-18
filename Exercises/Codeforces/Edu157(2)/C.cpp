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
// #define MUTIPLE_JUDGE
//#define CHECK_OUT_TIME

using namespace DEFINITION;
//using namespace MOLDULE;
using namespace CCLIB;

/*----------Code Area----------*/
#define N 200005

ll getdvback(string s,ll pos){//pos~end
    ll re=0,len=s.length();
    FORLL(i,pos,len-1) re+=s[i]-'0';
    return re;
}
ll getdvfront(string s,ll pos){//0~pos
    ll re=0;
    FORLL(i,0,pos) re+=s[i]-'0';
    return re;
}
void solve()
{
    vector<string> v[6];
    string ts;
    ll n;cin >> n;
    FORLL(i,1,n){
        cin >> ts;
        switch (ts.length())
        {
            case 1:v[1].emplace_back(ts);break;
            case 2:v[2].emplace_back(ts);break;
            case 3:v[3].emplace_back(ts);break;
            case 4:v[4].emplace_back(ts);break;
            case 5:v[5].emplace_back(ts);break;
        }
    }
    vector<ll> dv[6];
    SORT(v[1]);SORT(v[2]);SORT(v[3]);SORT(v[4]);SORT(v[5]);
    ll re=0;
    FORLL(i,1,5){
        ll vn=v[i].size(),cnt=1;
        if(vn==0) continue;
        FORLL(j,0,vn-1) dv[i].emplace_back(getdvback(v[i][j],0));
        SORT(dv[i]);
        FORLL(j,1,vn-1){
            if(dv[i][j]==dv[i][j-1]) cnt++;
            if(dv[i][j]!=dv[i][j-1]){
                re+=cnt*cnt;
                cnt=1;
            }
        }
        re+=cnt*cnt;cnt=1;
    }//组内自组

    ll nj=v[5].size(),ni=v[3].size();dv[5].clear();
    FORLL(i,0,nj-1) dv[5].emplace_back(getdvback(v[5][i],1)-(v[5][i][0]-'0'));SORT(dv[5]);
    ll i=0,j=0;
    while(i<ni&&j<nj){
        while(j<nj&&dv[3][i]>dv[5][j]) j++;
        while(i<ni&&dv[3][i]<dv[5][j]) i++;
        if(j>=nj||i>=ni||dv[3][i]!=dv[5][j]) continue;
        ll ti=i,tj=j,cnt=0;
        while(j<nj&&dv[5][j]==dv[3][ti]) j++;
        while(i<ni&&dv[3][i]==dv[3][ti]) i++;
        re+=(i-ti)*(j-tj);
    }//3+5

    nj=v[4].size(),ni=v[2].size();dv[4].clear();
    FORLL(i,0,nj-1) dv[4].emplace_back(getdvback(v[4][i],1)-(v[4][i][0]-'0'));SORT(dv[4]);
    i=0,j=0;
    while(i<ni&&j<nj){
        while(j<nj&&dv[2][i]>dv[4][j]) j++;
        while(i<ni&&dv[2][i]<dv[4][j]) i++;
        if(j>=nj||i>=ni||dv[2][i]!=dv[4][j]) continue;
        ll ti=i,tj=j,cnt=0;
        while(j<nj&&dv[4][j]==dv[2][ti]) j++;
        while(i<ni&&dv[2][i]==dv[2][ti]) i++;
        re+=(i-ti)*(j-tj);
    }//2+4

    nj=v[3].size(),ni=v[1].size();dv[3].clear();
    FORLL(i,0,nj-1) dv[3].emplace_back(getdvback(v[3][i],1)-(v[3][i][0]-'0'));SORT(dv[3]);
    i=0,j=0;
    while(i<ni&&j<nj){
        while(j<nj&&dv[1][i]>dv[3][j]) j++;
        while(i<ni&&dv[1][i]<dv[3][j]) i++;
        if(j>=nj||i>=ni||dv[1][i]!=dv[3][j]) continue;
        ll ti=i,tj=j,cnt=0;
        while(j<nj&&dv[3][j]==dv[1][ti]) j++;
        while(i<ni&&dv[1][i]==dv[1][ti]) i++;
        re+=(i-ti)*(j-tj);
    }//1+3

    nj=v[5].size(),ni=v[3].size();dv[5].clear();dv[3].clear();
    FORLL(i,0,nj-1) dv[5].emplace_back(getdvfront(v[5][i],3)-(v[5][i][4]-'0'));SORT(dv[5]);
    FORLL(i,0,ni-1) dv[3].emplace_back(getdvback(v[3][i],0));SORT(dv[3]);
    i=0,j=0;
    while(i<ni&&j<nj){
        while(j<nj&&dv[3][i]>dv[5][j]) j++;
        while(i<ni&&dv[3][i]<dv[5][j]) i++;
        if(j>=nj||i>=ni||dv[3][i]!=dv[5][j]) continue;
        ll ti=i,tj=j,cnt=0;
        while(j<nj&&dv[5][j]==dv[3][ti]) j++;
        while(i<ni&&dv[3][i]==dv[3][ti]) i++;
        re+=(i-ti)*(j-tj);
    }//5+3

    nj=v[4].size(),ni=v[2].size();dv[4].clear();
    FORLL(i,0,nj-1) dv[4].emplace_back(getdvfront(v[4][i],2)-(v[4][i][3]-'0'));SORT(dv[4]);
    i=0,j=0;
    while(i<ni&&j<nj){
        while(j<nj&&dv[2][i]>dv[4][j]) j++;
        while(i<ni&&dv[2][i]<dv[4][j]) i++;
        if(j>=nj||i>=ni||dv[2][i]!=dv[4][j]) continue;
        ll ti=i,tj=j,cnt=0;
        while(j<nj&&dv[4][j]==dv[2][ti]) j++;
        while(i<ni&&dv[2][i]==dv[2][ti]) i++;
        re+=(i-ti)*(j-tj);
    }//4+2

    nj=v[3].size(),ni=v[1].size();dv[3].clear();
    FORLL(i,0,nj-1) dv[3].emplace_back(getdvfront(v[3][i],1)-(v[3][i][2]-'0'));SORT(dv[3]);
    i=0,j=0;
    while(i<ni&&j<nj){
        while(j<nj&&dv[1][i]>dv[3][j]) j++;
        while(i<ni&&dv[1][i]<dv[3][j]) i++;
        if(j>=nj||i>=ni||dv[1][i]!=dv[3][j]) continue;
        ll ti=i,tj=j,cnt=0;
        while(j<nj&&dv[3][j]==dv[1][ti]) j++;
        while(i<ni&&dv[1][i]==dv[1][ti]) i++;
        re+=(i-ti)*(j-tj);
    }//3+1

    nj=v[5].size(),ni=v[1].size();dv[5].clear();
    FORLL(i,0,nj-1) dv[5].emplace_back(getdvfront(v[5][i],2)-getdvback(v[5][i],3));SORT(dv[5]);
    i=0,j=0;
    while(i<ni&&j<nj){
        while(j<nj&&dv[1][i]>dv[5][j]) j++;
        while(i<ni&&dv[1][i]<dv[5][j]) i++;
        if(j>=nj||i>=ni||dv[1][i]!=dv[5][j]) continue;
        ll ti=i,tj=j,cnt=0;
        while(j<nj&&dv[5][j]==dv[1][ti]) j++;
        while(i<ni&&dv[1][i]==dv[1][ti]) i++;
        re+=(i-ti)*(j-tj);
    }//5+1

    nj=v[5].size(),ni=v[1].size();dv[5].clear();
    FORLL(i,0,nj-1) dv[5].emplace_back(getdvback(v[5][i],2)-getdvfront(v[5][i],1));SORT(dv[5]);
    i=0,j=0;
    while(i<ni&&j<nj){
        while(j<nj&&dv[1][i]>dv[5][j]) j++;
        while(i<ni&&dv[1][i]<dv[5][j]) i++;
        if(j>=nj||i>=ni||dv[1][i]!=dv[5][j]) continue;
        ll ti=i,tj=j,cnt=0;
        while(j<nj&&dv[5][j]==dv[1][ti]) j++;
        while(i<ni&&dv[1][i]==dv[1][ti]) i++;
        re+=(i-ti)*(j-tj);
    }//1+5

    cout << re << endl;
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