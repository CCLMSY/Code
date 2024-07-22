#include<bits/stdc++.h>
using namespace std;
vector<int>v[202020];
int dp[100100];
int a[202020];
vector<pair<int,int>>vp;
vector<vector<int>>g;
bool cmp(pair<int,int>a,pair<int,int>b){
    return a.second-a.first<b.second-b.first;
}
int main(){
    int n,i,j,k;
    cin>>n;
    n*=2;
    for(i=1;i<=n;i++){
        cin>>a[i];
        v[a[i]].push_back(i);
    }
    for(i=1;i<=n/2;i++){
        vp.push_back({v[i][0],v[i][1]});
    }
    vp.push_back({0,2*n+1});
    v[0].push_back(2*n+1);

    sort(vp.begin(),vp.end(),cmp);
    int res=0;
    for(auto i:vp){
        int j=i.first,r=i.second;
        int tempdp[31703]={};
        tempdp[j]=a[j];
        for(k=j+1;k<=r;k++){
            tempdp[k]=tempdp[k-1]+a[j];
            int vv=a[k];
            if(k==v[vv][1]&&vv>a[j]&&v[vv][0]>j&&k!=r){
                tempdp[k]=max(tempdp[k],tempdp[v[vv][0]-1]+dp[vv]);
            }

        }
        dp[a[j]]=max(dp[a[j]],tempdp[r]);
        res=max(res,dp[a[j]]);
    }
    cout<<res;
}