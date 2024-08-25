#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
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
vector<int> e[2003];
int f[4003][2003],g[4003][2003],len[4003];
int pf[4003][2003],ipf[4003][2003],sz[4003],prod[2003];
int id[2003][2003],cnt;
int zf[2003],zp[2003];
void dfs(int x,int fa)
{
	if(x!=fa)
	{
		if(!id[x][fa]) id[x][fa]=++cnt;
		else return ;
	}
	int X=id[x][fa],Y;
	sz[X]=1;
	for(int y:e[x]) if(y!=fa)
		dfs(y,x),Y=id[y][x],sz[X]+=sz[Y],
		len[X]=max(len[X],len[Y]);
	if(x==fa) return ;
	for(int i=0; i<=len[X]; ++i) f[X][i]=1,zf[i]=0;
	for(int i=0; i<=len[X]; ++i) prod[i]=1,zp[i]=0;
	for(int y:e[x]) if(y!=fa)
	{
		Y=id[y][x];
		for(int i=0; i<len[Y]; ++i)
			if(pf[Y][i])
				f[X][i]=1ll*f[X][i]*pf[Y][i]%p;
			else ++zf[i];
		if(pf[len[Y]]) prod[len[Y]]=1ll*prod[len[Y]]*pf[Y][len[Y]]%p;
		else ++zp[Y];
	}
	for(int i=1; i<=len[X]; ++i)
		prod[i]=1ll*prod[i-1]*prod[i]%p,zp[i]+=zp[i-1];
	for(int i=0; i<=len[X]; ++i)
		f[X][i]=1ll*f[X][i]*prod[i]%p,zf[i]+=zp[i];
	for(int y:e[x]) if(y!=fa)
	{
		Y=id[y][x];
		for(int i=1; i<=len[Y]; ++i)
			if(pf[Y][i]&&!zf[i])
				g[X][i]=(g[X][i]+
				1ll*f[X][i]*ipf[Y][i]%p*g[Y][i])%p;
			else if(!pf[Y][i]&&zf[i]==1)
				g[X][i]=(g[X][i]+1ll*f[X][i]*g[Y][i])%p;
	}
	for(int i=len[X]; i>=1; --i)
		f[X][i]=(f[X][i]+p-f[X][i-1])%p;
	for(int i=len[X]; i>=0; --i)
		f[X][i+1]=(f[X][i+1]+f[X][i])%p,
		g[X][i+1]=(g[X][i+1]+g[X][i])%p;
	++len[X],g[X][1]+=sz[X];
	pf[X][0]=prod[0]=1;
	for(int i=1; i<=len[X]; ++i)
		pf[X][i]=(pf[X][i-1]+f[X][i])%p,
		prod[i]=1ll*prod[i-1]*max(pf[X][i],1)%p;
	int inv=qp(prod[len[X]],p-2);
	for(int i=len[X]; i>=1; --i)
		ipf[X][i]=1ll*prod[i-1]*inv%p,
		inv=1ll*inv*max(pf[X][i],1)%p;
	return ;
}
int n=read(),ans=n*(n-1)/2;
void DFS(int x,int fa)
{
	sz[x]=1;
	for(int y:e[x]) if(y!=fa)
		DFS(y,x),sz[x]+=sz[y];
	ans=(ans+sz[x]*(n-sz[x]))%p;
	return ;
}
int tmp[2003][3];
signed main()
{
	for(int i=1,u,v; i<n; ++i)
		u=read(),v=read(),
		e[u].push_back(v),
		e[v].push_back(u);
	for(int i=1; i<=n; ++i)
	{
		dfs(i,i),memset(tmp,0,sizeof(tmp));
		for(int j=1; j<=n; ++j) tmp[j][0]=1;
		for(int j:e[i])
		{
			int x=id[j][i];
			for(int k=1; k<=n; ++k)
				tmp[k][2]=(1ll*tmp[k][2]*pf[x][min(k,len[x])]
				+1ll*tmp[k][1]*g[x][k])%p,
				tmp[k][1]=(1ll*tmp[k][1]*pf[x][min(k,len[x])]
				+1ll*tmp[k][0]*g[x][k])%p,
				tmp[k][0]=1ll*tmp[k][0]*pf[x][min(k,len[x])]%p;
		}
		for(int j=1; j<=n; ++j) ans=(ans+tmp[j][2])%p;
	}
	DFS(1,1);
	printf("%d\n",ans);
	return 0;
}