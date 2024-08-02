#include<bits/stdc++.h>
using namespace std;
struct DSU{
    vector<int> fa,deep;
    DSU(int n):fa(n),deep(n){
        iota(begin(fa),end(fa),0);
    }
    int find(int x){
        if(x==fa[x]) return x;
        int tmp=find(fa[x]);
        deep[x]+=deep[fa[x]];
        return fa[x]=tmp;
    }
};
void solve(){
    int n;
    cin>>n;
    DSU dsu(n);
    vector<int> f(n);
    for(int i=0,u,v,c;i<n-1;i++){
        cin>>u>>v>>c;
        --u; --v; --c;
        dsu.fa[v]=u;
        dsu.deep[v]=1;
        dsu.find(v);
        f[dsu.find(u)]=max(f[dsu.find(u)],f[v]+dsu.deep[v]);
        cout<<f[c]<<' ';
    }
    cout<<'\n';
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t=1;
    cin>>t;
    while(t--) solve();
    return 0;
}
