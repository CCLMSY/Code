#include<bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll N=5005;
ll C[N][N]={{0}};
ll MOD=1e9+7;
ll n,m;

#define Get_Mod(x) (((x)+MOD)%MOD)
#define endl '\n'

void preC(){
    for(ll i=0;i<N;i++){
        C[i][0]=1;
        for(ll j=1;j<=i;j++){
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD;
        }
    }
}

ll qcpow(ll a,ll b,ll p){
    ll ret = 1;
    a%=p;
    while(b){
        if(b&1) ret = ret*a%p;
        a = a*a%p;
        b>>=1;
    }
    return ret;
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    cin >> n >> m >> MOD;
    preC();
    ll t,a,b,ans=0;
    for(ll i=0;i<=n;i++){
        t = qcpow(2,i,MOD)-1;
        a = qcpow(t,m-1,MOD);
        t = qcpow(2,m-1,MOD);
        b = qcpow(t,n-i,MOD);
        t = Get_Mod(a*b);
        t = Get_Mod(C[n][i]*t);
        ans = Get_Mod(ans+t);
    }
    if(n==1) cout << Get_Mod(1) << endl;
    else if(m==1) cout << Get_Mod(ans-1) << endl;
    else cout << ans << endl;

    return 0;
}