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
int T,n,m;
int _l[5005],_r[5005],_t[5005];

int _sumn,_summ;
int dp[5005],ndp[5005];
void solve(){
	scanf("%d%d",&n,&m);
	_sumn += n * n;
	_summ += m * m;
	rep(i,1,n) scanf("%d%d%d",&_l[i],&_r[i],&_t[i]);
	rep(i,2,n){
		assert(_l[i] <= _l[i - 1]);
		assert(_r[i] >= _r[i - 1]);
	}
	fill(dp,dp + m + 1,0);
	dp[0] = m + 1;
	per(i,n,1){
		rep(j,0,_l[i] - 1){
			if(_l[i] + _t[i] - 1 > _r[1]) break;
			chkmax(ndp[_l[i] + _t[i] - 1],dp[j]);
		}
		rep(j,_l[i],m){
			if(j + _t[i] > _r[1]) break;
			chkmax(ndp[j + _t[i]],dp[j]);
		}
		rep(j,0,m){
			dp[j] = max(ndp[j],min(dp[j] - 1,_r[i]) - _t[i] + 1);
			ndp[j] = 0;
		}
//		rep(j,0,m) cerr << dp[j] << " ";
//		cerr << endl; 
	}
	int Mx = 0;
	rep(j,0,_r[1]) if(dp[j] >= _l[1]) chkmax(Mx,dp[j] - j);
	if(Mx) printf("YES\n");
	else printf("NO\n");
}

int main(){	
//	freopen("example.in","r",stdin);
//	freopen("example.out","w",stdout);
	scanf("%d",&T);
	while(T--) solve();
//	cerr << _sumn << " " << _summ << endl;
	return 0;
}