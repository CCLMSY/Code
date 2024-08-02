#include <bits/stdc++.h>
constexpr int N = 5e4 + 10, L = 1010;
using bset = std::bitset<L>;
int n, m, q;
bset a[N];
int b[N], cnt[N][L], rk[L][N], pre[N][L];
std::vector<std::pair<int, int>> vec[L];
struct rmq {
	std::vector<std::vector<std::pair<int, int>>> st;	
	int n, m;
	void init(auto &vec) {
		n = vec.size();
		if(!n) return ;
		st.assign(m = std::__lg(n) + 1, vec);
		for(int i = 1; i < m; i ++) {
			for(int j = 0; j <= n - (1 << i); j ++) {
				st[i][j] = std::min(st[i - 1][j], st[i - 1][j + (1 << i - 1)]);
			}
		}
	}
	std::pair<int, int> query(int l, int r) {
		if(l > r) return {INT_MAX, -1};
		int k = std::__lg(r - l + 1);
		return std::min(st[k][l], st[k][r - (1 << k) + 1]);
	}
}ds[L];
int main() {
	// freopen("in.txt", "r", stdin);
	std::ios::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m >> q;
	memset(cnt[0], -1, sizeof cnt[0]);
	memset(pre, -1, sizeof pre); 
	for(int i = 1; i <= n; i ++) {
		std::cin >> a[i];
		int last = -1;
// 		for(int j = 0; j < m - j; j ++) {
// 			int o = a[i][j];
// 			a[i][j] = a[i][m - j - 1];
// 			a[i][m - j - 1] = o;
// 		}
		b[i] = -1;
		for(int j = 0; j < m; j ++) if(a[i][j]) {
			pre[i][j] = last;
			b[i] = ~b[i] ? j + 1 : j;  
			last = j;
		}
		memcpy(cnt[i], cnt[i - 1], sizeof cnt[i]);
		cnt[i][b[i]] ++;
	}
	static int sa[N], new_sa[N];
	std::iota(sa + 1, sa + n + 1, 1);
	for(int i = 0; i <= m; i ++) {
		int tot = 0;
		for(int j = 1; j <= n; j ++) {
			if(a[sa[j]][i] == 0) new_sa[++ tot] = sa[j]; 
		}
		for(int j = 1; j <= n; j ++) {
			if(a[sa[j]][i] == 1) new_sa[++ tot] = sa[j]; 
		}
		for(int j = 1; j <= n; j ++) {
			sa[j] = new_sa[j];
			rk[i][sa[j]] = j;
		}
	}
	for(int i = 1; i <= n; i ++) if(~b[i]) {
		vec[b[i]].emplace_back(a[i][b[i]] ? n + 1 : rk[b[i] - 1][i], i);
	}
	for(int i = 0; i <= m; i ++) {
		ds[i].init(vec[i]);
	}
	for(int i = 0; i < q; i ++) {
		int l, r;
		std::cin >> l >> r;
		assert(l <= r);
		int sum = 0, ans = 0, len = 0;
		static int buc[L];
		static std::pair<int, int> more[L];
		for(int i = 0; i <= m; i ++) {
			buc[i] = cnt[r][i] - cnt[l - 1][i];
			more[i] = {INT_MAX, -1};
			len += buc[i];
		}
		for(int i = 0; i <= m; i ++) {
			if(buc[i]) {
				ans = std::max(ans, len + i - sum);
				sum += buc[i];
			}
		}
		if(!sum) {
			std::cout << 0 << '\n';
			continue;
		}
		sum = 0;	
		int flag = 1;
		for(int i = m; i >= 0; i --) {
			if(buc[i]) {
				sum += buc[i];
				if(sum + i > ans) {
					flag = 0;
					break;
				} else if(sum + i == ans) {
					if(!i) continue;
					auto [type, pos] = std::min(more[i], ds[i].query(cnt[l - 1][i] + 1, cnt[r][i]));
					int k;
					if(type == n + 1) k = i - 1;
					else {
						k = pre[pos][i - 1];
						if(~pre[pos][k]) k ++;
						else type = n + 1;
					}
					buc[k] ++;
					more[k] = std::min(more[k], std::make_pair(type == n + 1 ? n + 1 : rk[k - 1][pos], pos));
				}
			}
		} 
		std::cout << ans - flag << '\n';
	}
	return 0;
}