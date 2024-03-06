#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
#define FORLL(i,l,r) for(ll i=l;i<=r;i++)

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
void solve(){
    ll n,m;cin >> n >> m;
    MSTree mst(n);
    ll u,v,w;
    FORLL(i,1,m){
        cin >> u >> v >> w;
        mst.add_edge(u,v,w);
    }
    mst.solve();
    if(mst.connected()) cout << mst.ans << endl;
    else cout << "orz\n";
}