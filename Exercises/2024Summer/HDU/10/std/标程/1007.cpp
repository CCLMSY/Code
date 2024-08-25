#include <bits/stdc++.h>

void solve() {
	int n, m;
	std::cin >> n >> m;
	
	std::vector<std::basic_string<int>> g(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		std::cin >> u >> v;
		u--, v--;
		g[u].push_back(v), g[v].push_back(u);
	}

	std::string ans(n - 1, '?');

	std::vector<int> siz(n), bel(n, -1);
	auto dfs = [&](auto &&self, int u, int b) -> void {
		bel[u] = b;
		siz[b]++;
		for (int v : g[u]) {
			if (bel[v] == -1) self(self, v, b);
		}
	};
	for (int i = 0; i < n; i++) {
		if (bel[i] == -1) dfs(dfs, i, i);
	}
	for (int i = 1; i < n; i++) {
		if (bel[i] != bel[0]) {
			if (siz[bel[0]] == 1) ans[i - 1] = 'B';
			else if (siz[bel[i]] == 1) ans[i - 1] = 'A';
			else ans[i - 1] = 'D';
		}
	}

	std::vector<bool> tvis(n);
	std::vector<int> tdis(n);
	auto tdfs = [&](auto &&self, int u, int f) {
		tvis[u] = true;
		for (int v : g[u]) {
			if (v != f) {
				if (tvis[v]) return false;
				tdis[v] = tdis[u] + 1;
				if (!self(self, v, u)) return false;
			}
		}
		return true;
	};
	if (tdfs(tdfs, 0, -1)) {
		for (int i = 1; i < n; i++) {
			if (bel[i] == bel[0]) ans[i - 1] = tdis[i] & 1 ? 'B' : 'A';
		}
	} else {
		std::vector<int> deg(n), p(n), d(n);
		std::iota(p.begin(), p.end(), 0);
		std::queue<int> q;
		std::vector<bool> vis(n);
		std::stack<std::pair<int, int>> stk;
		for (int i = 0; i < n; i++) {
			if (bel[i] == bel[0]) {
				deg[i] = g[i].size();
				if (deg[i] == 1) q.push(i);
			}
		}
		while (q.size()) {
			int u = q.front();
			q.pop();
			vis[u] = true;
			for (int v : g[u]) {
				if (!vis[v]) {
					stk.emplace(u, v);
					if (--deg[v] == 1) q.push(v);
				}
			}
		}
		while (stk.size()) {
			auto [u, v] = stk.top();
			stk.pop();
			p[u] = p[v];
			d[u] = d[v] + 1;
		}

		auto bfs = [&](int s) {
			constexpr int inf = 1e9;
			std::vector dis(n, std::array<int, 2>{inf, inf});
			std::queue<std::pair<int, int>> q;
			dis[s][0] = 0;
			q.emplace(s, 0);
			while (q.size()) {
				auto [u, p] = q.front();
				q.pop();
				for (int v : g[u]) {
					if (dis[v][!p] == inf) {
						dis[v][!p] = dis[u][p] + 1;
						q.emplace(v, !p);
					}
				}
			}
			return dis;
		};
		auto dis0 = bfs(0), disp0 = bfs(p[0]);

		for (int i = 1; i < n; i++) {
			if (bel[i] == bel[0]) {
				bool alice = dis0[p[i]][d[i] & 1] <= d[i];
				bool bob = disp0[i][!(d[0] & 1)] <= d[0] - 1;
				assert(!(alice && bob));
				ans[i - 1] = alice ? 'A' : bob ? 'B' : 'D';
			}
		}
	}

	std::cout << ans << '\n';
}

signed main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	std::cin >> t;
	while (t--) solve();
}