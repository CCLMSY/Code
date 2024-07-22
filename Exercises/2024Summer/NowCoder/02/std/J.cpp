#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;

#ifdef EMOFUNC
#include <debug.h>
#else
#define LOG(...)
#endif

const int mod = 998244353;

inline int add(int a, int b) { return a + b >= mod ? a + b - mod : a + b; }
inline void inc(int&a, int b) { if ((a += b) >= mod) a -= mod; }
inline int sub(int a, int b) { return a - b < 0 ? a - b + mod: a - b; }
inline void dec(int&a, int b) { if ((a -= b)<0) a += mod; }
inline int mul(int a, int b) { return (i64)a * b % mod; }

int qpow(int a, int n) {
    int ans = 1;
    for ( ; n; n >>= 1, a = i64(a) * a % mod) {
        if (n & 1) {
            ans = i64(ans) * a % mod;
        }
    }
    return ans;
}

namespace ntt {

// P = 998244353 = (119<<23) + 1
const int modinv2 = (mod + 1) / 2; // 1/2 in F_P
const int G = 3;

//-------------------------------NTT--------------------------------
int wn[30], iwn[30]; //wn[i] = G^((P-1)/(2^i)) (mod P), iwn[i] = wn[i]^(-1) (mod P)

//do this before NTT
inline void init() {
    wn[23] = qpow(G, (mod - 1) / (1 << 23));
    for (int i = 22; i >= 0; i--) {
        wn[i] = mul(wn[i + 1], wn[i + 1]);
    }

    iwn[23] = qpow(wn[23], (1 << 23) - 1);
    for (int i = 22; i >= 0; i--) {
        iwn[i] = mul(iwn[i + 1], iwn[i + 1]);
    }
}

inline void revbin_permute(int a[], int n) {
    int i = 1, j = n >> 1, k;
    for ( ; i < n - 1; i++) {
        if (i < j) swap(a[i], a[j]);
        for (k = n >> 1; j >= k; ) { j -= k; k >>= 1; }
        if (j < k) j += k;
    }
}

void NTT(int f[], int ldn, int is) {
    int n = (1 << ldn);
    revbin_permute(f, n);
    for (int i = 0; i < n; i += 2) {
        int tmp1 = f[i], tmp2 = f[i + 1];
        f[i] = add(tmp1, tmp2), f[i + 1] = sub(tmp1, tmp2);
    }
    for (int ldm = 2; ldm <= ldn; ldm++) {
        int m = (1 << ldm), mh = (m >> 1);
        int dw = is > 0 ? wn[ldm] : iwn[ldm], w = 1;
        for (int j = 0; j < mh; j++) {
            for (int r = 0; r < n; r += m) {
                int u = f[r + j], v = mul(f[r + j + mh], w);
                f[r + j] = add(u, v);
                f[r + j + mh] = sub(u, v);
            }
            w = mul(w, dw);
        }
    }
}

void convolution(int f[], int g[], int n) {
    int ldn = __lg(n);
    NTT(f, ldn, 1);
    NTT(g, ldn, 1); // g will be changed
    for (int i = 0; i < n; i++) {
        f[i] = mul(f[i], g[i]);
    }
    NTT(f, ldn, -1);
    int iv = qpow(n, mod-2);
    for (int i = 0; i < n; i++) {
        f[i] = mul(f[i], iv);
    }
}

}; // namespace ntt

namespace common {
    vector<int> fac;
    vector<int> ifac;
    vector<int> inv;

    void init(int n) {
        fac.resize(n + 1);
        ifac.resize(n + 1);
        inv.resize(n + 1);

        fac[0] = fac[1] = 1;
        ifac[0] = ifac[1] = 1;
        inv[1] = 1;
        for (int i = 2; i <= n; i++) {
            fac[i] = fac[i - 1] * i64(i) % mod;
            inv[i] = mod - mod / i * i64(inv[mod % i]) % mod;
            ifac[i] = ifac[i - 1] * i64(inv[i]) % mod;
        }
    }
}; // namespace common

struct matrix {
    matrix() = default;
    matrix(int n): n(n), v(n * n) {}

    static matrix id(int n) {
        matrix ident(n);
        for (int i = 0; i < n; i++) {
            ident.v[i * n + i] = 1;
        }
        return ident;
    }

    matrix operator * (const matrix& a) const {
        assert(n == a.n);
        matrix res(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    inc(res.v[i * n + k], mul(v[i * n + j], a.v[j * n + k]));
                }
            }
        }
        return res;
    }

    vector<int> v;
    int n;
};

template<typename T>
class spn {
public:
    spn(T* data, size_t len): data(data), len(len) {}
    T & operator [] (int idx) { return data[idx]; }
    size_t size() { return len; }
    spn<T> subspan(size_t start, size_t sublen) {
        return spn<T>(data + start, min(len - start, sublen));
    }
private:
    T* data;
    size_t len;
};

void lagrange(spn<const matrix> f, spn<const int> g, spn<matrix> outf, spn<int> outg, int o) {
    const int N = (1 << 18);
    static int a[N], b[N], c[N], d[N];

    using common::fac;
    using common::ifac;
    using common::inv;

    assert(f.size() == g.size());
    assert(outf.size() == outg.size());

    int n = f.size();
    int m = outf.size();
    
    while (o < n && m) {
        outf[0] = f[o];
        outg[0] = g[o];
        outf = outf.subspan(1, m - 1);
        outg = outg.subspan(1, m - 1);
        m--;
        o++;
    }

    if (m == 0) {
        return;
    }

    // ntt's length
    int ldn = __lg(n + n + m - 2) + 1;
    int len = 1 << ldn;
    assert(len <= N);

    int inv_len = qpow(len, mod - 2);
    for (int i = 0; i < n; i++) {
        a[i] = mul(ifac[i], ifac[n - 1 - i]);
        if ((n - 1 - i) & 1) {
            a[i] = mod - a[i];
        }
    }

    for (int i = 0; i < n + m; i++) {
        b[i] = qpow(add(sub(o, n - 1), i), mod - 2);
    }
    for (int i = n + m; i < len; i++) {
        b[i] = 0;
    }

    c[0] = 1;
    for (int i = 0; i < n; i++) {
        c[0] = mul(c[0], sub(o, i));
    }
    for (int i = 1; i < m; i++) {
        c[i] = mul(mul(c[i - 1], b[i - 1]), add(o, i)); 
    }

    ntt::NTT(b, ldn, 1);

    int md = f[0].n;
    for (int p = 0; p < md; p++) {
        for (int q = 0; q < md; q++) {
            for (int i = 0; i < n; i++) {
                d[i] = mul(a[i], f[i].v[p * md + q]);
            }
            for (int i = n; i < len; i++) {
                d[i] = 0;
            }
            ntt::NTT(d, ldn, 1);

            for (int i = 0; i < len; i++) {
                d[i] = mul(d[i], b[i]);
            }
            ntt::NTT(d, ldn, -1);

            for (int i = 0; i < m; i++) {
                outf[i].v[p * md + q] = mul(mul(d[n - 1 + i], c[i]), inv_len);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        d[i] = mul(a[i], g[i]);
    }
    for (int i = n; i < len; i++) {
        d[i] = 0;
    }
    ntt::NTT(d, ldn, 1);

    for (int i = 0; i < len; i++) {
        d[i] = mul(d[i], b[i]);
    }
    ntt::NTT(d, ldn, -1);

    for (int i = 0; i < m; i++) {
        outg[i] = mul(mul(d[n - 1 + i], c[i]), inv_len);
    }

}

// find a_n, where P_0(n) a_n = - \sum_{i=1}^{m} P_i(n) a_{n-i}
// param `a`: initial values a[0], ..., a[m - 1]
// param `p`: polynomial P_0(x), P_1(x), ..., P_m(x)
int p_recur(i64 n, const vector<int>& a, const vector<vector<int>>& p) {
    int m = a.size();

    if (n < m) {
        return a[n];
    }

    // k := max degree of P_i(n) 
    int k = int(p[0].size()) - 1;

    assert(m >= 1 && k >= 1 && p.size() == m + 1);

    auto eval = [](const vector<int>& p, int x) {
        int res = 0;
        for (int i = int(p.size()) - 1; i >= 0; i--) {
            res = add(mul(res, x), p[i]);
        }
        return res;
    };

    auto get_m = [&m, &p, &eval](int i) -> matrix {
        matrix mi(m);
        int val = eval(p[0], m + i);
        for (int j = 1; j < m; j++) {
            mi.v[j * m + j - 1] = val;
        }
        for (int j = 0; j < m; j++) {
            int val = eval(p[m - j], m + i);
            mi.v[j * m + m - 1] = val == 0 ? 0 : mod - val;
        }
        return mi;
    };

    i64 np = n - m + 1;

    auto get_f = [&get_m](int d, int x) -> matrix {
        matrix f = get_m(x);
        for (int i = 1; i < d; i++) {
            f = f * get_m(add(x, i));
        }
        return f;
    };

    auto get_g = [&m, &p, &eval](int d, int x) -> int {
        int g = eval(p[0], add(m, x));
        for (int i = 1; i < d; i++) {
            g = mul(g, eval(p[0], add(add(m, x), i)));
        }
        return g;
    };

    int s = ceil(sqrt(double(np) / k));
    int t = np / s;

    int tl = s * k + 1;
    assert(tl >= t);
    vector<matrix> f(tl, m);
    vector<int> g(tl);

    for (int i = 0; i <= k; i++) {
        f[i] = get_m(mul(i, s));
        g[i] = eval(p[0], add(m, mul(i, s)));
    }

    vector<matrix> tmpf(tl, m);
    vector<int> tmpg(tl);

    int inv_s = qpow(s, mod - 2);

    for (int i = __lg(s) - 1, d = 1; i >= 0; i--) {
        int dk = d * k;
        lagrange(
            spn<const matrix>(f.data(), dk + 1), spn<const int>(g.data(), dk + 1),
            spn<matrix>(f.data() + dk + 1, dk), spn<int>(g.data() + dk + 1, dk),
            dk + 1
        );
        lagrange(
            spn<const matrix>(f.data(), 2 * dk + 1), spn<const int>(g.data(), 2 * dk + 1),
            spn<matrix>(tmpf.data(), 2 * dk + 1), spn<int>(tmpg.data(), 2 * dk + 1),
            mul(d, inv_s)
        );

        for (int j = 0; j <= 2 * dk; j++) {
            f[j] = f[j] * tmpf[j];
            g[j] = mul(g[j], tmpg[j]);
        }
        
        d *= 2;

        if (!((s >> i) & 1)) {
            continue;
        }

        for (int j = d * k + 1; j <= (d + 1) * k; j++) {
            f[j] = get_f(d, mul(j, s));
            g[j] = get_g(d, mul(j, s));
        }

        for (int j = 0; j <= (d + 1) * k; j++) {
            f[j] = f[j] * get_m(add(mul(j, s), d));
            g[j] = mul(g[j], eval(p[0], add(m, add(mul(j, s), d))));
        }

        d++;
    }

    matrix M = matrix::id(m);
    int D = 1;
    
    for (int i = 0; i < t; i++) {
        M = M * f[i];
        D = mul(D, g[i]);
    }

    for (i64 i = i64(t) * s; i < np; i++) {
        M = M * get_m(i % mod);
        D = mul(D, eval(p[0], add(m, i % mod)));
    }

    int ans = 0;
    for (int i = 0; i < m; i++) {
        inc(ans, mul(a[i], M.v[i * m + (m - 1)]));
    }
    ans = mul(ans, qpow(D, mod - 2));

    return ans;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    ntt::init();
    common::init((1 << 18) - 1);

    i64 n;
    int a;
    cin >> n >> a;

    vector<int> f{1, a};
    vector<vector<int>> p{{mod - 1, 0}, {a, 0}, {mod - 1, 1}};
        
    int ans = p_recur(n, f, p);

    cout << ans << "\n";
    return 0;
}