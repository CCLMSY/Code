#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

inline ll gcd(ll x, ll y){
	if(y) return gcd(y, x % y);
	else return x;
}

inline ll power(ll x, ll y){
	ll ret = 1;
	while(y --) ret *= x;
	return ret;
}

class frac{
public:
	ll u, v;
	inline frac() {}
	inline frac(ll u0, ll v0){
		u = u0, v = v0;
	}
};

inline bool operator < (frac a, frac b){
	return __int128(a.u) * b.v < __int128(b.u) * a.v;
}

ll c = 0, a = 0, b = 0;

inline void solve(){
	scanf("%lld %lld %lld", &c, &a, &b); a = max(a, b - a);
	frac ans = frac(0, 1);
	if(a == b) ans = max(frac(c, 2), frac(c - 1, 1));
	else if(2 * a == b) ans = frac(c, 2);
	else for(ll i = 0 ; i < 16 ; i ++){
		frac ret = frac(c * (2 * a - b) * power(a, i) - i * b * (power(a, i) - power(b - a, i)), (2 * a - b) * (power(a, i) + power(b - a, i)));
		ans = max(ans, ret);
	}
	ll g = gcd(ans.u, ans.v);
	printf("%lld/%lld\n", ans.u / g, ans.v / g);
}

ll T = 0;

int main(){
	scanf("%lld", &T);
	for(ll i = 0 ; i < T ; i ++) solve();
	return 0;
}
