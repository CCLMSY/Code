#include<bits/stdc++.h>

#include <algorithm>
#include <array>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder {

namespace internal {

// @param n `0 <= n`
// @return minimum non-negative `x` s.t. `n <= 2**x`
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return minimum non-negative `x` s.t. `(n & (1 << x)) != 0`
int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}  // namespace internal

}  // namespace atcoder



#include <utility>

namespace atcoder {

namespace internal {

// @param m `1 <= m`
// @return x mod m
constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

// Fast modular multiplication by barrett reduction
// Reference: https://en.wikipedia.org/wiki/Barrett_reduction
// NOTE: reconsider after Ice Lake
struct barrett {
    unsigned int _m;
    unsigned long long im;

    // @param m `1 <= m < 2^31`
    barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}

    // @return m
    unsigned int umod() const { return _m; }

    // @param a `0 <= a < m`
    // @param b `0 <= b < m`
    // @return `a * b % m`
    unsigned int mul(unsigned int a, unsigned int b) const {
        // [1] m = 1
        // a = b = im = 0, so okay

        // [2] m >= 2
        // im = ceil(2^64 / m)
        // -> im * m = 2^64 + r (0 <= r < m)
        // let z = a*b = c*m + d (0 <= c, d < m)
        // a*b * im = (c*m + d) * im = c*(im*m) + d*im = c*2^64 + c*r + d*im
        // c*r + d*im < m * m + m * im < m * m + 2^64 + m <= 2^64 + m * (m + 1) < 2^64 * 2
        // ((ab * im) >> 64) == c or c + 1
        unsigned long long z = a;
        z *= b;
#ifdef _MSC_VER
        unsigned long long x;
        _umul128(z, im, &x);
#else
        unsigned long long x =
            (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
        unsigned int v = (unsigned int)(z - x * _m);
        if (_m <= v) v += _m;
        return v;
    }
};

// @param n `0 <= n`
// @param m `1 <= m`
// @return `(x ** n) % m`
constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
    if (m == 1) return 0;
    unsigned int _m = (unsigned int)(m);
    unsigned long long r = 1;
    unsigned long long y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = (r * y) % _m;
        y = (y * y) % _m;
        n >>= 1;
    }
    return r;
}

// Reference:
// M. Forisek and J. Jancina,
// Fast Primality Testing for Integers That Fit into a Machine Word
// @param n `0 <= n`
constexpr bool is_prime_constexpr(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr long long bases[3] = {2, 7, 61};
    for (long long a : bases) {
        long long t = d;
        long long y = pow_mod_constexpr(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}
template <int n> constexpr bool is_prime = is_prime_constexpr(n);

// @param b `1 <= b`
// @return pair(g, x) s.t. g = gcd(a, b), xa = g (mod b), 0 <= x < b/g
constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};

    // Contracts:
    // [1] s - m0 * a = 0 (mod b)
    // [2] t - m1 * a = 0 (mod b)
    // [3] s * |m1| + t * |m0| <= b
    long long s = b, t = a;
    long long m0 = 0, m1 = 1;

    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b

        // [3]:
        // (s - t * u) * |m1| + t * |m0 - m1 * u|
        // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)
        // = s * |m1| + t * |m0| <= b

        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    // by [3]: |m0| <= b/g
    // by g != b: |m0| < b/g
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

// Compile time primitive root
// @param m must be prime
// @return primitive root (and minimum in now)
constexpr int primitive_root_constexpr(int m) {
    if (m == 2) return 1;
    if (m == 167772161) return 3;
    if (m == 469762049) return 3;
    if (m == 754974721) return 11;
    if (m == 998244353) return 3;
    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    int x = (m - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (int i = 3; (long long)(i)*i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) {
        divs[cnt++] = x;
    }
    for (int g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < cnt; i++) {
            if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}
template <int m> constexpr int primitive_root = primitive_root_constexpr(m);

}  // namespace internal

}  // namespace atcoder


#include <cassert>
#include <numeric>
#include <type_traits>

namespace atcoder {

namespace internal {

#ifndef _MSC_VER
template <class T>
using is_signed_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value ||
                                  std::is_same<T, __int128>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using is_unsigned_int128 =
    typename std::conditional<std::is_same<T, __uint128_t>::value ||
                                  std::is_same<T, unsigned __int128>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using make_unsigned_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value,
                              __uint128_t,
                              unsigned __int128>;

template <class T>
using is_integral = typename std::conditional<std::is_integral<T>::value ||
                                                  is_signed_int128<T>::value ||
                                                  is_unsigned_int128<T>::value,
                                              std::true_type,
                                              std::false_type>::type;

template <class T>
using is_signed_int = typename std::conditional<(is_integral<T>::value &&
                                                 std::is_signed<T>::value) ||
                                                    is_signed_int128<T>::value,
                                                std::true_type,
                                                std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<(is_integral<T>::value &&
                               std::is_unsigned<T>::value) ||
                                  is_unsigned_int128<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<
    is_signed_int128<T>::value,
    make_unsigned_int128<T>,
    typename std::conditional<std::is_signed<T>::value,
                              std::make_unsigned<T>,
                              std::common_type<T>>::type>::type;

#else

template <class T> using is_integral = typename std::is_integral<T>;

template <class T>
using is_signed_int =
    typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<is_integral<T>::value &&
                                  std::is_unsigned<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<is_signed_int<T>::value,
                                              std::make_unsigned<T>,
                                              std::common_type<T>>::type;

#endif

template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

template <class T> using to_unsigned_t = typename to_unsigned<T>::type;

}  // namespace internal

}  // namespace atcoder

#include <cassert>
#include <numeric>
#include <type_traits>

#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder {

namespace internal {

struct modint_base {};
struct static_modint_base : modint_base {};

template <class T> using is_modint = std::is_base_of<modint_base, T>;
template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;

}  // namespace internal

template <int m, std::enable_if_t<(1 <= m)>* = nullptr>
struct static_modint : internal::static_modint_base {
    using mint = static_modint;

  public:
    static constexpr int mod() { return m; }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    static_modint() : _v(0) {}
    template <class T, internal::is_signed_int_t<T>* = nullptr>
    static_modint(T v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }
    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    static_modint(T v) {
        _v = (unsigned int)(v % umod());
    }
    static_modint(bool v) { _v = ((unsigned int)(v) % umod()); }

    unsigned int val() const { return _v; }

    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        if (prime) {
            assert(_v);
            return pow(umod() - 2);
        } else {
            auto eg = internal::inv_gcd(_v, m);
            assert(eg.first == 1);
            return eg.second;
        }
    }

    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }

  private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }
    static constexpr bool prime = internal::is_prime<m>;
};

template <int id> struct dynamic_modint : internal::modint_base {
    using mint = dynamic_modint;

  public:
    static int mod() { return (int)(bt.umod()); }
    static void set_mod(int m) {
        assert(1 <= m);
        bt = internal::barrett(m);
    }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    dynamic_modint() : _v(0) {}
    template <class T, internal::is_signed_int_t<T>* = nullptr>
    dynamic_modint(T v) {
        long long x = (long long)(v % (long long)(mod()));
        if (x < 0) x += mod();
        _v = (unsigned int)(x);
    }
    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    dynamic_modint(T v) {
        _v = (unsigned int)(v % mod());
    }
    dynamic_modint(bool v) { _v = ((unsigned int)(v) % mod()); }

    unsigned int val() const { return _v; }

    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v += mod() - rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        _v = bt.mul(_v, rhs._v);
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        auto eg = internal::inv_gcd(_v, mod());
        assert(eg.first == 1);
        return eg.second;
    }

    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }

  private:
    unsigned int _v;
    static internal::barrett bt;
    static unsigned int umod() { return bt.umod(); }
};
template <int id> internal::barrett dynamic_modint<id>::bt = 998244353;

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
using modint = dynamic_modint<-1>;

namespace internal {

template <class T>
using is_static_modint = std::is_base_of<internal::static_modint_base, T>;

template <class T>
using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;

template <class> struct is_dynamic_modint : public std::false_type {};
template <int id>
struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};

template <class T>
using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;

}  // namespace internal

}  // namespace atcoder

#include <cassert>
#include <type_traits>
#include <vector>

namespace atcoder {

namespace internal {

template <class mint, internal::is_static_modint_t<mint>* = nullptr>
void butterfly(std::vector<mint>& a) {
    static constexpr int g = internal::primitive_root<mint::mod()>;
    int n = int(a.size());
    int h = internal::ceil_pow2(n);

    static bool first = true;
    static mint sum_e[30];  // sum_e[i] = ies[0] * ... * ies[i - 1] * es[i]
    if (first) {
        first = false;
        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1
        int cnt2 = bsf(mint::mod() - 1);
        mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
            // e^(2^i) == 1
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_e[i] = es[i] * now;
            now *= ies[i];
        }
    }
    for (int ph = 1; ph <= h; ph++) {
        int w = 1 << (ph - 1), p = 1 << (h - ph);
        mint now = 1;
        for (int s = 0; s < w; s++) {
            int offset = s << (h - ph + 1);
            for (int i = 0; i < p; i++) {
                auto l = a[i + offset];
                auto r = a[i + offset + p] * now;
                a[i + offset] = l + r;
                a[i + offset + p] = l - r;
            }
            now *= sum_e[bsf(~(unsigned int)(s))];
        }
    }
}

template <class mint, internal::is_static_modint_t<mint>* = nullptr>
void butterfly_inv(std::vector<mint>& a) {
    static constexpr int g = internal::primitive_root<mint::mod()>;
    int n = int(a.size());
    int h = internal::ceil_pow2(n);

    static bool first = true;
    static mint sum_ie[30];  // sum_ie[i] = es[0] * ... * es[i - 1] * ies[i]
    if (first) {
        first = false;
        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1
        int cnt2 = bsf(mint::mod() - 1);
        mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
            // e^(2^i) == 1
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_ie[i] = ies[i] * now;
            now *= es[i];
        }
    }

    for (int ph = h; ph >= 1; ph--) {
        int w = 1 << (ph - 1), p = 1 << (h - ph);
        mint inow = 1;
        for (int s = 0; s < w; s++) {
            int offset = s << (h - ph + 1);
            for (int i = 0; i < p; i++) {
                auto l = a[i + offset];
                auto r = a[i + offset + p];
                a[i + offset] = l + r;
                a[i + offset + p] =
                    (unsigned long long)(mint::mod() + l.val() - r.val()) *
                    inow.val();
            }
            inow *= sum_ie[bsf(~(unsigned int)(s))];
        }
    }
}

}  // namespace internal

template <class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> convolution(std::vector<mint> a, std::vector<mint> b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    if (std::min(n, m) <= 60) {
        if (n < m) {
            std::swap(n, m);
            std::swap(a, b);
        }
        std::vector<mint> ans(n + m - 1);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[i + j] += a[i] * b[j];
            }
        }
        return ans;
    }
    int z = 1 << internal::ceil_pow2(n + m - 1);
    a.resize(z);
    internal::butterfly(a);
    b.resize(z);
    internal::butterfly(b);
    for (int i = 0; i < z; i++) {
        a[i] *= b[i];
    }
    internal::butterfly_inv(a);
    a.resize(n + m - 1);
    mint iz = mint(z).inv();
    for (int i = 0; i < n + m - 1; i++) a[i] *= iz;
    return a;
}

template <unsigned int mod = 998244353,
          class T,
          std::enable_if_t<internal::is_integral<T>::value>* = nullptr>
std::vector<T> convolution(const std::vector<T>& a, const std::vector<T>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    using mint = static_modint<mod>;
    std::vector<mint> a2(n), b2(m);
    for (int i = 0; i < n; i++) {
        a2[i] = mint(a[i]);
    }
    for (int i = 0; i < m; i++) {
        b2[i] = mint(b[i]);
    }
    auto c2 = convolution(move(a2), move(b2));
    std::vector<T> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        c[i] = c2[i].val();
    }
    return c;
}

std::vector<long long> convolution_ll(const std::vector<long long>& a,
                                      const std::vector<long long>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    static constexpr unsigned long long MOD1 = 754974721;  // 2^24
    static constexpr unsigned long long MOD2 = 167772161;  // 2^25
    static constexpr unsigned long long MOD3 = 469762049;  // 2^26
    static constexpr unsigned long long M2M3 = MOD2 * MOD3;
    static constexpr unsigned long long M1M3 = MOD1 * MOD3;
    static constexpr unsigned long long M1M2 = MOD1 * MOD2;
    static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;

    static constexpr unsigned long long i1 =
        internal::inv_gcd(MOD2 * MOD3, MOD1).second;
    static constexpr unsigned long long i2 =
        internal::inv_gcd(MOD1 * MOD3, MOD2).second;
    static constexpr unsigned long long i3 =
        internal::inv_gcd(MOD1 * MOD2, MOD3).second;

    auto c1 = convolution<MOD1>(a, b);
    auto c2 = convolution<MOD2>(a, b);
    auto c3 = convolution<MOD3>(a, b);

    std::vector<long long> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        unsigned long long x = 0;
        x += (c1[i] * i1) % MOD1 * M2M3;
        x += (c2[i] * i2) % MOD2 * M1M3;
        x += (c3[i] * i3) % MOD3 * M1M2;
        // B = 2^63, -B <= x, r(real value) < B
        // (x, x - M, x - 2M, or x - 3M) = r (mod 2B)
        // r = c1[i] (mod MOD1)
        // focus on MOD1
        // r = x, x - M', x - 2M', x - 3M' (M' = M % 2^64) (mod 2B)
        // r = x,
        //     x - M' + (0 or 2B),
        //     x - 2M' + (0, 2B or 4B),
        //     x - 3M' + (0, 2B, 4B or 6B) (without mod!)
        // (r - x) = 0, (0)
        //           - M' + (0 or 2B), (1)
        //           -2M' + (0 or 2B or 4B), (2)
        //           -3M' + (0 or 2B or 4B or 6B) (3) (mod MOD1)
        // we checked that
        //   ((1) mod MOD1) mod 5 = 2
        //   ((2) mod MOD1) mod 5 = 3
        //   ((3) mod MOD1) mod 5 = 4
        long long diff =
            c1[i] - internal::safe_mod((long long)(x), (long long)(MOD1));
        if (diff < 0) diff += MOD1;
        static constexpr unsigned long long offset[5] = {
            0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
        x -= offset[diff % 5];
        c[i] = x;
    }

    return c;
}

}  // namespace atcoder

namespace polynomial {

template<typename T>
constexpr T power(T a, long long b) {
    T res = 1;
    while (b) {
        if (b & 1) res *= a;
        if (b > 1) a *= a;
        b >>= 1;
    }
    return res;
}

template <class T, atcoder::internal::is_static_modint_t<T>* = nullptr>
class Poly : public std::vector<T> {
public:
    Poly() : std::vector<T>() {}
    explicit Poly(size_t count) : std::vector<T>(count) {}
    Poly(size_t count, const T& value) : std::vector<T>(count, value) {}

    Poly(const std::vector<T>& other) : std::vector<T>(other) {}
    Poly(std::vector<T>&& other) : std::vector<T>(std::move(other)) {}
    Poly(const std::initializer_list<T>& init) : std::vector<T>(init) {}

    template<class InputIterator>
    Poly(InputIterator first, InputIterator last) : std::vector<T>(first, last) {}

public:
    Poly& resize(size_t k) {
        this->std::vector<T>::resize(k);
        return *this;
    }
    Poly& rev(bool strip = true) {
        std::reverse(this->begin(), this->end());
        return (strip ? this->strip() : *this);
    }
    Poly& shift(int k, bool strip = true) {
        if (k >= 0) {
            this->insert(this->begin(), k, T(0));
        } else {
            this->erase(this->begin(), this->begin() + std::min(this->size(), static_cast<size_t>(-k)));
        }
        return (strip ? this->strip() : *this);
    }
    Poly& strip() {
        while (!this->empty() && this->back() == T(0)) {
            this->pop_back();
        }
        return *this;
    }
    Poly& trunc(size_t k, bool strip = true) {
        this->resize(std::min(this->size(), k));
        return (strip ? this->strip() : *this);
    }

    friend Poly presize(const Poly& a, size_t k) {
        return Poly(a).resize(k);
    }
    friend Poly prev(const Poly& a, bool strip = true) {
        return Poly(a).rev(strip);
    }
    friend Poly pshift(const Poly& a, int k, bool strip = true) {
        return Poly(a).shift(k, strip);
    }
    friend Poly pstrip(const Poly& a) {
        return Poly(a).strip();
    }
    friend Poly ptrunc(const Poly& a, size_t k, bool strip = true) {
        Poly b = Poly(a.begin(), a.begin() + std::min(a.size(), k));
        return (strip ? b.strip() : b);
    }

public:
    T operator () (const T& x) const {
        T y(0);
        for (ssize_t i = this->size() - 1; i >= 0; --i) {
            y = y * x + (*this)[i];
        }
        return y;
    }
    Poly& operator += (const Poly& b) {
        this->resize(std::max(this->size(), b.size()));
        for (size_t i = 0; i < b.size(); ++i) {
            (*this)[i] += b[i];
        }
        return this->strip();
    }
    Poly& operator -= (const Poly& b) {
        this->resize(std::max(this->size(), b.size()));
        for (size_t i = 0; i < b.size(); ++i) {
            (*this)[i] -= b[i];
        }
        return this->strip();
    }
    Poly& operator *= (const Poly& b) {
        return *this = *this * b;
    }
    Poly& operator /= (const Poly& b) {
        if (this->size() < b.size()) {
            return *this = Poly();
        }
        size_t len = this->size() - b.size() + 1;
        if (len <= 60) {
            T inv = T(1) / b.back();
            Poly res(len);
            for (ssize_t i = len - 1; i >= 0; --i) {
                res[i] = (*this)[i + b.size() - 1] * inv;
                for (size_t j = 0; j < b.size(); ++j) {
                    (*this)[i + j] -= res[i] * b[j];
                }
            }
            return (*this = std::move(res));
        }
        return (this->rev().trunc(len) *= prev(b).inv(len)).resize(len).rev();
    }
    Poly& operator %= (const Poly& b) {
        return *this -= *this / b * b;
    }

    Poly operator + (const Poly& b) const {
        return Poly(*this) += b;
    }
    Poly operator - (const Poly& b) const {
        return Poly(*this) -= b;
    }
    Poly operator * (const Poly& b) const {
        return Poly(atcoder::convolution(*this, b)).strip();
    }
    Poly operator / (const Poly& b) const {
        return Poly(*this) /= b;
    }
    Poly operator % (const Poly& b) const {
        return Poly(*this) %= b;
    }

public:
    Poly inv(size_t m) const {
        Poly x(m);
        x[0] = T(1) / (*this)[0];
        for (size_t k = 1; k < m; k *= 2) {
            std::vector<T> r(k * 2);
            for (size_t i = 0; i < k; ++i) {
                r[i] = x[i];
            }
            atcoder::internal::butterfly(r);
            std::vector<T> f(k * 2);
            for (size_t i = 0; i < std::min(k * 2, this->size()); ++i) {
                f[i] = (*this)[i];
            }
            atcoder::internal::butterfly(f);
            for (size_t i = 0; i < k * 2; ++i) {
                f[i] *= r[i];
            }
            atcoder::internal::butterfly_inv(f);
            for (size_t i = 0; i < k; ++i) {
                f[i] = T(0);
            }
            T inv = T(1) / T(k * 2);
            for (size_t i = k; i < k * 2; ++i) {
                f[i] *= inv;
            }
            atcoder::internal::butterfly(f);
            for (size_t i = 0; i < k * 2; ++i) {
                f[i] *= r[i];
            }
            atcoder::internal::butterfly_inv(f);
            for (size_t i = k; i < std::min(k * 2, m); ++i) {
                x[i] = -f[i] * inv;
            }
        }
        return x.strip();
    }
    Poly deriv() const {
        if (this->empty()) {
            return Poly();
        }
        Poly x(this->size() - 1);
        for (size_t i = 0; i + 1 < this->size(); ++i) {
            x[i] = (*this)[i + 1] * T(i + 1);
        }
        return x.strip();
    }
    Poly integr() const {
        static std::vector<T> inv(1);
        while (inv.size() <= this->size()) {
            inv.resize(inv.size() * 2);
            for (size_t i = inv.size() / 2; i < inv.size(); ++i) {
                inv[i] = T(1) / T(i);
            }
        }
        Poly x(this->size() + 1);
        for (size_t i = 0; i < this->size(); ++i) {
            x[i + 1] = (*this)[i] * inv[i + 1];
        }
        return x.strip();
    }
    Poly log(size_t m) const {
        if (m == 0) {
            return Poly();
        }
        return (this->deriv().trunc(m) * this->inv(m)).trunc(m - 1).integr();
    }
    Poly exp(size_t m) const {
        Poly x{1};
        size_t k = 1;
        while (k < m) {
            k *= 2;
            (x *= Poly{1} - x.log(k) + ptrunc(*this, k)).trunc(k);
        }
        return x.trunc(m);
    }
    Poly pow(long long k, size_t m) const {
        if (k < 0) {
            return this->inv(m).pow(-k, m);
        }
        if (k == 0) {
            return Poly{1};
        }
        size_t i = 0;
        while (i < this->size() && (*this)[i] == T(0)) {
            i++;
        }
        if (i == this->size() || i >= (m + k - 1) / k) {
            return Poly();
        }
        T v = (*this)[i];
        return ((pshift(*this, -i) * Poly{T(1) / v}).log(m - i * k) * Poly{k}).exp(m - i * k).shift(i * k) * Poly{power(v, k)};
    }
    Poly sqrt(size_t m) const {
        Poly x{1};
        const Poly inv_2{T(1) / T(2)};
        size_t k = 1;
        while (k < m) {
            k *= 2;
            x = (x + (ptrunc(*this, k) * x.inv(k)).trunc(k)) * inv_2;
        }
        return x.trunc(m);
    }
    Poly mulT(Poly b) const {
        if (b.size() == 0) {
            return Poly();
        }
        int n = b.size();
        std::reverse(b.begin(), b.end());
        return ((*this) * b).shift(-(n - 1));
    }
    std::vector<T> eval(std::vector<T> x) const {
        if (this->size() == 0) {
            return std::vector<T>(x.size(), 0);
        }
        const int n = std::max(x.size(), this->size());
        std::vector<Poly> q(4 * n);
        std::vector<T> ans(x.size());
        x.resize(n);
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                q[p] = Poly{1, -x[l]};
            } else {
                int m = (l + r) / 2;
                build(2 * p, l, m);
                build(2 * p + 1, m, r);
                q[p] = q[2 * p] * q[2 * p + 1];
            }
        };
        build(1, 0, n);
        std::function<void(int, int, int, const Poly &)> work = [&](int p, int l, int r, const Poly &num) {
            if (r - l == 1) {
                if (l < static_cast<int>(ans.size())) {
                    ans[l] = num[0];
                }
            } else {
                int m = (l + r) / 2;
                work(2 * p, l, m, num.mulT(q[2 * p + 1]).resize(m - l));
                work(2 * p + 1, m, r, num.mulT(q[2 * p]).resize(r - m));
            }
        };
        work(1, 0, n, mulT(q[1].inv(n)));
        return ans;
    }
};

} // nameapace polynomial

using namespace std;
typedef atcoder::static_modint<1004535809> MINT;
typedef polynomial::Poly<MINT> POLY;
const int MAXN=130005;
namespace stt
{
vector<int> e[MAXN];
int sz[MAXN],son[MAXN];
void hld(int u)
{
    sz[u]=1;
    for(auto v : e[u])
    {
        hld(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[son[u]])
            son[u]=v;
    }
}
int idx[MAXN],ty[MAXN<<2|1],cnt;
int fa[MAXN<<2|1],lson[MAXN<<2|1],rson[MAXN<<2|1];
int new_node(int t)
{
    int n=++cnt;
    ty[n]=t;
    return n;
}
int merge(const vector<pair<int,int>>& p,int t)
{
    if(p.size()==1)return p[0].first;
    int n=new_node(t),u=0;
    for(auto& [_,s] : p)u+=s;
    vector<pair<int,int>> pl,pr;
    for(auto& [f,s] : p)
        (u>s ? pl : pr).emplace_back(f,s),u-=2*s;
    lson[n]=merge(pl,t),fa[lson[n]]=n;
    rson[n]=merge(pr,t),fa[rson[n]]=n;
    return n;
}
int compress(int u);
int rake(int u)
{
    int n=(idx[u]=new_node(0));
    vector<pair<int,int>> pson;
    for(auto v : e[u])
        if(v!=son[u])pson.emplace_back(compress(v),sz[v]);
    if(!pson.empty())lson[n]=merge(pson,1),fa[lson[n]]=n,rson[n]=-1;
    return n;
}
int compress(int u)
{
    vector<pair<int,int>> ppath;
    for(int p=u; p; p=son[p])
        ppath.emplace_back(rake(p),sz[p]-sz[son[p]]);
    return merge(ppath,0);
}
POLY f[MAXN<<2|1],g[MAXN<<2|1];
void dfs1(int u)
{
    if(u<=0)return;
    dfs1(lson[u]),dfs1(rson[u]);
    if(ty[u])g[u]*=g[lson[u]]*g[rson[u]];
    else
    {
        if(rson[u]<0)g[u]*=g[lson[u]];
        else f[u]*=f[lson[u]]*f[rson[u]],g[u]*=g[lson[u]]*g[rson[u]];
    }
}
void dfs2(int u)
{
    if(u<=0)return;
    if(ty[u])
    {
        if(lson[u])g[lson[u]]=g[u]%g[lson[u]];
        if(rson[u])g[rson[u]]=g[u]%g[rson[u]];
    }
    else
    {
        if(rson[u]<0)g[lson[u]]=g[u]*f[u]%g[lson[u]];
        else
        {
            if(lson[u])g[lson[u]]=g[u]%g[lson[u]];
            if(rson[u])g[rson[u]]=g[u]*f[lson[u]]%g[rson[u]];
        }
    }
    dfs2(lson[u]),dfs2(rson[u]);
}
}
int fa[MAXN];
MINT p[MAXN];
int main()
{
    int q,u=1;
    scanf("%d",&q);
    for(int i=1; i<=q; i++)
    {
        int t,v;
        scanf("%d%d",&t,&v);
        while(t--)u=fa[u];
        stt::e[u].push_back(i+1);
        fa[i+1]=u;
        p[i+1]=p[u]+v;
        u=i+1;
    }
    stt::hld(1);
    int rt=stt::compress(1);
    for(int i=0; i<=stt::cnt; i++)
        stt::f[i]=stt::g[i]=POLY{1};
    for(int i=1; i<=q+1; i++)
        stt::f[stt::idx[i]]=stt::g[stt::idx[i]]=POLY{-p[i],1};
    stt::dfs1(rt);
    stt::g[rt]=POLY{1};
    stt::dfs2(rt);
    for(int i=2; i<=q+1; i++)
        printf("%d\n",stt::g[stt::idx[i]](p[i]).val());
    return 0;
}

