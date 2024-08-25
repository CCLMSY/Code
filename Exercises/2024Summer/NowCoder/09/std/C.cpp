#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 1000000007

char S[471];
int n, q, x, y, ans, Rsum[100471], Csum[100471], phi[100471], mark[100471];
vector<int> P, V[100471], Rmul[100471], Cmul[100471];
signed main() {
	scanf("%lld%lld", &n, &q);
	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (!mark[i]) {
			phi[i] = i - 1;
			P.push_back(i);
		}
		for (auto j : P) {
			if (i * j > n) {
				break;
			}
			mark[i * j] = 1;
			if (i % j == 0) {
				phi[i * j] = phi[i] * j;
				break;
			} else {
				phi[i * j] = phi[i] * (j - 1);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		int t = n / i;
		Rsum[i] = Csum[i] = t;
		Rmul[i].resize(t + 1, 1);
		Cmul[i].resize(t + 1, 1);
		for (int j = 1; j <= t; j++) {
			V[i * j].push_back(i);
		}
		ans = (ans + Rsum[i] * Csum[i] % mod * phi[i]) % mod;
	}
	while (q--) {
		scanf("%s%lld%lld", S, &x, &y);
		if (S[0] == 'R') {
			for (auto i : V[x]) {
				ans = (ans + mod - Rsum[i] * Csum[i] % mod * phi[i] % mod) % mod;
				Rsum[i] = (Rsum[i] + mod - Rmul[i][x / i]) % mod;
				Rmul[i][x / i] = Rmul[i][x / i] * y % mod;
				Rsum[i] = (Rsum[i] + Rmul[i][x / i]) % mod;
				ans = (ans + Rsum[i] * Csum[i] % mod * phi[i]) % mod;
			}
		} else {
			for (auto i : V[x]) {
				ans = (ans + mod - Rsum[i] * Csum[i] % mod * phi[i] % mod) % mod;
				Csum[i] = (Csum[i] + mod - Cmul[i][x / i]) % mod;
				Cmul[i][x / i] = Cmul[i][x / i] * y % mod;
				Csum[i] = (Csum[i] + Cmul[i][x / i]) % mod;
				ans = (ans + Rsum[i] * Csum[i] % mod * phi[i]) % mod;
			}
		}
		printf("%lld\n", ans);
	}
	fprintf(stderr, "%d\n", clock());
}
