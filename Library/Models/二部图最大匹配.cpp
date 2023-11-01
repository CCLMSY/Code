#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
struct augment_path {
	vector<vector<ll> > g;
	vector<ll> pa;  // 匹配
	vector<ll> pb;
	vector<ll> vis;  // 访问
	ll n, m;         // 两个点集中的顶点数量
	ll dfn;          // 时间戳记
	ll res;          // 匹配数
	augment_path(ll _n, ll _m) : n(_n), m(_m) {
		assert(0 <= n && 0 <= m);
		pa = vector<ll>(n, -1);
		pb = vector<ll>(m, -1);
		vis = vector<ll>(n);
		g.resize(n);
		res = 0;
		dfn = 0;
	}
	void add(ll from, ll to) {
		assert(0 <= from && from < n && 0 <= to && to < m);
		g[from].push_back(to);
	}
	bool dfs(ll v) {
		vis[v] = dfn;
		for (ll u : g[v]) {
			if (pb[u] == -1) {
				pb[u] = v;
				pa[v] = u;
				return true;
			}
		}
		for (ll u : g[v]) {
			if (vis[pb[u]] != dfn && dfs(pb[u])) {
				pa[v] = u;
				pb[u] = v;
				return true;
			}
		}
		return false;
	}
	ll solve() {
		while (true) {
			dfn++;
			ll cnt = 0;
			for (ll i = 0; i < n; i++) {
				if (pa[i] == -1 && dfs(i)) {
					cnt++;
				}
			}
			if (cnt == 0) {
				break;
			}
			res += cnt;
		}
		return res;
	}
};
int main(){
    ll n,m;
    cin >> n >> m;
    augment_path G(n,n);
    ll u,v;
    for(ll i=0;i<m;i++){
        cin >> u >> v;
        G.add(u,v);
    }cout << G.solve() << endl;
    return 0;
}