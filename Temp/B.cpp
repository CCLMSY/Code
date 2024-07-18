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
    void print_float(T value,ll digit=10){cout << fixed << setprecision(digit) << value;}

    vector<ll> snums;
    void Get_Nums(string s){ snums.clear(); ll n=s.length();ll t=0;ll flag=0; FORLL(i,0,n-1) if(s[i]<='9'&&s[i]>='0'){t*=10;t+=s[i]-'0';flag++;}else if(flag){snums.emplace_back(t);t=0;flag=0;} if(flag){snums.emplace_back(t);t=0;flag=0;}}

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
struct DSU
{
    vector<ll> parents, size;
    explicit DSU(ll n) : parents(n + 1), size(n + 1, 1) { iota(parents.begin(), parents.end(), 0); }
    ll find(ll x) { return (parents[x] == x) ? x : (parents[x] = find(parents[x])); }
    void merge(ll a, ll b)
    { // merge a into b
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (size[a] > size[b]) swap(a, b);
        parents[a] = b;
        size[b] += size[a];
    }
};
//最小生成树
struct MSTree{
private:
    struct Edge{
        ll u,v,w;
        bool operator>(const Edge &e) const{
            return w > e.w;
        }
    };
    ll n;
    DSU dsu;
    priority_queue<Edge,vector<Edge>,greater<Edge>> Q;
public:
    ll ans=0;
    vector<vector<pll>> G;
    vector<ll> fa;
    MSTree(ll _n):n(_n),dsu(_n),G(_n+1),fa(n+1,0){}
    void add_edge(ll u,ll v,ll w){
        Q.push({u,v,w});
    }
    void solve(){
        ans = 0;
        while(!Q.empty()){
            auto e = Q.top();Q.pop();
            if(dsu.find(e.u) != dsu.find(e.v)){
                dsu.merge(e.u,e.v);
                G[e.u].emplace_back(e.v,e.w);
                G[e.v].emplace_back(e.u,e.w);
                ans += e.w;
            }
        }
        //dfs求fa
        auto DFS = [&](auto &&self, ll u=1,ll f=0) -> void{
            fa[u] = f;
            for(auto &p:G[u]){
                ll v = p.first;
                if(v == f) continue;
                self(self,v,u);
            }
        };
        DFS(DFS);
        // DFS(); //求fa
    }
    //判断是否连通
    bool connected(){
        return dsu.size[dsu.find(1)] == n;
    }
};

const ll N = 1e5+5;
ll k,n,m,cnt,sum,ai,bi,ci,head[N],dis[N],vis[N];

struct Edge
{
    ll v,w,next;
}e[N];

void add(ll u,ll v,ll w)
{
    e[++k].v=v;
    e[k].w=w;
    e[k].next=head[u];
    head[u]=k;
}

priority_queue <pll,vector<pll>,greater<pll> > q;
void prim()
{
    dis[1]=0;
    q.push(make_pair(0,1));
    while(!q.empty()&&cnt<n)
    {
        int d=q.top().first,u=q.top().second;
        q.pop();
        if(vis[u]) continue;
        cnt++;
        sum+=d;
        vis[u]=1;
        for(register ll i=head[u];i!=-1;i=e[i].next)
            if(e[i].w<dis[e[i].v])
                dis[e[i].v]=e[i].w,q.push(make_pair(dis[e[i].v],e[i].v));
    }
}
void preprim(){
    FORLL(i,0,N-1){
        head[i] = -1;
        dis[i] = INF;
    } 
}

using namespace DEFINITION;
using namespace CCLIB;
// using namespace MODULE;

#define ONLINE_JUDGE
#define FAST_IO
#define MUTIPLE_JUDGE

/*----------Code Area----------*/
void prepare(){
    // Prepare_Combination(5005);
    // MOD = 1e9+7;
}
void solve()
{
    ll n,m,q;cin >> n >> m >> q;
    vector<tuple<ll,ll,ll>> edges;
    ll u,v,w;
    FORLL(i,1,m){
        cin >> u >> v >> w;
        edges.emplace_back(w,u,v);
    }
    ll nn;
    while(q--){
        cin >> nn;
        create_vec(vv,nn);
        
    }
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