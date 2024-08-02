#include<bits/stdc++.h>
using namespace std;
int solve(){
    int n;
    cin>>n;
    vector<int> a(n);
    for(auto &v:a) cin>>v,--v;
    int ans=0,n2=0;
    vector<bool> vis(n);
    auto bfs=[&](int x){
        int res=0;
        for(;!vis[x];x=a[x]){
            vis[x]=true;
            res++;
        }
        return res;
    };
    for(int i=0;i<n;i++){
        int len=bfs(i);
        ans+=len/3;
        if(len%3==2) n2++;
    }
    ans+=(n2+1)/2;
    return ans;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int t=1;
    cin>>t;
    while(t--) cout<<solve()<<'\n';
    return 0;
}
