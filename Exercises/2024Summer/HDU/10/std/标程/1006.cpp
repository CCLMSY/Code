#include <bits/stdc++.h>

constexpr int P = 998244353;

int power(int x, int y) {
	int res = 1;
	for (; y; y >>= 1) {
		if (y & 1) res = 1ll * res * x % P;
		x = 1ll * x * x % P;
	}
	return res;
}

std::vector<int> fac, ivfac;
void init(int n) {
	fac.resize(n + 1), ivfac.resize(n + 1);
	fac[0] = 1;
	for (int i = 1; i <= n; i++) fac[i] = 1ll * fac[i - 1] * i % P;
	ivfac[n] = power(fac[n], P - 2);
	for (int i = n; i >= 1; i--) ivfac[i - 1] = 1ll * ivfac[i] * i % P;
}
int binom(int n, int m) {
	if (n < m || m < 0) return 0;
	return 1ll * fac[n] * ivfac[m] % P * ivfac[n - m] % P;
}

void ntt(std::vector<int> &a, bool rev) {
	int n = a.size();
	static std::vector<int> r;
	if (r.size() != n) {
		r.resize(n);
		for (int i = 0; i < n; i++) r[i] = ((i & 1) ? (n >> 1) : 0) | (r[i >> 1] >> 1);
	}
	static std::vector<int> rt = {0, 1};
	if (rt.size() < n) {
		int i = std::__lg(rt.size());
		rt.resize(n);
		while ((1 << i) < n) {
			int w = power(3, (P - 1) >> (i + 1));
			for (int j = 1 << (i - 1); j < (1 << i); j++) {
				rt[j << 1] = rt[j];
				rt[j << 1 | 1] = 1ll * rt[j] * w % P;
			}
			i++;
		}
	}
	for (int i = 0; i < n; i++) if (r[i] < i) std::swap(a[i], a[r[i]]);
	for (int k = 1; k < n; k <<= 1) {
		for (int i = 0; i < n; i += k << 1) {
			for (int j = 0; j < k; j++) {
				int u = a[i + j], v = 1ll * a[i + j + k] * rt[j + k] % P;
				(a[i + j] = u + v) >= P && (a[i + j] -= P);
				(a[i + j + k] = u - v) < 0 && (a[i + j + k] += P);
			}
		}
	}
	if (rev) {
		std::reverse(a.begin() + 1, a.end());
		int ivn = power(n, P - 2);
		for (int &i : a) i = 1ll * i * ivn % P;
	}
}
std::vector<int> multiply(std::vector<int> a, std::vector<int> b) {
	int d = a.size() + b.size() - 1;
	if (std::min(a.size(), b.size()) <= 20 || std::max(a.size(), b.size()) <= 100) {
		std::vector<int> c(d);
		for (int i = 0; i < a.size(); i++) {
			for (int j = 0; j < b.size(); j++) c[i + j] = (c[i + j] + 1ll * a[i] * b[j]) % P;
		}
		return c;
	}
	int n = 1;
	while (n < d) n <<= 1;
	a.resize(n), b.resize(n);
	ntt(a, 0), ntt(b, 0);
	std::vector<int> c(n);
	for (int i = 0; i < n; i++) c[i] = 1ll * a[i] * b[i] % P;
	ntt(c, 1);
	c.resize(d);
	return c;
}
std::vector<int> inverse(const std::vector<int> &a, int n) {
	int m = 1;
	std::vector<int> b = {power(a[0], P - 2)}, c;
	while (m < n) {
		m <<= 1;
		if (m <= a.size()) c = std::vector<int>(a.begin(), a.begin() + m);
		else (c = a).resize(m);
		c = multiply(b, c);
		for (int &i : c) i = i ? P - i : 0;
		(c[0] += 2) >= P && (c[0] -= P);
		b = multiply(b, c);
		b.resize(m);
	}
	b.resize(n);
	return b;
}
std::vector<int> mulT(std::vector<int> a, std::vector<int> b) {
	if (b.empty()) return {};
	std::reverse(b.begin(), b.end());
	a = multiply(a, b);
	a.erase(a.begin(), a.begin() + b.size() - 1);
	return a;
}
std::vector<int> evaluation(const std::vector<int> &poly, const std::vector<int> &val) {
	std::vector<int> res(val.size());
	if (poly.empty()) return res;
	int n = std::max(poly.size(), val.size());
	std::vector<std::vector<int>> t(n << 2);
	auto build = [&](auto &&self, int p, int l, int r) -> void {
		if (l + 1 == r) {
			if (l < val.size()) t[p] = {1, val[l] ? P - val[l] : 0};
			else t[p] = {1};
		} else {
			int m = (l + r) >> 1;
			self(self, p << 1, l, m), self(self, p << 1 | 1, m, r);
			t[p] = multiply(t[p << 1], t[p << 1 | 1]);
		}
	};
	build(build, 1, 0, n);
	auto work = [&](auto &&self, int p, int l, int r, std::vector<int> a) -> void {
		if (l + 1 == r) {
			if (l < val.size()) res[l] = a[0];
		} else {
			int m = (l + r) >> 1;
			std::vector<int> f = mulT(a, t[p << 1 | 1]), g = mulT(a, t[p << 1]);
			f.resize(m - l), g.resize(r - m);
			self(self, p << 1, l, m, f), self(self, p << 1 | 1, m, r, g);
		}
	};
	work(work, 1, 0, n, mulT(poly, inverse(t[1], n)));
	return res;
}

void solve() {
	int n, m;
	std::cin >> n >> m;
	init(m);
	std::vector<int> a(n);
	for (int &i : a) std::cin >> i;
	int mx = *std::max_element(a.begin(), a.end());

	std::vector<int> f(m);
	int coef = 1;
	for (int i : a) coef = 1ll * coef * ivfac[i] % P * ivfac[mx - i] % P;
	f[mx] = 1ll * power(fac[mx], n) * coef % P;
	if (mx < m - 1) {
		auto get = [&](auto &&self, int l, int r) -> std::vector<int> {
			if (l + 1 == r) return {a[l] ? P - a[l] : 0, 1};
			int m = (l + r) >> 1;
			return multiply(self(self, l, m), self(self, m, r));
		};
		std::vector<int> poly = get(get, 0, n), val(m - mx - 1);
		for (int i = mx + 1; i < m; i++) val[i - mx - 1] = i;
		std::vector<int> res = evaluation(poly, val);
		for (int i = mx + 1; i < m; i++) {
			coef = 1ll * coef * power(res[i - mx - 1], P - 2) % P;
			f[i] = 1ll * power(fac[i], n) * coef % P;
		}
	}

	std::vector<int> g(m);
	for (int i = mx; i < m; i++) f[i] = 1ll * f[i] * ivfac[i] % P;
	for (int i = 0; i < m; i++) g[i] = (i & 1) ? P - ivfac[i] : ivfac[i];
	g = multiply(f, g);
	for (int i = 0; i < m; i++) g[i] = 1ll * g[i] * fac[i] % P;

	int ans = 0;
	for (int i = mx; i < m; i++) {
		ans = (ans + 1ll * binom(m, i) * g[i] % P * m % P * power(m - i, P - 2)) % P;
	}
	int tot = 1;
	for (int i : a) tot = 1ll * tot * binom(m, i) % P;
	std::cout << 1ll * ans * power(tot, P - 2) % P << '\n';
}

int main() {
	std::cin.tie(nullptr)->sync_with_stdio(false);
	int t;
	std::cin >> t;
	while (t--) solve();
}