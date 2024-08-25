#include<bits/stdc++.h>

using namespace std;

const int N=3e3+10,INF=1e9;

int n,m,a[N],b[N],v[11];
int dp1[N],dp2[N];

int get(int a,int b)
{
    if(b==-INF) return 0;
    for(int i=1;i<=10;i++)
        if(10*b<=a*i) return v[i];
    return 0;
}

void solve()
{
    for(int i=1;i<=10;i++) cin >> v[i];
    cin >> n >> m;
    for(int i=1;i<=n;i++) cin >> a[i] >> b[i];

    for(int i=1;i<=m;i++) dp1[i]=-INF;
    for(int i=1;i<=n;i++)
        for(int j=a[i];j<=m;j++)
            dp1[j]=max(dp1[j],dp1[j-a[i]]+b[i]);

    for(int i=1;i<=m;i++) dp2[i]=0;
    for(int i=1;i<=m;i++)
    {
        int t=get(i,dp1[i])*i;
        for(int j=i;j<=m;j++)
            dp2[j]=max(dp2[j],dp2[j-i]+t);
    }

    cout << dp2[m] << "\n";
}

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    while(T--) solve();
    return 0;
}