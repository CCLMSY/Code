#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
const int mod=998244353;
struct node{
	int maxv,tot,lzt;
};
node merge(node x,node y){
	x.lzt=y.lzt=0;
	if(x.maxv==y.maxv) (x.tot+=y.tot)%=mod;
	if(x.maxv<y.maxv) swap(x,y);
	return x;
}
struct sgt{
	node f[1000005];
	void pushdown(int i){
		f[i*2].lzt+=f[i].lzt;
		f[i*2].maxv+=f[i].lzt;
		f[i*2+1].lzt+=f[i].lzt;
		f[i*2+1].maxv+=f[i].lzt;
		f[i].lzt=0;
	}
	void change(int i,int l,int r,int ql,int qr,int cg){
		if(ql<=l&&r<=qr){
			f[i].lzt+=cg;
			f[i].maxv+=cg;
			return ;
		}
		pushdown(i);
		if(ql<=mid) change(i*2,l,mid,ql,qr,cg);
		if(qr>mid) change(i*2+1,mid+1,r,ql,qr,cg);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
	void changep(int i,int l,int r,int pos,int val){
		if(l==r){
			f[i].tot=val;
			return ;
		}
		pushdown(i);
		if(pos<=mid) changep(i*2,l,mid,pos,val);
		else changep(i*2+1,mid+1,r,pos,val);
		f[i]=merge(f[i*2],f[i*2+1]);
	}
}tree;
vector<int> vc[200005];
int a[200005],p[15],dp[200005];
signed main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i],vc[i].push_back(0);
	for(int i=1;i<=m;i++) cin>>p[i];
	tree.changep(1,0,n,0,1);
	for(int i=1;i<=n;i++){
		vc[a[i]].push_back(i);
		int now=vc[a[i]].size()-1;
		for(int j=1;j<=m;j++){
			if(now>=p[j]) tree.change(1,0,n,vc[a[i]][now-p[j]],vc[a[i]][now-p[j]+1]-1,-1);
			if(now>=p[j]+1) tree.change(1,0,n,vc[a[i]][now-p[j]-1],vc[a[i]][now-p[j]]-1,1);
		}
		dp[i]=tree.f[1].tot;
		tree.changep(1,0,n,i,dp[i]);
	}
	cout<<dp[n]; 
	return 0;
}
