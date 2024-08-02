#include <bits/stdc++.h>
using i64 = long long;
using poly = std::vector<int>;
constexpr int N = 2005, mod = 998244353;
constexpr int B = 50;
int n, d, k;
int fac[N], invfac[N], inv[N];
inline void upd(int &a, int b) {a += b, a = a >= mod ? a - mod : a;}
void init(int n) {
	fac[0] = invfac[0] = inv[1] = 1;
	for(int i = 2; i <= n; i ++) inv[i] = 1ll * inv[mod % i] * (mod - mod / i) % mod;
	for(int i = 1; i <= n; i ++) fac[i] = 1ll * fac[i - 1] * i % mod;
	for(int i = 1; i <= n; i ++) invfac[i] = 1ll * invfac[i - 1] * inv[i] % mod;
}
auto mul(auto a, auto b) {
	std::vector<int> c(n + 1);
	for(int i = 0; i <= n; i ++) if(a[i]) {
		for(int j = 0; i + j <= n; j ++) if(b[j]) {
			upd(c[i + j], 1ll * a[i] * b[j] % mod);
		}
	}
	return c;
}
int main() {
// 	freopen("in.txt", "r", stdin);
	std::ios::sync_with_stdio(false), std::cin.tie(0);
	init(500);
	std::cin >> n >> d >> k;
	if(d == 1) {
		std::cout << (n <= 2 ? 1 : 0) << '\n';
		return 0;
	} 
	poly f(n + 1), g(n + 1), h(n + 1), A(n + 1), B(n + 1); 
	for(int i = 0; i < d; i ++) {
		A[i] = invfac[i];
	}
	for(int i = 0; i < d - 1; i ++) {
		B[i] = invfac[i];
	}
	
	if(k == 1) {
		poly cur(n + 1); cur[0] = 1;
		for(int i = 1; i <= n; i ++) cur = mul(cur, A);
		std::cout << 1ll * cur[n - 2] * fac[n - 2] % mod << '\n';
		return 0;
	}
	{
		poly cur(n + 1); cur[0] = 1;
		for(int i = 1; i <= n; i ++) {
			cur = mul(cur, A);
			f[i] = 1ll * invfac[i - 1] * cur[i - 1] % mod * fac[i - 1] % mod;
		}
	}
	{
		poly cur(n + 1); cur[0] = 1;
		for(int i = 1; i <= n; i ++) {
			cur = mul(cur, i == 1 ? B : A);
			g[i] = 1ll * invfac[i - 1] * cur[i - 1] % mod * fac[i - 1] % mod;
		}
	}
	{
		h[1] = 1;
		poly cur = B;;
		for(int i = 2; i <= n; i ++) {
			cur = mul(cur, A);
			h[i] = 1ll * invfac[i - 1] * cur[i - 2] % mod * fac[i - 2] % mod;
		}
	}
	
	poly dp = f;
	for(int i = 2; i < k; i ++) {
		dp = mul(dp, g);;
	}
	dp = mul(dp, h);
	int ans = 1ll * dp[n] * fac[n - k] % mod;
	ans = 1ll * ans * fac[k] % mod * inv[2] % mod;
	std::cout << ans << '\n';
	std::cerr << 1.0 * clock() / CLOCKS_PER_SEC << '\n';
	return 0;
}