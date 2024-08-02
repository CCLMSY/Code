#include <bits/stdc++.h>
using i64 = long long;
constexpr int N = 1010, B = 20;
int n;
int a[N];
i64 mem1[N * N * B], *dp[N][N], *p1 = mem1;
int mem2[N * N * B], *opt[N][N], *p2 = mem2;
int main() {
// 	freopen("in.txt", "r", stdin);
	std::ios::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n;
	for(int i = 1; i <= n; i ++) {
		std::cin >> a[i];
	}
	for(int l = n; l >= 1; l --) {
		for(int r = l; r <= n; r ++) {
			dp[l][r] = p1 + B;
			p1 += 2 * B;
		}
	}
	for(int l = n; l >= 1; l --) {
		for(int r = l; r <= n; r ++) {
			opt[l][r] = p2 + B;
			p2 += 2 * B;
		}
	}
	memset(mem1, 0x3f, sizeof(mem1));
	int lim = B - 2;
	for(int l = n; l >= 1; l --) {
		for(int c = -lim; c <= lim; c ++) {
			dp[l][l][c] = 1ll * a[l] * c;
		}
		for(int r = l + 1; r <= n; r ++) {
			for(int c = -lim; c <= lim; c ++) {
				auto calc = [&] (int k) {
					i64 lval = dp[l][k][c - 1], rval = dp[k + 1][r][c + 1];
					if(lval + a[k + 1] < rval - a[k + 1]) return rval - a[k + 1];
					else if(lval + a[k] + 1 > rval - a[k] - 1) return lval + a[k] + 1;
					else return lval + rval < 0 ? (lval + rval) / 2 : (lval + rval + 1) / 2;
				};
				if(r == l + 1) {
					dp[l][r][c] = calc(l);
					opt[l][r][c] = l;
				} else {
					opt[l][r][c] = opt[l][r - 1][c];
					while(opt[l][r][c] + 1 < r && calc(opt[l][r][c]) > calc(opt[l][r][c] + 1)) {
						opt[l][r][c] ++;
					}
					dp[l][r][c] = calc(opt[l][r][c]);
				}
			}
		}
	}
	std::cout << dp[1][n][0] << '\n';
	return 0;
}