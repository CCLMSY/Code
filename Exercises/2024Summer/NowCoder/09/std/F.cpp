#include <bits/stdc++.h>
using namespace std;
constexpr int Spp{1<<20};
char buf[Spp],*p1,*p2;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,Spp,stdin),p1==p2)?EOF:*p1++)
template <typename T>
void read(T &x) {
	char c;int f{1};
	do x=(c=getchar())^48;
	while (!isdigit(c)&&c!='-');
	if (x==29) f=-1,x=0;
	while (isdigit(c=getchar()))
		x=(x*10)+(c^48);
	x*=f;
}
template <typename T,typename ...Args>
void read(T& x,Args&... args) {read(x);read(args...);}
constexpr int S2=1<<20;
char buf2[S2],*l2=buf2;
#define putchar(c) (l2==buf2+S2&&(fwrite(buf2,1,S2,stdout),l2=buf2),*l2++=(c))
int _st[22];
template<typename T>inline void write(T x)
{
	if(x<0)
		putchar('-'),x=-x;
	int tp=0;
	do
		_st[++tp]=x%10;
	while(x/=10);
	while(tp)
		putchar(_st[tp--]+'0');
	putchar('\n');
}
constexpr int N(1e6);
using ll=long long;
int f[N+5],a[N+5],lb[N+5],d[N+5];
int n,q;
struct SegmentTree {
    #define ls (u<<1)
    #define rs (u<<1|1)
    struct node {
        int max;
        int cnt,lcnt;
        ll sum,lsum,tag;
    } seg[N<<2];
    int findl(int &v,int u,int tl,int tr) {
        if (seg[u].max<=v) return 0;
        if (tl==tr) return v=seg[u].max,1;
        int mid{(tl+tr)>>1};
        if (seg[rs].max>v) {
            int ret{seg[u].lcnt + findl(v, rs, mid + 1, tr)};
            v=seg[u].max;
            return ret; 
        }
        return findl(v,ls,tl,mid);
    }
    void apply(ll k,int u) {
        seg[u].sum+=k*seg[u].cnt;
        seg[u].lsum+=k*seg[u].lcnt;
        seg[u].tag+=k;
    }
    void pushDown(int u) {
        if (seg[u].tag) {
            apply(seg[u].tag,ls);
            apply(seg[u].tag,rs),
            seg[u].tag=0;
        }
    }
    void build(int u,int tl,int tr) {
        if (tl==tr) {
            seg[u].max=a[tl];
            seg[u].cnt=1;
            return;
        }
        int mid{(tl+tr)>>1};
        build(ls,tl,mid), build(rs,mid+1,tr);
        seg[u].max=max(seg[ls].max,seg[rs].max);
        int tmp{seg[rs].max};
        seg[u].cnt=(seg[u].lcnt=findl(tmp,ls,tl,mid))+seg[rs].cnt;
    }
    pair<int,int> update(int l,int r,ll k,int u,int tl,int tr) {
        if (l<=tl&&tr<=r) {
            apply(k,u);
            return {0,0};
        }
        if (r<tl||tr<l) return {seg[u].cnt,0};
        pushDown(u);
        int mid{(tl+tr)>>1};ll mn{seg[ls].sum};
        auto [l1,r1]{update(l,r,k,ls,tl,mid)};
        auto [l2,r2]{update(l,r,k,rs,mid+1,tr)};
        seg[u].sum=seg[ls].sum+seg[rs].sum-mn+seg[u].lsum;
        seg[u].sum-=min(seg[ls].cnt-l1-r1,max(0,seg[ls].cnt-seg[u].lcnt-r1))*k;
        seg[u].lsum=seg[u].sum-seg[rs].sum;
        if (l1+r1+l2+r2==seg[ls].cnt+seg[rs].cnt) return {seg[u].cnt,0};
        else if (l1+r1==seg[ls].cnt) return {seg[u].lcnt+l2,r2};
        else if (l2+r2==seg[rs].cnt) return {min(l1,seg[u].lcnt),seg[rs].cnt+max(0,r1-seg[ls].cnt+seg[u].lcnt)};
        else return {min(l1,seg[u].lcnt),r2};
    }
    ll query(int l,int r,int &v,int u,int tl,int tr) {
        if (v>=seg[u].max) return 0;
        if (tl==tr) return v=seg[u].max,seg[u].sum;
        pushDown(u);
        int mid{(tl+tr)>>1};
        if (l<=tl&&tr<=r) {
            if (seg[rs].max>v) {
                auto ret{seg[u].lsum+query(l,r,v,rs,mid+1,tr)};
                v=seg[u].max;
                return ret;
            }
            return query(l,r,v,ls,tl,mid);
        }
        ll ret{0};
        if (r>mid) ret+=query(l,r,v,rs,mid+1,tr);
        if (l<=mid) ret+=query(l,r,v,ls,tl,mid);
        return ret;
    }
    ll qry(int l,int r) {
        int tmp=-n-1;
        return query(l,r,tmp,1,1,n);
    }
    #undef ls
    #undef rs
} seg;
vector<int> e[N+5];
int LCA(int u,int v) {
	if (d[u]<d[v]) swap(u,v);
	while (d[u]>d[v])
		if (d[lb[u]]<d[v]) u=f[u];
		else u=lb[u];
	while (u!=v)
		if (lb[u]==lb[v]) u=f[u],v=f[v];
		else u=lb[u],v=lb[v];
	return u;
}
int main() {
	read(n,q);
	for (int u{2};u<=n;++u) {
        read(f[u]);
        d[u]=d[f[u]]+1;
        a[u]=-d[u];
        int p{f[u]},q{lb[p]},r{lb[q]};
        lb[u]=(d[p]-d[q]!=d[q]-d[r]?p:r);
	}
    seg.build(1,1,n);
    ll lst{0};
	while (q--) {
        ll op,l,r;read(op,l,r);
        l=(l^lst)%n+1;r=(r^lst)%n+1;
        if (op==1) {
            ll x;read(x);
            x=(x^lst)%n+1;
            seg.update(l,r,x,1,1,n);
        } else {
            int z{LCA(l,r)};
            ll ans{seg.qry(z,l)+seg.qry(z,r)-seg.qry(z,z)};
            write(ans);
            lst^=ans;
        }
	}
	fwrite(buf2,1,l2-buf2,stdout);
	return 0;
}