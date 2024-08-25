#if defined(LOCAL) or not defined(LUOGU)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include<bits/stdc++.h>
using namespace std;
struct time_helper
{
#ifdef LOCAL
    clock_t time_last;
#endif
    time_helper()
    {
#ifdef LOCAL
        time_last=clock();
#endif
    }
    void test()
    {
#ifdef LOCAL
        auto time_now=clock();
        std::cerr<<"time:"<<1.*(time_now-time_last)/CLOCKS_PER_SEC<<";all_time:"<<1.*time_now/CLOCKS_PER_SEC<<std::endl;
        time_last=time_now;
#endif
    }
    ~time_helper()
    {
        test();
    }
}time_helper;
#ifdef LOCAL
#include"dbg.h"
#else
#define dbg(...) (__VA_ARGS__)
#endif
namespace Fread{const int SIZE=1<<16;char buf[SIZE],*S,*T;inline char getchar(){if(S==T){T=(S=buf)+fread(buf,1,SIZE,stdin);if(S==T)return'\n';}return *S++;}}namespace Fwrite{const int SIZE=1<<16;char buf[SIZE],*S=buf,*T=buf+SIZE;inline void flush(){fwrite(buf,1,S-buf,stdout);S=buf;}inline void putchar(char c){*S++=c;if(S==T)flush();}struct NTR{~NTR(){flush();}}ztr;}
#define getchar Fread::getchar
#define putchar Fwrite::putchar
#define Setprecision 10
#define between '\n'
template<typename T>struct is_char{static constexpr bool value=(std::is_same<T,char>::value||std::is_same<T,signed char>::value||std::is_same<T,unsigned char>::value);};template<typename T>struct is_integral_ex{static constexpr bool value=(std::is_integral<T>::value||std::is_same<T,__int128>::value)&&!is_char<T>::value;};template<typename T>struct is_floating_point_ex{static constexpr bool value=std::is_floating_point<T>::value||std::is_same<T,__float128>::value;};namespace Fastio{struct Reader{template<typename T>typename std::enable_if_t<std::is_class<T>::value,Reader&>operator>>(T&x){for(auto &y:x)*this>>y;return *this;}template<typename T>typename std::enable_if_t<is_integral_ex<T>::value,Reader&>operator>>(T&x){char c=getchar();short f=1;while(c<'0'||c>'9'){if(c=='-')f*=-1;c=getchar();}x=0;while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+(c^48);c=getchar();}x*=f;return *this;}template<typename T>typename std::enable_if_t<is_floating_point_ex<T>::value,Reader&>operator>>(T&x){char c=getchar();short f=1,s=0;x=0;T t=0;while((c<'0'||c>'9')&&c!='.'){if(c=='-')f*=-1;c=getchar();}while(c>='0'&&c<='9'&&c!='.')x=x*10+(c^48),c=getchar();if(c=='.')c=getchar();else return x*=f,*this;while(c>='0'&&c<='9')t=t*10+(c^48),s++,c=getchar();while(s--)t/=10.0;x=(x+t)*f;return*this;}template<typename T>typename std::enable_if_t<is_char<T>::value,Reader&>operator>>(T&c){c=getchar();while(c=='\n'||c==' '||c=='\r')c=getchar();return *this;}Reader&operator>>(char*str){int len=0;char c=getchar();while(c=='\n'||c==' '||c=='\r')c=getchar();while(c!='\n'&&c!=' '&&c!='\r')str[len++]=c,c=getchar();str[len]='\0';return*this;}Reader&operator>>(std::string&str){str.clear();char c=getchar();while(c=='\n'||c==' '||c=='\r')c=getchar();while(c!='\n'&&c!=' '&&c!='\r')str.push_back(c),c=getchar();return*this;}Reader(){}}cin;const char endl='\n';struct Writer{typedef __int128 mxdouble;template<typename T>typename std::enable_if_t<std::is_class<T>::value,Writer&>operator<<(T x){for(auto &y:x)*this<<y<<between;*this<<'\n';return *this;}template<typename T>typename std::enable_if_t<is_integral_ex<T>::value,Writer&>operator<<(T x){if(x==0)return putchar('0'),*this;if(x<0)putchar('-'),x=-x;static int sta[45];int top=0;while(x)sta[++top]=x%10,x/=10;while(top)putchar(sta[top]+'0'),--top;return*this;}template<typename T>typename std::enable_if_t<is_floating_point_ex<T>::value,Writer&>operator<<(T x){if(x<0)putchar('-'),x=-x;x+=pow(10,-Setprecision)/2;mxdouble _=x;x-=(T)_;static int sta[45];int top=0;while(_)sta[++top]=_%10,_/=10;if(!top)putchar('0');while(top)putchar(sta[top]+'0'),--top;putchar('.');for(int i=0;i<Setprecision;i++)x*=10;_=x;while(_)sta[++top]=_%10,_/=10;for(int i=0;i<Setprecision-top;i++)putchar('0');while(top)putchar(sta[top]+'0'),--top;return*this;}template<typename T>typename std::enable_if_t<is_char<T>::value,Writer&>operator<<(T c){putchar(c);return*this;}Writer&operator<<(char*str){int cur=0;while(str[cur])putchar(str[cur++]);return *this;}Writer&operator<<(const char*str){int cur=0;while(str[cur])putchar(str[cur++]);return*this;}Writer&operator<<(std::string str){int st=0,ed=str.size();while(st<ed)putchar(str[st++]);return*this;}Writer(){}}cout;}
#define cin Fastio::cin
#define cout Fastio::cout
#define endl Fastio::endl
 
void solve();
main()
{
    int t=1;
//    cin>>t;
    while(t--)solve();
}
int fa[100001],a[100001],b[100001],sz[100001],mxson[100001],dfn[100001],dc=0,top[100001],ed[100001];
vector<int>son[100001];
template<typename A,typename B=vector<A>,typename C=less<A>>
struct pq_with_del
{
	priority_queue<A,B,C>pq,pq2;
	size_t size()
	{
		return pq.size()-pq2.size();
	}
	bool empty()
	{
		return size()==0;
	}
	A top()
	{
		while(!pq2.empty()&&pq.top()==pq2.top())pq.pop(),pq2.pop();
		return pq.top();
	}
	void pop()
	{
		while(!pq2.empty()&&pq.top()==pq2.top())pq.pop(),pq2.pop();
		pq.pop();
	}
	void push(A u)
	{
		pq.push(u);
	}
	void del(A u)
	{
		pq2.push(u);
	}
};
struct pq_with_del_kth
{
	pq_with_del<long long,vector<long long>,greater<long long>>pq;
	pq_with_del<long long,vector<long long>,less<long long>>pq2;
	int k;
	long long sum,smallest;
	void set_k(int k_){k=k_,sum=0,smallest=0;}
	void update()
	{
		while(pq.size()>k)
		{
			long long u=pq.top();
			sum-=u;
			pq2.push(u);
			pq.pop();
		}
		while(pq.size()<k&&!pq2.empty())
		{
			long long u=pq2.top();
			sum+=u;
			pq.push(u);
			pq2.pop();
		}
		if(pq.size()==k&&k)smallest=pq.top();
		else smallest=0;
	}
	void add(long long u)
	{
		if(u>=smallest)pq.push(u),sum+=u;
		else pq2.push(u);
		update();
	}
	void del(long long u)
	{
		if(u>=smallest)pq.del(u),sum-=u;
		else pq2.del(u);
		update();
	}
}pq[100001];
struct node
{
	long long a,b;
	node(long long a=0,long long b=0):a(a),b(b){}
	long long apply(long long x){return max(a+x,b);}
}tr[400001];
node operator+(const node&u,const node&v)
{
	return node(u.a+v.a,max(u.a+v.b,u.b));
}
void update(int u,int l,int r,int pos,node val)
{
	if(l==r)
	{
		tr[u]=val;
//		cerr<<pos<<','<<val.a<<','<<val.b<<','<<val.apply(0)<<endl;
		return;
	}
	int mi=(l+r)/2;
	if(pos<=mi)update(u*2,l,mi,pos,val);
	else update(u*2+1,mi+1,r,pos,val);
	tr[u]=tr[u*2]+tr[u*2+1];
}
long long query(int u,int l,int r,int L,int R,long long v)
{
	if(L<=l&&r<=R)return tr[u].apply(v);
	int mi=(l+r)/2;
	if(R<=mi)return query(u*2,l,mi,L,R,v);
	if(mi<L)return query(u*2+1,mi+1,r,L,R,v);
	return query(u*2,l,mi,L,R,query(u*2+1,mi+1,r,L,R,v));
}
int n;
void dfs0(int u)
{
	sz[u]=1;
	for(auto v:son[u])
	{
		dfs0(v),sz[u]+=sz[v];
		if(sz[v]>sz[mxson[u]])mxson[u]=v;
	}
}
long long rv[100001];
void to_add(int u)
{
//	cerr<<u<<','<<pq[u].sum<<','<<a[u]<<','<<pq[u].smallest<<endl;
	if(b[u]==0)update(1,1,n,dfn[u],node(-1e17,a[u]));
	else update(1,1,n,dfn[u],node(pq[u].sum+a[u]-pq[u].smallest,pq[u].sum+a[u]));
}
void dfs(int u,int nt)
{
	dfn[u]=++dc,top[u]=nt,ed[nt]=dc;
	if(mxson[u])dfs(mxson[u],nt);
	for(auto v:son[u])
	if(v!=mxson[u])
	{
		dfs(v,v);
		pq[u].add(rv[v]=query(1,1,n,dfn[v],ed[v],0));
//		cerr<<u<<','<<v<<','<<rv[v]<<endl;
	}
	to_add(u);
}
void modify(int u)
{
	to_add(u);
	u=top[u];
	while(fa[u])
	{
		long long nw=query(1,1,n,dfn[u],ed[u],0);
		if(nw==rv[u])return;
		pq[fa[u]].del(rv[u]);
		rv[u]=nw;
		pq[fa[u]].add(rv[u]);
		u=fa[u];
		to_add(u);
		u=top[u];
	}
}
long long ask(int u)
{
	return query(1,1,n,dfn[u],ed[top[u]],0);
}
void solve()
{
	cin>>n;
	for(int x=2;x<=n;x++)
	cin>>fa[x],son[fa[x]].emplace_back(x);
	for(int x=1;x<=n;x++)
	cin>>a[x]>>b[x],pq[x].set_k(b[x]);
	dfs0(1);
	dfs(1,1);
	int q;
	cin>>q;
	while(q--)
	{
		int op;
		cin>>op;
		if(op==1)
		{
			int pos,val;
			cin>>pos>>val;
			a[pos]=val;
			modify(pos);
		}
		else
		{
			int v;
			cin>>v;
			cout<<ask(v)<<endl;
		}
	}
}
