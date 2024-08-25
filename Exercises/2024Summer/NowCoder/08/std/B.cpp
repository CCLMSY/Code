#include<bits/stdc++.h>
#define ll long long
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
int a[1<<20],f[1<<20],g[1<<20];
vector<pair<int,int>> q[1<<20];
int n,N,m,o;
pair<int,int> t[23];
struct seg
{
struct node{ll ans,s,c,t,t1,mn,mx;}f[1<<20];
void pd(int x,int y,int d)
{
	f[y].ans+=f[y].s*f[x].t,f[y].ans+=d*f[x].t1,f[y].t1+=f[x].t1;
	if(f[y].c) f[y].t1+=f[y].c*f[x].t; else f[y].t+=f[x].t;
	if(f[x].c) f[y].c=f[y].mn=f[y].mx=f[x].c,f[y].s=f[x].c*d;
	return ;
}
void push_down(int x,int ld,int rd)
{
	pd(x,x<<1,ld),pd(x,(x<<1)+1,rd),
	f[x].t=f[x].t1=f[x].c=0;
}
int A=0;
void update(int nl,int nr,int l,int r,int x,int v)
{
	// ++A;return;
	if(nr<l||r<nl||f[x].mn>=v) return ;
	if(l<=nl&&nr<=r&&f[x].mx<=v)
	{
		f[x].c=f[x].mn=f[x].mx=v,f[x].s=1ll*(nr-nl+1)*v;
		return ;
	}
	int mid=(nl+nr)>>1;
	push_down(x,mid-nl+1,nr-mid),
	update(nl,mid,l,r,x<<1,v),
	update(mid+1,nr,l,r,(x<<1)+1,v),
	f[x].ans=f[x<<1].ans+f[(x<<1)+1].ans,
	f[x].s=f[x<<1].s+f[(x<<1)+1].s,
	f[x].mx=max(f[x<<1].mx,f[(x<<1)+1].mx),
	f[x].mn=min(f[x<<1].mn,f[(x<<1)+1].mn);
	return ;
}
int query(int nl,int nr,int l,int r,int x)
{
	if(nr<l||r<nl) return 0;
	if(l<=nl&&nr<=r) return f[x].ans;
	int mid=(nl+nr)>>1;
	push_down(x,mid-nl+1,nr-mid);
	return query(nl,mid,l,r,x<<1)+
		query(mid+1,nr,l,r,(x<<1)+1);
}
int query1(int nl,int nr,int t,int x)
{
	if(nl==nr) return f[x].s;
	int mid=(nl+nr)>>1;
	push_down(x,mid-nl+1,nr-mid);
	if(t<=mid) return query1(nl,mid,t,x<<1);
	else return query1(mid+1,nr,t,(x<<1)+1);
}
ll query2(int nl,int nr,int l,int r,int x)
{
	if(nr<l||r<nl) return 0;
	if(l<=nl&&nr<=r) return f[x].ans;
	int mid=(nl+nr)>>1;
	push_down(x,mid-nl+1,nr-mid);
	return query2(nl,mid,l,r,x<<1)+
		query2(mid+1,nr,l,r,(x<<1)+1);
}
void flush()
{
	if(f[1].c) f[1].t1+=f[1].c,f[1].ans+=f[1].c*N;
	else ++f[1].t,f[1].ans+=f[1].s;
}
}T;
int h[1<<20];
void update(int x,int L)
{
	int c=0;
	for(int i=0; (1<<i)<L; ++i)
		if(f[((N+x)>>i)^1]==(1<<i))
			t[++c]={g[((N+x)>>i)^1],1<<i};
	sort(t+1,t+c+1);
	for(int i=c,X,Y=0; i>=1; --i)
		X=t[i].first,Y+=t[i].second,h[Y]=max(h[Y],X);
	return ;
}
inline bool update(int nl,int nr,int p,int x,int v)
{
	(!f[x]++)&&(g[x]=v);
	if(nl==nr) return 1;
	int mid=(nl+nr)>>1,L=nr-mid;
	if(p<=mid)
	{
		if(update(nl,mid,p,x<<1,v))
		{
			memset(h,0,(L+1)<<2),h[0]=N;
			for(int i=mid+1; i<=nr; ++i) update(i,L);
			int c=0,z=1;
			for(int i=(x<<1)+1,j=L; i>1; i>>=1,j<<=1)
				if(f[i^1]==j) t[++c]={g[i^1],j};
			sort(t+1,t+c+1),t[c+1]={0,0};
			for(int i=c-1; i>=1; --i) t[i].second+=t[i+1].second;
			for(int i=L-1; i>=0; --i)
			{
				h[i]=max(h[i],h[i+1]);
				while(z<=c&&t[z].first<=h[i])
					T.update(1,N,1,t[z].first,1,t[z].second+i),++z;
				if(h[i]>h[i+1]) T.update(1,N,1,h[i],1,t[z].second+i);
			}
		}
	}
	else
	{
		if(update(mid+1,nr,p,(x<<1)+1,v))
		{
			memset(h,0,(L+1)<<2),h[0]=N;
			for(int i=nl; i<=mid; ++i) update(i,L);
			int c=0,z=1;
			for(int i=x<<1,j=L; i>1; i>>=1,j<<=1)
				if(f[i^1]==j) t[++c]={g[i^1],j};
			sort(t+1,t+c+1),t[c+1]={0,0};
			for(int i=c-1; i>=1; --i) t[i].second+=t[i+1].second;
			for(int i=L-1; i>=0; --i)
			{
				h[i]=max(h[i],h[i+1]);
				while(z<=c&&t[z].first<=h[i])
					T.update(1,N,1,t[z].first,1,t[z].second+i),++z;
				if(h[i]>h[i+1]) T.update(1,N,1,h[i],1,t[z].second+i);
			}
		}
	}
	return (f[x]==nr-nl+1);
}
ll ans[1000003];
signed main()
{
	n=read(),N=1<<n,m=read(),o=2;
	for(int i=1; i<=N; ++i) a[i]=read();
	for(int i=1,l,r; i<=m; ++i)
		l=read(),r=read(),q[r].push_back({l,i});
	for(int i=1; i<=N; ++i)
	{
		if(i==N) T.update(1,N,1,1,1,N);
		update(0,N-1,a[i],1,i),T.flush();
		for(auto [x,y]:q[i])
			if(o==1) ans[y]=T.query1(1,N,x,1);
			else ans[y]=T.query2(1,N,x,N,1);
	}
	// printf("%d\n",T.A),exit(0);
	for(int i=1; i<=m; ++i)
		printf("%lld\n",ans[i]);
	return 0;
}