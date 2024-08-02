#include <bits/stdc++.h>
constexpr int mod = 1e9 + 7;
using poly = std::vector<int>;
using i64 = long long;
constexpr int N = 1e7 + 10;
int n, m, fac[N], inv[N], invfac[N];
i64 lim;
int tot, pr[N / 10], power[N];
std::bitset<N> vis;
inline void upd(int &a, int b) {a += b - mod, a += a >> 31 & mod;}
int fpw(int a, int b) {
	int ans = 1;
	for(; b; b >>= 1, a = 1ll * a * a % mod) if(b & 1) ans = 1ll * ans * a % mod;
	return ans;
}
void init(int n, int N) {
	fac[0] = invfac[0] = inv[1] = 1;
	for(int i = 1; i <= n; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
	for(int i = 2; i <= n; i ++) inv[i] = 1ll * (mod - mod / i) * inv[mod % i] % mod;
	for(int i = 1; i <= n; i ++) invfac[i] = 1ll * invfac[i - 1] * inv[i] % mod;
	power[1] = 1;
	for(int i = 2; i <= n; i ++) {
		if(!vis[i]) pr[++ tot] = i, power[i] = fpw(i, N);
		for(int j = 1; j <= tot && pr[j] * i <= n; j ++) {
			vis[i * pr[j]] = 1;
			power[i * pr[j]] = 1ll * power[i] * power[pr[j]] % mod;
			if(i % pr[j] == 0) break;
		}
	}
}
int binom(int n, int m) {
	return 1ll * fac[n] * invfac[m] % mod * invfac[n - m] % mod;
}
poly calc(int a, int b) {
	// std::cout << "a" << std::endl;
	poly f(a + b + 1);
	f[0] = a & 1 ? mod - 1 : 1;
	f[1] = ((a & 1 ? mod - b : b) + (a - 1 & 1 ? mod - a : a)) % mod;
	for(int i = 2; i <= a + b; i ++) {
		f[i] = mod - 1ll * inv[i] * (1ll * a * (f[i - 2] + f[i - 1]) % mod + 1ll * b * (f[i - 2] - f[i - 1] + mod) % mod 
			- 1ll * (i - 2) * f[i - 2] % mod + mod) % mod;
	}
	// std::cout << "a" << std::endl;
	return f;
}
poly solve(int m, int lim, int A) {
	poly f(m + 1);
	int way = 1ll * m * binom(m - 1, lim) % mod * A % mod;
	auto res = calc(lim, m - lim - 1);
	for(int i = 0; i < m; i ++) f[i] = 1ll * way * res[i] % mod * inv[m - i] % mod;
	for(int i = 0; i <= lim; i ++) upd(f[m], 1ll * A * binom(m, i) % mod);
	return f;
} 
poly solve(int m, int lim, int A, int B) {
	auto g = solve(m - 1, lim - 1, mod - B);
	std::vector<int> f(m + 1);
	for(int i = 0; i < m; i ++) g[i] = 1ll * g[i] * m % mod;
	int way = 1ll * m * binom(m - 1, lim) % mod * (A + 1ll * lim * B % mod) % mod;
	auto res = calc(lim, m - lim - 1);
	for(int i = 0; i < m; i ++) upd(g[i], 1ll * way * res[i] % mod);
	for(int i = 0; i < m; i ++) f[i] = 1ll * g[i] * inv[m - i] % mod;
	for(int i = 0; i <= lim; i ++) upd(f[m], 1ll * binom(m, i) * (A + 1ll * i * B % mod) % mod);
	return f;
}
poly solve(int m, int lim, int A, int B, int C) {
	auto g = solve(m - 1, lim - 1,  mod - (B + C) % mod, mod - 2 * C % mod);
	std::vector<int> f(m + 1);
	for(int i = 0; i < m; i ++) g[i] = 1ll * g[i] * m % mod;
	int way = 1ll * m * binom(m - 1, lim) % mod * (A + 1ll * lim * B % mod + 1ll * lim * lim % mod * C % mod) % mod;
	auto res = calc(lim, m - lim - 1);
	for(int i = 0; i < m; i ++) upd(g[i], 1ll * way * res[i] % mod);
	for(int i = 0; i < m; i ++) f[i] = 1ll * g[i] * inv[m - i] % mod;
	for(int i = 0; i <= lim; i ++) upd(f[m], 1ll * binom(m, i) * (A + 1ll * i * B % mod + 1ll * i * i % mod * C % mod) % mod);
	return f;
}
int main() {
// 	freopen("in.txt", "r", stdin);
	std::ios::sync_with_stdio(false), std::cin.tie(0);
	std::cin >> n >> m >> lim;
	init(1e7, n);
	int X = n % 2 == 0 ? (1ll * (n + n / 2) * (n / 2 + 1) - n / 2) % mod : 1ll * ((n + 1) / 2 + n) * (n + 1) / 2 % mod, Y = mod - n, Z = 1;
	int A = (X + 1ll * Y * n % mod * inv[2] % mod + 1ll * Z * n * n % mod * inv[4] % mod) % mod;
	int B = mod - (1ll * Y * inv[2] + 1ll * Z * n * inv[2]) % mod;
	int C = 1ll * Z * inv[4] % mod;
	int l = 0, r = (m - (n & 1)) / 2, pos = -1;
	while(l <= r) {
		int mid = l + r >> 1;
		int match = (n - 2 * mid - (n & 1)) / 2;
		i64 ans = n % 2 == 0 ? 
			2ll * (n + n / 2) * (n / 2 + 1) / 2 - 2ll * match * (match + 1) / 2 - 1ll  * match * (n - 1 - 2 * match) - n / 2 : 
			1ll * ((n + 1) / 2 + n) * (n + 1) / 2 - 2ll * match * (match + 1) / 2 - 1ll * match * ((n - 1) - 2 * match);
		if(ans <= lim) pos = mid, l = mid + 1;
		else r = mid - 1;
// 		std::cout << match << ":" << ans << '\n';
	}
	if(pos == -1) {
		std::cout << 0 << '\n';
		return 0;
	}
	auto F = solve(m, pos * 2 + (n & 1), A, B, C);
	int ans = 0;
	for(int i = 0; i <= m; i ++) {
		upd(ans, 1ll * F[i] * (2 * i - m > 0 ? power[2 * i - m] : (n & 1 ? mod - power[m - 2 * i] : power[m - 2 * i])) % mod);
	}
	ans = 1ll * ans * fpw(fpw(2, m), mod - 2) % mod;
	std::cout << ans << '\n';
	std::cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n';
	return 0;
}