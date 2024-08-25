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
using vd = vector<db>;
using vs = vector<string>;
mt19937 mrand(time(0));

void solve(void)
{
	int n, m;
	cin >> n >> m;
	const ll INF = bit(60);

	vector<vector<array<ll, 4>>> p(n + 2);
	vector<array<ll, 5>> e(m + 2);
	vl val(n + 2, INF);

	for (int i = 1; i <= m; i++)
	{
		ll a, b, x, y, z;
		cin >> a >> b >> x >> y >> z;
		if (x > y) swap(x, y), swap(a, b);

		e[i] = {a, b, x, y, z};
		p[a].pb({b, x, y, z});
		p[b].pb({a, y, x, z});
		val[a] = min(val[a], x + z);
		val[b] = min(val[b], y + z);
	}

	auto cmax = [&](ll x, ll y, ll z)
	{
		if (x + z < y) return y;
		return (x + y + z + 1) / 2;
	};

	vector<array<ll, 3>> evt;
	for (int i = 1; i <= m; i++)
	{
		auto [a, b, x, y, z] = e[i];
		ll v1 = x + 1;
		evt.pb({v1, 1, i});
		ll v2 = y + 1;
		evt.pb({v2, 2, i});
		ll v3 = cmax(x, y, z) + 1;
		evt.pb({v3, 3, i});
	}

	vi fa(n + 2), sz(n + 2, 1), cnt(n + 2);
	for (int i = 1; i <= n; i++)
		fa[i] = i;

	function<int(int)> find = [&](int x)
	{
		if (x == fa[x]) return x;
		return fa[x] = find(fa[x]);
	};

	int sum = n;
	vi ans;
	vi state(n + 2);

	for (int i = 1; i <= n; i++)
		evt.pb({val[i], 4, i});

	auto gmark = [&](int x)
	{
		cnt[x]++;
		int ns = cnt[x] > 0;
		sum -= ns && (!state[x]);
		state[x] = ns;
	};

	auto rmark = [&](int x)
	{
		cnt[x]--;
		int ns = cnt[x] > 0;
		sum += (!ns) && state[x];
		state[x] = ns;
	};

	sort(all(evt));
	for (auto [i, tp, id] : evt)
	{
		if (tp == 1)
		{
			int fu = find(e[id][0]);
			gmark(fu);
		}
		else if (tp == 2)
		{
			int fu = find(e[id][0]);
			rmark(fu);

			int fv = find(e[id][1]);
			if (fu == fv)
			{
				gmark(fu);
				continue;
			}

			if (sz[fu] > sz[fv]) swap(fu, fv);
			fa[fu] = fv;
			sz[fv] += sz[fu];
			cnt[fv] += cnt[fu];
			sum += state[fu] + state[fv] - 1;
			state[fv] = cnt[fv] > 0;
			sum -= state[fv];
		}
		else if (tp == 3)
		{
			int fu = find(e[id][0]);
			gmark(fu);
		}
		else
		{
			for (auto [v, x, y, z] : p[id])
				if (i > y)
					gmark(find(v));

			gmark(find(id));

			if (!sum) ans.pb(id);

			for (auto [v, x, y, z] : p[id])
				if (i > y)
					rmark(find(v));
			rmark(find(id));
		}
	}


	sort(all(ans));
	cout << Sz(ans) << "\n";
	for (auto x : ans)
		cout << x << " ";
	cout << "\n";
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	// cout << fixed << setprecision(10);

	int T;
	cin >> T;
	for (int i = 1; i <= T; i++)
	solve();

	return 0;
}