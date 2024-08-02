#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;
const int M = 1e9 + 7, inf = 0x3f3f3f3f;

struct PInt {
	int key, val;
	PInt(int v = 0) : key(v), val(v % M) {}
	PInt(ll v) : key(min(v, ll(inf))), val(v % M) {}
	friend PInt operator+(const PInt &a, const PInt &b) {
		PInt res;
		res.key = min(inf, a.key + b.key);
		res.val = a.val + b.val;
		res.val -= (res.val >= M ? M : 0);
		return res;
	}
	friend PInt operator-(const PInt &a, const PInt &b) {
		PInt res;
		res.key = (a.key == inf ? inf : a.key - b.key);
		res.val = a.val - b.val;
		res.val += (res.val < 0 ? M : 0);
		return res;
	}
	friend PInt operator*(const PInt &a, const PInt &b) {
		PInt res;
		res.key = min(ll(inf), 1ll * a.key * b.key);
		res.val = 1ll * a.val * b.val % M;
		return res;
	}
	friend bool operator<(const PInt &a, const PInt &b) {
		return a.key < b.key;
	}
	friend int udiv(const PInt &a, const PInt &b) {
		return (a.key + b.key - 1) / b.key;
	}
	operator int() const {
		return val;
	}
};

struct Node {
	PInt mul, base, rem;
	Node() : mul(1), base(0), rem(0) {}
	PInt operator()(PInt x) const {
		return rem + mul * (x - base);
	}
	friend Node operator+(const Node &a, const Node &b) {
		Node res;
		res.mul = a.mul * b.mul;
		if (a.rem < b.base) {
			auto r = b.base - a.rem;
			auto d = PInt(udiv(r, a.mul));
			res.base = a.base + d;
			res.rem = b(a.rem + a.mul * d);
		} else {
			res.base = a.base;
			res.rem = b(a.rem);
		}
		return res;
	}
};

struct Segt {
	const int N;
	vector<int> lx, pc;
	vector<Node> t;
	Segt(vector<int> l) : N(l.size() - 1), lx(l), pc(N), t(N << 2 | 1) {
		build(1, 0, N - 1);
	}
	void mul(int x, int v) {
		if (t[v].mul.key == inf) {
			t[v].rem = t[v].rem + t[v].mul;
		} else {
			int len = lx[x + 1] - lx[x];
			ll mul = t[v].mul.key * 2ll;
			ll dv = (len + mul - 1) / mul;
			ll rem = dv * mul - len;
			t[v].rem = PInt(rem);
			t[v].base = PInt(dv);
		}
		t[v].mul = t[v].mul * PInt(2);
	}
	void mul(int loc) {
		int x = lower_bound(lx.begin(), lx.end(), loc) - lx.begin();
		mul(x, 1, 0, N - 1);
	}
	int calc(int x) {
		auto [t, r] = calc(x, 1, 0, N - 1);
		return int(t + r);
	}
#define mid ((l + r) >> 1)
#define ls (v << 1)
#define rs (v << 1 | 1)
	void build(int v, int l, int r) {
		if (l == r) {
			t[v].base = lx[l + 1] - lx[l];
		} else {
			build(ls, l, mid);
			build(rs, mid + 1, r);
			t[v] = t[ls] + t[rs];
		}
	}
	void mul(int loc, int v, int l, int r) {
		if (l == r) {
			mul(loc, v);
		} else {
			if (loc <= mid) {
				mul(loc, ls, l, mid);
			} else {
				mul(loc, rs, mid + 1, r);
			}
			t[v] = t[ls] + t[rs];
		}
	}
	pair<PInt, PInt> calc(PInt x, int v, int l, int r) {
		if (!(PInt(x) < t[v].base)) {
			return {lx[r + 1] - lx[l], t[v](x)};
		} else {
			if (l == r) {
				return {x * t[v].mul, PInt(0)};
			}
			auto [t, rem] = calc(x, ls, l, mid);
			if (rem.key > 0) {
				auto [tx, rx] = calc(rem, rs, mid + 1, r);
				t = t + tx;
			}
			return {t, PInt(0)};
		}
	}
#undef rs
#undef ls
#undef mid
};

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	int q;
	cin >> q;
	vector<pair<int, int>> qr(q);
	vector<int> p = {0, inf};
	for (auto &[o, x] : qr) {
		cin >> o >> x;
		p.emplace_back(x);
	}
	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end());
	Segt tr(p);
	for (auto [o, x] : qr) {
		if (o == 1) {
			tr.mul(x);
		} else {
			cout << tr.calc(x) << '\n';
		}
	}
	return 0;
}
