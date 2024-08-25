#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j);i<=(k);i++)
#define per(i,j,k) for(int i=(j);i>=(k);i--)
#define uint unsigned int
#define ll long long
#define ull unsigned long long
#define db double
#define ldb long double
#define pii pair<int,int>
#define pll pair<ll,ll>
#define mkp make_pair
#define eb emplace_back
#define SZ(S) (int)S.size()
//#define mod 998244353
//#define mod 1000000007
#define inf 0x3f3f3f3f
#define linf 0x3f3f3f3f3f3f3f3f
using namespace std;

template <class T>
void chkmax(T &x,T y){
	if(x < y) x = y;
}

template <class T>
void chkmin(T &x,T y){
	if(x > y) x = y;
}

inline int popcnt(int x){
	return __builtin_popcount(x);
}

inline int ctz(int x){
	return __builtin_ctz(x);
}


/*ll power(ll p,int k = mod - 2){
	ll ans = 1;
	while(k){
		if(k % 2 == 1) ans = ans * p % mod;
		p = p * p % mod;
		k /= 2;	
	}
	return ans;
}*/
int T,n;
int a[505],b[505];

int flow[1005][1005],cst[1005][1005];
void mk(int u,int v,int w,int c){
	flow[u][v] = w;cst[u][v] = c;
	cst[v][u] = -c;
}
int h[1005],dis[1005],prv[1005],vis[1005],answer;
int s,t;
void dijsktra(){
	fill(vis,vis + 2 * n + 2,0);
	fill(dis,dis + 2 * n + 2,inf);
	dis[s] = 0;
	while(1){
		int u = -1;
		rep(v,s,t) if(!vis[v] && (u == -1 || dis[v] < dis[u])) u = v;
		if(u == -1) break;

		vis[u] = 1;
		rep(v,s,t){
			if(!flow[u][v]) continue;
			assert(h[u] + cst[u][v] >= h[v]);
			if(dis[v] > dis[u] + h[u] + cst[u][v] - h[v]){
				dis[v] = dis[u] + h[u] + cst[u][v] - h[v];
				prv[v] = u;
			}
		}
	}
	int cur = t;
	while(cur != s){
		answer += cst[prv[cur]][cur];
		flow[prv[cur]][cur]--;
		flow[cur][prv[cur]]++;
		cur = prv[cur];
	}
//	rep(v,s,t) printf("%d ",dis[v] + h[v]);
//	printf("\n");
	rep(v,s,t) h[v] += dis[v];
}

void solve(){
	scanf("%d",&n);
	rep(i,1,n) scanf("%d",&a[i]);
	answer = 0;
	rep(i,1,n){
		scanf("%d",&b[i]);
		answer += b[i];
	}

	s = 0;t = 2 * n + 1;
	rep(u,s,t) fill(flow[u],flow[u] + t + 1,0);
	rep(i,1,n){
		h[2 * i - 1] = h[2 * i - 2];
		h[2 * i] = h[2 * i - 1] - b[i];
		mk(s,2 * i - 1,1,0);
		mk(2 * i - 1,2 * i,1,-b[i]);
		mk(2 * i,t,1,0);
	}
	h[t] = h[2 * n];
	rep(i,1,n){
		rep(j,i + 1,n) if(a[i] > a[j]) mk(2 * i,2 * j - 1,1,0);
	}
	rep(k,1,n){
		if(answer) dijsktra();
		printf("%d ",answer);
	}
	printf("\n");
}

int main(){	
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	scanf("%d",&T);
	while(T--) solve();
//	cerr << clock() << endl;
	return 0;
}