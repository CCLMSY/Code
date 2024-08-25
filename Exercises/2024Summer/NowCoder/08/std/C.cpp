#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline ll read(){
   ll s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int p=998244353;
int qp(int x,int y)
{
	int res=1;
	for(int t=x; y; y>>=1,t=1ll*t*t%p)
		if(y&1) res=1ll*res*t%p;
	return res;
}
ll lb[64];
int n=read(),m=read(),m0=read(),w=read(),rk;
void ins(ll v)
{
	for(int i=w-1; i>=0; --i)
		if((v>>i)&1)
		{
			if(lb[i]) v^=lb[i];
			else{lb[i]=v,++rk;return ;}
		}
	return ;
}
struct node{int c,a[33],L;}G;
inline ll encode(node &t)
{
	ll res=0;
	for(int i=1,q=0; i<=n; ++i) if(t.a[i])
		res+=(1ll<<(i+q+t.a[i]))-(1ll<<(i+q)),q+=t.a[i];
	return (res<<10)+t.c;
}
unordered_map<ll,int> mp;
int dfs(node &t)
{
	if(t.c+t.L-1>m) return 0;
	if(t.c==m) return 1;
	ll code=encode(t);
	if(mp.count(code)) return mp[code];
	int res=0;
	++t.c,--t.L;
	for(int i=1; i<=n; ++i) if(t.a[i])
	{
		if(t.a[i]>1)
		{
			int q=t.a[i]*(t.a[i]-1)/2;
			t.a[i]-=2,++t.a[i*2],
			res=(res+1ll*i*i*q*dfs(t))%p,
			t.a[i]+=2,--t.a[i*2];
		}
		for(int j=i+1; j<=n; ++j) if(t.a[j])
		{		
			int q=t.a[i]*t.a[j];
			--t.a[i],--t.a[j],++t.a[i+j],
			res=(res+1ll*i*j*q*dfs(t))%p,
			++t.a[i],++t.a[j],--t.a[i+j];
		}
	}
	++t.L;
	int sum=-t.c+1;
	for(int i=1; i<=n; ++i)
		sum+=t.a[i]*i*(i-1)/2;
	if(sum) res=(res+1ll*sum*dfs(t))%p;
	--t.c;
	return mp[code]=res;
}
bool vis[33];
vector<pair<int,ll>> e[33];
ll dep[33];
int tot;
void dfs(int x)
{
	++tot,vis[x]=1;
	for(auto [y,z]:e[x])
		if(vis[y]) ins(dep[x]^dep[y]^z);
		else dep[y]=dep[x]^z,dfs(y);
}
int f[503][63];
signed main()
{
	ll c;
	for(int i=1,u,v; i<=m0; ++i)
		u=read(),v=read(),c=read(),
		e[u].push_back({v,c}),
		e[v].push_back({u,c});
	for(int i=1; i<=n; ++i)
		if(!vis[i]) tot=0,dfs(i),++G.a[tot],++G.L;
	G.c=m0;
	if(m-m0+1<G.L) puts("0"),exit(0);
	f[0][rk]=1;
	for(int i=0; i<500; ++i)
		for(int j=0; j<=w; ++j)
			f[i+1][j]=(f[i+1][j]+(1ll<<j)%p*f[i][j])%p,
			f[i+1][j+1]=(f[i+1][j+1]
			+((1ll<<w)-(1ll<<j))%p*f[i][j])%p;
	int ifac=1;
	for(int i=1; i<=m-m0; ++i) ifac=1ll*ifac*i%p;
	printf("%lld\n",1ll*dfs(G)*qp(ifac,p-2)%p*
	f[m-m0+1-G.L][w]%p*qp((1ll<<w)%p,G.L-1)%p);
	return 0;
}