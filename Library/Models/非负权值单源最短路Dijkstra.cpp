#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF=0x3fffffffffffffff;
#define FORLL(i,l,r) for(ll i=l;i<=r;i++)

//非负权值单源最短路Dijkstra O(mlogm)
class Dijkstra{
private:
    struct Edge{ ll v, w; };
    struct Node{
        ll dis, u;
        bool operator>(const Node &a) const { return dis > a.dis; }
    };
    vector<vector<Edge>> G;
    vector<int> vis;
    vector<ll> dis;
    priority_queue<Node,vector<Node>,greater<Node>> Q;
    ll n=0;
    //换源前初始化
    void Init(){
        while(!Q.empty()) Q.pop();
        FORLL(i,1,n){
            vis[i]=0;
            dis[i]=INF;
        }
    }
public:
    Dijkstra(ll _n):n(_n),G(_n+1),vis(_n+1,0),dis(_n+1,INF){}
    void AddEdge(ll u,ll v,ll w){//加边
        G[u].push_back({v,w});
    }
    //s为源点的单源最短路
    void Solve(ll s){
        Init();
        dis[s] = 0;
        Q.push({0, s});
        while (!Q.empty()) {
            ll u = Q.top().u;
            Q.pop();
            if (vis[u]) continue;
            vis[u] = 1;
            for (auto e : G[u]) {
                ll v = e.v, w = e.w;
                if (dis[v] > dis[u] + w) {
                    dis[v] = dis[u] + w;
                    Q.push({dis[v], v});
                }
            }
        }
    }
    //到t的最短路
    ll getDis(ll t){
        return dis[t];
    }
    //访问dis数组
    ll operator[](ll i){
        return dis[i];
    }
};
