#include<bits/stdc++.h>
using namespace std;
const int INF=1e9;
void solve(){
    int n,m,x;
    cin>>n>>m>>x;
    --x;
    vector<vector<pair<int,int>>> nxt(n);
    vector<pair<int,int>> e;
    for(int i=0,u,v;i<m;i++){
        cin>>u>>v;
        --u; --v;
        nxt[u].emplace_back(v,e.size());
        e.push_back({u,v});
        nxt[v].emplace_back(u,e.size());
        e.push_back({v,u});
    }
    vector<int> dis(e.size(),INF),vis(n);
    queue<int> qu;
    for(auto [v,id]:nxt[n-1]){
        dis[id^1]=0;
        dis[id]=1;
        qu.push(id);
    }
    while(qu.size()){
        auto eid=qu.front(); qu.pop();
        int u=e[eid].second;
        if(++vis[u]>2) continue;
        for(auto [v,id]:nxt[u]){
            if((id^eid)==1) continue;
            if(dis[id]!=INF) continue;
            dis[id]=dis[eid]+1;
            qu.push(id);
        }
    }
    vector<int> dis2(n,INF);
    qu.push(x);
    dis2[x]=0;
    while(qu.size()){
        int u=qu.front(); qu.pop();
        for(auto [v,id]:nxt[u]){
            if(dis2[v]!=INF||v==0) continue;
            dis2[v]=dis2[u]+1;
            qu.push(v);
        }
    }
    int ans=INF;
    for(auto [v,eid]:nxt[0])
        ans=min(ans,dis2[v]+dis[eid^1]);
    if(ans>=INF||nxt[n-1].size()<=1) puts("Boring Game");
    else printf("Vegetable fallleaves\n%d\n",ans);
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t=1;
    cin>>t;
    while(t--) solve();
    return 0;
}
