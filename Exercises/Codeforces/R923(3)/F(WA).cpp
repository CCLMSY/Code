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
    #define NO "NO\n"
    #define YES "YES\n"
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
    inline ll div(ll x, ll y) {return Get_Mod(1ll*x*inv(y));} 
    inline ll divto(ll &x, ll y) {return x = div(x, y);}
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
ll n,m;
vector<vector<pll>> G;
vector<ll> vis;
ll minw;//最小权
vector<ll> vans;
void solve()
{
    cin >> n >> m;
    G.clear();G.resize(m+1);
    vis.clear();vis.resize(m+1,0);
    minw=INF;vans.clear();
    FORLL(i,1,m)
    {
        ll u,v,w;
        cin >> u >> v >> w;
        G[u].pb(make_pair(v,w));
        G[v].pb(make_pair(u,w));
    }
    vector<ll> vbfs,vtmp,vminw(m+1,INF);
    vector<ll> fa(m+1,0);
    vector<ll>::iterator it;
    ll pre=0;
    FORLL(i,1,n) if(vis[i]==0)
    {
        // vpath[i].push_back(i);
        vbfs.push_back(i);
        vis[i]=1;
        while(vbfs.size())
        {
            for(auto &u:vbfs)
            {
                vtmp.clear();
                for(auto &x:G[u])
                {
                    ll v=x.first,w=x.second;
                    if(v==pre) continue;//不走回头路(不走上一步
                    if(vis[v]==0)
                    {
                        vis[v]=1;
                        vtmp.push_back(v);
                        fa[v]=u;
                        vminw[v]=min(vminw[u],w);//记录最小权
                    }else{
                        if(min({x.second,vminw[u],vminw[v]})<minw)
                        {
                            minw=min({x.second,vminw[u],vminw[v]});
                            vector<ll> pathu,pathv,uuu;
                            ll tmp=u;
                            while(tmp)
                            {
                                pathu.push_back(tmp);
                                tmp=fa[tmp];
                            }
                            tmp=v;
                            while(tmp)
                            {
                                pathv.push_back(tmp);
                                tmp=fa[tmp];
                            }
                            reverse(ALL(pathu));
                            uuu=pathu;SORT(uuu);
                            while(pathv.size()&&(it=lower_bound(ALL(uuu),pathv.back()))!=uuu.end()&&*it==pathv.back())
                            {
                                pathv.pop_back();
                            }
                            vans=pathu;
                            vans.insert(vans.end(),ALL(pathv));
                        }
                    }
                }
                pre=u;
                vbfs=vtmp;
            }
        }
    }cout << minw << ' ' << vans.size() << endl;
    FORLL(i,0,vans.size()-1) cout << vans[i] << Presentation(i,vans.size()-1);
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