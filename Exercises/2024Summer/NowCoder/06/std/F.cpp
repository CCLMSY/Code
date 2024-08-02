#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
int n , m;
vector<int> E[500005];
bool vis[500005];
int dis[500005];
int mxd;
void dfs(int fa,int u) {
    vis[u] = 1;
    if(dis[u] > dis[mxd]) mxd= u;
    for(auto v : E[u]) {
        if(v != fa) {
            dis[v] = dis[u] + 1;
            dfs(u , v);
        }
    }
}
void solv() {
    cin >> n >> m;
    for(int i = 1;i <= n;i++) E[i].clear() , vis[i] = 0 , dis[i] = 0;
    for(int i = 1;i <= m;i++) {
        int u , v;cin >> u >> v;
        E[u].push_back(v) ; E[v].push_back(u) ;
    }
    if(n == 2) {
        if(m == 1) cout << -1 << '\n';
        else cout << "1 2\n";
        return ;
    }
    if(n == 3) {
        if(m == 2) cout << -1 << '\n';
        else if(m == 0) cout << "1 2 3\n";
        else {
            if(E[1].size() && E[3].size()) cout << "1 2 3\n";
            else if(E[2].size() && E[3].size()) cout << "2 1 3\n";
            else cout << "1 3 2\n";
        }
        return ;
    }
    vector<pii> v;
    for(int i = 1;i <= n;i++) {
        if(!vis[i]) {
            mxd = i;
            dfs(0 , i) ;
            dis[mxd] = 0;
            int u = mxd;
            dfs(0 ,mxd) ;
            v.push_back({u , mxd}) ;
        }
    }
    auto adde = [&](int u,int v) ->void {
        E[u].push_back(v) ;
        E[v].push_back(u);
    };
    for(int i = 1;i < v.size();i++) {
        adde(v[i - 1].second , v[i].first);
    }
    dis[v[0].first] = 0; mxd = v[0].first;
    dfs(0 , v[0].first) ;
    int l = dis[mxd] + 1;
    if(l <= 3) {
        cout << -1 << '\n' ; return ;
    }
    vector<vector<int> > ve(dis[mxd] + 2) ;
    for(int i = 1;i <= n;i++) ve[dis[i] + 1].push_back(i) ;
    for(int i = l - 1 ; i >= 1;i -= 2) {
        for(auto x : ve[i]) cout << x <<' ';
    }
    for(int i = l ; i >= 1 ; i -= 2) {
        for(auto x : ve[i]) cout << x <<' ';
    }
    cout << '\n';
    return ;
}
int main() {
    ios::sync_with_stdio(false) ; cin.tie(0) ;
    int t ;cin >> t;
    while(t--) solv() ;
}
