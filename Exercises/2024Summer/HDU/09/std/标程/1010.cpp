#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define all(x) (x).begin(), (x).end()
#define Sz(x) (int)(x).size()
#define bit(x) (1ll << (x))
using ll = long long;
using db = double;
using ull = unsigned long long;
using pii = pair<int, int>;
using vi = vector<int>;
using vii = vector<vi>;
using vl = vector<ll>;
using vll = vector<vl>;
using vs = vector<string>;
using vd = vector<db>;
mt19937 mrand(time(0));

void solve(void)
{
	int n, k;
	cin >> n >> k;
	vi b(n + 2);
	for (int i = 1; i <= n; i++)
		cin >> b[i];

	vector<vector<array<int, 2>>> e(n + 2);
	for (int i = 1; i < n; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		e[u].pb({v, w});
		e[v].pb({u, w});
	}

	const ll INF = bit(60);
	vll f(n + 2, vl(n * 2 + 2, INF));
	vi sz(n + 2), lef(n + 2);
	function<void(int, int)> dfs = [&](int u, int fa)
	{
		sz[u] = 1;
		int son = 0;
		f[u][1] = 0;
		if (b[u]) f[u][0] = 0;
		for (auto [v, w] : e[u])
			if (v != fa)
			{
				son++;
				dfs(v, u);
				vl g(n * 2 + 2, INF);
				for (int a = 0; a <= sz[u] * 2; a++)
					for (int b = 0; b <= sz[v] * 2; b++) if (f[u][a] < INF && f[v][b] < INF)
						g[a + b] = min(g[a + b], f[u][a] + f[v][b] + 1LL * abs(b - sz[v]) * k * 2 + ((b - sz[v] < lef[v]) ? w * 2 : 0));

				f[u] = g;
				sz[u] += sz[v];
				lef[u] += lef[v];
			}

		if (!son) 
		{
			f[u][2] = 0;
			lef[u] = 1;
		}
	};

	dfs(1, 0);

	cout << f[1][n] << "\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	// cout << fixed << setprecision(10);

	int T = 1;
	cin >> T;
	for (int i = 1; i <= T; i++)
	solve();

	return 0;
}