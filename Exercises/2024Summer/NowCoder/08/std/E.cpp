#include<bits/stdc++.h>
using namespace std;
#define ll long long
inline ll read(){
   ll s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
const int N=1.1e6,M=108;
bool vis[1100003];
int pr[100003],pc,ans;
inline int S(ll x)
{
	int r=0;
	while(x) r+=x%10,x/=10;
	return r;
}
vector<pair<ll,int>> a[110];
ll val[110],n;
#define pt vector<pair<ll,int>>::iterator
void dfs(ll x,pt s,pt t,int req)
{
	if(s==t)
	{
		if(S(x)==req) ans+=(x>req);
		return ;
	}
	auto [y,z]=*s;
	++s,dfs(x,s,t,req);
	for(int i=1; i<=z; ++i)
		x*=y,dfs(x,s,t,req);
	return ;
}
void HaitangSuki()
{
	n=read(),ans=0;
	if(n<=M)
	{
		for(int i=1; i<=n; ++i) ans+=(n%i==S(i));
		printf("%d\n",ans);
		return ;
	}
	for(int i=0; i<=M; ++i) val[i]=n-i,a[i].clear();
	for(int i=1; 1ll*pr[i]*pr[i]<=n; ++i)
		if(pr[i]<=M)
		{
			for(int j=0; j<=M; ++j)
			{
				int cnt=0;
				while(val[j]%pr[i]==0)
					val[j]/=pr[i],++cnt;
				if(cnt) a[j].push_back({pr[i],cnt});
			}	
		}
		else if(n%pr[i]<=M)
		{
			int j=n%pr[i],cnt=0;
			while(val[j]%pr[i]==0)
				val[j]/=pr[i],++cnt;
			if(cnt) a[j].push_back({pr[i],cnt});
		}
	for(int i=0; i<=M; ++i)
		if(val[i]>1)
			a[i].push_back({val[i],1});
	for(int i=0; i<=M; ++i)
		dfs(1,a[i].begin(),a[i].end(),i);
	printf("%d\n",ans);
	return ;
}
signed main()
{
	for(int i=2; i<=N; ++i) if(!vis[i])
	{
		pr[++pc]=i;
		for(int j=2; i*j<=N; ++j) vis[i*j]=1;
	}
	for(int T=read(); T--; HaitangSuki());
	return 0;
}