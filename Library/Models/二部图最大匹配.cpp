#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// 二部图最大匹配 增广路算法
// 解决的问题：给定一个二分图G，即分左右两部分，各部分之间的点没有边连接
// 要求选出一些边，使得这些边没有公共顶点，且边的数量最大。
// 时间复杂度O(nm)
struct augment_path
{
	vector<vector<ll>> g;
	vector<ll> pa; // 匹配
	vector<ll> pb;
	vector<ll> vis; // 访问
	ll n, m;		// 两个点集中的顶点数量
	ll dfn;			// 时间戳记
	ll res;			// 匹配数
	augment_path(ll _n, ll _m) : n(_n+1), m(_m+1){
		assert(0 <= n && 0 <= m);
		pa = vector<ll>(n, -1);
		pb = vector<ll>(m, -1);
		vis = vector<ll>(n);
		g.resize(n);
		res = 0;
		dfn = 0;
	}
	// 添加一条左部点from到右部点to的边
	void add(ll from, ll to){
		assert(0 < from && from <= n && 0 < to && to <= m);
		g[from].push_back(to);
	}
	bool dfs(ll v)
	{
		vis[v] = dfn;
		for (ll u : g[v]){
			if (pb[u] == -1){
				pb[u] = v;
				pa[v] = u;
				return true;
			}
		}
		for (ll u : g[v]){
			if (vis[pb[u]] != dfn && dfs(pb[u])){
				pa[v] = u;
				pb[u] = v;
				return true;
			}
		}
		return false;
	}
	// 返回最大匹配数
	ll solve(){
		while (true){
			dfn++;
			ll cnt = 0;
			for (ll i = 0; i < n; i++)
				if (pa[i] == -1 && dfs(i)) cnt++;
			if (cnt == 0) break; 
			res += cnt;
		}
		return res;
	}
};
int main()
{
	ll n, m, e;
	cin >> n >> m >> e;
	augment_path G(n, m);
	ll u, v;
	for (ll i = 0; i < e; i++)
	{
		cin >> u >> v;
		G.add(u, v);
	}
	cout << G.solve() << endl;
	return 0;
}