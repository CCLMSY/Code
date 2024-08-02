#include <bits/stdc++.h>
#define fp(i, a, b) for(int i(a), ed(b); i <= ed; ++i)
#define fb(i, a, b) for(int i(a), ed(b); i >= ed; --i)
#define go(u, i) for(int i(head[u]); i; i = e[i].nxt)
using namespace std;
const int maxn = 1<<18, mod = 998244353, G = 3, invG = 332748118;
int n, m, nxt[maxn], kmp[maxn][2];
int v[maxn], cnt[maxn], inv[maxn], f[maxn], g[maxn];
int lim, hst, rev[maxn];
char t[maxn];
inline void build(){
	int now = 0;
	fp(i, 2, m){
		while(now && t[now+1] != t[i])now = nxt[now];
		if(t[now+1] == t[i])++now;
		nxt[i] = now;
	}
	kmp[0][t[1]-'a'] = 1;
	fp(i, 1, m-1){
		int c = t[i+1]-'a';
		kmp[i][c] = i+1, kmp[i][!c] = kmp[nxt[i]][!c];
	}
}
inline int fpow(int a, int b, int ans = 1){
	for(; b; b >>= 1, a = 1ll*a*a%mod)if(b&1)ans = 1ll*ans*a%mod;
	return ans;
}
inline void ntt(int *a, int type){
	fp(i, 0, lim-1)if(i > rev[i])swap(a[i], a[rev[i]]);
	for(int md = 1; md < lim; md <<= 1){
		int len = md<<1, Gn = fpow(type ? invG : G, (mod-1)/len);
		for(int l = 0; l < lim; l += len){
			for(int nw = 0, Pow = 1; nw < md; ++nw, Pow = 1ll*Pow*Gn%mod){
				int x = a[l+nw], y = 1ll*Pow*a[l+nw+md]%mod;
				a[l+nw] = (x+y)%mod, a[l+nw+md] = (x-y+mod)%mod;
			}
		}
	}
	if(!type)return;
	int inv = fpow(lim, mod-2);
	fp(i, 0, lim-1)a[i] = 1ll*a[i]*inv%mod;
}
inline void init(int n){
	lim = 1, hst = 0;
	while(lim < n)lim <<= 1, ++hst;
	fp(i, 0, lim-1)rev[i] = (rev[i>>1]>>1) | ((i&1)<<hst-1);
}
int inv_ary[maxn];
void get_inv(int *a, int *f, int n){
	if(n == 1)return f[0] = fpow(a[0], mod-2), void();
	get_inv(a, f, n+1>>1), init(2*n-1);
	fp(i, 0, n-1)inv_ary[i] = a[i];
	ntt(f, 0), ntt(inv_ary, 0);
	fp(i, 0, lim-1)f[i] = 1ll*f[i]*(2-1ll*f[i]*inv_ary[i]%mod+mod)%mod;
	ntt(f, 1);
	fp(i, n, lim-1)f[i] = 0;
	fp(i, 0, lim-1)inv_ary[i] = 0;
}
int ln_ary[maxn];
inline void get_ln(int *a, int *f, int n){
	get_inv(a, ln_ary, n), init(2*n-2);
	fp(i, 1, n-1)f[i-1] = 1ll*a[i]*i%mod;
	ntt(f, 0), ntt(ln_ary, 0);
	fp(i, 0, lim-1)f[i] = 1ll*f[i]*ln_ary[i]%mod;
	ntt(f, 1);
	fp(i, n, lim-1)f[i] = 0;
	fp(i, 0, lim-1)ln_ary[i] = 0;
	fb(i, n-1, 1)f[i] = 1ll*f[i-1]*inv[i]%mod;
	f[0] = 0;
}
int exp_ary[maxn];
void get_exp(int *a, int *f, int n){
	if(n == 1)return f[0] = 1, void();
	get_exp(a, f, n+1>>1), get_ln(f, exp_ary, n), init(2*n-1);
	fp(i, 0, n-1)exp_ary[i] = (a[i]-exp_ary[i]+mod)%mod;
	if((++exp_ary[0]) == mod)exp_ary[0] = 0;
	ntt(f, 0), ntt(exp_ary, 0);
	fp(i, 0, lim-1)f[i] = 1ll*f[i]*exp_ary[i]%mod;
	ntt(f, 1);
	fp(i, n, lim-1)f[i] = 0;
	fp(i, 0, lim-1)exp_ary[i] = 0;
}
int main(){
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	cin >> n >> t+1, m = strlen(t+1);
	if(n < m){
		fp(i, 0, n)printf("0 ");
		return 0;
	}
	n -= m, build();
	fp(i, 0, m-1)fp(c, 0, 1)if(kmp[i][c] <= i)v[i+1] = i-kmp[i][c]+1;
	fp(i, 1, m)++cnt[v[i]];
	inv[1] = 1;
	fp(i, 2, n)inv[i] = mod - 1ll*(mod/i)*inv[mod%i]%mod;
	fp(i, 1, m)if(cnt[i])for(int j = i, d = 1; j <= n; j += i, ++d){
		if(d&1)f[j] = (f[j] + 1ll*cnt[i]*inv[d])%mod;
		else f[j] = (f[j] - 1ll*cnt[i]*inv[d]%mod + mod)%mod;
	}
	get_exp(f, g, n+1);
	fp(i, 1, m)cout << 0 << ' ';
	fp(i, 0, n)cout << g[i] << ' ';
	return 0;
}
