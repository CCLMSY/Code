#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

#define FORLL(i,l,r) for(ll i=l;i<=r;i++)
#define ALL(A) (A).begin(),(A).end()

struct DSU{
	vector<ll> fa,sz;
	ll n;
	DSU(ll _n){
		n=_n;
		fa.resize(n+1);
		sz.resize(n+1,1);
		FORLL(i,0,n) fa[i]=i;
	}
	ll find(ll x){
		if(fa[x]==x) return x;
		return (fa[x]=find(fa[x]));
	}
	void merge(ll x,ll y){
		x=find(x);
		y=find(y);
		if(x==y) return ;
		if(sz[x]<sz[y]) swap(x,y);
		sz[x]+=sz[y];
		fa[y]=x;		
	}
};

int main(){
	ll n,t;cin >> n;
	DSU dsu(n);
	FORLL(i,1,n){
		cin >> t;
		dsu.merge(i,t);
	}
	FORLL(i,1,n){
		cout << setw(6) << "i:" << i << setw(6) << "fa:" << dsu.find(i) << setw(6) << "sz:" << dsu.sz[dsu.find(i)] << endl;
	}
	return 0;
} 
