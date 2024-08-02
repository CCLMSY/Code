#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e5 + 10, mod = 998244353;
int n, q, inv[N];
int ans;
struct lct {
	#define ls son[u][0]
	#define rs son[u][1]
	int siz[N], vsiz[N], fa[N], son[N][2];
	inline int nrt(int u) {return son[fa[u]][0] == u || son[fa[u]][1] == u;}
	inline int type(int u) {return son[fa[u]][1] == u;}
	inline void up(int u) {
		siz[u] = siz[ls] + siz[rs] + vsiz[u] + 1;
	}
	void rot(int u) {
		int f = fa[u], g = fa[f], k = type(u), w = son[u][!k];
		if(nrt(f)) son[g][type(f)] = u;
		son[u][!k] = f, son[f][k] = w;
		if(w) fa[w] = f;
		fa[u] = g, fa[f] = u;
		up(f), up(u);
	}
	void splay(int u) {
		while(nrt(u)) {
			int f = fa[u];
			if(nrt(f)) rot(type(u) == type(f) ? f : u);
			rot(u);
		}  
	}
	void access(int u) {
		for(int x = 0; u; u = fa[x = u]) {
			splay(u);
			if(rs) {
				ans = 1ll * ans * inv[siz[rs]] % mod;
				vsiz[u] += siz[rs];
			}
			if(x) {
				ans = 1ll * ans * siz[x] % mod;
				vsiz[u] -= siz[x];
			}
			rs = x, up(u);
		}
	}	
}ds;
int main() {
//	freopen("in.txt", "r", stdin);
	std::ios::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> q;
	for(int i = 2; i <= n; i ++) {
		std::cin >> ds.fa[i];
	}
	for(int i = n; i >= 1; i --) {
		ds.siz[i] = ds.vsiz[i] + 1;
		if(i > 1) {
			ds.vsiz[ds.fa[i]] += ds.siz[i];
		} 
	}
	inv[1] = 1;
	ans = 1;
	for(int i = 2; i <= n; i ++) inv[i] = 1ll  * (mod - mod / i) * inv[mod % i] % mod;
	for(int i = 2; i <= n; i ++) ans = 1ll * ans * inv[ds.siz[i]] % mod;
	int fac = 1;
	for(int i = 1; i < n; i ++) fac = 1ll * fac * i % mod;
	for(int i = 1; i <= q; i ++) {
		int u;
		std::cin >> u;
		ds.access(u);
		std::cout << 1ll * ans * fac % mod << '\n';
	}
	return 0;
}
