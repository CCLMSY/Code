#include<bits/stdc++.h>
using namespace std;
inline int read(){
   int s=0,w=1;
   char ch=getchar();
   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
   return s*w;
}
pair<int,int> a[1<<18],s[1<<18],t[1<<18];
int p[1<<18],b[1<<18],all;
struct seg3
{
	struct node{int x,y;bool gg;};
	node merge(node ls,node rs)
	{
		return (node){
		max(ls.x,rs.x),min(ls.y,rs.y),
		ls.gg||rs.gg||(ls.x>rs.y)};
	}
	vector<node> f;
	vector<int> id;
	inline void resize(int mxn)
	{
		id.resize(mxn);
		int N=1;
		while(N<=mxn) N<<=1;
		f.resize(N<<1);
		return ;
	}
	inline void build(int nl,int nr,int x)
	{
		if(nl==nr)
		{
			f[x]=(node){s[nl].first,s[nl].second,0};
			return ;
		}
		int mid=(nl+nr)>>1;
		build(nl,mid,x<<1),
		build(mid+1,nr,(x<<1)+1),
		f[x]=merge(f[x<<1],f[(x<<1)+1]);
	}
	inline void update(int nl,int nr,int t,int x,pair<int,int> o)
	{
		if(nl==nr)
		{
			f[x]=(node){o.first,o.second,0};
			return ;
		}
		int mid=(nl+nr)>>1;
		if(t<=mid) update(nl,mid,t,x<<1,o);
		else update(mid+1,nr,t,(x<<1)+1,o);
		f[x]=merge(f[x<<1],f[(x<<1)+1]);
		return ;
	}
}tr[1<<18];
void build(int nl,int nr,int x)
{
	if(nl==nr) return ;
	int mid=(nl+nr)>>1;
	build(nl,mid,x<<1),
	build(mid+1,nr,(x<<1)+1);
	int pl=nl,pr=mid+1,pt=nl;
	while(pl<=mid&&pr<=nr)
		if(a[pl]<=a[pr]) t[pt++]=a[pl++];
		else t[pt++]=a[pr++];
	while(pl<=mid) t[pt++]=a[pl++];
	while(pr<=nr) t[pt++]=a[pr++];
	tr[x].resize(nr-nl+1);
	for(int i=nl; i<=nr; ++i)
	{
		a[i]=t[i],tr[x].id[a[i].second-nl]=i-nl;
		if(a[i].second<=mid) s[i-nl]={b[a[i].second],1e9};
		else s[i-nl]={0,b[a[i].second]};
	}
	tr[x].build(0,nr-nl,1),
	all+=tr[x].f[1].gg;
	return ;
}
void update(int nl,int nr,int t,int x,int v)
{
	if(nl==nr) return ;
	int mid=(nl+nr)>>1;
	if(t<=mid) update(nl,mid,t,x<<1,v);
	else update(mid+1,nr,t,(x<<1)+1,v);
	all-=tr[x].f[1].gg;
	if(t<=mid) tr[x].update(0,nr-nl,tr[x].id[t-nl],1,{v,1e9});
	else tr[x].update(0,nr-nl,tr[x].id[t-nl],1,{0,v});
	all+=tr[x].f[1].gg;
}
signed main()
{
	int n=read(),m=read();
	for(int i=1; i<=n; ++i) p[i]=read();
	for(int i=1; i<=n; ++i) a[p[i]]={read(),p[i]};
	for(int i=1; i<=n; ++i) b[p[i]]=read();
	build(1,n,1);
	for(int x,y,X,Y; m--;)
	{
		x=p[read()],y=p[read()];
		if(x!=y)
		{
			X=b[x],Y=b[y],
			update(1,n,x,1,Y),
			update(1,n,y,1,X),
			swap(b[x],b[y]);
		}
		if(all) puts("No");
		else puts("Yes");
	}
	return 0;
}