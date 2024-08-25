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
int n=read(),inv=qp(n-1,p-2),suma=0;
struct seg
{
	int c[100003];
	struct node{int mul,add,sum,qwq,cnt;}f[400003];
	void push_down(int x,int ls,int rs,int ld,int rd)
	{
		f[ls].mul=1ll*f[ls].mul*f[x].mul%p,
		f[ls].add=1ll*f[ls].add*f[x].mul%p,
		f[ls].sum=1ll*f[ls].sum*f[x].mul%p,
		f[ls].qwq=1ll*f[ls].qwq*f[x].mul%p,
		f[rs].mul=1ll*f[rs].mul*f[x].mul%p,
		f[rs].add=1ll*f[rs].add*f[x].mul%p,
		f[rs].sum=1ll*f[rs].sum*f[x].mul%p,
		f[rs].qwq=1ll*f[rs].qwq*f[x].mul%p,
		f[ls].add=(f[ls].add+f[x].add)%p,
		f[ls].sum=(f[ls].sum+1ll*f[x].add*ld)%p,
		f[ls].qwq=(f[ls].qwq+1ll*f[x].add*f[ls].cnt)%p,
		f[rs].add=(f[rs].add+f[x].add)%p,
		f[rs].sum=(f[rs].sum+1ll*f[x].add*rd)%p,
		f[rs].qwq=(f[rs].qwq+1ll*f[x].add*f[rs].cnt)%p,
		f[x].mul=1,f[x].add=0;
		return ;
	}
	void build(int nl,int nr,int x)
	{
		if(nl==nr)
		{
			f[x].mul=1,f[x].cnt=c[nl];
			return ;
		}
		int mid=(nl+nr)>>1;
		build(nl,mid,x<<1),build(mid+1,nr,(x<<1)+1),
		f[x].mul=1,f[x].cnt=(f[x<<1].cnt+f[(x<<1)+1].cnt)%p;
		return ;
	}
	void umul(int nl,int nr,int l,int r,int x,int v)
	{
		if(l<=nl&&nr<=r)
		{
			f[x].mul=1ll*f[x].mul*v%p,
			f[x].add=1ll*f[x].add*v%p,
			f[x].sum=1ll*f[x].sum*v%p,
			f[x].qwq=1ll*f[x].qwq*v%p;
			return ;
		}
		if(nr<l||r<nl) return ;
		int mid=(nl+nr)>>1;
		push_down(x,x<<1,(x<<1)+1,mid-nl+1,nr-mid),
		umul(nl,mid,l,r,x<<1,v),
		umul(mid+1,nr,l,r,(x<<1)+1,v),
		f[x].sum=(f[x<<1].sum+f[(x<<1)+1].sum)%p,
		f[x].qwq=(f[x<<1].qwq+f[(x<<1)+1].qwq)%p;
		return ;
	}
	void uadd(int nl,int nr,int l,int r,int x,int v)
	{
		if(l<=nl&&nr<=r)
		{
			f[x].add=(f[x].add+v)%p,
			f[x].sum=(f[x].sum+1ll*v*(nr-nl+1))%p,
			f[x].qwq=(f[x].qwq+1ll*v*f[x].cnt)%p;
			return ;
		}
		if(nr<l||r<nl) return ;
		int mid=(nl+nr)>>1;
		push_down(x,x<<1,(x<<1)+1,mid-nl+1,nr-mid),
		uadd(nl,mid,l,r,x<<1,v),
		uadd(mid+1,nr,l,r,(x<<1)+1,v),
		f[x].sum=(f[x<<1].sum+f[(x<<1)+1].sum)%p,
		f[x].qwq=(f[x<<1].qwq+f[(x<<1)+1].qwq)%p;
		return ;
	}
	int query(int nl,int nr,int l,int r,int x)
	{
		if(l<=nl&&nr<=r) return f[x].sum;
		if(nr<l||r<nl) return 0;
		int mid=(nl+nr)>>1;
		push_down(x,x<<1,(x<<1)+1,mid-nl+1,nr-mid);
		return (query(nl,mid,l,r,x<<1)+
				query(mid+1,nr,l,r,(x<<1)+1))%p;
	}
	int operator[](int x){return query(1,n,x,x,1);}
	int qwq(int nl,int nr,int l,int r,int x)
	{
		if(l<=nl&&nr<=r) return f[x].qwq;
		if(nr<l||r<nl) return 0;
		int mid=(nl+nr)>>1;
		push_down(x,x<<1,(x<<1)+1,mid-nl+1,nr-mid);
		return (qwq(nl,mid,l,r,x<<1)+
				qwq(mid+1,nr,l,r,(x<<1)+1))%p;
	}
}sf,sg;
struct seg2
{
	int pre[100003];
	bool flg;
	int sz,val;
	void resize(int x,int y){sz=x,val=y;}
	int operator[](int x)
	{
		if(x>=sz) return val;
		if(flg) return sg[x];
		return sf[x];
	}
	int query()
	{
		if(flg) return
			(1ll*val*(pre[n]+p-pre[sz-1])
			+sg.qwq(1,n,1,sz-1,1))%p;
		return (1ll*val*(pre[n]+p-pre[sz-1])
			+sf.qwq(1,n,1,sz-1,1))%p;
	}
}f,g;
int a[100003],ans[100003];
signed main()
{
	for(int i=1; i<=n; ++i)
		a[i]=read(),suma=(suma+a[i])%p,
		sf.c[a[i]]=(sf.c[a[i]]+a[i])%p,
		++sg.c[a[i]];
	for(int i=1; i<=n; ++i)
		f.pre[i]=(f.pre[i-1]+sf.c[i])%p,
		g.pre[i]=(g.pre[i-1]+sg.c[i])%p;
	g.flg=1,sf.build(1,n,1),sg.build(1,n,1);
	for(int i=1; i<=n; ++i)
	{
		int tf=1,tg=a[i];
		if(i>1) tf=(p+sf[n]-sf[a[i]])%p,tg=1ll*tf*a[i]%p;
		f.resize(a[i],(sf[a[i]]+tf)%p),
		g.resize(a[i],(sg[a[i]]+tg)%p),
		ans[i]=(ans[i]+p-1ll*inv*f[n]%p*suma%p)%p,
		ans[i]=(ans[i]+1ll*inv*g[n]%p*n)%p;
		ans[i]=(ans[i]+1ll*inv*f.query())%p,
		ans[i]=(ans[i]+p-1ll*inv*g.query()%p)%p;
		sf.umul(1,n,1,a[i]-1,1,inv+1),
		sf.uadd(1,n,a[i],n,1,1ll*inv*(sf[a[i]]+tf)%p),
		sg.umul(1,n,1,a[i]-1,1,inv+1),
		sg.uadd(1,n,a[i],n,1,1ll*inv*(sg[a[i]]+tg)%p),
		ans[i]=(ans[i]+p-sg[a[i]])%p;
		ans[i]=(ans[i]+p-1ll*(p+sf[n]-sf[a[i]])*a[i]%p)%p;
	}
	for(int i=1; i<=n; ++i) ans[i]=(ans[i]+sg[a[i]])%p;
	for(int i=1; i<=n; ++i)
		ans[i]=(ans[i]+1ll*(p+sf[n]-sf[a[i]])*a[i])%p;
	for(int i=1; i<=n; ++i) printf("%d\n",ans[i]);
	return 0;
}