#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 55;
int n, m;
i64 G[N];
int main() {
// 	freopen("in.txt", "r", stdin);
	std::ios::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m;
	for(int i = 1; i <= m; i ++) {
		int u, v;
		std::cin >> u >> v;
		u --, v --;
		G[u] |= 1ll << v;
		G[v] |= 1ll << u;
	}
	int ans = 0;
	for(int i = 0; i < n; i ++) {
		std::function<void(int, int, i64)> dfs = [&] (int u, int cnt, i64 ban) {
			i64 next = G[u] & ~ban;
			ans = std::max(ans, cnt);
			while(next) {
				int i = __builtin_ctzll(next);
				next ^= 1ll << i;
				dfs(i, cnt + 1, ban | G[u]);
			}
		};
		dfs(i, 1, 1ll << i);
	}
	std::cout << ans << '\n';
	std::cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n';
	return 0;
}