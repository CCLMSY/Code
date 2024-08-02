#include <bits/stdc++.h>
using tp = std::tuple<int, int, int, int>;
using pr = std::pair<int, int>;
using u64 = unsigned long long;
constexpr int K = 12, N = 1e5 + 10;
int n, m, k;
std::vector<std::pair<int, int>> vec[K];
struct dsu_t {
	int fa[N], siz[N];
	int find(int x) {return fa[x] == x ? x : fa[x] = find(fa[x]);}
	void init() {std::iota(fa + 1, fa + n + 1, 1); std::fill(siz +1 , siz + n + 1, 1);}
	void merge(int u, int v) {
		u = find(u), v = find(v); 
		if(siz[u] > siz[v]) std::swap(u, v);
		fa[u] = v; 
		siz[v] += siz[u];
	}
}dsu;
void clear() {
	for(int i = 1; i <= k; i ++) vec[i].clear();
}
void solve() {
	std::cin >> n >> m >> k;
	for(int i = 0; i < m; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		vec[w].emplace_back(u, v);
	}
	std::vector<int> cnt(1 << k);
	for(int s = 0; s < 1 << k; s ++) {
		int tot = 0;
		dsu.init();
		for(int i = 0; i < k; i ++) if(s >> i & 1) {
			for(auto [u, v] : vec[i + 1]) {
				if(dsu.find(u) != dsu.find(v)) {
					dsu.merge(u, v);
					tot ++;
				}
			}
		}
		cnt[s] = tot;
	}
	int flag = 0;
	for(int i = 1; i <= k; i ++) {
		int limit = cnt[1 << i - 1], ok = 1;
		for(int s = 0; s < 1 << k; s ++) if(s >> i - 1 & 1) {
			if(n - 1 - cnt[s] > (k - __builtin_popcount(s)) * limit) {
				ok = 0;
				break;
			}
		}
		if(ok) {
			std::cout << i << '\n';
			flag = 1;
			break;
		}
	}
	assert(flag);
}
int main() {
// 	freopen("in.txt", "r", stdin);
	std::ios::sync_with_stdio(false), std::cin.tie(0);
	int T;
	for(std::cin >> T; T; T --) {
		solve();
		clear();
	}
	return 0;
}