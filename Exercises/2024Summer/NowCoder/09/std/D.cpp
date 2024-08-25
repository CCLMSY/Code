#include<bits/stdc++.h>
#define ll long long
#define mxn 2097152
#define md 1000000007
#define pb push_back
#define mkp make_pair
#define ld long double
#define umap unordered_map
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
#define drep(i,a,b) for(int i=a;i>=b;--i)
#define pq priority_queue
using namespace std;
inline int read(){
	int x=0;char ch=getchar();
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x;
}
int n;
ll mn,ans,f[mxn];
signed main(){
	n=1<<read();
	rept(i,0,n)f[i]=read()?-1:1;
	for(int w=1;w<n;w<<=1){
		for(int j=0;j<n;j+=w<<1){
			rept(i,j,j+w){
				ll x=f[i],y=f[i+w];
				f[i]=x+y,f[i+w]=x-y;
			}
		}
	}
	mn=-2e18;
	rept(i,0,n){
		mn=max(mn,abs(f[i]));
		ll x=(n>>1)-(f[i]>>1);
		ans=(ans+x*x)%md;
		x=(n>>1)+(f[i]>>1);
		ans=(ans+x*x)%md;
	}
	cout<<ans<<" "<<(n>>1)-(mn>>1);
	return 0;
}