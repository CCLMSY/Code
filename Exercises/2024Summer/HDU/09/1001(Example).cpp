#include <bits/stdc++.h>
using namespace std;
int T,n,k,sz[200005],f[200005],jie[200005],ni[200005];
const int mod=998244353;
int ksm(int x,int y) //快速幂
{
    int num=1;
    while(y)
    {
        if(y&1)num=1ll*num*x%mod;
        x=1ll*x*x%mod;
        y>>=1;
    }
    return num;
}
int C(int m,int n) //组合数
{
    return 1ll*jie[n]*ni[m]%mod*ni[n-m]%mod;
}
vector<int>to[200005];
void dfs(int u)
{
    sz[u]=1; //子树u的大小奇偶性
    f[u]=1;
    int num=1;
    for(auto v:to[u])
    {
        dfs(v);
        num+=sz[v];
        sz[u]^=sz[v];
        f[u]=1ll*f[u]*f[v]%mod;
    }
    // printf("%d %d %d\n",u,num,C(num/2,num));
    f[u]=1ll*f[u]*C(num/2,num)%mod; 
    return;
}
int main() {
    jie[0]=1;
    for(int i=1;i<=200000;i++)jie[i]=1ll*jie[i-1]*i%mod; //阶乘
    ni[200000]=ksm(jie[200000],mod-2);
    // printf("%lld\n",1ll*jie[200000]*ni[200000]%mod);
    for(int i=200000;i;i--)ni[i-1]=1ll*ni[i]*i%mod; // 逆[i]=1/i! 逆元快速处理
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) to[i].clear();
        for(int x,i=2;i<=n;i++)scanf("%d",&x),to[x].push_back(i);
        dfs(1);
        printf("%d\n",ksm(f[1]*(sz[1]+1)%mod,k));
    }
    return 0;
}